#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
#include <QMediaPlayer>

MyButton::MyButton(QWidget* parent) : QPushButton(parent) {
    __init__();
}

void MyButton::__init__() {
    this->_type = blank;
    this->_isMine = false;
    this->_isFlagMax = false;
}

//重载鼠标点击事件
void MyButton::mousePressEvent(QMouseEvent* e) {
    //先写右键 右键插旗子
    if(e->button() == Qt::RightButton) {
        switch (this->_type) {
            case blank:
                if(!this->_isFlagMax) {//这里需要保证旗帜数量不是最大才可以
                    this->setStyleSheet("background-image:url(:/res/flag.gif);");
                    this->_type = flag;
                    //更新mineLcd的数据
                    emit this->flag_changed(true);//true表示出现flag减少数字
                }
                break;
            case flag:
                this->setStyleSheet("background-image:url(:/res/ask.gif);");
                this->_type = ask;
                emit this->flag_changed(false);//true表示flag小时增加数字
                break;
            case ask:
                this->setStyleSheet("background-image:url(:/res/blank.gif);");
                this->_type = blank;
                break;
            default:
                break;
        }
    } else if(e->button() == Qt::LeftButton) {
        //如果点击的是旗帜那么增加旗帜
        if(this->_type == flag)emit this->flag_changed(false);
        //踩到雷或者踩到空白地方
        if(this->_isMine == true) {
            this->setStyleSheet("background-image:url(:/res/error.gif);");
            this->setEnabled(false);
            //触发游戏结束
            emit gameisover();
        } else {
            //如果该处minearound为0,把他周围的几个全翻开,然后再查看有没有空白,如果没有空白,则停止
            emit this->isClicked();//这个信号后面的处理当中包含了禁用按钮
        }
    }
}
