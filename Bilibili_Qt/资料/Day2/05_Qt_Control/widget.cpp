#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QListWidgetItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置单选按钮 默认选中
    ui->rBtnMan->setChecked(true);

    //选中女后打印信息
    connect(ui->rBtnWoman, &QPushButton::clicked, [=]()
            { qDebug() << "选中了女生"; });

    //多选按钮 2是选中 0是未选中
    connect(ui->cBox2, &QCheckBox::stateChanged, [=](int state)
            { qDebug() << state; });

    //利用listWidget写诗
    // QListWidgetItem *item = new QListWidgetItem("锄禾日当午");
    // //将一行的诗放到框架中
    // ui->listWidget->addItem(item);
    // item->setTextAlignment(Qt::AlignHCenter);

    // QStringList QList<QString>
    QStringList list;
    list << "锄禾日当午"
         << "汗滴禾下土"
         << "谁知盘中餐"
         << "粒粒皆辛苦";
    ui->listWidget->addItems(list);
}

Widget::~Widget()
{
    delete ui;
}
