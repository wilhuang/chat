#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_back_clicked();
    void reshow();

signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消息

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
