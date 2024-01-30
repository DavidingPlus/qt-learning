#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mybutton.h"
#include <QMediaPlayer>

#define MAXSIZE 99

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr, int level = 0); //默认为0是简单
    ~MainWindow();

    void __init__(int level);//传递难度参数

    void createBtns();//创建按钮

    void timerRun();//定时器启动函数

    void createMines();//生成雷的坐标

    void dealFlag();//处理flag信号

    int generateRandomNumber(int max);//生成随机数来埋雷

    void _init_Mines();//初始化雷的坐标

    void bindMines();//绑定雷 将雷的按钮修改为true

    void reStartGame();//重新开始游戏

    void _initAllBlanks();//初始化所有的按钮下标,查询他周围有几个雷

    void dealBtns(int i, int j); //处理鼠标被点击之后

    void flagput_release(int i, int j, bool ok); //旗帜放置正确

    void GameWinner();//游戏胜利

    void playVideo(QString url);//播放音乐
signals:
    void FlagMaxed(bool ok);//旗帜数量达到最大的信号

private slots:
    void on_smileBtn_clicked();

private:
    Ui::MainWindow* ui;

    QTimer* _timer;//定时器

    int _Btnx;
    int _Btny;//按钮的 x * y 布局
    MyButton* _btns[MAXSIZE][MAXSIZE]; //按钮簇 Btnx*Btny 用二位数组来表示

    int _mineNum; //地雷数
    int _mineRemains; //被正确的旗帜覆盖之后的雷个数 为0则触发胜利
    QList<int* > _mines; //用二维数组来埋雷
    int _flagNum; //旗帜数量
};
#endif // MAINWINDOW_H
