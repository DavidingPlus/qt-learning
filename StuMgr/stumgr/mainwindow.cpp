#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QSqlDatabase>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), _sql(nullptr) {
    ui->setupUi(this);

//    //先进行数据库的连接,如果连接不上就退出程序
    this->_sql = StuSql::getinstance();//这个单例函数里面会调用默认构造函数 也就会调用 __init__()函数

//    //登录界面
//    this->_login.show();
//    //登录界面成功表示成功登录
//    //信号槽里面传入指针
//    connect(&_login, &Page_Login::sendLoginSuccess,  [ = ]() {
//        this->_login.hide();
//        this->show();
//    });

    //设置tableWidget属性
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //只能选中一个
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能修改
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection); //只能选中一个
}

//点击查看学生和用户表的交互
void MainWindow::on_stuBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::on_userBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

MainWindow::~MainWindow() {
    delete ui;
}

//按退出按钮退出
void MainWindow::on_exitBtn_clicked() {
    this->close();
}

void MainWindow::on_simulationBtn_clicked() {
    //模拟数据的时候每次进来都让数据进行重置 不能把tablewidget重置 否则头就没了
    this->_sql->clear();
    //记得对测试表进行初始化 成员属性需要先置空
    this->testList.clear();
    this->InittestList();
    //制作100条学生数据
    for(int i = 0; i < this->testList.size(); ++i) {
        StuInfo info;
        info._name = testList[i];

        auto grade = QRandomGenerator::global()->bounded(7, 10);
        auto uiclass = QRandomGenerator::global()->bounded(1, 9);
        auto age = QRandomGenerator::global()->bounded(12, 16);

        info._grade = grade;
        info._class = uiclass;
        info._age = age;
        info._studentid = i + 1;
        info._phone = "13366666666";
        info._wechat = "XiaoLuBan_OvO";
        this->_sql->addStu(info);
    }

    //创建表来存入测试数据
    int cnt = this->_sql->getStuCount();
    ui->labelCnt->setText(QString("学生数量: %1").arg(QString::number(cnt)));
    this->stus = _sql->getPageStu(0, cnt);
    //创建完了就插入tableWidget
    ui->tableWidget->setRowCount(cnt);
    for(int i = 0; i < stus.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(stus[i]._id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(stus[i]._name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(stus[i]._age)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(stus[i]._grade)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(stus[i]._class)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(stus[i] ._studentid)));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(stus[i]._phone));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(stus[i]._wechat));
    }
}

void MainWindow::on_addBtn_clicked() {
    this->_adddlg.selection = true;
    //这里的类对象不能是指针否则会出错 然后需要调用exec()创建模态对话框!!!!
    this->_adddlg._clear();
    this->_adddlg.exec();
    this->updateTable();
}

void MainWindow::on_changeBtn_clicked() {
    this->_adddlg.selection = false;
    //选中指定的行进行修改
    int row = ui->tableWidget->currentRow();
    if(row < 0) {
        QMessageBox::warning(this, "错误", "没有选择合适的行,请重新选择");
        return;
    }
    //如果行合适就跳出对话框进行修改
    //先获得数据
    StuInfo info;
    //需要把id拿出来 不然执行数据的时候找不到!!!!
    info._id = ui->tableWidget->item(row, 0)->text().toInt();
    info._name = ui->tableWidget->item(row, 1)->text();
    info._age = ui->tableWidget->item(row, 2)->text().toInt();
    info._class = ui->tableWidget->item(row, 3)->text().toInt();
    info._grade = ui->tableWidget->item(row, 4)->text().toInt();
    info._studentid = ui->tableWidget->item(row, 5)->text().toInt();
    info._phone = ui->tableWidget->item(row, 6)->text();
    info._wechat = ui->tableWidget->item(row, 7)->text();

    this->_adddlg._clear();
    this->_adddlg.setData(info);
    this->_adddlg.exec();
    this->updateTable();
}

void MainWindow::on_clearBtn_clicked() {
    this->_sql->clear();
    this->updateTable();
}

