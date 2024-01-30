#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置合适的大小比例
    this->resize(1000, 800);

    this->_player = new QMediaPlayer(this);
    this->_playerlist = new QMediaPlaylist(this);
    this->_mywidget = new QVideoWidget(ui->label);
    // 设置播放列表
    this->_player->setPlaylist(_playerlist);
    // 设置播放地点
    this->_player->setVideoOutput(_mywidget);
    // 调整播放窗口的大小 这个东西在每一帧的绘图函数中重载进行实现
    //    this->_mywidget->setFixedSize(ui->label->size());

    // 设置初始音量
    this->_player->setVolume(50);
    // 滑动条也到50
    ui->volumeSlider->setValue(50);

    // 视频播放自动更改进度条改变
    connect(_player, &QMediaPlayer::positionChanged, ui->processSlider, [=](qint64 position)
            { ui->processSlider->setValue((int)position); });
    // 视频切换改变进度条的总时长
    connect(_player, &QMediaPlayer::durationChanged, ui->processSlider, [=](qint64 duration)
            { ui->processSlider->setRange(0, (int)duration); });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    // 每一帧都进行绘画，绘画的图案设置和label控件设置为一样大,在绘制的过程中每时每刻调用这个函数就可以保证大小是lable控件大小了
    this->_mywidget->resize(ui->label->size());
}

// openBtn控件
void Widget::on_openBtn_clicked()
{
    QStringList mylist = QFileDialog::getOpenFileNames(this, "选择播放资源", "E:\\pubg素材\\PLAYERUNKNOWN'S BATTLEGROUNDS", "allfiles(*.*);;"
                                                                                                                            "MP3(*.mp3);;"
                                                                                                                            "MP4(*.mp4);;");

    for (int i = 0; i < mylist.size(); ++i)
        this->_playerlist->addMedia(QUrl(mylist[i]));
}

// start_pauseBtn控件
// 这里播放不了视频是因为没安装解码器，安装之后就可以进行视频的播放了!!!
void Widget::on_start_pauseBtn_clicked()
{
    if (is_started)
    {
        // 现在点击的是暂停按钮
        this->is_started = false;
        this->_player->pause();
        // 设置背景填充,格式按照ui里面的来进行填充
        ui->start_pauseBtn->setStyleSheet("QPushButton#start_pauseBtn{border-image:url(:/res/start.png)}");
    }
    else
    {
        // 现在点击的是播放按钮
        this->is_started = true;
        this->_player->play();
        ui->start_pauseBtn->setStyleSheet("QPushButton#start_pauseBtn{border-image:url(:/res/pause.jpg)}");
        // 把停止按钮控件设置为可以按
        ui->stopBtn->setEnabled(true);
    }
}

// stopBtn控件
void Widget::on_stopBtn_clicked()
{
    this->_player->stop();
    // 按了一次之后设置为不能再次按下
    ui->stopBtn->setEnabled(false);
    //    this->is_started = false;
    ui->start_pauseBtn->setStyleSheet("QPushButton#start_pauseBtn{border-image:url(:/res/start.png)}");
}

// preBtn控件
void Widget::on_preBtn_clicked()
{
    this->_player->stop();
    this->_playerlist->previous(); // 切换到上一个视频
    this->_player->play();
}

// nextBtn控件
void Widget::on_nextBtn_clicked()
{
    this->_player->stop();
    this->_playerlist->next(); // 切换到下一个视频
    this->_player->play();
}

// volumeSlider控件
void Widget::on_volumeSlider_valueChanged(int value)
{
    this->_player->setVolume(value);
}

// processSlider控件
void Widget::on_processSlider_valueChanged(int value)
{
    this->_player->setPosition((qint64)value);
}
