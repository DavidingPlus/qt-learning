#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_openBtn_clicked();

    void on_start_pauseBtn_clicked();

    //重写绘图事件来让一帧一帧播放时 使其大小固定为label的大小
    void paintEvent(QPaintEvent*);

    void on_volumeSlider_valueChanged(int value);

    void on_processSlider_valueChanged(int value);

signals:
    void isSliderMax();//监听进度条是不是最大值

private:
    Ui::MainWindow* ui;
    //定义视频播放器对象
    QMediaPlayer* _player = nullptr;
    //定义播放widget控件
    QVideoWidget* _widget = nullptr;

    //设置播放路径
    QString _path = QString();
    //是否正在播放
    bool is_playing = false;
    //播放视频函数
    void playVideo();
};
#endif // MAINWINDOW_H
