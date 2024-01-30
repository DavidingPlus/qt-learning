#include "widget.h"
#include <QPushButton>
#include <QFont>
#include "student.h"
#include "button.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Hello QT");
    this->resize(800,400);//设置窗口大小
    this->setFixedSize(800,400);

    //创建按钮
    QPushButton* btn=new QPushButton(this);
    btn->setText("开始游戏");
    //设置字体
    QFont font("楷体",20,10,1);
    btn->setFont(font);
    btn->move(100,100);

    //了解
    //设置背景颜色background-color hover鼠标悬浮 pressed鼠标按下
    btn->setStyleSheet("QPushButton{background-color:red;}\
                        QPushButton:hover{background-color:green;}\
                        QPushButton:pressed{background-color:yellow;}");

//    需要把stu放到对象树里面使得其自动被析构释放
//    Student如果后面创建那么会挡住前面的按钮导致没办法操作所以注释掉 因为Student继承了QWidget空窗口类
//    为了防止出现问题继承QObject类 什么都为空就可以了 就不会挡住了!!!
    Student* stu=new Student;
    stu->setParent(this);//设置父亲为本窗口 当本窗口释放时，会释放孩子

    //自定义button
    Button* btn2=new Button(this);
    btn2->setText("自定义按钮");

    Button* btn3=new Button(this,"自定义按钮2");
    btn3->move(80,30);
}

Widget::~Widget()
{
}

