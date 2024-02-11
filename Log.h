#pragma once 

#include <string>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <condition_variable>

#include "noncopyable.h"
#include "Timestamp.h"
enum LogLevel {
    INFO,
    ERROR,
    WARN,
    FATAL,
    DEBUG,
};

static std::mutex f_mutex;

#define MAXLEN 256
#define LOG_INFO(logmsgformat, ...)                             \
    do {                                                        \
        Log& lp = Log::getInstance();                           \
        lp.setLogLevel(INFO);                                   \
        char buf[MAXLEN] = {0};                                 \
        snprintf(buf, sizeof buf, logmsgformat, ##__VA_ARGS__); \
        std::unique_lock<std::mutex> lock_(f_mutex);            \
        lp.writeLog(buf);                                       \
    } while (0)

#define LOG_DEBUG(logmsgformat, ...)                            \
    do {                                                        \
        Log& lp = Log::getInstance();                           \
        lp.setLogLevel(DEBUG);                                  \
        char buf[MAXLEN] = {0};                                 \
        snprintf(buf, sizeof buf, logmsgformat, ##__VA_ARGS__); \
        std::unique_lock<std::mutex> lock_(f_mutex);            \
        lp.writeLog(buf);                                       \
    } while (0)

#define LOG_WARN(logmsgformat, ...)                             \
    do {                                                        \
        Log& lp = Log::getInstance();                           \
        lp.setLogLevel(WARN);                                   \
        char buf[MAXLEN] = {0};                                 \
        snprintf(buf, sizeof buf, logmsgformat, ##__VA_ARGS__); \
        std::unique_lock<std::mutex> lock_(f_mutex);            \
        lp.writeLog(buf);                                       \
    } while (0)

#define LOG_ERROR(logmsgformat, ...)                            \
    do {                                                        \
        Log& lp = Log::getInstance();                           \
        lp.setLogLevel(ERROR);                                  \
        char buf[MAXLEN] = {0};                                 \
        snprintf(buf, sizeof buf, logmsgformat, ##__VA_ARGS__); \
        std::unique_lock<std::mutex> lock_(f_mutex);            \
        lp.writeLog(buf);                                       \
    } while (0)

#define LOG_FATAL(logmsgformat, ...)                            \
    do {                                                        \
        Log& lp = Log::getInstance();                           \
        lp.setLogLevel(FATAL);                                  \
        char buf[MAXLEN] = {0};                                 \
        snprintf(buf, sizeof buf, logmsgformat, ##__VA_ARGS__); \
        std::unique_lock<std::mutex> lock_(f_mutex);            \
        lp.writeLog(buf);                                       \
        exit(-1);                                               \
    } while (0)

class Log : noncopyable {
public:
    
    static Log& getInstance(); 
    void writeLog(const char* s);
    void setLogLevel(LogLevel logLevel) {
        logLevel_ = logLevel;
    }
private:
    //Log() {};
    LogLevel logLevel_;
};