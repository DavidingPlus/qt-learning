#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>
#include <QDebug>

// Teacher 类 老师类
// Student 类 学生类
//下课后,老师会出发信号,饿了,学生响应信号,请客吃饭

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建一个老师对象
    this->zt = new Teacher(this);
    //创建一个学生对象
    this->st = new Student(this);

    // //老师饿了 学生请客的连接
    // connect(zt, &Teacher::hungry, st, &Student::treat);

    // //调用下课函数来触发老师饿了 先做好连接 再触发条件
    // classIsOver();

    //连接带参数的 信号和槽
    //函数指针 -> 函数地址 注意指明是作用域下的函数指针!!!!!
    void (Teacher::*teacherSingal)(QString) = &Teacher::hungry;
    void (Student::*studentSingal)(QString) = &Student::treat;
    connect(zt, teacherSingal, st, studentSingal);
    // classIsOver();

    //点击一个下课的按钮,再触发下课
    QPushButton *btn1 = new QPushButton("下课1", this);
    //重置窗口大小
    this->resize(600, 400);
    //点击按钮 触发下课
    connect(btn1, &QPushButton::clicked, this, &Widget::classIsOver);

    //分割,上面是宫保鸡丁,下面是无参构造

    //无参信号和槽连接
    void (Teacher::*teacherSingal2)(void) = &Teacher::hungry;
    void (Student::*studentSingal2)(void) = &Student::treat;
    connect(zt, teacherSingal2, st, studentSingal2);

    //点击一个另一个下课的按钮,再触发下课
    QPushButton *btn2 = new QPushButton("下课2", this);
    btn2->move(100, 0);

    //信号连接信号
    connect(btn2, &QPushButton::clicked, zt, teacherSingal2);

    //断开信号
    // disconnect(zt, teacherSingal2, st, studentSingal2);

    //扩展
    // 1.信号是可以连接信号
    // 2.一个信号可以连接多个槽函数
    // 3.多个信号可以连接同一个槽函数
    // 4.信号和槽函数的参数 必须 类型一一对应!!!!!
    // 5.信号和槽的参数个数 是不是要一致? 信号的参数个数可以多余槽函数的参数个数

    // Qt4版本以前信号和槽的连接方式
    //利用Qt4信号槽 连接无参版本
    // Qt4版本 底层SIGNAL("hungry()")
    // connect(zt, SIGNAL(hungry()), st, SLOT(treat()));
    // connect(zt, SIGNAL(hungry(QString)), st, SLOT(treat(QString)));
    // Qt4版本优点:参数直观 缺点:类型不做检测 编译器不会检测参数类型
    // Qt5以上支持 Qt4版本的写法 反之不支持

    // lambda表达式
    // = 号值传递 & 引用传递
    // QPushButton *btn2 = new QPushButton;
    // [btn1]()
    // {
    //     btn1->setText("aaaa");
    //     // btn2->setText("bbb");//btn2看不到
    // }();

    // mutable 修饰 值传递变量 ，可以修改拷贝出的数据，改变不了本体
    // QPushButton *myBtn = new QPushButton(this);
    // QPushButton *myBtn2 = new QPushButton(this);
    // myBtn2->move(100, 100);
    // int m = 10;

    // connect(myBtn, &QPushButton::clicked, this, [m]() mutable
    //         { m = 100 + 10; qDebug() << m; }); //默认是只读状态 mutable 加上后可以修改 直参不会影响到本体

    // connect(myBtn2, &QPushButton::clicked, this, [=]()
    //         { qDebug() << m; });

    // qDebug() << m;

    // int ret = []() -> int
    // { return 1000; }();
    // qDebug() << "ret = " << ret;

    //利用 lambda 表达式 实现点击按钮 关闭窗口
    // lambda 表达式 [](){} 匿名函数
    // []标识符 ()参数 {}实现体
    QPushButton *btn3 = new QPushButton("关闭", this);
    btn3->move(200, 0);
    connect(btn3, &QPushButton::clicked, this, [=]() { // btn3->setText("aaaa");
        this->close();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::classIsOver()
{
    //下课函数,调用后出发老师饿了的信号
    // emit zt->hungry();
    emit zt->hungry("宫保鸡丁");
}
