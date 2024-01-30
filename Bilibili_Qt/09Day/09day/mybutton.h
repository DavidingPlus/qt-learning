#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QToolButton>

class MyButton : public QToolButton {
    Q_OBJECT
public:
    explicit MyButton(QWidget* parent = nullptr);

    //重写鼠标函数
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);

    QPoint mousePressPos;//鼠标点击位置

signals:

};

#endif // MYBUTTON_H
