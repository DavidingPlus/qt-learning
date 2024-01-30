#include "playscene.h"
#include <QPainter>
#include <QDebug>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QFont>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>

//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}

//重写构造函数
PlayScene::PlayScene(int level)
{
//    QString str=QString("level %1 playing").arg(level);
//    qDebug()<<str;
    this->levelIndex=level;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(500,700);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

    //创建菜单栏
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu* startMenu=bar->addMenu("开始");
    //创建退出 菜单项
    QAction* quitAction=startMenu->addAction("退出");
    //信号槽
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton* backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&QPushButton::clicked,[=](){
//        qDebug()<<"backBtn clicked";
        //告诉场景 我返回了 chooseLevelScene监听playScene的返回按钮
            emit this->playSceneBack();
    });

    //显示当前的关卡数
    QLabel* label=new QLabel(this);
//    //设置字体
    QFont font;
    font.setFamily("楷体");
    font.setPointSize(18);
    QString str=QString("Level : %1").arg(QString::number(this->levelIndex));
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));

    //初始化每个关卡的二维数组
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
        {
            this->gameArray[i][j]=dataConfig().mData[this->levelIndex][i][j];
        }

    //胜利图片显示
    QLabel* winLabel=new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,pix.width(),pix.height());
    winLabel->setPixmap(pix);
    winLabel->setParent(this);
    //符号代表放到屏幕的上方，看不见，等会儿成功的时候将其y坐标反过来就砸下来了
    winLabel->move((this->width()-pix.width())*0.5,-this->height()*0.3);

    //显示金币背景图案
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
        {
            //绘制背景图片
            QPixmap pix=QPixmap(":/res/BoardNode.png");
            QLabel* label=new QLabel(this);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->move(150+i*50,300+j*50);

            //进行判断看是选择金币还是选择银币
            QString str;
            if(this->gameArray[i][j])//金币
                str=":/res/Coin0001.png";
            else
                str=":/res/Coin0008.png";

            //创建金币
            MyCoin* coin= new MyCoin(str);
            coin->setParent(this);
            //将其对其居中
            coin->move(152+i*50,302+j*50);
            //给属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];

            //将金币放入到金币的二维数据中以便后期维护
            this->coinBtn[i][j]=coin;

            //点击金币进行翻转
            connect(coin,&QPushButton::clicked,[=](){
                //点击某个金币的时候其他金币不能点击 那就将其设为true
                for(int i=0;i<4;++i)
                    for(int j=0;j<4;++j)
                        coinBtn[i][j]->is_Win=true;


                coin->changeFlag();
                this->gameArray[i][j]=!this->gameArray[i][j]?1:0;

                //进行周围金币的反转 延时反转
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)//右侧金币反转
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]?1:0;
                    }
                    //左侧
                    if(coin->posX-1>=0){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]?1:0;
                    }
                    //上面
                    if(coin->posY-1>=0){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]?1:0;
                    }
                    //下面
                    if(coin->posY+1<=3){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]?1:0;
                    }

                    //其他金币翻完之后 解开禁用
                    for(int i=0;i<4;++i)
                        for(int j=0;j<4;++j)
                            coinBtn[i][j]->is_Win=false;

                    //在翻完之后立刻做判断 所以写在这
                    //判断是否胜利
                    this->is_Win=true;
                    for(int i=0;i<4;++i)
                        for(int j=0;j<4;++j)
                            if(coinBtn[i][j]->flag==false)//只要一个是反面就算失败
                            {
                                this->is_Win=false;
                                //注意这里break是跳不出多层循环的 建议使用goto;
                                goto finals;
                            }
                    finals:
                    if(this->is_Win==true){
                            //胜利了
//                        qDebug()<<"Winner!!!";
                        for(int i=0;i<4;++i)
                            for(int j=0;j<4;++j)
                                coinBtn[i][j]->is_Win=true;
                        //将胜利的图片砸下来
                        QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),-winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });
            });
        }
}

//重写paintEvent事件
void PlayScene::paintEvent(QPaintEvent*)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(QSize(pix.width()*1.2,pix.height()*1.2));
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
