#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>

static bool Is_Open = false;

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    //  创建一个新窗口对象
    QPushButton *wid = new QPushButton;
    wid->setWindowTitle("新窗口");
    wid->resize(600, 400);

    // if (ui->pushButton->text() == "OPEN" && !Is_Open) //窗口没打开
    connect(ui->pushButton, &QPushButton::clicked, wid, [=]()
            { wid->show(); ui->pushButton->setText("CLOSE");Is_Open=true; });
}

Widget::~Widget()
{
    delete ui;
}
