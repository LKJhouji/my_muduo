#pragma once

#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>

#include "Timestamp.h"
#include "Poller.h"

class EpollPoller : public Poller {
public:
    EpollPoller(EventLoop* loop);
    ~EpollPoller();

    //监听通道 超时时间 监听通道列表
    Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
    //更新通道
    void updateChannel(Channel* channel) override;
    //去除通道
    void removeChannel(Channel* channel) override;
private:
    //内部实现public中函数的private函数
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
    void update(int operation, Channel* channel);

    int epollfd_;   //epoll文件描述符

    using EventList = std::vector<struct epoll_event>;  //事件集合
    EventList events_;
    static const int kInitEventListSize = 16;   //集合默认长度
};