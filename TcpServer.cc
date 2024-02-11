#include "TcpServer.h"

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if (loop == nullptr) {
        LOG_FATAL("%s--%s--%d--%d : loop is null\n", __FILE__, __FUNCTION__, __LINE__, errno);      
    }
    return loop;
}

TcpServer::TcpServer(EventLoop* loop, 
                const InetAddress& listenAddr, 
                const std::string& name, 
                Option option) 
                : loop_(CheckLoopNotNull(loop))
                , ipPort_(listenAddr.toIpPort())
                , name_(name)
                , acceptor_(new Acceptor(loop, listenAddr, option == kReusePort))
                , threadPool_(new EventLoopThreadPool(loop, name))
                , connectionCallback_()
                , messageCallback_()
                , started_(0) 
                , nextConnId_(1)
                {
                    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
                }

TcpServer::~TcpServer() { 
    for (auto& item : connections_) {
        TcpConnectionPtr conn(item.second); //新建shared_ptr指向相同内存地址，引用计数+1
        item.second.reset();    //置空
        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectionDestroyed, conn));
    }
}

//设置底层subloop的个数
void TcpServer::setThreadNum(int numThreads) {
    threadPool_->setThreadNum(numThreads);
}

//开始监听 loop.loop()
void TcpServer::start() {
    //防止一个TcpServer被start多次
    if (started_++ == 0) {
        threadPool_->start(threadInitCallback_);
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}

//新连接回调，得创建对应的subloop，所以在TcpServer中定义这个函数比较合适
void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr) {
    EventLoop* ioLoop = threadPool_->getNextLoop(); //轮询，从线程池中取出一个subloop
    LOG_INFO("%s--%s--%d : TcpServer has totally %d TcpConnection\n", __FILE__, __FUNCTION__, __LINE__, nextConnId_);
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;
    LOG_INFO("%s--%s--%d : TcpServer::newConnection [%s] - new connection [%s] from %s\n", __FILE__, __FUNCTION__, __LINE__, name_.c_str(), connName.c_str(), peerAddr.toIpPort().c_str());

    //通过sockfd获取其绑定的本机的ip地址和端口信息
    sockaddr_in local;
    ::bzero(&local, sizeof local);
    socklen_t addrlen = sizeof(local);
    if (::getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0) {   //getsockname可以将sockfd获取的绑定的本地ip地址和端口信息放在local中,获得的即127.0.0.1：8000
        LOG_ERROR("%s--%s--%d--%d : TcpServer::newConnection getsockname error", __FILE__, __FUNCTION__, __LINE__, errno);
    }
    InetAddress localAddr(local);   //将获取到的本地地址和端口号存放到InetAddress对应的类中

    //针对连接成功的sockfd，建立对应的TcpConnection连接
    TcpConnectionPtr conn(new TcpConnection(ioLoop, connName, sockfd, localAddr, peerAddr));
    connections_[connName] = conn;
    conn->setConnectionCallback(connectionCallback_);   //在EchoServer中确认好，此时只是回调
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));
    ioLoop->runInLoop(std::bind(&TcpConnection::connectionEstablished, conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn) {
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn) {
    LOG_INFO("%s--%s--%d : TcpServer::removeConnectionInLoop [%s] - connection %s\n", __FILE__, __FUNCTION__, __LINE__, name_.c_str(), conn->name().c_str());
    connections_.erase(conn->name());
    EventLoop* ioLoop = conn->getLoop();
    ioLoop->runInLoop(std::bind(&TcpConnection::connectionDestroyed, conn));
}
