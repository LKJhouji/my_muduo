#pragma once 

#include <iostream>
#include <string>
#include <time.h>

//时间类
class Timestamp {
public:
    Timestamp() : microSecondsSinceEpoch_(0) {}
    explicit Timestamp(int64_t microSecondsSinceEpochArg)   //time_t = int64_t,explicit 构造防止隐式转换
    : microSecondsSinceEpoch_(microSecondsSinceEpochArg) {}
    //返回当前时间对象
    static Timestamp now();
    //转换成msg字符串
    std::string toString() const;
private:
    int64_t microSecondsSinceEpoch_; //长整型
};