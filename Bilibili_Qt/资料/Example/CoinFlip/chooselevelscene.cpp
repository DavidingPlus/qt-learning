#include "chooselevelscene.h"
#include <QMenuBar>
#include <QAction>
#include "mypushbutton.h"
#include <QDebug>
#include <QLabel>
#include "playscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(480, 882);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //创建退出菜单项
    QAction *quitAction = startMenu->addAction("退出");
    //点击退出 实现游戏退出
    connect(quitAction, &QAction::triggered, [=]()
            { this->close(); });

    //返回按钮
    MyPushButton *backbtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width() - backbtn->width(), this->height() - backbtn->height());

    //点击返回
    connect(backbtn, &MyPushButton::clicked, [=]()
            { 
                // qDebug() << "点击了返回按钮"; 
                //告诉主场景 我返回了 主场景监听ChooseLevelScene的返回按钮
                emit this->chooseSceneBack(); });

    //创建选择关卡的按钮 用一个for循环写一个矩阵
    for (auto i = 0; i < 20; ++i)
    {
        MyPushButton *menubtn = new MyPushButton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(37.5 + i % 4 * 105, 195 + i / 4 * 105);

        //监听每个按钮的点击事件
        connect(menubtn, &QPushButton::clicked, [=]()
                {
                    QString str = QString("您选择的第 %1 关").arg(i + 1);
                    qDebug() << str;

                    //进入到游戏场景
                    this->hide(); //将选关场景隐藏掉
                    play = new PlayScene(i + 1);//创建游戏场景
                    play->show(); 
                    
                    connect(play,&PlayScene::chooseSceneBack,[=](){
                        this->show();
                        delete play;
                        play = nullptr;
                    }); });

        QLabel *label = new QLabel(this);
        label->setFixedSize(menubtn->width(), menubtn->height());
        label->setText(QString::number(i + 1));
        label->move(37.5 + i % 4 * 105, 195 + i / 4 * 105);
        //设置 label文字的对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //创建背景
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 1.4, pix.height() * 1.4);
    painter.drawPixmap(this->width() * 0.5 - pix.width() * 0.5, 60, pix.width(), pix.height(), pix);
}
