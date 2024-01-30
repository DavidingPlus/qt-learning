#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setWindowTitle("登录窗口");
    // setFixedSize(549, 410);
}

MainWindow::~MainWindow()
{
    delete ui;
}
