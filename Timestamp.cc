#include "Timestamp.h"

Timestamp Timestamp::now() {
    return Timestamp(time(nullptr));
}
std::string Timestamp::toString() const {
    char buf[128] = {0};
    tm* my_tm = localtime(&microSecond_);
    snprintf(buf, sizeof buf, "%d/%d/%d %d:%d:%d", my_tm->tm_year + 1900, my_tm->tm_mon + 1, my_tm->tm_mday, my_tm->tm_hour, my_tm->tm_min, my_tm->tm_sec);    
    return buf;
}

// int main() {
//     Timestamp ts = Timestamp::now();
//     std::cout << ts.toString() << std::endl;
//     return 0;
// }