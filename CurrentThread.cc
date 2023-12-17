#include "CurrentThread.h"

void cacheTid() {
    if (t_cacheTid == 0) {
        t_cacheTid = static_cast<pid_t>(::syscall(SYS_gettid));
    }
}