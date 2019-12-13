#include "client.h"

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

//Buffer Buf;

Client::Client() {
    clientAddr.sin_family = PF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    clientAddr.sin_port = htons(SERVER_PORT);
}

void Client::init() {
    std::cout << "Init client..." << std::endl;
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);
    //初始化传输协议
    memset(&msg,0,sizeof(msg));
    memcpy(msg.Header,HEAD,HEAD_TAIL);
    memcpy(msg.Tail,TAIL,HEAD_TAIL);
}

int Client::login(char *uname,char *passwd) {
    init();
    int err=1;
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));
    //        pwd=MD5(passwd);
    //数据封装
    memcpy(msg.Url,LOGIN,HEAD_TAIL);
    msg.ParamSize[0]=strlen(uname);
    msg.ParamSize[1]=strlen(passwd);
    memcpy(msg.Body, uname, msg.ParamSize[0]);
    memcpy(msg.Body+msg.ParamSize[0], passwd, msg.ParamSize[1]);

    std::cout<<"send Header from client: "<<msg.Header<<std::endl;
    std::cout<<"send Url from client: "<<msg.Url<<std::endl;
    std::cout<<"send ParamSize from client: "<<msg.ParamSize<<std::endl;
    std::cout<<"send Body from client: "<<msg.Body<<std::endl;
    std::cout<<"send Tail from client: "<<msg.Tail<<std::endl;

    send(sock, (const char *)&msg, sizeof(Msg), 0);
    recv(sock, (char*)&msg, sizeof(msg), 0);
    std::cout<<"recv Header from client: "<<msg.Header<<std::endl;
    if (msg.StatusCode==CODE_ERR) err=-1;
    if (msg.StatusCode==CODE_OK)
    {
        //数据msg装入缓存Buf
//        msg

        err=0;
    }
    memset(&msg,0,sizeof(msg));  //重置缓冲区
    closesocket(sock);  //关闭套接字
    WSACleanup();  //终止使用 DLL
    return err;
}


//目前注册信息较少,与login函数仅有请求路径的不同.
int Client::regis(char *uname,char *passwd) {
    init();
    int status=1;
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));
    //数据封装
    msg.ParamSize[0]=strlen(uname);
    msg.ParamSize[1]=strlen(passwd);
    memcpy(msg.Body,uname,msg.ParamSize[0]);
    memcpy(msg.Body+msg.ParamSize[0],passwd,msg.ParamSize[1]);
    std::cout<<msg.ParamSize<<std::endl;
    std::cout<<uname<<std::endl;
    std::cout<<msg.ParamSize[1]<<std::endl;
    std::cout<<passwd<<std::endl;
    std::cout<<msg.Body<<std::endl;

    send(sock, (const char *)&msg, sizeof(msg), 0);
    recv(sock, (char*)&msg, sizeof(msg), 0);
    if (msg.StatusCode==CODE_OK) status=0;
    if (msg.StatusCode==CODE_ERR) status=-1;
    memset(&msg,0,sizeof(msg));  //重置缓冲区
    closesocket(sock);  //关闭套接字

    WSACleanup();  //终止使用 DLL
    return status;
}
