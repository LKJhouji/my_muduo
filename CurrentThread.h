#pragma once

#include <unistd.h>
#include <sys/syscall.h>

extern __thread pid_t t_cacheTid;
void cacheTid();    //缓存tid

inline pid_t tid() {
    if (__builtin_expect(t_cacheTid == 0, 0)) {
        cacheTid();
    }
    return t_cacheTid;
}

