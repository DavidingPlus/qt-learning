#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int level);

    int levelIndex; // 记录所选关卡

    // 重写paintEvent事件
    void paintEvent(QPaintEvent *);

    // 二维数组维护每关的具体数据
    int gameArray[4][4];

    // 维护硬币
    MyCoin *coinBtn[4][4];

    // 是否胜利的标志
    bool is_Win = false;
signals:
    void playSceneBack();
};

#endif // PLAYSCENE_H
