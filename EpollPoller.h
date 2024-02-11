#pragma once

#include <sys/epoll.h>

#include "Poller.h"
#include "EventLoop.h"
#include "string.h"
#include "Thread.h"


class Channel;

class EpollPoller : public Poller {
public:
    EpollPoller(EventLoop* loop);
    ~EpollPoller() override;
    // 重写父类的函数
    Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
    void updateChannel(Channel* channel) override;
    void removeChannel(Channel* channel) override;
    
private:
    static const int kInitEventListSize = 16;
    using EventList = std::vector<epoll_event>; //自己用，为私有
    void update(int operation, Channel* channel);
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
    int epollfd_;
    EventList events_;
};