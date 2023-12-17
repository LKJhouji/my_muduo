#pragma once 

//无法拷贝

class noncopyable {
public:
    noncopyable(const noncopyable&) = delete;
    void operator= (const noncopyable&) = delete;
protected:  //专门用来继承的类
    noncopyable() = default;
    ~noncopyable() = default;
};