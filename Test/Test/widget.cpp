#include "widget.h"
#include "ui_widget.h"
#include <QStack>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStack<int>s;

    s.push(1);
    s.push(2);
    qDebug()<<s.top();

    s.insert(1,3); // 任意位置插入,wth？？？

    s.pop();
    qDebug()<<s.top();

}

Widget::~Widget()
{
    delete ui;
}
