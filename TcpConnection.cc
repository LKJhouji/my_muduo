#include "TcpConnection.h"
#include "Log.h"
#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if (loop == nullptr) {
        LOG_FATAL("%s--%s--%d--%d : loop is null\n", __FILE__, __FUNCTION__, __LINE__, errno);      
    }
    return loop;
}

TcpConnection::TcpConnection(EventLoop* loop, const std::string& name, int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr) : loop_(CheckLoopNotNull(loop)), name_(name), state_(kConnecting), socket_(new Socket(sockfd)), channel_(new Channel(loop, sockfd)), localAddr_(localAddr), peerAddr_(peerAddr), highWaterMark_(64 * 1024 * 1024) /*64MB*/{
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));
    LOG_INFO("%s--%s--%d--%d : TcpConnection::ctor[%s] at fd = %d\n", __FILE__, __FUNCTION__, __LINE__, errno, name_.c_str(), sockfd);
    socket_->setKeepAlive(true);

}
TcpConnection::~TcpConnection() {
    LOG_INFO("%s--%s--%d--%d : TcpConnection::dtor[%s] at fd = %d state=%d\n", __FILE__, __FUNCTION__, __LINE__, errno, name_.c_str(), channel_->fd(), static_cast<int>(state_));
}
void TcpConnection::send(const std::string& buf) {
    if (state_ == kConnected) {
        if (loop_->isInLoopThread()) {
            sendInLoop(buf.c_str(), buf.size());
        }
        else {
            loop_->queueInLoop(std::bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size()));
        }
    }
}

void TcpConnection::sendInLoop(const void* message, size_t len) {
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;
    //之前调用过该connection的shutdown, 不能再发送了
    if (state_ == kDisconnected) {
        LOG_ERROR("%s--%s--%d--%d : tcpconnection is disconnected\n", __FILE__, __FUNCTION__, __LINE__, errno);
        return;
    }
    //表示channel第一次发送数据，且缓冲区没有待发送数据。
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0) {
        nwrote = ::write(channel_->fd(), message, len);
        if (nwrote >= 0) {
            remaining = len - nwrote;
            if (remaining == 0 && writeCompleteCallback_) {
                //已经完成发送事件了，不用再给channel设置epollout事件。
                //从这里看出loop负责处理业务
                loop_->runInLoop(std::bind(writeCompleteCallback_, shared_from_this()));    //异步调用对类有保活机制
            }
        }
        else {  //nwrote < 0
            nwrote = 0;
            if (errno != EWOULDBLOCK) { //非阻塞模式下执行阻塞操作导致程序挂起，影响性能
                LOG_ERROR("%s--%s--%d--%d : tcpconnection write error\n", __FILE__, __FUNCTION__, __LINE__, errno);
                if (errno == EPIPE || errno == ECONNRESET) {    
                    //broken pipe 表示网络套接字被断开或关闭
                    //Connection reset by peer 表示网络连接被用户端重置
                    faultError = true;
                }
            }
        }
    }
    //这次write没有将数据完全发送出去，剩余的数据需要保存到缓冲区中，并给channel注册epollout事件， poller发现tcp可读缓冲区有剩余数据未读，会通知channel，调用writecallback。
    if (!faultError && remaining > 0) {
        size_t oldLen = outputBuffer_.readableBytes();  //之前还有部分可读缓冲区的数据没有发送出去
        if (oldLen + remaining >= highWaterMark_ && oldLen < highWaterMark_ && highWaterMarkCallback_) {
            loop_->runInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
        }
        outputBuffer_.append((char*)message + nwrote, remaining);  //将剩余的数据放到outputBuffer中去
        if (!channel_->isWriting()) {
            channel_->enableWriting();  //让poller能够监听到epollout事件
        }
    }
}

//关闭连接
void TcpConnection::shutdown() {
    if (state_ == kConnected) {
        setState(kDisconnecting);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, shared_from_this())); 
    }
}

//连接建立
void TcpConnection::connectionEstablished() {
    setState(kConnected);
    channel_->tie(shared_from_this());
    channel_->enableReading();  //向channel注册epollin事件
    connectionCallback_(shared_from_this());  //新连接建立执行回调
}

//连接销毁
void TcpConnection::connectionDestroyed() {
    if (state_ == kConnected) {
        setState(kDisconnected);
        connectionCallback_(shared_from_this());  //连接断开执行回调
    }
    channel_->remove();  //从poller中移除channel
}    

//读事件处理函数
void TcpConnection::handleRead(Timestamp receivedTime) {
    int savedErrno = 0;
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
    if (n > 0) {
        //已经建立连接的用户，有可读事件发生，调用用户传入的回调函数onMessage
        messageCallback_(shared_from_this(), &inputBuffer_, receivedTime);
    }
    else if (n == 0) {
        handleClose();  //连接已经关闭
    }
    else {
        errno = savedErrno;
        LOG_ERROR("%s--%s--%d--%d : readFd error\n", __FILE__, __FUNCTION__, __LINE__, errno);
        handleError();  //发生错误
    }
}

//写事件处理函数
void TcpConnection::handleWrite() {
    if (channel_->isWriting()) {
        int savedErrno = 0;
        ssize_t n = outputBuffer_.writeFd(channel_->fd(), &savedErrno);
        if (n > 0) {
            outputBuffer_.retrieve(n);  //调位操作，我感觉他的布局有点混乱，整个muduo还是有一些逻辑不够清晰
            if (outputBuffer_.readableBytes() == 0) {
                channel_->disableWriting(); //写完之后，关闭读事件
                if (writeCompleteCallback_) {
                    loop_->runInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
                }
                if (state_ == kDisconnecting) {
                    shutdownInLoop();
                }
            }
        }
        else {
            LOG_ERROR("%s--%s--%d--%d : writeFd error\n", __FILE__, __FUNCTION__, __LINE__, errno);
        }
    }
    else {
        LOG_ERROR("%s--%s--%d--%d : TcpConnection fd = %d is down, no more writing \n", __FILE__, __FUNCTION__, __LINE__, errno, channel_->fd());
    }
}

//错误事件处理函数
void TcpConnection::handleError() {
    int optval;
    socklen_t optlen = sizeof optval;
    int err;
    //可以查看sockfd报错的错误码
    if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0) {
        err = errno;
    }
    else {
        err = optval;
    }
    LOG_ERROR("%s--%s--%d--%d : handleError name:%s - SO_ERROR:%d\n", __FILE__, __FUNCTION__, __LINE__, errno, name_.c_str(), err);
}

//关闭事件处理函数
void TcpConnection::handleClose() {
    LOG_INFO("%s--%s--%d :handleclose fd=%d state=%d \n", __FILE__, __FUNCTION__, __LINE__, channel_->fd(), (int)state_);
    setState(kDisconnected);
    channel_->disableAll();

    TcpConnectionPtr connPtr(shared_from_this());
    connectionCallback_(connPtr);
    closeCallback_(connPtr);
}

void TcpConnection::shutdownInLoop() {
    if (!channel_->isWriting()) {
        socket_->shutdownWrite();
    }
}