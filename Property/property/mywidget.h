#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT

     Q_PROPERTY(int age READ getAge WRITE setAge)

public:
    explicit MyWidget(QWidget *parent = nullptr);

    int getAge();

    void setAge(int age);

signals:

private:
    int m_age = 0;
};

#endif // MYWIDGET_H
