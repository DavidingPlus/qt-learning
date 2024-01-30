#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

onceagain:
    auto btn = QMessageBox::question(this, "哈哈哈哈哈哈哈", "你是傻播一吗", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(btn == QMessageBox::Yes)
        QMessageBox::information(this, "哈哈哈哈哈哈哈你是傻播一", "知道就好");
    else {
        QMessageBox::information(this, "不可能", "给我重新选!!!!");
        goto onceagain;
    }

}

MainWindow::~MainWindow() {
    delete ui;
}

