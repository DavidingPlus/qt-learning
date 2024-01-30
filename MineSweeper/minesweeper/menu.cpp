#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Menu) {
    ui->setupUi(this);

    this->setFixedSize(500, 500);

    //radioBtn设置 同时只能选中一个!!!!
    //默认选中 简单
    ui->easyRadioBtn->setChecked(true);
}

Menu::~Menu() {
    delete ui;
}

void Menu::on_startBtn_clicked() {
    this->mainwindow = new MainWindow(this, this->_gameLevel);
    this->hide();
    this->mainwindow->show();
}

void Menu::on_exitBtn_clicked() {
    exit(0);
}

//设置难度
void Menu::on_easyRadioBtn_clicked() {
    this->_gameLevel = easy;
}

void Menu::on_middleRadioBtn_clicked() {
    this->_gameLevel = middle;
}

void Menu::on_hardRadioBtn_clicked() {
    this->_gameLevel = hard;
}
