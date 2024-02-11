#include "EpollPoller.h"
#include "Log.h"

//实现channel与epoll_event一一映射

enum status {
    kNew, //channel 未添加到 Poller 中
    kAdded,     //channel 已添加到 Poller 中
    kDeleted,    //channel 从 Poller 中删除
};

EpollPoller::EpollPoller(EventLoop* loop) : Poller(loop), epollfd_(::epoll_create1(EPOLL_CLOEXEC)), events_(kInitEventListSize) {
    if (epollfd_ < 0) {
        LOG_FATAL("%s--%s--%d--%d : epoll_create error\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
}

EpollPoller::~EpollPoller() {
    ::close(epollfd_);
}

Timestamp EpollPoller::poll(int timeoutMs, ChannelList* activeChannels) {   //设置channel感兴趣的事件
    /* Wait for events on an epoll instance "epfd". Returns the number of
   triggered events returned in "events" buffer. Or -1 in case of
   error with the "errno" variable set to the specific error code. The
   "events" parameter is a buffer that will contain triggered
   events. The "maxevents" is the maximum number of events to be
   returned ( usually size of "events" ). The "timeout" parameter
   specifies the maximum wait time in milliseconds (-1 == infinite).

   This function is a cancellation point and therefore not marked with
   __THROW.  */
    int numEvent = ::epoll_wait(epollfd_, &*events_.begin(), events_.size(), timeoutMs);
    Timestamp now = Timestamp::now();
    int saveErrno = errno;
    if (numEvent < 0) {
        if (saveErrno != EINTR) { //中断
            errno = saveErrno;
            LOG_FATAL("%s--%s--%d--%d : epoll_wait error in thread %d\n", __FILE__, __FUNCTION__, __LINE__, errno, loop_->threadId());
        }
    }
    else if (numEvent == 0) {
        LOG_INFO("%s--%s--%d : no events happend in thread %d\n", __FILE__, __FUNCTION__, __LINE__, loop_->threadId());
    }
    else {
        LOG_INFO("%s--%s--%d : epoll_wait %d events happened in thread %d\n", __FILE__, __FUNCTION__, __LINE__, numEvent, loop_->threadId());
        fillActiveChannels(numEvent, activeChannels);
        if (numEvent >= events_.size()) {
            events_.resize(numEvent * 2);
        }
    }
    return now;
}

void EpollPoller::updateChannel(Channel* channel) { //通过改变channel来改变对应的epoll_event
    int status = channel->status();
    if (status == kNew || status == kDeleted) {
        if (status == kNew) {
            int fd = channel->fd();
            channels_[fd] = channel;
        }
        channel->set_status(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else {  //channel已注册到Poller上了
        int fd = channel->fd();
        if (channel->isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
            channel->set_status(kDeleted);  //只是不监听了
        }
        else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EpollPoller::removeChannel(Channel* channel) {
    int fd = channel->fd();
    channels_.erase(fd);
    int status = channel->status();
    if (status == kAdded) {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_status(kNew);
}

void EpollPoller::update(int operation, Channel* channel) { //epoll_ctl，对指定的channel进行修改
    epoll_event event;
    memset(&event, 0, sizeof event);
    event.events = channel->events();
    event.data.fd = channel->fd();
    event.data.ptr = channel;
    if (::epoll_ctl(epollfd_, operation, channel->fd(), &event) == -1) {
        if (operation == EPOLL_CTL_DEL) {
            LOG_ERROR("%s--%s--%d--%d : epoll_ctl error\n", __FILE__, __FUNCTION__, __LINE__, errno);
        }
        else {
            LOG_FATAL("%s--%s--%d--%d : epoll_ctl error\n", __FILE__, __FUNCTION__, __LINE__, errno);
        }
    }
}

void EpollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const {
    for (int i = 0; i < numEvents; i++) {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);    //channel和event之间建立了连接
        activeChannels->push_back(channel);
    }
}