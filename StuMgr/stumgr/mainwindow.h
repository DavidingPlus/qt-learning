#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"page_login.h"
#include "stusql.h"
#include <QMainWindow>
#include "adddlg.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    //创建登录界面对象
    Page_Login _login;

    //测试样例对象
    QStringList testList;
    void InittestList();

    //创建数据库连接对象
    StuSql* _sql;

    //用一个表来存储学生的信息
    QList<StuInfo> stus;

    //创建增加窗口对象
    AddDlg _adddlg;

private slots:
    void on_exitBtn_clicked();

    void on_simulationBtn_clicked();

    void on_addBtn_clicked();

    void on_clearBtn_clicked();

    void on_updateBtn_clicked();

    void on_changeBtn_clicked();

    void on_delBtn_clicked();

    void on_searchBtn_clicked();

    void on_stuBtn_clicked();

    void on_userBtn_clicked();

    void on_updageBtn_2_clicked();

private:
    Ui::MainWindow* ui;

    void updateTable();
    void updateTable_2();
};
#endif // MAINWINDOW_H