void MainWindow::updateTable() {
    ui->tableWidget->clear();
    QStringList l;
    l << "id" << "姓名" << "年龄" << "年级" << "班级" << "学号" << "电话" << "微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    //生成表头之后从stus里面读取数据来进行存储
    int cnt = this->_sql->getStuCount();
    ui->labelCnt->setText(QString("学生数量: %1").arg(QString::number(cnt)));
    //这个是把sql数据库里面存放的数据放到stus表当中了 所以不用担心QList表没有及时更新
    this->stus = _sql->getPageStu(0, cnt);
    //创建完了就插入tableWidget
    ui->tableWidget->setRowCount(cnt);
    for(int i = 0; i < stus.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(stus[i]._id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(stus[i]._name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(stus[i]._age)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(stus[i]._grade)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(stus[i]._class)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(stus[i]._studentid)));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(stus[i]._phone));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(stus[i]._wechat));
    }
}

void MainWindow::updateTable_2() {
    ui->tableWidget_2->clear();
    QStringList l;
    l << "用户名" << "密码" << "身份";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    //TODO
}

void MainWindow::on_updateBtn_clicked() {
    this->updateTable();
}


void MainWindow::on_updageBtn_2_clicked() {
    this->updateTable_2();
}

void MainWindow::on_delBtn_clicked() {
    int row = ui->tableWidget->currentRow();
    if(row < 0) {
        QMessageBox::warning(this, "错误", "没有选择合适的行,请重新选择");
        return;
    }
    auto ret = QMessageBox::question(this, "删除", "你确定要删除吗", QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes) {
        int id = ui->tableWidget->item(row, 0)->text().toInt();
        this->_sql->delStu(id);
        this->updateTable();
        QMessageBox::information(this, "删除", "删除成功!");
    }
}

//现在的功能只能查询一个参数
//TODO
void MainWindow::on_searchBtn_clicked() {
    //获取lineedit里面的文本 先只实现只查询一个参数
    QString linetext = ui->lineEdit->text();
    if(linetext.isEmpty()) {
        QMessageBox::information(this, "提示", "查询语句不能为空!!!");
        return;
    }
    QStringList info_list = linetext.split('=');

    ui->tableWidget->clear();
    QStringList l;
    l << "id" << "姓名" << "年龄" << "年级" << "班级" << "学号" << "电话" << "微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    //遍历所有的数据库内容进行查找
    //先做只查询一个的情况
    int rows = 0;
    for(int i = 0; i < this->stus.size(); ++i) {
        bool flag = false;
        if(info_list[0] == "id") {
            if(info_list[1] == QString::number(stus[i]._id))
                flag = true;
        } else if(info_list[0] == "name") {
            if(info_list[1] == stus[i]._name)
                flag = true;
        } else if(info_list[0] == "age") {
            if(info_list[1] == QString::number(stus[i]._age))
                flag = true;
        } else if(info_list[0] == "grade") {
            if(info_list[1] == QString::number(stus[i]._grade))
                flag = true;
        } else if(info_list[0] == "studentid") {
            if(info_list[1] == QString::number(stus[i]._studentid))
                flag = true;
        } else if(info_list[0] == "phone") {
            if(info_list[1] == stus[i]._phone)
                flag = true;
        } else if(info_list[0] == "wechat") {
            if(info_list[1] == stus[i]._wechat)
                flag = true;
        } else if(info_list[0] == "id") {
            if(info_list[1] == QString::number(stus[i]._id))
                flag = true;
        }
        //查到了就把数据插入表中
        if(flag) {
            //这个i代表第i行
            //用rows来进行行的技术
            ui->tableWidget->setItem(rows, 0, new QTableWidgetItem(QString::number(stus[i]._id)));
            ui->tableWidget->setItem(rows, 1, new QTableWidgetItem(stus[i]._name));
            ui->tableWidget->setItem(rows, 2, new QTableWidgetItem(QString::number(stus[i]._age)));
            ui->tableWidget->setItem(rows, 3, new QTableWidgetItem(QString::number(stus[i]._grade)));
            ui->tableWidget->setItem(rows, 4, new QTableWidgetItem(QString::number(stus[i]._class)));
            ui->tableWidget->setItem(rows, 5, new QTableWidgetItem(QString::number(stus[i]._studentid)));
            ui->tableWidget->setItem(rows, 6, new QTableWidgetItem(stus[i]._phone));
            ui->tableWidget->setItem(rows, 7, new QTableWidgetItem(stus[i]._wechat));
            ++rows;
        }
    }
    //更新学生数量
    ui->labelCnt->setText(QString("学生数量: %1").arg(QString::number(rows)));
}

