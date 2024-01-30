#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>  // 鼠标事件

#include <QLabel>       // 标签，放在主窗体的状态栏中
#include <QPoint>       // 点，用来表达鼠标的位置

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // 复写鼠标事件虚函数
    void mousePressEvent(QMouseEvent *e);       //按压事件
    void mouseReleaseEvent(QMouseEvent *e);     //松开事件
    void mouseMoveEvent(QMouseEvent *e);        //移动事件
    void mouseDoubleClickEvent(QMouseEvent *e); //双击事件

private:
    QLabel *mouseState;
    QLabel *mousePosition;

    // 保存光标在刚刚按下的时候，在窗口内部的相对位置
    // 结合板书，即矢量AB
    QPoint beginPos;
};

#endif // MAINWINDOW_H
