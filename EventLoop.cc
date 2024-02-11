#include <sys/eventfd.h>
#include <mutex>
#include "EventLoop.h"
#include "Poller.h"
#include "Log.h"
#include "Channel.h"


__thread EventLoop* t_loopInThisThread = nullptr; //线程中对应的EventLoop

const int kPollTimeMs = 30000; //poller的等待时间

int createEventFd() {
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0) {
        LOG_FATAL("%s--%s--%d--%d : eventfd error\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
    return evtfd;
}

EventLoop::EventLoop() : threadId_(CurrentThread::tid()), poller_(Poller::newDefaultPoller(this)), looping_(false), quit_(false), callingPendingFunctors_(false), wakeupFd_(createEventFd()), wakeupChannel_(new Channel(this, wakeupFd_)) {
    LOG_INFO("%s--%s--%d : EventLoop created %p in thread %d\n", __FILE__, __FUNCTION__, __LINE__, this, threadId_);
    if (t_loopInThisThread) {
        LOG_FATAL("%s--%s--%d--%d : Another EventLoop %p exists in this thread %d\n", __FILE__, __FUNCTION__, __LINE__, errno, this, threadId_);
    }
    else t_loopInThisThread = this;
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
    wakeupChannel_->enableReading();
}

EventLoop::~EventLoop() {
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    ::close(wakeupFd_);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop() {
    looping_ = true;
    quit_ = false;
    LOG_INFO("%s--%s--%d : EventLoop %p start looping\n", __FILE__, __FUNCTION__, __LINE__, this);
    while (!quit_) {
        activeChannels_.clear();
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
        for (Channel* channel : activeChannels_) {
            channel->handleEvent(pollReturnTime_);
        }
        doPendingFunctors();
    }
    LOG_INFO("%s--%s--%d : EventLoop %p stop looping\n", __FILE__, __FUNCTION__, __LINE__, this);
    looping_ = false;
}

void EventLoop::quit() {
    quit_ = true;
    
    if (!isInLoopThread()) {
        wakeup();
    }
}

void EventLoop::runInLoop(Functor cb) {
    if (isInLoopThread()) {
        cb();
    }
    else {
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(Functor cb) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        pendingFunctors_.push_back(cb);
    }
    if (!isInLoopThread() || callingPendingFunctors_) {
        wakeup();
    }
}

void EventLoop::updateChannel(Channel* channel) {
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel) {
    poller_->removeChannel(channel);
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = ::write(wakeupFd_, &one, sizeof one);
    if (n != sizeof one) {
        LOG_ERROR("%s--%s--%d--%d : write error\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
}

bool EventLoop::hasChannel(Channel* channel) {
    return poller_->hasChannel(channel);
}

void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = ::read(wakeupFd_, &one, sizeof one);
    if (n != sizeof one) {
        LOG_ERROR("%s--%s--%d--%d : read error\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
}
void EventLoop::doPendingFunctors() {
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_);
    }

    for (const Functor &functor : functors)
    {
        functor(); // 执行当前loop需要执行的回调操作
    }
    
    if (functors.empty()) {
        LOG_INFO("%s--%s--%d : no PendingFunctors in thread %d\n", __FILE__, __FUNCTION__, __LINE__, CurrentThread::tid());
        return;
    }
    callingPendingFunctors_ = false;

    LOG_INFO("%s--%s--%d : doPendingFunctors succeed in thread %d\n", __FILE__, __FUNCTION__, __LINE__, CurrentThread::tid());
}