void MainWindow::InittestList() {
    this->testList.append("阮元岩");
    this->testList.append("牧斐然");
    this->testList.append("滑彬梦");
    this->testList.append("奚尤慧");
    this->testList.append("贺垚喜");
    this->testList.append("刘舟尉");
    this->testList.append("计韵玉");
    this->testList.append("甄蔚宝");
    this->testList.append("武典歌");
    this->testList.append("翁卿溢");
    this->testList.append("富欢洋");
    this->testList.append("凌佳爽");
    this->testList.append("农芊娣");
    this->testList.append("陶乾汉");
    this->testList.append("胡淞心");
    this->testList.append("喻滢敏");
    this->testList.append("申彭烈");
    this->testList.append("赖良莺");
    this->testList.append("廉魁帅");
    this->testList.append("滕或琚");
    this->testList.append("柏润予");
    this->testList.append("章漪吟");
    this->testList.append("洪曼奕");
    this->testList.append("华弛准");
    this->testList.append("祝隽宏");
    this->testList.append("包渊勃");
    this->testList.append("郦艺雄");
    this->testList.append("富列奕");
    this->testList.append("何舒辰");
    this->testList.append("叶曦鑫");
    this->testList.append("奚格岚");
    this->testList.append("瞿稳莹");
    this->testList.append("蔡添征");
    this->testList.append("董伶泳");
    this->testList.append("宫臻轩");
    this->testList.append("仲梅妹");
    this->testList.append("经崧千");
    this->testList.append("柳俭信");
    this->testList.append("范闯垚");
    this->testList.append("费宏中");
    this->testList.append("邵翔希");
    this->testList.append("曹登歆");
    this->testList.append("单艳奇");
    this->testList.append("秋程树");
    this->testList.append("余翰舜");
    this->testList.append("邓影洵");
    this->testList.append("魏心然");
    this->testList.append("褚余峥");
    this->testList.append("松悦姿");
    this->testList.append("姚或盼");
    this->testList.append("魏遥诺");
    this->testList.append("单游莹");
    this->testList.append("韩琳珏");
    this->testList.append("葛磊陵");
    this->testList.append("邢赢舒");
    this->testList.append("水竹璇");
    this->testList.append("郎延能");
    this->testList.append("段歌晴");
    this->testList.append("荣凌秀");
    this->testList.append("滑惠林");
    this->testList.append("杭宇峻");
    this->testList.append("宣思盛");
    this->testList.append("雷蔷艳");
    this->testList.append("崔骏磊");
    this->testList.append("黎铃虹");
    this->testList.append("史淞涌");
    this->testList.append("俞研熠");
    this->testList.append("蒋骊念");
    this->testList.append("马璇娆");
    this->testList.append("萧展普");
    this->testList.append("林霜芮");
    this->testList.append("韩榕品");
    this->testList.append("武开坦");
    this->testList.append("符莲椒");
    this->testList.append("羿恋眉");
    this->testList.append("方仲存");
    this->testList.append("花千里");
    this->testList.append("纪瑛熙");
    this->testList.append("何慈依");
    this->testList.append("郭嫣宝");
    this->testList.append("农肠昀");
    this->testList.append("喻凝一");
    this->testList.append("徐荟盼");
    this->testList.append("农耘淳");
    this->testList.append("荣焰群");
    this->testList.append("郜威淮");
    this->testList.append("王斯恋");
    this->testList.append("屈琼芊");
    this->testList.append("祝曙弛");
    this->testList.append("邵昆里");
    this->testList.append("解瀚亚");
    this->testList.append("司纳樱");
    this->testList.append("华镇来");
    this->testList.append("杜洵灵");
    this->testList.append("蒙凝静");
    this->testList.append("昌含蝶");
    this->testList.append("郭莲诚");
    this->testList.append("屈承涛");
    this->testList.append("符潇开");
    this->testList.append("刘秀钧");
}
