#pragma once

#include <functional>
#include <atomic>
#include <memory>
#include <semaphore.h>
#include <vector>
#include <mutex>

#include "Timestamp.h"
#include "noncopyable.h"
#include "Thread.h"

class Poller;
class Channel;

class EventLoop : noncopyable {
public:
    using Functor = std::function<void()>;  
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    void runInLoop(Functor cb);
    void queueInLoop(Functor cb);
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    Timestamp getPollReturnTime() const { return pollReturnTime_; }
    void wakeup();
    bool hasChannel(Channel* channel);
    const pid_t threadId() const { return threadId_; }
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
private:
    void handleRead();
    void doPendingFunctors();
    using ChannelList = std::vector<Channel*>;
    const pid_t threadId_;
    std::unique_ptr<Poller> poller_;
    Timestamp pollReturnTime_;
    std::atomic_bool looping_;
    std::atomic_bool quit_;
    int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannel_;
    ChannelList activeChannels_;
    std::mutex mutex_;
    std::atomic_bool callingPendingFunctors_;
    std::vector<Functor> pendingFunctors_;
};