#include "Log.h"

Log& Log::getInstance() {
    static Log log;
    return log;
}


// [] : time, msg
void Log::writeLog(const char* s) {
    std::string ss;
    switch (logLevel_)
    {
    case INFO:
        ss += "[INFO] : ";
        break;
    case DEBUG:
        ss += "[DEBUG] : ";
        break;
    case ERROR:
        ss += "[ERROR] : ";
        break;
    case FATAL:
        ss += "[FATAL] : ";
        break;
    case WARN:
        ss += "[WARN] : ";
        break;
    default:
        break;
    }
    std::cout << ss << Timestamp::now().toString() << ", " << s << std::endl;
}

// int main() {
//     LOG_INFO("%s, %s, %d : main error\n", __FILE__, __FUNCTION__, __LINE__);
//     return 0;
// }