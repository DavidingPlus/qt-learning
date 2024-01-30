#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>
#include <QMouseEvent>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

//    this->setMouseTracking(true);//这个可以设置默认就进行追踪鼠标指针 不按鼠标也可以追踪
}

Widget::~Widget() {
    delete ui;
}

//事件重写
void Widget::keyPressEvent(QKeyEvent* e) { //按下键盘事件
    switch (e->key()) {
        case Qt::Key_W:
            qDebug() << "w";
            break;
        case Qt::Key_S:
            qDebug() << "s";
            break;
        case Qt::Key_A:
            qDebug() << "a";
            break;
        case Qt::Key_D:
            qDebug() << "d";
            break;
        default:
            break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent* e) { //键盘抬起事件
    switch (e->key()) {
        case Qt::Key_Up:
            qDebug() << "up";
            break;
        case Qt::Key_Down:
            qDebug() << "down";
            break;
        case Qt::Key_Left:
            qDebug() << "left";
            break;
        case Qt::Key_Right:
            qDebug() << "right";
            break;
        default:
            break;
    }
}


void Widget::mouseDoubleClickEvent(QMouseEvent* e) { //鼠标双击事件
//    qDebug() << "double clicked";
    if(e->button() == Qt::LeftButton)qDebug() << "left button" << e->pos() << e->globalPosition(); //pos() 相当于本物体左上角的位置 globalpos() 相当于屏幕窗口左上角的位置
    else if(e->button() == Qt::RightButton)qDebug() << "right button";
}

//默认是点击了鼠标之后会继续响应鼠标的移动
void Widget::mouseMoveEvent(QMouseEvent* e) { //鼠标移动事件
    qDebug() << "Moved";
}


void Widget::mousePressEvent(QMouseEvent* e) { //鼠标按下事件
    if(e->button() == Qt::MiddleButton)
        qDebug() << "middle button pressed";
    else if(e->button() == Qt::LeftButton)
        qDebug() << "left button pressed";
    else if(e->button() == Qt::RightButton)
        qDebug() << "right button pressed";
}

void Widget::mouseReleaseEvent(QMouseEvent* e) { //鼠标释放事件
    if(e->button() == Qt::MiddleButton)
        qDebug() << "middle button released";
    else if(e->button() == Qt::LeftButton)
        qDebug() << "left button released";
    else if(e->button() == Qt::RightButton)
        qDebug() << "right button released";
}

void Widget::wheelEvent(QWheelEvent* e) { //鼠标滚轮事件
    qDebug() << "wheeling";
}

//void Widget::enterEvent(QEvent* e) { //鼠标进入事件
//    qDebug() << "you entered";
//}

//void Widget::leaveEvent(QEvent* e) { //鼠标离开事件
//    qDebug() << "you left";
//}
