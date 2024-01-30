#include "ui_adddlg.h"
#include "stusql.h"
#include <QMessageBox>
#include "adddlg.h"

AddDlg::AddDlg(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::AddDlg)
{
    ui->setupUi(this);
}

AddDlg::~AddDlg()
{
    delete ui;
}

void AddDlg::_clear()
{
    // 把控件中的所有值清空
    ui->lineClass->clear();
    ui->lineGrade->clear();
    ui->lineName->clear();
    ui->linePhone->clear();
    ui->lineStuID->clear();
    ui->lineWechat->clear();
    ui->spinBoxAge->setValue(0);
}

void AddDlg::setData(StuInfo info)
{
    // 更新一下updateID
    this->updateID = info._id;
    ui->lineName->setText(info._name);
    ui->spinBoxAge->setValue(info._age);
    ui->lineClass->setText(QString::number(info._class));
    ui->lineGrade->setText(QString::number(info._grade));
    ui->lineStuID->setText(QString::number(info._studentid));
    ui->linePhone->setText(info._phone);
    ui->lineWechat->setText(info._wechat);
}

void AddDlg::on_cancelBtn_clicked()
{
    this->close();
}

void AddDlg::on_saveBtn_clicked()
{
    // 如何判断是增加还是修改
    // 看selection
    auto ptr = StuSql::getinstance();
    StuInfo info;
    info._name = ui->lineName->text();
    info._age = ui->spinBoxAge->text().toInt();
    info._class = ui->lineClass->text().toInt();
    info._grade = ui->lineGrade->text().toInt();
    info._studentid = ui->lineStuID->text().toInt();
    info._phone = ui->linePhone->text();
    info._wechat = ui->lineWechat->text();
    if (selection)
    {
        ptr->addStu(info);
        QMessageBox::information(this, "增加", "存储成功");
    }
    else
    {
        info._id = this->updateID;
        ptr->updateStuInfo(info); // 之前很多次失败的原因 没传id 导致找不到!!!!
        QMessageBox::information(this, "修改", "修改成功");
    }
    this->close();
}
