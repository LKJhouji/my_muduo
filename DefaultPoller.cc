#include "EpollPoller.h"
#include "Poller.h"

Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if (::getenv("MUDUO_USE_POLL") != nullptr) {
        return nullptr;
    }
    else  {
        return new EpollPoller(loop);
    }
}