#include "Poller.h"
#include "Channel.h"

Poller::Poller(EventLoop* loop) : loop_(loop) {}

Poller::~Poller() = default;

//判断通道是否存在
bool Poller::hasChannel(Channel* channel) const {
    ChannelMap::const_iterator it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}