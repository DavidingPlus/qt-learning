#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);

    //传入的金币路径还是银币路径 表示显示金币还是银币
    MyCoin(QString btnImg);

    //金币的属性
    int posX;
    int posY;
    bool flag; //正反面标志

    //改变标志的方法
    void changeFlag();
    //定时器
    QTimer* timer1;//正面翻反面定时器
    QTimer* timer2;//反面翻正面定时器
    int min=1;//图片序号最小值
    int max=8;//图片序号最大值

    //为了防止用户连续双点导致体验不好,加一个执行动画标志,需要一个动画结束之后才能播放另一个动画
    bool is_Animation=false;

    //重写按下
    void mousePressEvent(QMouseEvent*e);

    //判断是否胜利
    bool is_Win=false;

signals:

};

#endif // MYCOIN_H
