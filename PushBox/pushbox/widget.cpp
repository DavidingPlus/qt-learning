#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMediaPlayer>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

    //先显示开始菜单
    this->_menu = new Menu(this);
    this->hide();
    _menu->show();

    //监听打开游戏的信号
    connect(this->_menu, &Menu::startGame, [ = ]() {
        _menu->hide();
        this->show();
    });

    //初始化人物
    this->_role = new Role(this);
    //初始化地图
    this->_Map = new GameMap(this);
    //初始化加载地图文件
    this->_gamePath = QString("./Map/lv1.txt");
    this->_Map->__init__(_gamePath);

    //初始化画家
    this->_MapPainter = new QPainter(this);

    //设置大小
    this->setFixedSize(1024, 768);

    //创建定时器来实时更新函数
    this->_gameTimer = new QTimer(this);
    this->_gameTimer->start(100);
    connect(this->_gameTimer, &QTimer::timeout, [ = ]() {
        this->update();
    });

    //初始化胜利图案
    ui->winLabel->setGeometry(QRect((this->width() - ui->winLabel->width()) * 0.5, -170, ui->winLabel->width(), ui->winLabel->height()));
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent*) {
    //设置画布
    this->_MapPainter->begin(this);

    //画背景
    this->_MapPainter->drawImage(QRect(0, 0, 1024, 768), QImage(":/res/ground.png"));

    //画地图
    this->_Map->Paint(this->_MapPainter, QPoint(10, 300));

    //画人物
    this->_role->Paint(this->_MapPainter, QPoint(10, 300));

    //结束
    this->_MapPainter->end();
}

void Widget::keyPressEvent(QKeyEvent* e) {
    if(_is_win)return;

    switch (e->key()) {
        case Qt::Key_W:
        case Qt::Key_Up: {
                //Move只是简单的移动，真正的移动还需要判断能否移动的逻辑
                //逻辑碰撞检测函数 并且移动
                Move_withoutCollsion(-1, 0);
                break;
            }
        case Qt::Key_S:
        case Qt::Key_Down: {
                Move_withoutCollsion(1, 0);
                break;
            }
        case Qt::Key_A:
        case Qt::Key_Left: {
                Move_withoutCollsion(0, -1);
                break;
            }
        case Qt::Key_D:
        case Qt::Key_Right: {
                Move_withoutCollsion(0, 1);
                break;
            }
        default:
            break;
    }
    //移动之后来判断是否胜利
    if(this->is_Win()) {
        //让游戏无法移动
        this->_is_win = true;
        //将重新开始按钮设置为false
        ui->restartBtn->setEnabled(false);
        //并且执行打印胜利画面的动画
        this->gameWinAnimation();
        //添加胜利音效
        this->soundPlay("qrc:/res/LevelWinSound.wav");
    }
}

//胜利动画函数
void Widget::gameWinAnimation() {
    //将胜利的图片砸下来
    QPropertyAnimation* animation = new QPropertyAnimation(ui->winLabel, "geometry");
    //设置时间间隔
    animation->setDuration(1000);
    //设置开始位置
    animation->setStartValue(QRect(ui->winLabel->x(), ui->winLabel->y(), ui->winLabel->width(), ui->winLabel->height()));
    //设置结束位置
    animation->setEndValue(QRect(ui->winLabel->x(), -ui->winLabel->y(), ui->winLabel->width(), ui->winLabel->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void Widget::soundPlay(QString url) {
    //注意qsound只能放 wav格式的音乐
    //QSound* sound = new QSound(path);
    //这里用QmediaPlayer
    QMediaPlayer* media = new QMediaPlayer(this);
    //注意这里需要传入url 和平常的path不一样
    media->setMedia(QUrl(url));
    media->setVolume(60);
    media->play();
}

//判断是否胜利
bool Widget::is_Win() {
//遍历数组 如果找不到目标点那就是胜利了
    for(int i = 0; i < this->_Map->_row; ++i)
        for(int j = 0; j < this->_Map->_col; ++j)
            if(this->_Map->_pmap[i][j] == Point)return false;
    return true;
}

void Widget::Move_withoutCollsion(int drow, int dcol) {
    //判断新位置是否合法
    int newRow = this->_role->_roleRow + drow;
    int newCol = this->_role->_roleCol + dcol;

    //前方是墙
    if(this->_Map->_pmap[newRow][newCol] == Wall)return ;

    //前方是箱子
    else if (this->_Map->_pmap[newRow][newCol] == Box) {
        //定义箱子前方
        int newBoxRow = this->_role->_roleRow + 2 * drow;
        int newBoxCol = this->_role->_roleCol + 2 * dcol;
        if(this->_Map->_pmap[newBoxRow][newBoxCol] == Road) {
            //如果箱子前面是路,把箱子的位置变成路,路变成箱子,交换
            //改变地图元素 不管人 人在另一个类当中
            this->_Map->_pmap[newRow][newCol] = Road;
            this->_Map->_pmap[newBoxRow][newBoxCol] = Box;
            //推箱子播放音效
            this->soundPlay("qrc:/res/push.wav");
        } else if (this->_Map->_pmap[newBoxRow][newBoxCol] == Point) { //前方是目标点
            this->_Map->_pmap[newRow][newCol] = Road;
            this->_Map->_pmap[newBoxRow][newBoxCol] = Inpoint;
            //推箱子播放音效
            this->soundPlay("qrc:/res/push.wav");
        } else //否则无法推动
            return;
    }

    //前方是进目标点
    else if(this->_Map->_pmap[newRow][newCol] == Inpoint) {
        //定义目标前方
        int newInpointRow = this->_role->_roleRow + 2 * drow;
        int newInpointCol = this->_role->_roleCol + 2 * dcol;
        if(this->_Map->_pmap[newInpointRow][newInpointCol] == Road) {
            this->_Map->_pmap[newRow][newCol] = Point;
            this->_Map->_pmap[newInpointRow][newInpointCol] = Box;
        } else if (this->_Map->_pmap[newInpointRow][newInpointCol] == Point) { //前方是目标点
            this->_Map->_pmap[newRow][newCol] = Point;
            this->_Map->_pmap[newInpointRow][newInpointCol] = Inpoint;
        } else return;
    }

    //否则移动
    this->_role->Move(drow, dcol);
    //    qDebug() << this->_role->_rolepos;
}

void Widget::on_exitBtn_clicked() {
    exit(0);
}

//重新开始游戏
void Widget::on_restartBtn_clicked() {
    //重新加载这个地图文件
    this->_Map->__init__(this->_gamePath);
    //将人复位
    this->_role->__init__();
}
