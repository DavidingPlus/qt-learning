#ifndef STUSQL_H
#define STUSQL_H

#include <QWidget>
#include <QSqlDatabase>

// 学生信息
struct StuInfo
{
    int _id;
    QString _name;
    int _age;
    int _grade;
    int _class;
    int _studentid;
    QString _phone;
    QString _wechat;
};

// 用户信息
struct UserInfo
{
    QString _username;
    QString _password;
    QString _aut;
};

class StuSql : public QWidget
{
    Q_OBJECT
public:
    static StuSql *ptrstuSql;
    static StuSql *getinstance();

    explicit StuSql(QWidget *parent = nullptr);

    // 初始化
    void __init__();
    // 查询所有学生数量
    int getStuCount();
    // 查询第几页学生数据 页数从0开始
    QList<StuInfo> getPageStu(int page, int count); // 参数1 页数 参数2 数量
    // 增加学生
    void addStu(StuInfo);
    // 删除学生
    void delStu(int id);
    // 清空学生表
    void clear();
    // 修改学生信息
    void updateStuInfo(StuInfo info);
    // 查询所有用户
    QList<UserInfo> getAllUser();
    // 查询用户名是否存在
    bool isExist(QString username);
    // 更新用户信息
    void updateUserInfo(UserInfo info);
    // 添加单个用户
    void addUser(UserInfo info);
    // 删除单个用户
    void delUser(QString username);
signals:

private:
    QSqlDatabase db; // 创建数据库连接对象
};

#endif // STUSQL_H
