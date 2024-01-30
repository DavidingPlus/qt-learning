#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {

}

void MyLabel::mouseDoubleClickEvent(QMouseEvent*) {
    emit this->isDoubleclicked();
}
