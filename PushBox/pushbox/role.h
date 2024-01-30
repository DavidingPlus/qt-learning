#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QPoint>
#include <QImage>

class Role : public QObject {
    Q_OBJECT
public:
    explicit Role(QObject* parent = nullptr);

    void __init__();

    //对应在地图的映射
    QPoint _rolepos;
    //对应在数组当中的映射
    int _roleRow;//人物在数组当中的横坐标
    int _roleCol;//人物在数组当中的纵坐标

    void Move(int drow, int dcol);//移动函数
    void Paint(QPainter* painter, QPoint pos); //绘制自己函数

    //人物图片
    QImage _img;

signals:

};

#endif // ROLE_H
