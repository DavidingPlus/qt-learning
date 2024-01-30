#include "page_login.h"
#include "qmessagebox.h"
#include "ui_page_login.h"
#include "mainwindow.h"
#include "stusql.h"

Page_Login::Page_Login(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::Page_Login)
{
    ui->setupUi(this);

    // 设置固定窗口大小
    this->setFixedSize(400, 300);
}

Page_Login::~Page_Login()
{
    delete ui;
}

void Page_Login::on_exitBtn_clicked()
{
    // 退出
    this->close();
}

void Page_Login::on_loginBtn_clicked()
{
    // 数据库查找用户名和密码
    QList<UserInfo> users = StuSql().getAllUser();
    bool flag = false;
    for (int i = 0; i < users.size(); ++i)
        // 逐个进行比对
        if (ui->line_user->text() == users[i]._username && ui->line_password->text() == users[i]._password)
        {
            flag = true;
            break;
        }
    // 如果失败提示
    if (!flag)
    {
        QMessageBox::warning(this, "错误", "用户名或密码错误");
        return;
    }
    // 成功进入主界面
    emit sendLoginSuccess();
}
