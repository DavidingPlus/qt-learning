#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>

// PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
// {
// }

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    this->setFixedSize(480, 882);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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
                QTimer::singleShot(500,this,[=](){ emit this->chooseSceneBack();}); });

    //显示当前关卡数
    QLabel *label = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(QRect(45, this->height() - 75, 240, 100));
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //创建背景
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 1.4, pix.height() * 1.4);
    painter.drawPixmap(this->width() * 0.5 - pix.width() * 0.5, 60, pix.width(), pix.height(), pix);
}
