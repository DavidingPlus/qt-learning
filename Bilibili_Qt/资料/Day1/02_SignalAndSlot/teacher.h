#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    //自定义信号 写到 signals 下
    //返回值 void 只需要声明 不需要实现
    //可以有参数 可以发生重载
    void hungry();

    void hungry(QString foodName);
};

#endif // TEACHER_H
