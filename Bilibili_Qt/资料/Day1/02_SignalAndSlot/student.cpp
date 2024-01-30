#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{
}

void Student::treat()
{
    qDebug() << "请老师吃饭";
}

void Student::treat(QString foodName)
{
    // QString -> char * 就不会打印出来双引号了!!!
    //先转成 QByteArray (.toUtf8) 再转成 char *
    qDebug() << "请老师吃饭,老师要吃: " << foodName.toUtf8().data();
}