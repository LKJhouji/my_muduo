#include "InetAddress.h"


InetAddress::InetAddress(uint16_t port, std::string ip) {
    bzero(&addr_, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_.sin_port = htons(port);
}

std::string InetAddress::toIp() const {
    char buf[64] = {0};
    inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);   //第二个参数是sin_addr
    return buf;
}

std::string InetAddress::toIpPort() const {
    char buf[64] = {0};
    inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);   
    size_t len = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf + len, ":%u", port);
    return buf;
}

uint16_t InetAddress::port() const {
    return ntohs(addr_.sin_port);
}

// int main() {
//     InetAddress inetaddress(8080);
//     std::cout << inetaddress.toIpPort() << std::endl;
//     return 0;
// }