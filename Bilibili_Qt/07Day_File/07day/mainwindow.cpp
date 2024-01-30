#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

//文件读取操作
void MainWindow::on_fileBtn_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "选择文件", "D:/");
    ui->lineEdit->setText(path);
    //读出文件内容
    QFile* file = new QFile(path, this); //构建文件对象对文件做相关操作
    bool ret = file->open(QIODevice::ReadOnly);
    if(!ret)return;//打开文件用于读 判断是否正常打开

    QByteArray arr; //字节数组 动态数组!!!
    //判断文件结尾 atend()
    while(!file->atEnd())
        arr += file->readLine();
    ui->textEdit->setText(QString(arr));
    //关闭文件
    file->close();
}

//文件写入 另存为
void MainWindow::on_saveasBtn_clicked() {
    QString path = QFileDialog::getSaveFileName(this, "另存为", "./未命名.txt"); // ./ 当前项目文件夹
    //写
    QFile* file = new QFile(path, this);
    bool ret = file->open(QIODevice::WriteOnly);
    if(!ret)return;

    QString text = ui->textEdit->toPlainText(); //得到文本框内容
    file->write(text.toUtf8());//转化为字节数组

    file->close();
}

//文件写入 另存为二进制文件
void MainWindow::on_saveasBinBtn_clicked() {
    QString path = QFileDialog::getSaveFileName(this, "另存为二进制", "./未命名.bin", "*.bin"); // ./ 当前项目文件夹
    QString text = ui->textEdit->toPlainText(); //得到文本框内容

    QFile* file = new QFile(path, this);
    bool ret = file->open(QIODevice::WriteOnly);
    if(!ret)return;

    //创建数据流对象
    QDataStream fout(file);//传入文件对象指针
    QString str = "你怎么睡得着?";
    fout << 12345;
    fout << str;
    file->close();
}

//读取二进制文件
void MainWindow::on_openbinBtn_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "选择二进制文件", "D:/", "*.bin *.txt");

    //文件对象
    QFile* file = new QFile(path, this);
    bool ret = file->open(QIODevice::ReadOnly);
    if(!ret)return;

    //创建数据流对象
    QDataStream fin(file);//传入文件对象指针
    int num;
    QString str;
    fin >> num;
    fin >> str;
    qDebug() << num << str;

    file->close();
}
