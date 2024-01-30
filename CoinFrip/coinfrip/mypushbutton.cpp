#include "mypushbutton.h"
#include<QDebug>
#include<QPainter>
#include<QPropertyAnimation>
#include<QRect>
//MyPushButton::MyPushButton(QPushButton *parent)
//    : QWidget{parent}
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    //返回bool值来判断是否加载成功
    bool ret=pix.load(this->normalImgPath);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }

    //设置固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//弹跳特效
void MyPushButton::zoom(bool up_down)//1代表向下跳  0代表向上跳
{
    //创建动画的对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //向上跳和向下跳的开始结束位置不同
    int offset=10;
    if(up_down){
        //设置起始位置
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //结束位置
        animation->setEndValue(QRect(this->x(),this->y()+offset,this->width(),this->height()));
    }
    else{
        //设置起始位置
        animation->setStartValue(QRect(this->x(),this->y()+offset,this->width(),this->height()));
        //结束位置
        animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    }
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

//按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")//传入的图片不为空说明需要有按下的状态
    {
        QPixmap pix;
        //返回bool值来判断是否加载成功
        bool ret=pix.load(this->pressImgPath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        //设置固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他的内容
    return QPushButton::mousePressEvent(e);
}

//释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")//传入的图片不为空说明需要有按下的状态 切换成初始图片
    {
        QPixmap pix;
        //返回bool值来判断是否加载成功
        bool ret=pix.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        //设置固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他的内容
    return QPushButton::mouseReleaseEvent(e);
}
