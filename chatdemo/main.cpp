/**
*@file man.cpp
*
*@brief 这是一个使用socket+sqlite+qt_ui的一个chat_demo
*
*@author wilhuang
*
*@date 2019/12/5
*@version 1.0.0
*
*@note ui组件使用蛇形命名规范,变量与函数使用小驼峰,类名使用大驼峰,接口以I开头
*/

#include "global.h"
#include "login.h"
#include <QApplication>

//extern Buffer Buf;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
//    Buf.user[0].status=0;
//    std::cout<<Buf.user[0].status<<std::endl;
    return a.exec();
}
