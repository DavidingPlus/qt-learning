#include "gamemap.h"
#include <QFile>
#include <QDebug>

GameMap::GameMap(QObject* parent) : QObject(parent) {
    this->_row = 0;
    this->_col = 0;
    this->_pmap = nullptr;
}

GameMap::~GameMap() {
    this->memClear();
}

void GameMap::memClear() {
    //内存清理函数
    if(this->_pmap) {
        //清理地图对象
        for(int i = 0; i < this->_row; ++i)
            delete []this->_pmap[i];
        delete []this->_pmap;
        //重置行列
        this->_row = 0;
        this->_col = 0;
    }
}

void GameMap::Paint(QPainter* painter, QPoint pos) {
    //遍历地图
    for(int i = 0; i < this->_row; ++i )
        for(int j = 0; j < this->_col; ++j ) {
            QString ImageUrl = NULL;
            switch(this->_pmap[i][j]) {
                case Road:
                    ImageUrl = ":/res/sky.png";
                    break;
                case Wall:
                    ImageUrl = ":/res/wall.png";
                    break;
                case Box:
                    ImageUrl = ":/res/case.png";
                    break;
                case Point:
                    ImageUrl = ":/res/end.png";
                    break;
                case Inpoint:
                    ImageUrl = ":/res/win.png";
                    break;
            }
            QImage img(ImageUrl);
            painter->drawImage(QPoint(pos.x() + j * img.width(), pos.y() + i * img.height()), img);
        }
}

bool GameMap::__init__(QString path) {
    QFile file(path);//创建文件对象
    if(!file.open(QIODevice::ReadOnly))return false;
    //用字节数组去接
    QByteArray arrAll = file.readAll();
    arrAll.replace("\r\n", "\n");//处理字符串
    QList<QByteArray>lineList = arrAll.split('\n');
    this->_row = lineList.size();//确定行

    //构造二维数组，开辟内存，准备存入元素了
    this->_pmap = new int* [this->_row];

    for(int i = 0; i < this->_row; ++i) {
        QList<QByteArray>colList =  lineList[i].split(',');
        this->_col = colList.size();//确定列
        this->_pmap[i] = new int[this->_col];

        for(int j = 0; j < this->_col; ++j)
            this->_pmap[i][j] = colList[j].toInt();
    }

    return true;
}
