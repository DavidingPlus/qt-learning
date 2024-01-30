#include "widget.h"
#include <QPushButton>
#include <QDebug>
#include <QLabel> //文本控件
#include <QSlider> //滑动条控件
#include <QProgressBar>> //进度条控件
#include <QTextEdit> //文本编辑框控件
#include <QFont>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800,600);
    //定义最大化按钮
    auto btnMax=new QPushButton("最大化",this);
    //建立连接
    connect(btnMax,&QPushButton::clicked,[=](){
        this->showMaximized();
    });

    //定义最小化按钮
    auto btnMin=new QPushButton("最小化",this);
    btnMin->move(100,0);
    //建立连接
    connect(btnMin,&QPushButton::clicked,[=](){
        this->showMinimized();
    });

    //定义正常化按钮
    auto btnNormal=new QPushButton("正常",this);
    btnNormal->move(200,0);
    //建立连接
    connect(btnNormal,&QPushButton::clicked,[=](){
        this->showNormal();
    });

    //设置一个按钮
    //鼠标按下 打印 被打了
    //鼠标抬起 打印 被打死了
    auto btn=new QPushButton("老鼠",this);
    btn->setGeometry(100,200,100,50);
    connect(btn,&QPushButton::pressed,[=](){
        qDebug()<<"be hitten";
    });
    connect(btn,&QPushButton::released,[=](){
        qDebug()<<"be hitten to death";
    });

    //指针指向lambda函数 来传参
//    int num1=1,num2=2;
//    void (*pfun)(int&)=[](int&n)->void{
//        n=250;
//    };
//    pfun(num1);
//    qDebug()<<num1;

    //常用控件
    //文字控件
    QLabel* label=new QLabel("今天天气如何",this);
    label->move(0,100);
//    label->setText("今天天气如何");
    label->setFont(QFont("楷体",20,10,1));

    //滑动条控件
    QSlider* slider=new QSlider(this);
    slider->move(400,100);
    slider->setValue(50);
    //通过滑动 滑动条改变字体大小 这个valueChanged里面可以传入参数 与后面的lambda表达式进行连接就可以实现参数的传递
    connect(slider,&QSlider::valueChanged,label,[=](int _value){
        label->setFont(QFont("楷体",_value,10,1));
    });

    //进度条
    QProgressBar* probar=new QProgressBar(this);
    probar->move(0,300);
    probar->resize(this->width(),20);
    probar->setValue(50);
    probar->setMaximum(99);
    //通过滑动 滑动条改变进度条
    connect(slider,&QSlider::valueChanged,probar,[=](int _value){
        probar->setValue(_value);
    });

    //文本编辑框
    QTextEdit *textedit=new QTextEdit(this);
    textedit->move(0,300);
    textedit->resize(200,100);
    textedit->setFontUnderline(true);
    textedit->setFontPointSize(qreal(35.5));
    textedit->setText("hello");//这个需要先设置文字的属性再设置文字内容才可以生效！！！
    //练习 编辑文本编辑框中的文字将其显示在label框架上
    connect(textedit,&QTextEdit::textChanged,label,[=](){
        QString text=textedit->toPlainText();//这个函数用来查询文本编辑框的内容
        label->setText(text);
    });

    //老版本信号槽写法 QT4以前
    auto btnold=new QPushButton("老版本测试按钮",this);
    btnold->move(300,0);
    connect(btnold,SIGNAL(clicked()),this,SLOT(showMaximized()));
}

Widget::~Widget()
{
}

