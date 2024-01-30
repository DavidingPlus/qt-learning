#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

    QPixmap img(":/res/1.png");
    QIcon icon(img);
    ui->toolBtn->setIcon(icon);
    ui->toolBtn->setIconSize(img.size());
}

Widget::~Widget() {
    delete ui;
}
