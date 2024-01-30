#include "role.h"
#include <QPainter>

Role::Role(QObject* parent) : QObject(parent) {
    this->__init__();
}

void Role::__init__() {
    this->_roleRow = 1;
    this->_roleCol = 1;
    //图片
    this->_img = QImage(":/res/people.png");
    //显示位置
    this->_rolepos = QPoint(this->_roleCol * this-> _img.width(), this->_roleRow * this->_img.height()); //注意qt的坐标机制和数组的坐标恰好是横纵颠倒的
}

//简单移动函数
void Role::Move(int drow, int dcol) {
    this->_roleRow += drow;
    this->_roleCol += dcol;
    this->_rolepos = QPoint(this->_roleCol * this-> _img.width(), this->_roleRow * this->_img.height());//更新位置
}

void Role::Paint(QPainter* painter, QPoint pos) {
    painter->drawImage(this->_rolepos + pos, this->_img);
}
