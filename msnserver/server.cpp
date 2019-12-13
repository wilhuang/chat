#include "server.h"
#include "sql.h"

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

Server::Server() {
    //    //初始化 DLL
    //    WSADATA wsaData;
    //    WSAStartup( MAKEWORD(2, 2), &wsaData);
    // 初始化服务器地址和端口
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    // 初始化socket
    servSock = 0;
    msgSize=sizeof(Msg);
}

void Server::init() {
    std::cout << "Init Server..." << std::endl;
    std::cout<<"Buffer Size set:"<<msgSize<<std::endl;
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);
    // 初始化服务器地址和端口
    //创建socket
    servSock = socket(PF_INET, SOCK_STREAM, 0);
    bind(servSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    //监听
    memset(&msg,0,sizeof(msg));
    listen(servSock, 5);
    std::cout << "Start to listen: " << SERVER_IP<<":"<<SERVER_PORT << std::endl;
}

void Server::msgReset()
{
    memset(&msg,0,sizeof(msg));
    memcpy(msg.Header,HEAD,HEAD_TAIL);
    memcpy(msg.Tail,TAIL,HEAD_TAIL);
}

void Server::start() {
    init();
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    while(1){
        SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
        recv(clntSock, (char *)&msg, msgSize, 0);  //接收客户端发来的数据
        std::cout<<"recv Header from client: "<<msg.Header<<std::endl;
        std::cout<<"recv Url from client: "<<msg.Url<<std::endl;
        std::cout<<"recv ParamSize from client: "<<msg.ParamSize<<std::endl;
        std::cout<<"recv Body from client: "<<msg.Body<<std::endl;
        std::cout<<"recv Tail from client: "<<msg.Tail<<std::endl;
        if(!strcmp(msg.Header,HEAD)&&!strcmp(msg.Tail,TAIL)){
            std::cout<<"Header and Tail Pass"<<std::endl;
            if (!strcmp(msg.Url,GETALLUSER)){
                std::cout<<"Messages getting ..."<<std::endl;
                Users user[1];
                memset(&user,0,sizeof(user));
                SQLIndex index;
                int err=index.sqlFind(msg,user);
                msgReset();
                if (err==-1) {
                    msg.StatusCode=CODE_ERR;
                }
                if (err==1) {
                    msg.StatusCode=CODE_NOK;
                }
                if (err==0) {
                    msg.StatusCode=CODE_OK;
                    Users users[30];
                    memset(&users,0,sizeof(users));
                    int errs=index.sqlFindAll(user[0].uid,users);
                    if (err!=0) {
                        msg.StatusCode=CODE_ERR;
                    } else {
                        //                        msg.ParamSize[0]=strlen(uname);
                        //                        msg.ParamSize[1]=strlen(passwd);
                        //                        memcpy(msg.Body, uname, msg.ParamSize[0]);
                        //                        memcpy(msg.Body+msg.ParamSize[0], passwd, msg.ParamSize[1]);
                    }
                }

                std::cout << err<<user[0].uid << std::endl;
                std::cout << user[0].uname << std::endl;
                send(clntSock, (const char *)&msg,msgSize, 0);  //将数据返回
            }
            if (!strcmp(msg.Url,LOGIN)){
                std::cout<<"Logining ..."<<std::endl;
                Users users[50];
                memset(&users,0,sizeof(users));
                msg.StatusCode=CODE_OK;
                SQLIndex index;
                int err=index.sqlFind(msg,users);
                if (err==-1) {msg.StatusCode=CODE_ERR;};
                if (err==1) {msg.StatusCode=CODE_NOK;};
                std::cout << err<<users[0].uid << std::endl;
                std::cout << users[0].uname << std::endl;
                send(clntSock, (const char *)&msg,msgSize, 0);  //将数据返回
            }
            if (!strcmp(msg.Url,REGISTER)){
                std::cout<<"Registering ..."<<std::endl;
                msg.StatusCode=CODE_OK;
                SQLIndex index;
                int err=index.sqlCreate(msg);
                if (err==-1) {msg.StatusCode=CODE_ERR;};
                if (err==1) {msg.StatusCode=CODE_NOK;};
                send(clntSock, (const char *)&msg,msgSize, 0);  //将数据返回
            }
        }
        closesocket(clntSock);  //关闭套接字
        memset(&msg,0,msgSize);  //重置缓冲区
        //        i--;
    }
    close();
}

void Server::close() {
    //关闭套接字
    closesocket(servSock);
    //关闭DLL
    WSACleanup();
}
