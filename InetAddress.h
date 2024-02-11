#pragma once

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

#include "copyable.h"

 
class InetAddress : copyable {
public:
    InetAddress(uint16_t port = 8000, const char* ip = "127.0.0.1");
    InetAddress(sockaddr_in addr) {
        addr_ = addr;
    }

    uint16_t toPort() const {
        return ntohs(addr_.sin_port);
    }

    std::string toIp() const;

    std::string toIpPort() const;

    const sa_family_t family() const {
        return addr_.sin_family;
    }

    const sockaddr_in* getSockAddr() const { return &addr_; }
    void setSockAddr(sockaddr_in addr) { addr_ = addr; }
    void setSockAddr(uint16_t port, const char* ip);
private:
    sockaddr_in addr_;
};