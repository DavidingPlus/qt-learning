#include "stusql.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

StuSql* StuSql::ptrstuSql = nullptr;

StuSql* StuSql::getinstance() {
    if (nullptr == ptrstuSql) // 静态变量判空最好nullptr放前面
        ptrstuSql = new StuSql;
    return ptrstuSql;
}

StuSql::StuSql(QWidget* parent)
    : QWidget{parent} {
    this->__init__();
}

void StuSql::__init__() {
    //    连接成功 用ODBC来实现qt和mysql的连接
    this->db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1"); // 连接本地主机
    db.setPort(3306);
    db.setDatabaseName("mysql2");
    db.setUserName("root");
    db.setPassword("05121428");
    bool ok = db.open();
    if (ok)
        // 这个this 需要的是个QWidget对象
        // 成功就不发声明了
        QMessageBox::information(this, "success", "恭喜您,数据库连接成功");
//        ;
    else {
        QMessageBox::information(this, "failed", "非常抱歉,数据库连接失败,请退出重试");
        exit(0);
    }

    // 做一些测试 用于测试连接之后数据能否插入
    // 测试成功
    //     QSqlQuery q("", db);
    //     q.exec("INSERT INTO student VALUES (NULL, '张三', 12, 3, 2, 1, 15940224444, 'asdzhang');");
}

// 实现类函数
int StuSql::getStuCount() {
    QSqlQuery sql(this->db);
    sql.exec("select count(id) from student");
    int cnt = 0;
    while (sql.next())
        cnt = sql.value(0).toInt();
    return cnt;
}

QList<StuInfo> StuSql::getPageStu(int page, int count) {
    QList<StuInfo> l;
    QSqlQuery sql(this->db);
    QString strsql = QString("select * from student order by id limit %1 offset %2").arg(count).arg(page * count);
    sql.exec(strsql);

    StuInfo info;
    while (sql.next()) {
        info._id = sql.value(0).toInt();
        info._name = sql.value(1).toString();
        info._age = sql.value(2).toInt();
        info._grade = sql.value(3).toInt();
        info._class = sql.value(4).toInt();
        info._studentid = sql.value(5).toInt();
        info._phone = sql.value(6).toString();
        info._wechat = sql.value(7).toString();
        l.push_back(info);
    }
    return l;
}

void StuSql::addStu(StuInfo info) {
    QSqlQuery sql(this->db);
    // 注意这里名字需要加引号 因为字符串里面存着的不带引号
    QString strsql = QString("insert into student values(null,'%1',%2,%3,%4,%5,'%6','%7');").arg(info._name).arg(info._age).arg(info._grade).arg(info._class).arg(info._studentid).arg(info._phone).arg(info._wechat);
    sql.exec(strsql);
}

void StuSql::delStu(int id) {
    QSqlQuery sql(this->db);
    QString strsql = QString("delete from student where id = %1;").arg(id);
    sql.exec(strsql);
}

void StuSql::clear() {
    QSqlQuery sql(this->db);
    // 这个语句可以用来删除整个表内的所有数据 包括自动生成的id 这样之后第一个自动生成的id就是1了
    sql.exec("truncate table student");
}

void StuSql::updateStuInfo(StuInfo info) {
    QSqlQuery sql(this->db);
    QString strsql = QString("update student set name='%1',age=%2,grade=%3,class=%4,studentid=%5,phone='%6',wechat='%7' where id=%8;")
                     .arg(info._name)
                     .arg(info._age)
                     .arg(info._grade)
                     .arg(info._class)
                     .arg(info._studentid)
                     .arg(info._phone)
                     .arg(info._wechat)
                     .arg(info._id);
    sql.exec(strsql);
}

QList<UserInfo> StuSql::getAllUser() {
    QList<UserInfo> l;
    QSqlQuery sql(this->db);
    QString strsql = QString("select * from user");
    sql.exec(strsql);

    UserInfo info;
    while (sql.next()) {
        info._username = sql.value(0).toString();
        info._password = sql.value(1).toString();
        info._aut = sql.value(2).toString();
        l.push_back(info);
    }
    return l;
}

bool StuSql::isExist(QString username) {
    QSqlQuery sql(this->db);
    QString strsql = QString("select *from user where username='%1';").arg(username);
    sql.exec(strsql);
    return sql.next();
}

void StuSql::updateUserInfo(UserInfo info) {
    QSqlQuery sql(this->db);
    QString strsql = QString("update user set "
                             "password='%1',aut='%2' where username='%3';")
                     .arg(info._password)
                     .arg(info._aut)
                     .arg(info._username);
    sql.exec(strsql);
}

void StuSql::addUser(UserInfo info) {
    QSqlQuery sql(this->db);
    // 注意这里名字需要加引号 因为字符串里面存着的不带引号
    QString strsql = QString("insert into user values('%1','%2','%3');")
                     .arg(info._username)
                     .arg(info._password)
                     .arg(info._aut);
    sql.exec(strsql);
}

void StuSql::delUser(QString username) {
    QSqlQuery sql(this->db);
    QString strsql = QString("delete from user where username = '%1';").arg(username);
    sql.exec(strsql);
}
