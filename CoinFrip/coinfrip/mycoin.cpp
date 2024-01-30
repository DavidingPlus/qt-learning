#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QPushButton *parent)
//    : QWidget{parent}
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret){
        qDebug()<<"picture loaded failed";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    this->timer1=new QTimer(this);
    this->timer2=new QTimer(this);

    //连接写到上面 做一次信号槽链接就可以了 监听正面翻反面的信号并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断如果翻完了，将min 重置为 1
        if(this->min>this->max){
            this->min=1;
            this->is_Animation=false;//动画做完了
            timer1->stop();
        }
    });

    //反面翻正面
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%8.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断如果翻完了，将min 重置为 1
        if(this->max<this->min){
            this->max=8;
            this->is_Animation=false;//动画做完了
            timer2->stop();
        }
    });
}

//改变标志的方法
void MyCoin::changeFlag()
{
    //如果是这正面 翻成反面
    if(this->flag){
        this->timer1->start(30);
        this->is_Animation=true;//开始动画
        this->flag=false;
    }
    //反面翻成正面
    else{
        this->timer2->start(30);
        this->is_Animation=true;
        this->flag=true;
    }
}

//重写按下
void MyCoin::mousePressEvent(QMouseEvent*e)
{
    if(this->is_Animation||this->is_Win){
        //如果正在做动画 或者胜利了
        //则在做动画的过程中点击是没有作用的
        return;
    }
    return QPushButton::mousePressEvent(e);
}
