#ifndef REGIS_H
#define REGIS_H

#include <QMainWindow>
#include <QMessageBox>
namespace Ui {
class Regis;
}

class Regis : public QMainWindow
{
    Q_OBJECT

public:
    explicit Regis(QWidget *parent = 0);
    ~Regis();

private slots:
    void on_btn_register_clicked();

    void on_btn_loginback_clicked();


signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消息


private:
    Ui::Regis *ui;
};

#endif // REGIS_H
