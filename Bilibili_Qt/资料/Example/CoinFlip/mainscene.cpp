#include "mainscene.h"
#include "./ui_mainscene.h"
#include <QPainter>
#include <QAction>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景
    //设置固定大小
    setFixedSize(480, 882);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit, &QAction::triggered, [=]()
            { this->close(); });

    //开始按钮
    MyPushButton *startbtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width() * 0.5 - startbtn->width() * 0.5, this->height() * 0.75);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=]() { //延时返回
        QTimer::singleShot(500, this, [=]()
                           {
        //将选择关卡的场景隐藏掉 
        chooseScene->hide();
        //重新显示主场景 
        this->show(); });
    });

    connect(startbtn, &QPushButton::clicked, [=]()
            {
        //做一个弹起特效
        startbtn->zoom(1);

        //延时进入
        QTimer::singleShot(500, this, [=]()
                           {
        //进入到选择关卡的场景中
        //自身隐藏并且显示选择关卡场景
        this->hide();
        chooseScene->show(); }); });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家
    QPainter painter(this);
    QPixmap pix;
    //加载对象
    pix.load(":/res/PlayLevelSceneBg.png");
    //开始画
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    //缩放比例
    pix = pix.scaled(pix.width() * 0.8, pix.height() * 0.8);
    painter.drawPixmap(10, 30, pix);
}
