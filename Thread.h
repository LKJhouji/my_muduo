#pragma once

#include <functional>
#include <string>

#include "noncopyable.h"

class Thread : noncopyable {
public:
    using ThreadFunc = std::function<void()>;
    using string = std::string;

    explicit Thread(ThreadFunc func, const string& name);

    ~Thread();
    void start();
    int join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const string& name() { return name_; }
private:
    void setDefaultName();

    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    string name_;

};