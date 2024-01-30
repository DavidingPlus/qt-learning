#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QPainter>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

    //初始化画家对象
    this->_painter = new QPainter(this);

    //老式定期器写法
    this->_timerId1 = this->startTimer(1000); //开启定时器 每1000毫秒打印 1
    this->_timerId2 = this->startTimer(500); //开启定时器 每500毫秒打印 2

    //新式定时器写法
    this->_timer = new QTimer(this);
    this->_timer->start(2000);//开启定时器 每2000毫秒打印3
    connect(this->_timer, &QTimer::timeout, [ = ]() {
        static int num = 0;
        ui->lcdNumber_3->display(++num);
    });
}

Widget::~Widget() {
    delete ui;
}

//老式定时器写法 重载定时器更新函数
void Widget::timerEvent(QTimerEvent* e) {
    if(e->timerId() == this->_timerId1) { //判断定时器
        static int num1 = 0;
        ui->lcdNumber->display(++num1);
    } else if (e->timerId() == this->_timerId2) {
        static int num2 = 0;
        ui->lcdNumber_2->display(++num2);
    }
}

//注意重载的时候需要保证要开始也要结束!!!!!!!!! 最开始是begin() 最后面是end()!!!
void Widget::paintEvent(QPaintEvent*) {
    this->_painter->begin(this);//设置画图设备(画布)

    QPen pen(Qt::red);//创建画笔
    pen.setWidth(10);//设置宽度
    this->_painter->setPen(pen);//设置画笔

    //画直线
    this->_painter->drawLine(0, 0, 100, 100);

    this->_painter->end();//记得要结束绘画!!!
}


