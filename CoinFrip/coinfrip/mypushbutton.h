#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数 参数1 正常显示的图片路径 参数2 按下后显示的图片路径
    MyPushButton(QString normalImg,QString pressImg="");

    //正常显示的图片路径
    QString normalImgPath;
    //按下后显示的图片路径
    QString pressImgPath;

    //弹跳特效
    void zoom(bool up_down);//1代表向下跳  0代表向上跳

    //重写按钮 按下 和 释放 事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
