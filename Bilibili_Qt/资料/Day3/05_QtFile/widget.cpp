#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击选取文件按钮 弹出文件对话框
    connect(ui->pushButton, &QPushButton::clicked, [=]()
            {
                QString path = QFileDialog::getOpenFileName(this, "打开文件", "C:/Users/DavidingPlus/Desktop");
                //将路径放入到lineEdit中
                ui->lineEdit->setText(path);

                //编码格式类
                // QTextCodec *codec=QTextCodec::codecForName("gbk");

                //读取内容 放到 textEdit中
                // Qfile 默认支持的格式是 utf-8
                QFile file(path); //参数就是读取文件的路径
                //设置打开方式
                file.open(QIODevice::ReadOnly);
                QByteArray array;
                // array= file.readAll(); //全部读完

                while (!file.atEnd())
                    array += file.readLine(); //按行读

                //将读取到的数据放到textEdit中
                // ui->textEdit->setText(codec->toUnicode(array));
                ui->textEdit->setText(array);

                //对文件对象进行关闭
                file.close();

                //进行写文件
                //用追加的方式进行写
                // file.open(QFileDevice::Append);
                // file.write("啊啊啊啊啊");
                // file.close();

                // QFileInfo 文件信息类
                QFileInfo info(path);

                qDebug() << "大小: " << info.size() << " 后缀名: " << info.suffix() << " 文件名称: " << info.fileName() << " 文件路径: " << info.path();
                qDebug() << "创建日期: " << info.birthTime().toString("yyyy/MM/dd hh:mm:ss").toUtf8().data(); 
                qDebug() << "最后修改日期: " << info.lastModified().toString("yyyy/MM/dd hh:mm:ss").toUtf8().data(); });
}

Widget::~Widget()
{
    delete ui;
}
