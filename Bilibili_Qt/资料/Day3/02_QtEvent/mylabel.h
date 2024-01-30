#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = nullptr);

    //这些事件都是父类当中写好的 我们只是运用并且重载一下实现自己的功能

    //鼠标进入事件
    virtual void enterEvent(QEvent *event);

    //鼠标离开事件
    virtual void leaveEvent(QEvent *event);

    //鼠标按下
    virtual void mouseMoveEvent(QMouseEvent *event);

    //鼠标释放
    virtual void mousePressEvent(QMouseEvent *event);

    //鼠标移动
    virtual void mouseReleaseEvent(QMouseEvent *event);

    //通过event事件分发器 拦截 鼠标按下按键
    virtual bool event(QEvent *e);

signals:
};

#endif // MYLABEL_H
