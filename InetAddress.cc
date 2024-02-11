#include "InetAddress.h"
#include "Log.h"

std::string InetAddress::toIpPort() const {
    return toIp() + " : " + std::to_string(toPort());
}

std::string InetAddress::toIp() const {
    char buf[64] = {0};
    if (::inet_ntop(addr_.sin_family, &addr_.sin_addr, buf, sizeof buf) == nullptr) {
        LOG_ERROR("%s--%s--%d--%d : inet_ntop error\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
    return buf;
}

InetAddress::InetAddress(uint16_t port, const char* ip) {
    bzero(&addr_, sizeof addr_);
    addr_.sin_family = AF_INET;
    if (::inet_pton(addr_.sin_family, ip, &addr_.sin_addr) != 1) {
        LOG_FATAL("%s--%s--%d--%d : inet_pton error\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
    addr_.sin_port = htons(port);
}

void InetAddress::setSockAddr(uint16_t port, const char* ip) {
    bzero(&addr_, sizeof addr_);
    addr_.sin_family = AF_INET;
    if (::inet_pton(addr_.sin_family, ip, &addr_.sin_addr) != 1) {
        LOG_FATAL("%s--%s--%d--%d : inet_pton error\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
    addr_.sin_port = htons(port);
}


// int main () {
//     InetAddress ia;
//     std::cout << ia.toIpPort() << std::endl;
//     ia.setSockAddr(8080, "191.255.255.255");
//     std::cout << ia.toIpPort() << std::endl;
//     return 0;
// }