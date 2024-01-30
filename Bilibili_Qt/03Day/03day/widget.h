#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "boss.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Boss* boss;

    //死亡信号 槽函数
    void BossDeadBroadCast();
};
#endif // WIDGET_H
