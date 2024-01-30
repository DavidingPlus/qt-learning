#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->resize(800, 600);
    this->setWindowTitle("五大部件主窗口");

    //菜单栏 在主窗口中只存在一个
    QMenuBar* menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);
    menuBar->addMenu("文件")->addMenu("打开")->addAction("测试子项");
    menuBar->addMenu("编辑");

    //工具栏 可以不只一个
    QToolBar* toolBar = new QToolBar(this);
    this->addToolBar(Qt::TopToolBarArea, toolBar); //默认停靠范围
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea); //设置允许停靠范围 按位或 | 连接
    toolBar->setMovable(true);//设置是否可以移动
    toolBar->setFloatable(false);//设置是否可悬浮
    toolBar->addAction("编辑");
    //添加分割线 位置取决于代码的位置
    toolBar->addSeparator();
    toolBar->addAction("打开");

    //状态栏 在主窗口中只有一个
    QStatusBar* statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    statusBar->addWidget(new QPushButton("FPS:600"));//添加按钮
    statusBar->addWidget(new QLabel("PIN:20"));//添加文本
    statusBar->addPermanentWidget(new QLabel("今天天气很好"));//默认在右边添加

    //中心部件 只有一个
    this->setCentralWidget(new QTextEdit("请输入...", this));

    //衔接部件 浮动窗口
    QDockWidget* dockwidget = new QDockWidget("文本1", this);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockwidget);
    dockwidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);//设置允许停靠区域
}

MainWindow::~MainWindow() {
    delete ui;
}

