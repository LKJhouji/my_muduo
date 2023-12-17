#pragma once 

#include <functional>
#include <memory>
#include <sys/epoll.h>

#include "noncopyable.h"
#include "Timestamp.h"

class EventLoop;    //如果下面只用到EventLoop指针 编译时候能够知道分配空间大小 就可用声明 而不是头文件 这样会减少信息暴露量

//fd通道，注册 更新 删除fd上关注事件，事件发生时进行相应的回调
class Channel : noncopyable {   //noncopyable其实是解释性代码
public:
    //回调函数命名
    using EventCallback = std::function<void()>; 
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    //处理就绪事件，完成对应回调
    void handleEvent(Timestamp receiveTime);

    //设置回调函数 set
    void setReadCallback(ReadEventCallback cb) { 
        readCallback_ = std::move(cb); 
    }   //移动构造 cb失效
    void setWriteCallback(EventCallback cb) {
        writeCallback_ = std::move(cb);
    }
    void setCloseCallback(EventCallback cb) { 
        closeCallback_ = std::move(cb); 
    }
    void setErrorCallback(EventCallback cb) { 
        errorCallback_ = std::move(cb); 
    }

    void tie(const std::shared_ptr<void>&);

    //返回文件描述符 get
    int fd() const { return fd_; }

    //返回监听事件类型 get
    int events() const { return events_; }

    //设置就绪事件 set
    void set_revents(int revt) { revents_ = revt; }
    
    //是否是空事件
    bool isNoneEvent() { return events_ == kNoneEvent; }

    //判断 修改监听事件类型
    void enableReading() {events_ |= kReadEvent; update(); }
    void disableReading() {events_ &= ~kReadEvent; update(); }
    void enableWriting() {events_ |= kWriteEvent; update(); }
    void disableWriting() {events_ &= ~kWriteEvent; update(); }
    void disableAll() {events_ = kNoneEvent; update(); }
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isReading() const { return events_ & kReadEvent; }

    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    //属于哪个事件循环
    EventLoop* ownerLoop() { return loop_; }

    //删除Channel
    void remove();
private:
    //事件
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;   //事件循环
    const int fd_;      //文件描述符
    int events_;         //监听事件类型
    int revents_;       //返回就绪事件类型
    int index_;     //Channel状态

    std::weak_ptr<void> tie_;
    bool tied_;

    //就绪事件回调函数
    ReadEventCallback readCallback_;    
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;

    void update();
    //处理就绪事件
    void handleEventWithGuard(Timestamp receiveTime);
};