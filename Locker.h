#pragma once

#include "Log.h"

class Locker {
public:
    Locker() {
        if (pthread_mutex_init(&mutex_, nullptr) != 0) {
            LOG_FATAL("Locker::pthread_mutex_init error\n");
        }
    }
    ~Locker() {
        if (pthread_mutex_destroy(&mutex_) != 0) {
            LOG_ERROR("Locker::pthread_mutex_destroy error\n");
        }
    }
    bool lock() {
        return pthread_mutex_lock(&mutex_) == 0;
    }
    bool unlock() {
        return pthread_mutex_unlock(&mutex_) == 0;
    }
    pthread_mutex_t* getLocker() {
        return &mutex_;
    }
private:
    pthread_mutex_t mutex_;
};