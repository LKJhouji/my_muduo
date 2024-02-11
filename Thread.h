#pragma once

#include <sys/syscall.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <functional>
#include <atomic>

#include "noncopyable.h"


namespace CurrentThread {
    extern __thread int t_cachedTid;
    inline int tid() {
        if (t_cachedTid == 0) {
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
        return t_cachedTid;
    }
};

class Thread : noncopyable {
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc, const std::string &name = std::string());
    ~Thread();

    void start();
    void join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }

    static int numCreated() { return numCreated_; }
private:
    void setDefaultName();

    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    static std::atomic_int numCreated_;
};