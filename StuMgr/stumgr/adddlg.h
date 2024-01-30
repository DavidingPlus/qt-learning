#ifndef ADDDLG_H
#define ADDDLG_H

#include <QDialog>
#include "stusql.h"

namespace Ui
{
    class AddDlg;
}

class AddDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddDlg(QWidget *parent = nullptr);
    ~AddDlg();

    void _clear();

    void setData(StuInfo info);

    bool selection; // true表示增加 false表示修改
    int updateID;   // 需要被更新的id

private slots:
    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::AddDlg *ui;
};

#endif // ADDDLG_H
