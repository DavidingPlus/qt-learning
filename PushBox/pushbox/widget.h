#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gamemap.h"
#include "role.h"
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent*);
    void drawMap(int x = 0, int y = 0); //画地图
    void keyPressEvent(QKeyEvent* e);//键盘按键事件
    void Move_withoutCollsion(int drow, int dcol); //逻辑碰撞检测函数

private slots:
    void on_exitBtn_clicked();

    void on_restartBtn_clicked();

private:
    Ui::Widget* ui;

    //定义地图
    GameMap* _Map;

    //定义画图的画家
    QPainter* _MapPainter;

    //定义角色
    Role* _role;

    //定义游戏更新定时器
    QTimer* _gameTimer;

    //是否胜利的元素来禁用胜利之后的按键移动
    bool _is_win = false;

    //判断是否胜利
    bool is_Win();

    //定义开始菜单对象
    Menu* _menu;

    //定义地图路径
    QString _gamePath = NULL;

    //游戏胜利动画函数
    void gameWinAnimation();

    //音乐播放函数
    void soundPlay(QString path);
};
#endif // WIDGET_H
