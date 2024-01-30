#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);

    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//网络请求函数
void MainWindow::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));//get()函数发送网络请求

    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));  //有可用数据时
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateDataReadProgress(qint64,qint64))); //更新进度条
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));    //下载完成后
}
//有可用数据,进行读取数据到file中
void MainWindow::httpReadyRead()
{
    if(file)file->write(reply->readAll());  //如果文件存在，则写入文件
}
 //更新进度条
void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);    //最大值
    ui->progressBar->setValue(bytesRead);    //当前值
}
//下载完成后
void MainWindow::httpFinished()
{
    ui->progressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

//下载按钮
void MainWindow::on_pushButton_clicked()
{
//    downloadfolder();   //创建下载目录
    QString dir = downloadfolder("./downloads/");   //创建下载目录

    url = ui->lineEdit->text(); //获取界面输入的url地址
    QFileInfo info(url.path());
    QString fileName(info.fileName());  //获取文件名
    file = new QFile(dir+fileName);
    qDebug()<<dir;
    qDebug()<<fileName;
    if(!file->open(QIODevice::WriteOnly))
    {   //如果打开文件失败，则删除file，并使file指针为0，然后返回
        qDebug()<<"file open error";
        delete file;
        file = 0;
        return;
    }
    startRequest(url);  //进行链接请求
    ui->progressBar->setValue(0);   //进度条值设置为0
    ui->progressBar->show();    //显示进度条
}
//创建下载目录
QString MainWindow::downloadfolder(QString dir)
{
    QDir *temp = new QDir;    //获取QDir的地址，不是复制一个QDir
    //判断文件夹是否存在
//    bool exist = temp->exists("./download");
    bool exist = temp->exists(dir);
    if(exist)
        QMessageBox::warning(this,tr("creat folder"),tr("The folder is exist!"));
     else {
         bool ok = temp->mkdir(dir);    //当文件夹不存在时进行创建
//         bool ok = temp->mkdir("./download");    //当文件夹不存在时进行创建
         if(ok)
             QMessageBox::warning(this,tr("creat folder"),tr("Creat the folder successful"));
        }
    return dir;
}
