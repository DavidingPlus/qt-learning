#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪状态
    setMouseTracking(true);
}

//鼠标进入事件
void myLabel::enterEvent(QEvent *event)
{
    qDebug() << "鼠标进入了";
}

//鼠标离开事件
void myLabel::leaveEvent(QEvent *event)
{
    qDebug() << "鼠标离开了";
}

//鼠标按下
void myLabel::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键按下 提示信息
    if (event->button() == Qt::LeftButton)
    {
        QString str = QString("鼠标按下了 x=%1  y=%2  globalX = %3  globalY = %4").arg(event->x()).arg(event->y()).arg(event->globalX()).arg(event->globalY()); //链式编程!!!
        qDebug() << str;
    }
}

//鼠标释放
void myLabel::mouseReleaseEvent(QMouseEvent *event)
{
    //当鼠标左键释放 提示信息
    if (event->button() == Qt::LeftButton)
    {
        QString str = QString("鼠标释放了 x=%1  y=%2  globalX = %3  globalY = %4").arg(event->x()).arg(event->y()).arg(event->globalX()).arg(event->globalY()); //链式编程!!!
        qDebug() << str;
    }
}

//鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *event)
{
    //当鼠标左键移动 提示信息
    // if (event->buttons() & Qt::LeftButton) // buttons() 当中存了一段时间内的按键 &(按位与) 作用判断每一个是否为左键 左键则通过!!!
    // {
    QString str = QString("鼠标移动了 x=%1  y=%2  globalX = %3  globalY = %4").arg(event->x()).arg(event->y()).arg(event->globalX()).arg(event->globalY()); //链式编程!!!
    qDebug() << str;
    // }
}

//事件分发器拦截
bool myLabel::event(QEvent *event)
{
    //如果是鼠标按下 在event事件中拦截操作
    if (event->type() == QEvent::MouseButtonPress)
    {
        //静态类型转换!!!
        QMouseEvent *ev = static_cast<QMouseEvent *>(event);
        QString str = QString("Event函数中,鼠标按下了 x=%1  y=%2  globalX = %3  globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY()); //链式编程!!!
        qDebug() << str;

        return true; // true代表用户自己处理这个事件,不向下分发
    }

    //其他事件 交给父类处理 默认处理
    return QLabel::event(event);
}