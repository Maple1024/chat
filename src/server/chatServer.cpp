#include "chatServer.hpp"
#include "chatService.hpp"
#include <functional>
using namespace std;
using namespace placeholders;

//启动服务
void ChatServer::start(){
    _server.start();
}
ChatServer::ChatServer(EventLoop *loop,
            const InetAddress &listenAddr,
            const string &nameArg)
            :_server(loop,listenAddr,nameArg),_loop(loop)
            {
                //注册链接回调
                _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));
                //注册消息回调
                _server.setMessageCallback(std::bind(&ChatServer::onMessage,this,_1,_2,_3));
                //设置线程数量
                _server.setThreadNum(4);
            }

   //上报链接信息的回调函数
    void ChatServer::onConnection(const TcpConnectionPtr& conn){
        //客户端断开连接
        if(!conn->connected()){
            conn->shutdown();
        }
    }
    //上报读写信息的回调函数
    void ChatServer::onMessage(const TcpConnectionPtr& conn,Buffer* buffer,Timestamp time){
        string buf=buffer->retrieveAllAsString();
        //数据的反序列化
        json js=json::parse(buf);
        //达到的目的是：完全解耦网络模块的代码和业务模块的代码
        //通过js["msgid"]获取=>>业务handler=>>conn js time
        auto msgHandler=ChatService::instance()->getHandler(js["msgid"].get<int>());
        msgHandler(conn,js,time);
    }