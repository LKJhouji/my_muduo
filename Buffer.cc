#include <sys/uio.h>
#include <unistd.h>
#include "Buffer.h"

//从fd上读取数据，读到buffer缓冲区中，使用到缓冲区中可写部分
//为什么要用第二个内存块来存
ssize_t Buffer::readFd(int fd, int* savedErrno) {
    char extrabuf[65536] = {0};
    struct iovec vec[2];
    const size_t writable = writableBytes();
    vec[0].iov_base = &*buffer_.begin() + writerIndex_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof extrabuf;
    const int iovcnt = (writable <= sizeof extrabuf) ? 2 : 1;
    const int n = ::readv(fd, vec, iovcnt);
    if (n < 0) {
        *savedErrno = errno;
    }
    else if (n <= writable) {   //可写缓冲区剩余大小能够读完
        writerIndex_ += n;
    }
    else {
        writerIndex_ = buffer_.size();
        append(extrabuf, n - writable); //将extrabuf中n - writable拷贝到入可写缓冲区中，虽然我不明白为什么这么做
    }
    return n;
}

//向fd中发送数据
ssize_t Buffer::writeFd(int fd, int* savedErrno) {
    ssize_t n = ::write(fd, &*buffer_.begin(), readableBytes());
    if (n < 0) {
        *savedErrno = errno;
    }
    return n;
}