#pragma once

#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <strings.h>
#include <iostream>
//#include <netinet/in.h>

#include "copyable.h"


//封装ip地址与端口号
class InetAddress : copyable {
public:
    InetAddress(uint16_t port, std::string ip = "127.0.0.1");     //初始化ip，port
    InetAddress(const struct sockaddr_in& addr) {   
        addr_ = addr;
    };
    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t port() const;

private:
    struct sockaddr_in addr_;
};