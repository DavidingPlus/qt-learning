#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    // 配置主场景
    // 设置固定大小
    this->setFixedSize(500, 700);

    // 设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 设置标题
    setWindowTitle("选择关卡场景");

    // 创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    // 创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    // 创建退出 菜单项
    QAction *quitAction = startMenu->addAction("退出");
    // 信号槽
    connect(quitAction, &QAction::triggered, [=]()
            { this->close(); });

    // 返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    // 点击返回
    connect(backBtn, &QPushButton::clicked, [=]()
            {
//        qDebug()<<"backBtn clicked";
        //告诉主场景 我返回了 主场景监听chooseLevelScene的返回按钮
        emit this->chooseSceneBack(); });

    // 创建选择关卡的按钮
    // 一个for循环写一个矩阵
    for (int i = 0; i < 20; ++i)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        // 用取余和取整除来得到矩阵
        menuBtn->move(70 + i % 4 * 100, 200 + i / 4 * 80);

        // 监听每个按钮的监听事件
        connect(menuBtn, &QPushButton::clicked, [=]()
                {
//            QString str=QString("Level %1 selected").arg(i+1);
//            qDebug()<<str;
                this->hide();
                //进入到游戏场景
                this->play=new PlayScene(i+1);
                //设置游戏场景的位置
                this->play->setGeometry(this->geometry());
                this->play->show();

            //监听选择关卡的返回按钮的信号
            //这里为什么要写在里面?(有点小迷)
            //因为前面是监听每个按钮的事件，当按了按钮的时候进入到关卡中，在点击返回按钮之后才返回选择关卡的界面
            connect(play,&PlayScene::playSceneBack,[=](){
                QTimer::singleShot(500,this,[=](){
                    //设置该场景的位置
                    this->setGeometry(play->geometry());
                    //每次都是新创建 所以可以将关卡删除掉
                    delete this->play;
                    this->play=nullptr;
                    this->show();//将选择关卡场景隐藏掉
                });
            }); });

        // 用标签部件
        QLabel *label = new QLabel;
        label->setParent(menuBtn); // 将label挂载在menuBtn上 省得移动
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        //        label->move(70+i%4*100,200+i/4*80);
        // 设置对齐方式 设置水平居中和垂直居中 用 | 连接
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        // 设置让鼠标进行穿透 因为后创建标签会导致标签覆盖在按钮上面 导致点击的是标签而不是按钮触发不了按钮点击
        // 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

// 重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    // 加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(QSize(pix.width() * 1.2, pix.height() * 1.2));
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
