#pragma once 

#include <sys/socket.h>
#include <netinet/tcp.h>


#include "noncopyable.h"
#include "InetAddress.h"

class Socket : noncopyable {
public:
    explicit Socket(int sockfd) : sockfd_(sockfd) {} 
    ~Socket();

    int fd() const { return sockfd_; }
    void listen();
    void bind(const InetAddress& localAddr);
    int accept(InetAddress& peerAddr);
    void shutdownWrite();
    void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setKeepAlive(bool on);
private:
    const int sockfd_;
};