#include "widget.h"
#include "./ui_widget.h"
#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
        ui->setupUi(this);

        //栈控件使用

        //设置默认定位到scrollArea
        ui->stackedWidget->setCurrentIndex(0);

        // scrollArea按钮
        connect(ui->btn_scrollArea, &QPushButton::clicked, [=]()
                { ui->stackedWidget->setCurrentIndex(0); });

        // toolbox按钮
        connect(ui->btn_toolbox, &QPushButton::clicked, [=]()
                { ui->stackedWidget->setCurrentIndex(2); });

        // tab Widget按钮
        connect(ui->btn_tabwidget, &QPushButton::clicked, [=]()
                { ui->stackedWidget->setCurrentIndex(1); });

        //下拉框
        ui->comboBox->addItems(QStringList() << "奔驰"
                                             << "宝马"
                                             << "拖拉机");
        //点击按钮选中拖拉机
        connect(ui->btn_select, &QPushButton::clicked, [=]()
                { 
                // ui->comboBox->setCurrentIndex(2);
                ui->comboBox->setCurrentText("拖拉机"); });

        //利用QLabel显示图片
        ui->lbl_Image->setPixmap(QPixmap(":/Image/butterfly.png"));

        //利用QLabel显示 gif动态图片
        QMovie *movie = new QMovie(":/Image/mario.gif");
        ui->lbl_movie->setMovie(movie);
        //播放动图
        movie->start();
}

Widget::~Widget()
{
        delete ui;
}
