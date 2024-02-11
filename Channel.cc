#include "Channel.h"
#include "EventLoop.h"
#include "Log.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI; //后者表示紧急或周期性事件发生
const int Channel::kWriteEvent = EPOLLOUT;
void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::remove() {
    loop_->removeChannel(this);
}

void Channel::handleEventWithGuard(Timestamp receiveTime) {
    LOG_INFO("%s--%s--%d : channel handle revents : %d in thread %d\n", __FILE__, __FUNCTION__, __LINE__, revents_, loop_->threadId());
    //EPOLLHUP挂断
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        if (closeCallback_) closeCallback_();
    }
    else if (revents_ & EPOLLERR) {
        if (errorCallback_) errorCallback_();
    }
    else if (revents_ & EPOLLIN) {
        if (readCallback_) readCallback_(receiveTime);
    }

    else if (revents_ & EPOLLOUT) {
        if (writeCallback_) writeCallback_();
    }
}

void Channel::handleEvent(Timestamp receiveTime) {
    if (tied_) {
        if (tie_) {
            handleEventWithGuard(receiveTime);
        }
    }
    else {
        handleEventWithGuard(receiveTime);
    }
}

void Channel::tie(const std::shared_ptr<void>& obj)  {
    tie_ = obj;
    tied_ = true;
}