#include "widget.h"
#include "boss.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(600,500);
    //观察者 boss 处理函数 死亡打印
    //被观察者 按钮 信号点击
    //按钮点击 处理boss死亡

//    auto boss1=new Boss("boss1",2000,this);
//    auto boss2=new Boss("boss2",1500,this);
//    this->boss=new Boss("bigBoss",10000,this);
//    auto btn=new QPushButton("击杀",this);
//    //点击按钮击杀boss
//    connect(btn,&QPushButton::clicked,boss1,&Boss::BossDead);

    //点击按钮发送boss死亡信号
    QPushButton* btn2=new QPushButton("播放死亡信号",this);
    connect(btn2,&QPushButton::clicked,this,&Widget::BossDeadBroadCast);//点击触发信号广播 除法boss死亡信号
//    connect(this->boss,&Boss::DeadSingal,this->boss,&Boss::BossDeadSlot);//死亡信号触发后 死亡槽函数处理
}

Widget::~Widget()
{
}

void Widget::BossDeadBroadCast()
{
    //触发死亡信号逻辑
    qDebug()<<"death reported";
//    emit this->boss->DeadSingal();//此处为触发信号
}
