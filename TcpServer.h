#pragma once
#include <functional>
#include <unordered_map>
#include "noncopyable.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Callbacks.h"
#include "Log.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "TcpConnection.h"
class TcpServer : noncopyable {
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
    enum Option {
        kNoReusePort,
        kReusePort,
    };
    TcpServer(EventLoop* loop, const InetAddress& listenAddr, const std::string& name, Option option = kNoReusePort);
    ~TcpServer();
    void setThreadInitCallback(const ThreadInitCallback& cb) {
        threadInitCallback_ = cb;
    }
    void setConnectionCallback(const ConnectionCallback& cb) {
        connectionCallback_ = cb;
    }
    void setMessageCallback(const MessageCallback& cb) {
        messageCallback_ = cb;
    }
    void setWriteCompleteCallback(const WriteCompleteCallback& cb) {
        writeCompleteCallback_ = cb;
    }
    void setThreadNum(int numThreads);
    void start();   //服务器开始监听

private:
    void newConnection(int sockfd, const InetAddress& peerAddr);
    void removeConnection(const TcpConnectionPtr& conn);
    void removeConnectionInLoop(const TcpConnectionPtr& conn);
    ThreadInitCallback threadInitCallback_; //loop线程初始化的回调
    ConnectionCallback connectionCallback_; //有新连接时的回调
    MessageCallback messageCallback_;   //有读写信息时的回调
    WriteCompleteCallback writeCompleteCallback_;   //消息发送完成以后的回调
    EventLoop* loop_;
    const std::string ipPort_;  
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;
    std::atomic_int started_;
    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;
    ConnectionMap connections_;
    int nextConnId_;
};