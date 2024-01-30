#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建一个新窗口
    QWidget *wid = new QWidget;
    connect(ui->pushButton, &QPushButton::clicked, wid, [=]()
            { OpenNewWidget(wid); }); //这个是lambda表达式的形式
    connect(ui->pushButton_2, &QPushButton::clicked, wid, &QPushButton::close);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::OpenNewWidget(QWidget *wid)
{
    wid->setWindowTitle("新窗口");
    wid->show();
}
