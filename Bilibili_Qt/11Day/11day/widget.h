#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

protected:
    void timerEvent(QTimerEvent* e);//重载定时器更新函数
    void paintEvent(QPaintEvent* );//重载画家绘画函数

    //做两个timerid
    int _timerId1;
    int _timerId2;

    //定时器对象
    QTimer* _timer;

    //定义画家对象
    QPainter* _painter;

private:
    Ui::Widget* ui;
};
#endif // WIDGET_H
