#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include <QProcess>
#include <QMouseEvent>

/*
 * 扫雷难度
 * 初级 10雷 9*9
 * 中级 30雷 16*16
 * 高级 50雷 20*20
 * 自定义 做一个widget就可以了
*/

void MainWindow::__init__(int level)
{
    switch (level)
    {
        //初始化边和雷的个数
        case 0:
            this->_mineNum = 10;
            this->_Btnx = 9;
            this->_Btny = 9;
            break;
        case 1:
            this->_mineNum = 30;
            this->_Btnx = 16;
            this->_Btny = 16;
            break;
        case 2:
            this->_mineNum = 50;
            this->_Btnx = 20;
            this->_Btny = 20;
            break;
    }
    this->_mineRemains = this->_mineNum;
    this->_flagNum = this->_mineNum;

    //初始化flagLcd
    ui->flagLcd->display(QString::number(this->_flagNum));
}

MainWindow::MainWindow(QWidget* parent, int level)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //接收到菜单栏的信息之后初始化数据
    //先初始化数据
    this->__init__(level);

    //设置窗口大小 注意数组 坐标x y和 qt x y 是相反的!!!
    this->setFixedSize(40 * _Btny, 95 +  40 * _Btnx);

    //实现actionexit退出功能
    connect(ui->actionexit, &QAction::triggered, [ = ]()
    {
        exit(0);
    });

    //设置定时器让timerLcd开始倒计时
    this->timerRun();

    //创建按钮簇
    this->createBtns();

    //监听flag信号
    this->dealFlag();

    //FlagMaxed槽函数
    connect(this, &MainWindow::FlagMaxed, [ = ](bool ok)
    {
        for(int i = 0; i < this->_Btnx; ++i)
            for(int j = 0; j < this->_Btny; ++j)
                if(ok) this->_btns[i][j]->_isFlagMax = true;
                else this->_btns[i][j]->_isFlagMax = false;
    });

    //生成雷
    this->_init_Mines();

    //绑定雷,修改参数为True
    this->bindMines();

    //初始化所有的非雷按钮 更改其周围的雷数量
    this->_initAllBlanks();

    //如果踩到雷了监听游戏结束函数
    for(int i = 0; i < this->_Btnx; ++i)
        for(int j = 0; j < this->_Btny; ++j)
        {
            connect(this->_btns[i][j], &MyButton::gameisover, [ = ]()
            {
                this->_timer->stop();
                //播放音乐
                this->playVideo("qrc:/res/Fail.wav");
                ui->smileBtn->setStyleSheet("border-image:url(:/res/Ooo.gif);");
                auto ret = QMessageBox::question(this, "游戏结束", "踩到雷了,是否重来!", QMessageBox::Yes | QMessageBox::No);
                if(ret == QMessageBox::No) exit(0);
                else
                {
                    //重新开始游戏
                    this->reStartGame();
                }
            });
        }

    //监听blank按钮被点击
    for(int i = 0; i < this->_Btnx; ++i)
        for(int j = 0; j < this->_Btny; ++j)
        {
            connect(this->_btns[i][j], &MyButton::isClicked,  [ = ]()
            {
                this->dealBtns(i, j);
            });
        }
}

void MainWindow::createBtns()
{
    for(int i = 0; i < this->_Btnx; ++i)
    {
        for(int j = 0; j < this->_Btny; ++j)
        {
            //设置父亲 大小 位置 图案
            this->_btns[i][j] = new MyButton(this);
            this->_btns[i][j]->setFixedSize(40, 40);
            this->_btns[i][j]->move(j * this->_btns[i][j]->width(), 95 + i * this->_btns[i][j]->height());
            this->_btns[i][j]->setStyleSheet("background-image:url(:/res/blank.gif);");
        }
    }
}

//查询QList<int*>中是否存在目标元素
bool Find(QList<int*>mines, int* mine)
{
    for(int i = 0; i < mines.size(); ++i)
        if(mines[i][0] == mine[0] && mines[i][1] == mine[1])return true;
    return false;
}

void MainWindow::flagput_release(int i, int j, bool ok)
{
    //如果旗帜数量正确那么则减一
    int* mine = new int[2];
    mine[0] = i;
    mine[1] = j;
    if(Find(this->_mines, mine))
    {
        if(ok)
        {
            //如果减到0则跳转到胜利界面
            if(--this->_mineRemains == 0) this->GameWinner();
        }
        else this->_mineRemains++;
    }
}

void MainWindow::GameWinner()
{
    this->_timer->stop();
    //播放音乐
    this->playVideo("qrc:/res/Success.wav");
    auto ret = QMessageBox::question(this, "游戏胜利", "恭喜您游戏胜利,请问您需要再尝试一次吗?", QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::No) exit(0);
    else this->reStartGame();
}

