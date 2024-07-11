#include "attendancewin.h"
#include "ui_attendancewin.h"
#include "registerwin.h"

#include <QDateTime>
#include <QThread>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

AttendanceWin::AttendanceWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceWin)
{
    ui->setupUi(this);

    connect(&mserver, &QTcpServer::newConnection, this, &AttendanceWin::acceptClient);

    mserver.listen(QHostAddress::Any, 9999); // 监听启动服务器

    bsize = 0;

    // 给sql模型绑定表格
    model.setTable("employee");

    // 创建一个线程
    QThread *thread = new QThread();
    // 把 QFaceObject 对象移动到 thread 线程中执行
    fObj.moveToThread(thread);
    // 启动线程
    thread->start();
    connect(this, &AttendanceWin::query, &fObj, &QFaceObject::face_query);
    // 关联 QFaceObject 对象里面的 send_faceid 信号
    connect(&fObj, &QFaceObject::send_faceid, this, &AttendanceWin::recv_faceid);

    connect(ui->registerWidget, &RegisterWin::registe_success, this, &AttendanceWin::reloadFaceDataBase);

}

AttendanceWin::~AttendanceWin()
{
    delete ui;
}

void AttendanceWin::reloadFaceDataBase()
{
    fObj.loadFaceData();
}

void AttendanceWin::acceptClient()
{
    // 获取客户端通信套接字
    msocket = mserver.nextPendingConnection();

    // 当客户端有数据到达 发送 readyRead 信号
    connect(msocket, &QTcpSocket::readyRead, this, &AttendanceWin::readData);
}

void AttendanceWin::readData()
{
    // 读取数据流
    QDataStream stream(msocket); // 把套接字绑定到数据流
    stream.setVersion(QDataStream::Qt_5_7); // 与发动端版本相同

    if(0 == bsize)
    {
        if(msocket->bytesAvailable() < (qint64)sizeof(bsize))
            return;
        // 采集数据长度
        stream >> bsize;
    }

    if(msocket->bytesAvailable() < (qint64)bsize) // 说明数据还没有发送完成，返回继续等待
        return;

    QByteArray data;
    stream >> data;
    bsize = 0;
    if(0 == data.size()) // 没有读取到数据
        return;

    // 显示图片
    QPixmap mmp;
    mmp.loadFromData(data, "jpg");
    mmp = mmp.scaled(ui->picLb->size());
    ui->picLb->setPixmap(mmp);

    // 人脸识别
    cv::Mat faceImage;
    std::vector<uchar> decode;
    decode.resize(data.size());
    memcpy(decode.data(), data.data(), data.size());
    faceImage = cv::imdecode(decode, cv::IMREAD_COLOR);
//    int faceid = fObj.face_query(faceImage); // 消耗资源较多
    emit query(faceImage);

}

void AttendanceWin::recv_faceid(int64_t faceid)
{
    qDebug() << "faceid: " <<faceid;

    // 从数据库中查询faceID对应的个人信息
    // 给模型设置过滤器
    if(faceid < 0)
    {
        QString sdmsg = "{\"employeeID\":\"\", \"name\":\"\", \"department\":\"\", \"time\":\"\"}";
        msocket->write(sdmsg.toUtf8());
        return;
    }
//    model.setTable("employee");
    model.setFilter(QString("faceID=%1").arg(faceid));
    // 查询
    model.select();
    // 判断是否查询到数据
    if(model.rowCount() == 1)
    {
        // 工号 姓名 部门 时间
        // {"employeeID":"%1", "name":"%2", "department":"软件", "time":"%3"}
        QSqlRecord record = model.record(0);
        QString sdmsg = QString("{\"employeeID\":\"%1\", \"name\":\"%2\", \"department\":\"%3\", \"time\":\"%4\"}")
                .arg(record.value("employeeID").toString())
                .arg(record.value("name").toString())
                .arg(record.value("department").toString())
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh::mm::ss"));


//        model.setTable("attendance");
        // 把考勤数据插入数据库
        QString insertSql = QString("INSERT INTO attendance(employeeID, department, name) VALUES ('%1', '%2', '%3')")
                .arg(record.value("employeeID").toString())
                .arg(record.value("department").toString())
                .arg(record.value("name").toString());
        QSqlQuery query;
        if(!query.exec(insertSql))
        {
            qDebug() << "考勤表插入失败";
            qDebug() << query.lastError().text();
            QString sdmsg = "{\"employeeID\":\"\", \"name\":\"\", \"department\":\"\", \"time\":\"\"}";
            msocket->write(sdmsg.toUtf8());
            return;
        }
        else
        {
            qDebug() << "考勤表插入成功";
            msocket->write(sdmsg.toUtf8()); // 把打包好的数据发送到客户端
        }
    }
}
