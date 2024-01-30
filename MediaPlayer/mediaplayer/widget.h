#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_openBtn_clicked();

    void on_start_pauseBtn_clicked();

    void on_stopBtn_clicked();

    void on_preBtn_clicked();

    void on_nextBtn_clicked();

    void on_processSlider_valueChanged(int value);

    void on_volumeSlider_valueChanged(int value);

private:
    Ui::Widget *ui;
    // 定义控件
    QMediaPlayer *_player = nullptr;
    QMediaPlaylist *_playerlist = nullptr;
    QVideoWidget *_mywidget = nullptr;
    bool is_started = false; // 是否播放
};
#endif // WIDGET_H
