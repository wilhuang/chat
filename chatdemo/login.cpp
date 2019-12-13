#include "login.h"
#include "mainwindow.h"
#include "ui_login.h"
#include "client.h"
#include "regis.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::reshow()
{
    this->show();
}

void Login::on_btn_register_clicked()
{
    this->hide();//主界面关闭
    Regis *rg=new Regis(this);//新建子界面
    connect(rg,SIGNAL(sendsignal()),this,SLOT(reshow()));
    rg->show();//显示主页面
}

void Login::on_btn_login_clicked()
{
    //获得输入框文本：edit_uname->text()
    //trimmed()去掉前后空格
    //tr()函数,防止设置中文时乱码
    //此处查询服务器账号信息
    QByteArray unameba = ui->edit_uname->text().trimmed().toLatin1();
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
    std::cout<<"input uname: "<<uname<<std::endl;
    std::cout<<"input passwd: "<<passwd<<std::endl;
    Client client;
    int err=client.login(uname,passwd);
    free(uname);
    free(passwd);
//    int err=0;
    if (!err)
    {
        this->hide();//主界面关闭
        MainWindow *mw=new MainWindow(this);//新建子界面
        connect(mw,SIGNAL(sendsignal()),this,SLOT(reshow()));
        mw->show();//显示主页面
    } else {
        QMessageBox::warning(this, tr("警告!"),tr("用户名或密码错误!"),QMessageBox::Close);
        // 清空密码框内容
        ui->edit_passwd->clear();
        //光标定位
        ui->edit_uname->setFocus();
    }
}

