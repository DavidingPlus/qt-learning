#include "boss.h"
#include <QDebug>

Boss::Boss(QString name,int exp,QWidget *parent)
    : QWidget{parent}
{
    this->exp=exp;
    this->name=name;
}


void Boss::BossDeadSlot()//boss 死亡槽函数
{
    qDebug()<<this->name<<" is dead! exp dropped "<<this->exp;
}
