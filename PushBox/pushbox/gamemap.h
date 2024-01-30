#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <QWidget>
#include <QPainter>

enum MapElement {
    //这个枚举默认是有排序的 0 1 2 3 4
    Road,
    Wall,
    Box,
    Point,
    Inpoint
};

class GameMap : public QObject {
    Q_OBJECT
public:
    explicit GameMap(QObject* parent = nullptr);
    ~GameMap();

    void memClear();
    void Paint(QPainter* painter, QPoint pos = QPoint(0, 0));

    bool __init__(QString path);

    int _row;
    int _col;
    int** _pmap;//用于开辟二维数组 2D地图

signals:

};

#endif // GAMEMAP_H
