#ifndef BOSS_H
#define BOSS_H

#include <QWidget>

class Boss : public QWidget
{
    Q_OBJECT
public:
    //explicit 关键字 修饰函数 参数 无法自动转换类型 只能传入基类类型 不能传入派生类类型
    explicit Boss(QString name,int exp,QWidget *parent = nullptr);

    int exp;//经验值

    QString name;//名字

signals://自定义信号定义
    void DeadSingal();//boss死亡信号

public slots://槽函数定义
    void BossDeadSlot();//boss 死亡槽函数

};

#endif // BOSS_H
