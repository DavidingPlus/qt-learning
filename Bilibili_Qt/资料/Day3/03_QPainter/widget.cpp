#include "widget.h"
#include "./ui_widget.h"
#include <QPainter> //画家类
#include <QPen>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    //声明定时器
    QTimer *timer = new QTimer(this);
    //当第一次点击激活定时器
    connect(ui->btn_move, &QPushButton::clicked, [=]()
            { timer->start(500); });

    //将定时器和点击连接在一起
    connect(timer, &QTimer::timeout, [=]()
            { ui->btn_move->clicked(true); });

    //点击移动按钮,移动图片 使用定时器让他自动播放
    connect(ui->btn_move, &QPushButton::clicked, [=]()
            {  posX += 20;
             //如果超出屏幕 从0开始
             if(posX>this->width()) posX=0;
            //如果要手动调用绘图事件 用update更新
        update(); });

    //点击暂停按钮让其暂停
    connect(ui->btn_stop, &QPushButton::clicked, [=]()
            { timer->stop(); });

    //点击重置按钮将其重置
    connect(ui->btn_restart, &QPushButton::clicked, [=]()
            { posX=0;update();timer->stop(); });
}

void Widget::paintEvent(QPaintEvent *)
{
    // //实例化画家对象
    // QPainter painter(this); // this 指定的是绘图设备

    // //设置画笔
    // QPen pen(QColor(255, 0, 0));
    // //设置画笔宽度
    // pen.setWidth(3);
    // //设置画笔风格
    // pen.setStyle(Qt::DotLine);
    // //让画家使用这个笔
    // painter.setPen(pen);

    // //设置画刷
    // QBrush brush(Qt::cyan);
    // //设置画刷风格
    // brush.setStyle(Qt::Dense7Pattern);
    // //让画家使用这个画刷
    // painter.setBrush(brush);

    // //画线
    // painter.drawLine(QPoint(0, 0), QPoint(200, 200));
    // //画图
    // painter.drawEllipse(QPoint(200, 200), 100, 100);
    // //画矩形
    // painter.drawRect(QRect(40, 40, 100, 100));
    // //画文字
    // painter.drawText(QRect(200, 400, 200, 100), "好好学习,天天向上");

    //             高级设置                //
    // QPainter painter(this);
    // painter.drawEllipse(QPoint(200, 100), 100, 100);
    // //设置 抗锯齿能力 效率较低
    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.drawEllipse(QPoint(400, 100), 100, 100);

    //画矩形
    // painter.drawRect(QRect(40, 40, 100, 100));
    // //移动画家 让画家画画的起始位置移动多少位置,不是移动到多少位置!!!!
    // painter.translate(200, 0);
    // //保存画家状态
    // painter.save();

    // painter.drawRect(QRect(40, 40, 100, 100));
    // painter.translate(200, 0);

    // //还原画家保存状态
    // painter.restore();
    // painter.drawRect(QRect(40, 40, 100, 100));

    //               利用画家画资源图片               //
    QPainter painter(this);

    painter.drawPixmap(posX, 0, QPixmap(":/Image/Luffy.png"));
}

Widget::~Widget()
{
    delete ui;
}
