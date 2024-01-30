#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include <QFileDialog>//文件对话框
#include <QColorDialog>//颜色对话框
#include <QFontDialog>//文字对话框
#include <QMessageBox>//消息对话框 警告 普通 错误
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //模态窗口
    connect(ui->btn, &QPushButton::clicked, [ = ]() {
        //创建窗口
        //模态窗口 窗口出现的时候不能处理该窗口之外的操作!!!!!
        QDialog dialog(this);//这里需要用局部变量 不能放在堆区防止内存溢出 需要局部变量加上消息捕捉循环来让窗口显示 否则会一闪而过
        dialog.resize(400, 200);
//        dialog.show(); //这里调用show会导致变成非模态对话框

        dialog.exec();//进入消息捕捉循环 自然而言就会出现 会停顿直到关掉窗口!!!
    });

    //非模态窗口
    connect(ui->btn_2, &QPushButton::clicked, [ = ]() {
        QDialog dialog(this);
        dialog.resize(400, 200);
        dialog.show(); //这里调用show会导致变成非模态对话框 这是一种写法

        dialog.exec();
    });

    //方式2
    connect(ui->btn_3, &QPushButton::clicked, [ = ]() {
        QDialog* dialog = new QDialog(this);
        dialog->resize(400, 200);
        dialog->show();
        dialog->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放对话框 需要设置一下 使用堆区非模块对话框的注意事项!!!
    });

    //文件对话框
    connect(ui->btn_4, &QPushButton::clicked, [ = ]() {
        //参数1 父亲 参数2 对话框标题 参数3 默认路径 参数4 过滤的文件(只显示这些文件)
        QString fileName =  QFileDialog::getOpenFileName(this, "打开文本文件", "D:/", "*.txt");
        qDebug() << "get the fucking file name : " << fileName;

    });

    //颜色对话框
    connect(ui->btn_5, &QPushButton::clicked, [ = ]() {
        auto color = QColorDialog::getColor(Qt::blue, this, "文字颜色");//第一个参数 默认颜色
        //文本编辑框可以设置颜色 标签不可以设置颜色
        ui->textEdit->setTextColor(color);
        ui->textEdit->setText("你好");
    });

    //文字对话框
    connect(ui->btn_6, &QPushButton::clicked, [ = ]() {
        bool bl = true;//是否使用 用户使用的字体
        QFont font = QFontDialog::getFont(&bl, this);
        ui->label->setFont(font);
        ui->label->setText("你好");
//        qDebug() << bl;
    });

    //消息对话框
    //参数1 父亲,参数2 标题,参数3 内容,参数4 按钮,参数5 回车时默认选择
    QMessageBox::critical(this, "错误", "你错了", QMessageBox::Close); //危险对话框
    QMessageBox::warning(this, "警告", "你错了");//警告对话框
    QMessageBox::information(this, "提示", "你错了"); //提示对话框
onceagain:
    auto btn = QMessageBox::question(this, "问题", "你爱我吗", QMessageBox::Yes | QMessageBox::No, QMessageBox::No); //问题对话框
    if(btn == QMessageBox::Yes)
        QMessageBox::information(this, "好呀", "我也爱你");
    else {
        QMessageBox::information(this, "错误", "系统错误");
        goto onceagain;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

