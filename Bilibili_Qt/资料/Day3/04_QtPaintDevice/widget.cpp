#include "widget.h"
#include "./ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // pixmap绘图设备 专门为平台做了显示优化
    // QPixmap pix(300, 300);

    // //填充颜色
    // pix.fill(Qt::white);

    // //声明画家
    // QPainter painter(&pix);
    // painter.setPen(QPen(Qt::green));
    // painter.drawEllipse(QPoint(150, 150), 100, 100);

    //保存
    // pix.save("D:/Code/QT/Bilibili/Day3/04_QtPaintDevice/pix.png");

    // QImage 绘图设备 可以对像素进行访问
    // QImage img(300, 300, QImage::Format_RGB32);
    // img.fill(Qt::white);

    // QPainter painter(&img);
    // painter.setPen(QPen(Qt::blue));
    // painter.drawEllipse(QPoint(150, 150), 100, 100);

    // img.save("D:/Code/QT/Bilibili/Day3/04_QtPaintDevice/img.png");

    // QPicture 绘图设备 可以记录和重现绘图的指令
    QPicture pic;
    QPainter painter;
    painter.begin(&pic); //开始往pic上画

    painter.setPen(QPen(Qt::cyan));
    painter.drawEllipse(QPoint(150, 150), 100, 100);
    painter.end(); //结束画画

    //保存到磁盘
    pic.save("D:/Code/QT/Bilibili/Day3/04_QtPaintDevice/pic.zt");

    Widget::~Widget()
    {
        delete ui;
    }

    //绘图事件
    void Widget::paintEvent(QPaintEvent *)
    {
        // QPainter painter(this);

        // //利用QImage 对像素进行修改
        // QImage img;
        // img.load(":/Image/Luffy.png");

        // //修改像素点
        // for (int i = 50; i < 100; ++i)
        //     for (int j = 50; j < 100; ++j)
        //     {
        //         QRgb value = qRgb(255, 0, 0);
        //         img.setPixel(i, j, value);
        //     }

        // painter.drawImage(0, 0, img);

        //重现QPicture绘图指令
        QPainter painter(this);
        QPicture pic;
        pic.load("D:/Code/QT/Bilibili/Day3/04_QtPaintDevice/pic.zt");
        painter.drawPicture(0, 0, pic);
    }
