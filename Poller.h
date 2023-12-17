#pragma once

#include <vector>
#include <unordered_map>

#include "Timestamp.h"
#include "noncopyable.h"

class EventLoop;
class Channel;

//Poller抽象类 下面有Epoll Poll Select等具体I/O多路复用类
class Poller : noncopyable {    //解释代码，增强可读性
public: //都可以用
    using ChannelList = std::vector<Channel*>;  //就绪事件通道集合

    Poller(EventLoop* loop);
    virtual ~Poller();

    //监听通道
    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0; //ChannelList是监听到的就绪事件表

    //更新通道
    virtual void updateChannel(Channel* channel) = 0;

    //删除通道
    virtual void removeChannel(Channel* channel) = 0;

    //判断通道是否存在
    virtual bool hasChannel(Channel* channel) const;

    //获取Poller实例
    static Poller* newDefaultPoller(EventLoop* loop);

protected:  //给子类用
    using ChannelMap = std::unordered_map<int, Channel*>;
    ChannelMap channels_;

private:    //给自己用
    EventLoop* loop_;   //事件循环
};
