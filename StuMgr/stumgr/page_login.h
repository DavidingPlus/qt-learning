#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>

namespace Ui {
    class Page_Login;
}

class Page_Login : public QWidget {
    Q_OBJECT

public:
    explicit Page_Login(QWidget* parent = nullptr);
    ~Page_Login();

private slots:
    void on_exitBtn_clicked();

    void on_loginBtn_clicked();
signals:
    void sendLoginSuccess();

private:
    Ui::Page_Login* ui;
};

#endif // PAGE_LOGIN_H
