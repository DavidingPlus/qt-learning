#include "button.h"
#include <QPushButton>

Button::Button(QWidget *parent)
    : QPushButton{parent}
{

}

Button::Button(QWidget* parent,QString name)
{
    this->setParent(parent);
    this->setText(name);
}

Button::~Button()
{
    qDebug()<<"custom button released";
}
