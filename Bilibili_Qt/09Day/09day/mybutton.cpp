#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget* parent)
    : QToolButton{parent} {

}

void MyButton::mouseMoveEvent(QMouseEvent* e) {
    //求鼠标移动量=鼠标新位置 - 鼠标点击位置
    QPoint deltaMove = e->pos() - this->mousePressPos; //移动量
    //求窗口位置= 原位置 + 移动量
    this->move(this->pos() + deltaMove);
}

void MyButton::mousePressEvent(QMouseEvent* e) {
    this->mousePressPos = e->pos();
    qDebug() << "mouse pos" << this->mousePressPos;
}
