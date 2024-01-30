#include "student.h"
#include <QDebug>

Student::Student()
{
}

Student::~Student()
{
    qDebug()<<"student released";
}
