#ifndef MYWIDGET2_H
#define MYWIDGET2_H

#include <QWidget>

class MyWidget2 : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int age MEMBER m_age)

public:
    explicit MyWidget2(QWidget *parent = nullptr);

signals:

private:
    int m_age = 0;
};

#endif // MYWIDGET2_H
