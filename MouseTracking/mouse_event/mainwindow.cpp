#include "mainwindow.h"
#include <QStatusBar>
#include <QToolTip>  // 提示，贴士
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 状态栏临时部件特征:
    // 1，依次显示在状态栏最左侧（若有多个）
    // 2，会被临时消息遮蔽
    mousePosition = new QLabel("临时部件", this);
    this->statusBar()->addWidget(mousePosition);

    // 状态栏永久部件特征:
    // 1，依次小时在状态栏的最右侧（若有多个）
    // 2，不会被临时消息遮蔽
    mouseState    = new QLabel("永久部件", this);
    this->statusBar()->addPermanentWidget(mouseState);

    // 设定鼠标的追踪
    this->setMouseTracking(true);

    // 调整u的大小
    this->resize(400, 300);
}

MainWindow::~MainWindow()
{

}

// #### 按压事件 ####
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QString msg = "鼠标按下";

    switch(e->button())
    {
    case Qt::LeftButton:
        msg += "（左键）";
        // 记录当前位置，因为用户可能要拖拽
        // 当前位置: 指的是光标在窗口内的位置
        beginPos = e->globalPos() - this->frameGeometry().topLeft();
        break;

    case Qt::RightButton:
        msg += "（右键）"; break;
    case Qt::MiddleButton:
        msg += "（滚轮）"; break;
    }

    mouseState->setText(msg);

}

// #### 松开事件 ####
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    mouseState->setText("松开");

    QString msg;
    if(e->buttons() & Qt::LeftButton)
        msg += "左键未松开";
    if(e->buttons() & Qt::RightButton)
        msg += "右键未松开";
    if(e->buttons() & Qt::MiddleButton)
        msg += "滚轮未松开";

    statusBar()->showMessage(msg);
}

// #### 移动事件 ####
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    // 状态栏的临时部件显示: 光标的窗口内位置
    QString pos = QString("(%1, %2)").arg(e->x()).arg(e->y());
    mousePosition->setText("鼠标当前位置:"+pos);

    // 在光标旁边提示框显示: 光标的全局位置
    QString globalPos = QString("(%1, %2)").arg(e->globalX()).arg(e->globalY());
//    QToolTip::showText(e->globalPos(), globalPos);

    // e->buttons() 返回值
    // 1，当发生 mouseMoveEvent 时，返回按住的键们
    // 2，当发生 mousePressEvent 或 mouseDoubleClickEvent 时，返回触发该事件的键们
    // 3，当发生 mouseReleaseEvnt 时，返回未松开的键们
    if(e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos()-beginPos);
        beginPos = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
    QString pos = QString("(%1, %2)").arg(e->x()).arg(e->y());
    mousePosition->setText("双击事件，鼠标当前位置:"+pos);
}
