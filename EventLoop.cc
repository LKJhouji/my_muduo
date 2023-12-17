
#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"

//线程局部变量
__thread EventLoop* t_loopInThisThread = nullptr;

//I/O复用超时时间 10 s
const int kPollTimeMs = 10000;

int createEventfd() {
  int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evtfd < 0) {
    LOG_FATAL("func %s => eventfd error\n", __FUNCTION__);
  }
  return evtfd;
}

EventLoop* EventLoop::getEventLoopOfCurrentThread() {
  return t_loopInThisThread;
}

EventLoop::EventLoop() 
  : looping_(false),
    quit_(false),
    eventHandling_(false),
    callingPendingFunctors_(false),
    iteration_(0),
    threadId_(tid()),
    poller_(Poller::newDefaultPoller(this)),
    wakeupFd_(0),
    wakeupChannel_(new Channel(this, wakeupFd_)),
    currentActiveChannel_(nullptr) {
  LOG_INFO("EventLoop created %p in thread %d\n", this, threadId_);
  if (t_loopInThisThread) {
    LOG_FATAL("Another EventLoop %p exists in \
                this thread %d\n", t_loopInThisThread, threadId_);
  }
  else {
    t_loopInThisThread = this;
  }
  //给wakeup通道设置感兴趣事件和回调函数
  wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
  wakeupChannel_->enableReading();
}

EventLoop::~EventLoop() {
  LOG_INFO("EventLoop %p of thread %d destructs in \
            thread %d", t_loopInThisThread, threadId_, tid());
  wakeupChannel_->disableAll();
  wakeupChannel_->remove();  // 等价 removeChannel(wakeupChannel_);
  ::close(wakeupFd_);
  t_loopInThisThread = nullptr;
}

//事件循环开始
void EventLoop::loop() {
  looping_ = true;
  quit_ = false;
  LOG_INFO("Eventloop %p starts looping\n", this);

  while (!quit_) {
    //循环监听
    activeChannels_.clear();
    pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);

    //处理事件
    eventHandling_ = true;
    for (Channel* channel : activeChannels_) {
      currentActiveChannel_ = channel;
      currentActiveChannel_->handleEvent(pollReturnTime_);
    }
    currentActiveChannel_ = nullptr;
    eventHandling_ = false;
    doPendingFunctors();
  }

  LOG_INFO("Eventloop %p stop looping\n", this);
  looping_ = false;
}

//事件循环结束
void EventLoop::quit() {
  quit_ = true;

  if (!isInLoopThread()) {  // 当前线程不是该事件循环所处线程，得先激活才能执行退出
    wakeup();
  }
}

//线程为事件所处线程就执行回调函数 否则放入等待集合中
void EventLoop::runInLoop(Functor cb) {
  if (isInLoopThread()) {
    cb();
  }
  else {
    queueInLoop(std::move(cb));
  }
}

void EventLoop::queueInLoop(Functor cb) {
  {
    std::unique_lock<std::mutex> lk(mutex_);
    pendingFunctors_.push_back(std::move(cb));  //防止cb内存泄漏
  }
  if (!isInLoopThread() || callingPendingFunctors_) {
    wakeup();
  }
}

size_t EventLoop::queueSize() const {
  
  std::unique_lock<std::mutex> lk(mutex_);  //不给mutex_加mutable属性 const会报错
  return pendingFunctors_.size();
}

//wakup通道读，便于激活线程
void EventLoop::handleRead() {
  uint64_t one = 1;
  ssize_t n = read(wakeupFd_, &one, sizeof one);
  if (n != sizeof one) {
    LOG_ERROR("func %s => reads %ld bytes instead of 8", __FUNCTION__, n);
  }
}

void EventLoop::updateChannel(Channel* channel) {
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel) {
    poller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel* channel) const {
    return poller_->hasChannel(channel);
}

void EventLoop::wakeup() {
  uint64_t one = 1;
  ssize_t n = write(wakeupFd_, &one, sizeof one);
  if (n != sizeof one) {
    LOG_ERROR("func %s => writes %ld bytes instead of 8", __FUNCTION__, n);
  }
}

void EventLoop::doPendingFunctors() {
  std::vector<Functor> functors;
  callingPendingFunctors_ = true;

  {
    //原子操作 防止其他线程增加pendingFunctors clear时漏掉待处理回调
    std::unique_lock<std::mutex> lk(mutex_);
    functors.swap(pendingFunctors_);  
  }

  for (const Functor& functor : functors) {
    functor();
  }
  callingPendingFunctors_ = false;
}

