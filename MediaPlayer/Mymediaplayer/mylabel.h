#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel {
    Q_OBJECT
public:
    explicit MyLabel(QWidget* parent = nullptr);

    //重写鼠标双击事件
    void mouseDoubleClickEvent(QMouseEvent*);

signals:
    void isDoubleclicked();

};

#endif // MYLABEL_H
