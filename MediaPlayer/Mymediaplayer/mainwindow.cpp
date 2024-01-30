#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include "mylabel.h"

//将秒数转化为时分秒的格式
QString transform(int secs) {
    //将秒数转化为时分秒格式
    int H = secs / (60 * 60);
    int M = (secs - (H * 60 * 60)) / 60;
    int S = (secs - (H * 60 * 60)) - M * 60;
    QString hour = QString::number(H);
    if (hour.length() == 1) hour = "0" + hour;
    QString min = QString::number(M);
    if (min.length() == 1) min = "0" + min;
    QString sec = QString::number(S);
    if (sec.length() == 1) sec = "0" + sec;
    QString Time = hour + ":" + min + ":" + sec;

    return Time;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setFixedSize(1000, 800);

    //在调用构造函数的时候设置进度条为不可滑动，只有当有文件进来的时候才可以滑动
    ui->processSlider->setEnabled(false);

    //设置一些播放的参数
    this->_player = new QMediaPlayer(this);
    this->_widget = new QVideoWidget(ui->label);
    //设置播放地点
    this->_player->setVideoOutput(this->_widget);

    //设置初始音量 并且滑动条置为一半
    this->_player->setVolume(50);
    ui->volumeSlider->setValue(50);
    ui->volumeSlider->setRange(0, 100);

    //设置进度条随视频变化而变化 同时改变timeLabel的值
    connect(this->_player, &QMediaPlayer::positionChanged, ui->processSlider, [ = ](int position) {
        ui->processSlider->setValue(position);
        //设置durationLabel的值
        ui->durationLabel->setText(transform(this->_player->duration() / 1000));
        //设置timeLabel的值
        ui->timeLabel->setText(transform(this->_player->position() / 1000));
    });

    //打开文件,设置进度条
    connect(this->_player, &QMediaPlayer::durationChanged, ui->processSlider, [ = ](int duration) {
        ui->processSlider->setRange(0, duration);
    });

    //如果进度条最大值了需要改变按钮
    connect(this, &MainWindow::isSliderMax, this, [ = ]() {
        //暂停
        this->is_playing = false;
        this->_player->pause();
        // 设置背景填充,格式按照ui里面的来进行填充
        ui->start_pauseBtn->setStyleSheet("QPushButton#start_pauseBtn{border-image:url(:/res/start.png)}");
    });

    //监听一下双击事件
    connect(ui->label, &MyLabel::isDoubleclicked, this, [ = ]() {
        playVideo();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

//一次打开一个视频进行播放
void MainWindow::on_openBtn_clicked() {
    //记住上次打开的路径
    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();

    QString path = QFileDialog::getOpenFileName(this, "选择文件", lastPath, "*.mp4;;*.mp3");
    if(path == NULL)return;

    //将文件添加到播放列表中
    this->_player->setMedia(QUrl::fromLocalFile(path));
    //将路径保存显示到UI上
    this->_path = path;
    ui->pathLabel->setText(this->_path);

    //将标识设置为false来让其播放
    this->is_playing = false;
    //调用播放按钮自动播放
    this->playVideo();
    //设置进度条为可滑动
    ui->processSlider->setEnabled(true);
}

void MainWindow::on_start_pauseBtn_clicked() {
    //如果没有路径则表示没有视频进入 无法触动播放按钮
    if(this->_path == NULL)return;
    //有一个特殊情况,就是进度条为满的时候再点击这个是重新播放
    if(ui->processSlider->value() == ui->processSlider->maximum())
        //把进度条设置为0
        ui->processSlider->setValue(0);
    this->playVideo();
}

void MainWindow::paintEvent(QPaintEvent*) {
    this->_widget->resize(ui->label->size());
}

void MainWindow::on_volumeSlider_valueChanged(int value) {
    this->_player->setVolume(value);
    ui->volume->setText(QString::number(value));
}

void MainWindow::on_processSlider_valueChanged(int value) {
    if(this->_path == NULL)return;
    this->_player->setPosition(value);
    //监听这个value值是不是最大值
    if(value == ui->processSlider->maximum())emit this->isSliderMax();
}

void MainWindow::playVideo() {
    if(this->is_playing) { //为真表示正在播放
        //暂停
        this->is_playing = false;
        this->_player->pause();
        // 设置背景填充,格式按照ui里面的来进行填充
        ui->start_pauseBtn->setStyleSheet("QPushButton#start_pauseBtn{border-image:url(:/res/start.png)}");
    } else {
        //播放
        this->is_playing = true;
        this->_player->play();
        ui->start_pauseBtn->setStyleSheet("QPushButton#start_pauseBtn{border-image:url(:/res/pause.png)}");
    }
}
