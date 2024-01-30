#include "mywidget.h"
#include <QPushButton> //按钮控件的头文件
#include "mypushbutton.h"
#include <QDebug>

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "myWidget的构造调用";

    //创建一个按钮
    QPushButton *btn = new QPushButton;
    // btn->show(); // show以顶层方式弹出窗口控件,一般用于Main函数,这里按钮需要依赖于父类进行输出,不是很合适
    //让btn对象依赖于 myWidget窗口中
    btn->setParent(this);

    //显示文本
    btn->setText("第一个按钮");

    //创建第二个按钮
    QPushButton *btn2 = new QPushButton("第二个按钮", this);

    //移动btn2按钮
    btn2->move(100, 100);

    //重置整体窗口大小
    resize(900, 600);
    //重置按钮大小
    btn2->resize(150, 100);

    //设置固定窗口大小
    setFixedSize(900, 600);

    //设置窗口标题
    setWindowTitle("第一个窗口");

    //创建一个自己按钮对象 创建自己的类的时候 需要将文件添加到CMakeLists.txt当中!!!!!!!
    MyPushButton *myBtn = new MyPushButton;
    // QPushButton *myBtn = new QPushButton;
    myBtn->setParent(this); //设置到对象树中
    myBtn->setText("我自己的按钮");
    myBtn->move(200, 0);

    //需求 点击我的按钮 关闭窗口
    // connect(信号的发送者,发送的具体信号(函数的地址),信号的接收者,信号的处理(槽函数))
    // 信号 singals 槽 slots
    // 信号槽的优点: 松散耦合 信号发送端 和 接受端本身没有关联,通过 connect 连接 将两端 耦合在一起
    // connect(myBtn, &MyPushButton::clicked, this, &myWidget::close);
    connect(myBtn, &QPushButton::clicked, this, &QPushButton::close);
}

myWidget::~myWidget()
{
    qDebug() << "myWidget的析构调用";
}