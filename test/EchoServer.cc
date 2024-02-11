#include <my_muduo/TcpServer.h>

class EchoServer : noncopyable {
public:
    EchoServer(EventLoop* loop, 
            const InetAddress& addr,
            const std::string& name)
            : server_(loop, addr, name)
            , loop_(loop) {
                server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
                server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                server_.setThreadNum(3);
            }
    void start() {
        server_.start();
    }
private:
    void onConnection(const TcpConnectionPtr& conn) {
        if (conn->connected()) {
            LOG_INFO("%s--%s--%d : Connection UP : %s\n", __FILE__, __FUNCTION__, __LINE__, conn->peerAddr().toIpPort().c_str());
        }
        else {
            LOG_INFO("%s--%s--%d : Connection DOWN : %s\n", __FILE__, __FUNCTION__, __LINE__, conn->peerAddr().toIpPort().c_str());
        }
    }


    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
        std::string msg(buf->retrieveAllAsString());
        conn->send(msg);
        conn->shutdown(); // 写端关闭
    }
    TcpServer server_;
    EventLoop* loop_;
};

int main() {
    EventLoop loop;
    InetAddress addr(8000);
    EchoServer echoServer(&loop, addr, "EchoServer-apylee");
    echoServer.start(); //整个TcpServer开始
    loop.loop();    //mainloop
    return 0;
}