#include "widget.h"
#include "ui_widget.h"
#include "mywidget.h"
#include "mywidget2.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 测试不带MEMBER
    MyWidget mw;
    mw.setProperty("age",18);

    auto res = mw.property("age");
    qDebug() << res;

    // 测试带MEMBER
    MyWidget2 mw2;
    mw2.setProperty("age",19);

    auto res2 = mw2.property("age");
    qDebug() << res2;
}

Widget::~Widget()
{
    delete ui;
}
