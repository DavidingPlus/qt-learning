#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui->actionNew->setIcon(QIcon("D:/文档/狗头像.jpg"));

    //使用添加Qt资源 ": + 前缀名 + 文件名 "
    ui->actionNew->setIcon(QIcon("D:/Code/QT/Bilibili/Day2/02_QtSource/Image/Luffy.png"));
    ui->actionOpen->setIcon(QIcon("D:/Code/QT/Bilibili/Day2/02_QtSource/Image/LuffyQ.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
