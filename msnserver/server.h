#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <WinSock2.h>

#include "global.h"
#include "include/tip.h"

// 服务端类，用来处理客户端请求

class Server {

public:
    // 无参数构造函数
    Server();
    // 启动服务端
    void start();

private:
    // 初始化服务器端设置
    void init();
    // 关闭服务端
    void close();

    void msgReset();
    // 服务器端serverAddr信息
    sockaddr_in serverAddr;
    //创建监听的socket
    SOCKET servSock;

    int msgSize;

    Msg msg;

};

#endif // SERVER_H
