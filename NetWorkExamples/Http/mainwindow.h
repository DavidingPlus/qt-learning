#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
class QFile;
class QNetworkReply;
class QNetworkAccessManager;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startRequest(QUrl url);
    QString downloadfolder(QString dir);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;

    QNetworkReply *reply;
    QUrl url;   //网络地址
    QFile *file;    //文件指针
private slots:
    void httpFinished();    //完成下载后的处理动作
    void httpReadyRead();   //接受数据时的处理动作
    void updateDataReadProgress(qint64,qint64); //跟新进度条
    void on_pushButton_clicked();   //下载按钮的单击事件槽函数
};

#endif // MAINWINDOW_H
