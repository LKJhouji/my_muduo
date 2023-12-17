#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <sys/eventfd.h>

#include "noncopyable.h"
#include "Timestamp.h"
#include "CurrentThread.h"
#include "Log.h"
#include "Locker.h"

class Channel;
class Poller;

class EventLoop : noncopyable {
public:
    using Functor = std::function<void()>;
    EventLoop();
    ~EventLoop();

    void loop();

    void quit();

    //数据到达的当前时间
    Timestamp pollReturnTime() const { return pollReturnTime_; }

    //迭代
    int64_t iteration() const { return iteration_; }


    void runInLoop(Functor cb);

    void queueInLoop(Functor cb);
    size_t queueSize() const;

    void wakeup();
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    bool hasChannel(Channel* channel) const;

    //当前线程执行的该事件循环
    bool isInLoopThread() const { return threadId_ == tid(); }  
    bool eventHandling() const { return eventHandling_; }

    static EventLoop* getEventLoopOfCurrentThread();
protected:

private:
    void handleRead();  // waked up
    void doPendingFunctors();
    
    using ChannelList = std::vector<Channel*>;

    std::atomic_bool looping_;
    std::atomic_bool quit_;
    std::atomic_bool eventHandling_;
    std::atomic_bool callingPendingFunctors_;   //有需要执行的回调操作
    std::vector<Functor> pendingFunctors_;  //回调操作集合

    //Locker locker_; C语言
    mutable std::mutex mutex_;  // C++

    Timestamp pollReturnTime_;
    int64_t iteration_;
    const pid_t threadId_;
    std::unique_ptr<Poller> poller_;    //Poller 
    
    int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannel_;

    ChannelList activeChannels_;
    Channel* currentActiveChannel_;   
};