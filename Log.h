#pragma once

#include <iostream>
//#include <string>
//系统头文件和自定义头文件中间应该空行
#include "noncopyable.h"

//日志级别 INFO WARN DEBUG ERROR
enum {
    INFO,
    WARN,
    DEBUG,
    ERROR,
};

//宏
#define MUDEBUG
//体验感设计 LOG_INFO("%s, %d", arg1, arg2)
#define LOG_INFO(logmsgformat, ...)                         \
    do {                                                    \
        Log& log = Log::getInstance();                      \
        log.setLogLevel(INFO);                              \
        char buf[1024] = {0};                               \
        snprintf(buf, 1024, logmsgformat, ##__VA_ARGS__);   \
    } while (0)

#define LOG_WARN(logmsgformat, ...)                         \
    do {                                                    \
        Log& log = Log::getInstance();                      \
        log.setLogLevel(WARN);                              \
        char buf[1024] = {0};                               \
        snprintf(buf, 1024, logmsgformat, ##__VA_ARGS__);   \
    } while (0)

#define LOG_ERROR(logmsgformat, ...)                        \
    do {                                                    \
        Log& log = Log::getInstance();                      \
        log.setLogLevel(ERROR);                             \
        char buf[1024] = {0};                               \
        snprintf(buf, 1024, logmsgformat, ##__VA_ARGS__);   \
    } while (0)

#define LOG_FATAL(logmsgformat, ...)                        \
    do {                                                    \
        Log& log = Log::getInstance();                      \
        log.setLogLevel(ERROR);                             \
        char buf[1024] = {0};                               \
        snprintf(buf, 1024, logmsgformat, ##__VA_ARGS__);   \
        exit(-1);                                           \
    } while (0)

#ifdef MUDEBUG
#define LOG_DEBUG(logmsgformat, ...)                        \
    do {                                                    \
        Log& log = Log::getInstance();                      \
        log.setLogLevel(DEBUG);                             \
        char buf[1024] = {0};                               \
        snprintf(buf, 1024, logmsgformat, ##__VA_ARGS__);   \
    } while (0)
#else
#define LOG_DEBUG(logmsgformat, ...)
#endif

//日志
class Log : noncopyable {
public:
    //获取日志对象
    static Log& getInstance();
    //写日志
    void writeLog(std::string& s);
    //设置日志级别
    void setLogLevel(int level);
private:
    Log() {}
    int level_; //区分系统变量，放后
};