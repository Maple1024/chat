#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "userModel.hpp"
using json=nlohmann::json;
using namespace std;
using namespace muduo;
using namespace muduo::net;

using MsgHandler=std::function<void(const TcpConnectionPtr &conn,json &js,Timestamp)>;
//聊天服务器业务类
class ChatService{
public:
    //获取单例对象的接口函数
    static ChatService* instance();
    //处理登录业务
    void login(const TcpConnectionPtr& conn,json &js,Timestamp time);

    //处理注册业务
    void reg(const TcpConnectionPtr &conn,json &js,Timestamp time);

    //获取消息对应的处理器
    MsgHandler getHandler(int msgid); 

    void clientCloseException(const TcpConnectionPtr& conn);
private:
    ChatService();

    //存储消息id和其对应的业务处理方法
    unordered_map<int,MsgHandler>_msgHandlerMap;

    //存储在线用户的通信连接
    unordered_map<int,TcpConnectionPtr>_userConnMap;

    //业务操作类
    UserModel _userModel;

    mutex _connMutex;

};
#endif