void MainWindow::playVideo(QString url)
{
    QMediaPlayer* player = new QMediaPlayer(this);
    player->setMedia(QUrl(url));
    player->setVolume(30);
    player->play();
}

void MainWindow::dealFlag()
{
    for(int i = 0; i < this->_Btnx; ++i)
    {
        for(int j = 0; j < this->_Btny; ++j)
            connect(this->_btns[i][j], &MyButton::flag_changed, [ = ](bool ok)
        {
            if(ok)  //这里是点击右键生成旗帜
            {
                //如果正确放置则减一
                ui->flagLcd->display(--this->_flagNum);
                //如果_flagNum为0则不能点击空白变成flag
                if(this->_flagNum == 0)
                    emit FlagMaxed(true);
            }
            else
            {
                ui->flagLcd->display(++this->_flagNum);
                if(this->_flagNum == 1)
                    emit FlagMaxed(false);
            }
            //最后看是否需要更改mineRemains的数量
            this->flagput_release(i, j, ok);
        });
    }
}

int MainWindow::generateRandomNumber(int max)
{
    int num = QRandomGenerator::global()->bounded(max);
    return num;
}

void MainWindow::_init_Mines()
{
    //生成雷的坐标
    for(int i = 0; i < this->_mineNum; ++i)
    {
        int* mine = new int[2];
        mine[0] = generateRandomNumber(this->_Btnx);
        mine[1] = generateRandomNumber(this->_Btny);
        //注意这个点不能重复 contains 存在返回true
        if(Find(this->_mines, mine))
        {
            --i;
            continue;
        }
        this->_mines.append(mine);
//        qDebug() << "(" << mine[0] << "," << mine[1] << ")";//测试雷 打印坐标
    }
}

void MainWindow::bindMines()
{
    for(int i = 0; i < this->_Btnx; ++i)
        for(int j = 0; j < this->_Btny; ++j)
        {
            int* mine = new int[2];
            mine[0] = i;
            mine[1] = j;
            //查得到表明是雷
            if(Find(this->_mines, mine))
                this->_btns[i][j]->_isMine = true;
        }
}

void MainWindow::reStartGame()
{
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath());
}

void MainWindow::_initAllBlanks()
{
    for(int i = 0; i < this->_Btnx; ++i)
        for(int j = 0; j < this->_Btny; ++j)
        {
            //不是雷
            if(this->_btns[i][j]->_isMine)
                this->_btns[i][j]->_Minearound = -1;//与0做区分
            else   //注意数组越界的情况
            {
                for(int k = -1; k < 2; ++k)
                    for(int l = -1; l < 2; ++l)
                    {
                        if(!(k == 0 && l == 0))//自己不用遍历
                            if((i + k >= 0 && i + k < this->_Btnx) && (j + l >= 0 && j + l < this->_Btny)) //数组不越界
                                //判断是不是为雷
                                if(this->_btns[i + k][j + l]->_isMine)
                                    this->_btns[i][j]->_Minearound++;
                    }
            }
        }
}

void MainWindow::dealBtns(int i, int j)
{
    //处理本按钮
    if(this->_btns[i][j]->_is_handled)
        return;
    this->_btns[i][j]->_is_handled = true;
    int num = this->_btns[i][j]->_Minearound;
    QString url = ":/res/" + QString::number(num) + ".gif";
    QString strs = QString("background-image:url(%1);").arg(url);
    this->_btns[i][j]->setStyleSheet(strs);
    this->_btns[i][j]->setEnabled(false);
    //如果是空白,递归处理周围的按钮
    if(num == 0)
    {
        for(int k = -1; k < 2; ++k)
            for(int l = -1; l < 2; ++l)
            {
                if(!(k == 0 && l == 0))//自己不用遍历
                    if((i + k >= 0 && i + k < this->_Btnx) && (j + l >= 0 && j + l < this->_Btny))  //数组不越界
                        dealBtns(i + k, j + l);
            }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerRun()
{
    this->_timer = new QTimer(this);
    _timer->start(1000);
    connect(_timer, &QTimer::timeout, [ = ]()
    {
        static int numTime = 1000;
        ui->timeLcd->display(--numTime);
        if(ui->timeLcd->value() == 0)   //时间到了
        {
            this->_timer->stop();
            ui->smileBtn->setStyleSheet("border-image:url(:/res/Ooo.gif);");
            auto ret = QMessageBox::question(this, "时间到了", "是否重新开始?", QMessageBox::Yes | QMessageBox::No);
            if(ret == QMessageBox::No) //退出
                exit(0);
            else
            {
                //重新开始游戏
                this->reStartGame();
            }
        }
    });
}

void MainWindow::on_smileBtn_clicked()
{
    this->reStartGame();
}
