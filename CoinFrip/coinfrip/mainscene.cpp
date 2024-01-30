#include "mainscene.h"
#include "./ui_mainscene.h"
#include <QPainter>
#include <QPushButton>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>

MainScene::MainScene(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene) {
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    this->setFixedSize(500, 700);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮的实现
    connect(ui->actionquit, &QAction::triggered, [ = ]() {
        this->close();
    });

    //开始按钮
    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move((this->width() - startBtn->width()) * 0.5, this->height() * 0.7);

    //实例化关卡选择场景
    this->chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [ = ]() {
        QTimer::singleShot(500, this, [ = ]() {
            //设置当前场景的位置
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();//将选择关卡场景隐藏掉
            this->show();//重新显示主场景
        });
    });

    //信号槽
    connect(startBtn, &MyPushButton::clicked, [ = ]() {
        //qDebug()<<"startBtn clicked";
        //做一个弹起的特效
        startBtn->zoom(1);
        startBtn->zoom(0);

        //进入到选择关卡场景
        //延时进入 singleShot()
        QTimer::singleShot(500, this, [ = ]() {
            //设置chooseScene场景位置
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示界面
            this->chooseScene->show();
        });
    });

}

void MainScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    //缩放
    pix = pix.scaled(pix.width() * 1.1, pix.height() * 1.1);
    painter.drawPixmap(10, 30, pix);
}

MainScene::~MainScene() {
    delete ui;
}
