#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "mainwindow.h"

enum Level
{
    easy,
    middle,
    hard
};

namespace Ui
{
    class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget* parent = nullptr);
    ~Menu();

private slots:
    void on_startBtn_clicked();

    void on_exitBtn_clicked();

    void on_easyRadioBtn_clicked();

    void on_middleRadioBtn_clicked();

    void on_hardRadioBtn_clicked();
private:
    Ui::Menu* ui;

    //主游戏栏对象
    MainWindow* mainwindow;

    //游戏难度 默认为简单
    Level _gameLevel = easy;
};

#endif // MENU_H
