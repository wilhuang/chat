#ifndef TIP_H
#define TIP_H

#include <iostream>

// msg的body与头尾大小
//注意:windows缓存区最大为2966个字节
//此为实际测试值,可能存在其他占用,建议使用时小于该值
#define BODY_SIZE 2400
#define PARAMSIZE 30
#define HEAD_TAIL 4
//状态码
#define CODE_OK 200
#define CODE_NOK 404
#define CODE_ERR 500
//头和尾
#define HEAD "Hed"
#define TAIL "Tal"
//获取资源路径Url
#define LOGIN "Log"
#define REGISTER "reg"
#define GETALLUSER "gau"
#define SENDMSG "msg"

typedef struct
{
    char header[HEAD_TAIL];
    char url[HEAD_TAIL];
}Heads;

typedef struct
{
    uint16_t statusCode; //状态码
    char tail[HEAD_TAIL];
}Tails;

typedef struct
{
    Heads heads;
    uint16_t paramSize[PARAMSIZE];//传输体长度
    char body[BODY_SIZE];//传输体
    Tails tails;
}Msgs;

typedef struct
{
    int uid;
    char uname[36];
    int status;
}Users;

typedef struct
{
    int gid;
    char gname[36];
    int gnum;
    int status;
}Groups;

typedef struct
{
    char message[255];
    char sendtime[20];
    int gid;
    int uid;
}Messages;

class Tip
{
public:
    Tip();
    Msgs msg;
    void encode(Users user[]);
    void decode();
    void init();
    int msgSize;
    int pparam;
    int pbody;
};

Tip::Tip()
{
    msgSize=sizeof(Msgs);
}

void Tip::init()
{
    pparam=0;
    pbody=0;
    memset(&msg,0,msgSize);
}

//可能存在内存溢出问题
void Tip::encode(Users user[])
{
    for(int i=0;user[i].uid!=0;i++)
    {
        msg.paramSize[pparam+i]=strlen(user[i].uname);
        memcpy(msg.body+s,user[i].uname,msg.paramSize[pparam+i]);
        pbody+=msg.paramSize[pparam+i];
    }
    pparam++;
}

///**
//*
//*200：成功，这个成功只是表示服务器正常处理完成了，并不能表示逻辑的正确性
//*404：一般为文件，目录不存在，但也可以将其他情况伪装成为不存在
//*500：出现这个一般都是服务端的代码直接抛出异常导致
//*
//* /

//以下为通用协议

typedef struct
{
    //
    char Header[HEAD_TAIL];//传输头
    char Url[HEAD_TAIL];//资源请求路径
    uint16_t ParamSize[PARAMSIZE];//传输体长度
    char Body[BODY_SIZE];//传输体
    uint16_t StatusCode;//状态码
    char Tail[HEAD_TAIL];//传输尾
}Msg;

#endif // GLOBAL_H
