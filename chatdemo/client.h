#ifndef CLIENT_H
#define CLIENT_H

#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#include "global.h"
#include "../msnserver/include/tip.h"

class Client {

public:
    // 无参数构造函数
    Client();

    // 初始化服务器端设置
    void init();

    //登录程序
    int login(char *uname,char *passwd);

    //注册程序
    int regis(char *uname,char *passwd);

    // 启动服务端
    void heartbeat();

    Msg msg;
private:

    // 服务器端clientAddr信息
    sockaddr_in clientAddr;
};

#endif // CLIENT_H
