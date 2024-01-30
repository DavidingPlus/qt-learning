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

    void keyPressEvent(QKeyEvent* e);//按下键盘事件
    void keyReleaseEvent(QKeyEvent* e);//键盘抬起事件

    //给某个界面写的进入离开事件
//    void enterEvent(QEvent* e);//进入事件
//    void leaveEvent(QEvent* e);//离开事件

    void mouseDoubleClickEvent(QMouseEvent* e);//鼠标双击事件

    void mouseMoveEvent(QMouseEvent* e);//鼠标移动事件
    void mousePressEvent(QMouseEvent* e);//鼠标按下事件
    void mouseReleaseEvent(QMouseEvent* e);//鼠标释放事件

    void wheelEvent(QWheelEvent* e);//鼠标滚轮事件


private:
    Ui::Widget* ui;
};
#endif // WIDGET_H
