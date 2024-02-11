#pragma once

#include <iostream>
#include <string>


class Timestamp {
public:
    Timestamp() : microSecond_(0) {}
    explicit Timestamp(int64_t microSecond) : microSecond_(microSecond) {}
    static Timestamp now();
    std::string toString() const;
private:
    int64_t microSecond_;
};