#include "menu.h"
#include "ui_menu.h"
#include <QPainter>

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Menu) {
    ui->setupUi(this);

    this->setFixedSize(1024, 768);
}

Menu::~Menu() {
    delete ui;
}

void Menu::paintEvent(QPaintEvent* ) {
    this->_painter = new QPainter(this);
    this->_painter->begin(this);
    //画背景
    this->_painter->drawImage(QRect(0, 0, 1024, 768), QImage(":/res/ground.png"));
    this->_painter->end();
}

void Menu::on_startBtn_clicked() {
    emit startGame();
}

void Menu::on_closeBtn_clicked() {
    exit(0);
}
