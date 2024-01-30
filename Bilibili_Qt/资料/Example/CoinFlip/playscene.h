#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    // explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex; //内部成员属性 记录所选关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
