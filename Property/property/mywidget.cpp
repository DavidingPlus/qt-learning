#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}

int MyWidget::getAge()
{
    return m_age;
}

void MyWidget::setAge(int age)
{
    m_age = age;
}
