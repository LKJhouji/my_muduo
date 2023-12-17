#include "Poller.h"
#include "EpollPoller.h"
#include "Log.h"
#include "Channel.h"

//Channel状态机
//Channel未添加到Poller中
const int kNew = -1;
//Channel已添加到Poller中
const int kAdded = 1;
//Channel已从Poller中删除
const int kDeleted = 2;

EpollPoller::EpollPoller(EventLoop* loop) 
    : Poller(loop), 
      epollfd_(epoll_create1(EPOLL_CLOEXEC)), 
      events_(kInitEventListSize) {
    if (epollfd_ < 0)
      LOG_FATAL("epoll create error : %d\n", errno);
}

EpollPoller::~EpollPoller() {
    ::close(epollfd_);
}

//监听通道 超时时间 监听通道列表
Timestamp EpollPoller::poll(int timeoutMs, ChannelList* activeChannels) {
  LOG_INFO("fd total count = %d\n", static_cast<int>(channels_.size()));
  //返回值 大于 0 正常 等于 0 没有监听事件发生 
  int num_events = ::epoll_wait(epollfd_, &*events_.begin(), events_.size(), timeoutMs);
  Timestamp current(Timestamp::now());
  int savedErrno = errno;
  if (num_events > 0) {
    LOG_INFO("%d events happend\n", num_events);
    fillActiveChannels(num_events, activeChannels);
    if (num_events == events_.size()) {
      events_.resize(events_.size() * 2);
    }
  }
  else if (num_events == 0) {
    LOG_INFO("nothing happend\n");
  }
  else {
    if (errno != EINTR) { //不是中断信号
      errno = savedErrno;
      LOG_FATAL("func = %s => epoll_wait error\n", __FUNCTION__);
    }
  }
  return current;
}
//更新通道
void EpollPoller::updateChannel(Channel* channel) {
  const int index = channel->index();
  LOG_INFO("func = %s => fd = %d, events = %d, index = %d\n", __FUNCTION__, channel->fd(), channel->events(), index);
  if (index == kNew || index == kDeleted) {
    if(index == kNew) { //新连接 如果是 kDeleted 应该是重建连接
      int fd = channel->fd();
      channels_[fd] = channel;
    }
    channel->set_index(kAdded);
    update(EPOLL_CTL_ADD, channel);
  }
  else {
    int fd = channel->fd();
    if (channel->isNoneEvent()) { //可以删除了
      channel->set_index(kDeleted);
      update(EPOLL_CTL_DEL, channel);
    } 
    else {
      update(EPOLL_CTL_MOD, channel);
    }
  }
}
//去除通道
void EpollPoller::removeChannel(Channel* channel) {
  int fd = channel->fd();
  int index = channel->index();
  LOG_INFO("func = %s => fd = %d, index = %d\n", __FUNCTION__, fd, index);
  channels_.erase(fd);

  if (index == kAdded)
  {
    update(EPOLL_CTL_DEL, channel);
  }
  channel->set_index(kNew);
}

//内部实现public中函数的private函数
void EpollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const {
  for (int i = 0; i < numEvents; i++) {
    Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
    channel->set_revents(events_[i].events);
    activeChannels->push_back(channel);
  }
}

void EpollPoller::update(int operation, Channel* channel) {
  epoll_event event;
  memset(&event, 0, sizeof event);
  event.events = channel->events();
  event.data.ptr = channel;
  int fd = channel->fd();
  if (::epoll_ctl(epollfd_, operation, fd, &event) < 0) {
    if (operation == EPOLL_CTL_DEL) {
      LOG_ERROR("epoll del error = %d\n", errno);
    }
    else {
      LOG_FATAL("epoll add/mod error = %d\n", errno);
    }
  }
}