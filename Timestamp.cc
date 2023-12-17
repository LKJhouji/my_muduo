#include "Timestamp.h"

//返回当前时间对象
Timestamp Timestamp::now() {
    return Timestamp(time(NULL));   //返回的当前时间对象成员microSecondsSinceEpoch_为当前时间
    //time() => /* Return the current time and put it in *TIMER if TIMER is not NULL.  */
}   
//转换成msg字符串
std::string Timestamp::toString() const {
    char buf[1024] = {0};
    tm* tm_time = localtime(&microSecondsSinceEpoch_);  //可查看tm
    snprintf(buf, 1024, "%4d/%02d/%02d %02d:%02d:%02d", 
            tm_time->tm_year + 1900,
            tm_time->tm_mon + 1,
            tm_time->tm_mday,
            tm_time->tm_hour,
            tm_time->tm_min,
            tm_time->tm_sec
    );
    return buf;
}

// int main() {
//     std::cout << Timestamp::now().toString() << std::endl;
//     return 0;
// }