#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//将按钮分类
enum BtnType {
    Num,//数字
    Op,//运算符
    Dot,//点
    Equal,//等于
    Clear,//清除
    Back,//退格
    Sgn,//正负号类型
    Null//空类型
};

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

private:
    Ui::Widget* ui;

    QString num1;//操作数1
    QString num2;//操作数2
    QString op;//运算符

public slots:
    void OnClicked(BtnType _type, QString _btn); //点击按钮调用槽函数
};
#endif // WIDGET_H
