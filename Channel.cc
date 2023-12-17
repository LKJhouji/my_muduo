#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop* loop, int fd) 
    : loop_(loop), 
      fd_(fd), 
      events_(0), 
      revents_(0), 
      index_(-1), 
      tied_(false) {

}

Channel::~Channel() {

}

//处理就绪事件，完成对应回调
void Channel::handleEvent(Timestamp receiveTime) {
    std::shared_ptr<void> guard;
  if (tied_)
  {
    //升级为共享指针
    guard = tie_.lock();
    if (guard)
    {
      handleEventWithGuard(receiveTime);
    }
  }
  else
  {
    handleEventWithGuard(receiveTime);
  }
}


void Channel::tie(const std::shared_ptr<void>& obj) {
    tie_ = obj;
    tied_ = true;
}


void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::remove() {
    loop_->removeChannel(this);
}
    
void Channel::handleEventWithGuard(Timestamp receiveTime) {
    //关闭
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        if (closeCallback_) {
            closeCallback_();
        }
    }
    if (revents_ & EPOLLERR) {
        if (errorCallback_) {
            errorCallback_();
        }
    }
    //可读 紧急 重置
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
        if (readCallback_) {
            readCallback_(receiveTime);
        }
    }
    if (revents_ & EPOLLOUT) {
        if (writeCallback_) {
            writeCallback_();
        }
    }
}

