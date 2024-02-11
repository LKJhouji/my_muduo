#pragma once

#include <functional>
#include <sys/epoll.h>
#include <memory>

#include "noncopyable.h"
#include "Timestamp.h"

class EventLoop;  


class Channel : noncopyable {
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;
    Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd), events_(0), status_(0), tied_(false) {}
    ~Channel() = default;

    int fd() const { return fd_; }
    EventLoop* loop() const { return loop_; }
    int status() const { return status_; }
    int events() const { return events_; }
    bool isReading() const { return events_ & kReadEvent; }
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isNoneEvent() const { return events_ == kNoneEvent; }
    void enableReading() { events_ |= kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() { events_ = kNoneEvent; update(); }
    void setReadCallback(const ReadEventCallback& cb) { readCallback_ = cb; }
    void setWriteCallback(const EventCallback& cb) { writeCallback_ = cb; }
    void setErrorCallback(const EventCallback& cb) { errorCallback_ = cb; }
    void setCloseCallback(const EventCallback& cb) { closeCallback_ = cb; }
    void remove();
    void set_revents(int revents) { revents_ = revents; }
    void set_status(int status) { status_ = status; }
    void handleEvent(Timestamp receiveTime);
    void tie(const std::shared_ptr<void>& obj);
private:
    void handleEventWithGuard(Timestamp receiveTime);
    void update();
    EventLoop* loop_;
    int fd_;
    int events_;
    int revents_;
    int status_;
    std::shared_ptr<void> tie_; // 绑定到TcpConnection
    bool tied_;
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
    ReadEventCallback readCallback_;
};