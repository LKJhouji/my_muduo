#pragma once

#include <memory>
#include <atomic>

#include "noncopyable.h"
#include "InetAddress.h"
#include "Callbacks.h"
#include "Buffer.h"

class EventLoop;
class Channel;
class Socket;

class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(EventLoop* loop, const std::string& name, int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr);
    ~TcpConnection();
    EventLoop* getLoop() const { return loop_; }
    const std::string& name() const { return name_; }
    const InetAddress& localAddr() const { return localAddr_; }
    const InetAddress& peerAddr() const { return peerAddr_; }
    bool connected() const { return state_ == kConnected; }
    void send(const std::string& buf);  //发送数据
    void shutdown();    //关闭连接
    void setConnectionCallback(const ConnectionCallback& cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback& cb) { messageCallback_ = cb; }
    void setCloseCallback(const CloseCallback& cb) { closeCallback_ = cb; }
    void setHighWaterMarkCallback(const HighWaterMarkCallback& cb) { highWaterMarkCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback& cb) { writeCompleteCallback_ = cb; }
    void connectionEstablished();  //连接建立
    void connectionDestroyed();    //连接销毁

private:
    enum State {kDisconnected, kConnecting, kConnected, kDisconnecting};
    void setState(State s) { state_ = s; }
    void handleRead(Timestamp receivedTime);  //读事件处理函数
    void handleWrite();  //写事件处理函数
    void handleError();  //错误事件处理函数
    void handleClose();  //关闭事件处理函数
    void sendInLoop(const void* message, size_t len);
    void shutdownInLoop();
    EventLoop* loop_;   //肯定不是mainloop,是给subloop的
    const std::string name_;
    const InetAddress localAddr_;
    const InetAddress peerAddr_;
    std::atomic_int state_;
    ConnectionCallback connectionCallback_; //有新连接时的回调
    MessageCallback messageCallback_;   //有读写消息时的回调
    CloseCallback closeCallback_;   //消息发送完成以后的回调
    HighWaterMarkCallback highWaterMarkCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    //和Acceptor相似, Acceptor => mainloop, TcpConnection => subloop
    std::unique_ptr<Channel> channel_;
    std::unique_ptr<Socket> socket_;
    size_t highWaterMark_;  //写缓冲区水位
    Buffer inputBuffer_;  //发送数据缓存区
    Buffer outputBuffer_;  //接收数据缓存区
};