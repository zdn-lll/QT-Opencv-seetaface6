#include "attendancewin.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <opencv.hpp>
#include "registerwin.h"
#include "selectwin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<int64_t>("int64_t");

//    RegisterWin w1;
//    w1.show();

    // 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库名称
    db.setDatabaseName("server.db");
    // 打开数据库
    if(!db.open())
    {
        qDebug() << db.lastError().text();
        return -1;
    }
    // 创建员工信息表
    QString createSql = "CREATE TABLE "
                        "IF NOT EXISTS "
                        "employee("
                        "employeeID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "name VARCHAR(256),"
                        "sex VARCHAR(256),"
                        "birthday TEXT,"
                        "address TEXT,"
                        "phone TEXT,"
                        "faceID INTEGER UNIQUE,"
                        "headFile TEXT"
                        ")";
    QSqlQuery query;
    if(!query.exec(createSql))
    {
        qDebug() << query.lastError().text();
        return  -1;
    }

    // 创建考勤表
    createSql.clear();
    createSql = "CREATE TABLE "
                "IF NOT EXISTS "
                "attendance("
                "attendanceID INTEGER PRIMARY KEY AUTOINCREMENT,"
                "employeeID INTEGER,"
                "attendanceTime TimeStamp NOT NULL DEFAULT(datetime('now','localtime'))"
                ")";
    if(!query.exec(createSql))
    {
        qDebug() << query.lastError().text();
        return  -1;
    }

    AttendanceWin w;
    w.show();

//    SelectWin w2;
//    w2.show();
    return a.exec();
}
