#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include "../msnserver/include/tip.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_btn_register_clicked();

    void on_btn_login_clicked();

    void reshow();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
