#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(800,600);

    connect(ui->closeBtn,&QPushButton::clicked,this,&QWidget::close);
    // connect(ui->closeBtn,&QPushButton::clicked,this,[=](){
    //     this->close();
    // });
}

Widget::~Widget()
{
    delete ui;
}
