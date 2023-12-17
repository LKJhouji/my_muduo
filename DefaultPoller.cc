#include "Poller.h"
#include "EpollPoller.h"    //最好不要放Poller.h中，确保功能分离，上层不能调用下层


Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if (getenv("MUDUO_USE_POLL"))
        return nullptr;
    else 
        return new EpollPoller(loop);
}