#include "regis.h"
#include "ui_regis.h"
#include "client.h"
#include "login.h"

Regis::Regis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Regis)
{
    ui->setupUi(this);
}

Regis::~Regis()
{
    delete ui;
}

void Regis::on_btn_register_clicked()
{
    //获得输入框文本：edit_uname->text()
    //trimmed()去掉前后空格
    //tr()函数,防止设置中文时乱码
    //此处查询服务器账号信息
    QByteArray unameba = ui->edit_uname->text().trimmed().toLatin1();
    std::cout<<unameba.length()<<std::endl;
    QByteArray passwdba = ui->edit_passwd->text().toLatin1();
    char *uname = NULL;
    char *passwd = NULL;
    uname = (char *)malloc(unameba.length()+1);
    passwd = (char *)malloc(passwdba.length()+1);
    memset(uname, 0, unameba.length());
    memset(passwd,0,passwdba.length());
    memcpy(uname, unameba.data(), unameba.length());
    memcpy(passwd, passwdba.data(), passwdba.length());
    uname[unameba.length()] = '\0';
    passwd[passwdba.length()] = '\0';
    std::cout<<strlen(uname)<<std::endl;
    Client client;
    int err=client.login(uname,passwd);
    if (!err)
    {
        QMessageBox::information(this, tr("恭喜!"),tr("注册成功!"),QMessageBox::Ok);
    } else {
        QMessageBox::warning(this, tr("错误!"),tr("注册失败,请重试!"),QMessageBox::Close);
        // 清空密码框内容
        ui->edit_passwd->clear();
        //光标定位
        ui->edit_uname->setFocus();
    }
}



void Regis::on_btn_loginback_clicked()
{
    emit sendsignal();
    this->close();
}
