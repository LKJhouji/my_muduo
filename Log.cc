#include "Log.h"

//获取日志对象
Log& Log::getInstance() {
    static Log log;
    return log;
}

//写日志 [日志级别] time : msg
void Log::writeLog(std::string& msg) {
    switch (level_)
    {
    case INFO:
        std::cout << "[INFO] ";
        break;
    case DEBUG:
        std::cout << "[DEBUG] ";
        break;
    case WARN:
        std::cout << "[WARN] ";
        break;
    case ERROR:
        std::cout << "[ERROR] ";
        break;
    default:
        break;
    }
    std::cout << "time : " << msg << std::endl;
}

//设置日志级别
void Log::setLogLevel(int level) {
    level_ = level;
}