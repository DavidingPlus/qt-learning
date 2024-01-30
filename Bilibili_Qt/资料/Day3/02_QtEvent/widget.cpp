#include "widget.h"
#include "./ui_widget.h"
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器
    id1 = startTimer(1000); //参数1 间隔 单位 毫秒
    id2 = startTimer(2000);

    //定时器第二种方式
    QTimer *timer = new QTimer(this);
    //启动定时器
    timer->start(500);

    connect(timer, &QTimer::timeout, [=]()
            {
                static size_t num3 = 1;
                // label_4 每隔0.5秒 +1
                ui->label_4->setText(QString::number(num3++)); });

    //点击暂停或者开始按钮实现停止或者启动定时器
    connect(ui->btn_stop, &QPushButton::clicked, [=]()
            { timer->stop(); });
    connect(ui->btn_start, &QPushButton::clicked, [=]()
            { timer->start(500); });

    //给lable 安装事件过滤器
    //步骤1 安装事件过滤器
    ui->label->installEventFilter(this);
}

//步骤2 重写 eventfilter事件
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *ev = static_cast<QMouseEvent *>(event);
        QString str = QString("事件过滤器中,鼠标按下了 x=%1  y=%2  globalX = %3  globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY()); //链式编程!!!
        qDebug() << str;

        return true; // true代表用户自己处理这个事件,不向下分发
    }

    //其他事件 交给父类处理 默认处理
    return QWidget::eventFilter(obj, event);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    static size_t num1 = 1;
    static size_t num2 = 1;
    if (event->timerId() == id1)
    {
        // label_2 每隔1秒 +1
        ui->label_2->setText(QString::number(num1++));
    }
    if (event->timerId() == id2)
        // label_3 每隔2秒 +1
        ui->label_3->setText(QString::number(num2++));
}
