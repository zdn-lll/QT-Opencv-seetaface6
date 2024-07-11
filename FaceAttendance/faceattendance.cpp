#include "faceattendance.h"
#include "ui_faceattendance.h"

#include <QBuffer>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

FaceAttendance::FaceAttendance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FaceAttendance)
{
    ui->setupUi(this);
    // 打开摄像头
    cap.open(1); //dev/video;
    // 启动定时器时间
    startTimer(100);

    // 导入级联分类器文件
    cascade.load("C:/opencv452/etc/haarcascades/haarcascade_frontalface_alt2.xml");

    isConnect = 0;
    // QTcpSocket 断开信号 disconnected 连接成功信号 connected
    connect(&msocket, &QTcpSocket::disconnected, this, &FaceAttendance::start_connect);
    connect(&msocket, &QTcpSocket::connected, this, &FaceAttendance::stop_connect);
    // 关联接收数据的槽函数
    connect(&msocket, &QTcpSocket::readyRead, this, &FaceAttendance::recv_data);

    // 定时连接服务器
    connect(&mtimer, &QTimer::timeout, this, &FaceAttendance::timer_connect);
    // 启动定时器
    mtimer.start(5000); // 每5秒连接一次，直到连接成功，就不再连接

    flag = 0;

    ui->certificationWidget->hide();
//    ui->headpicLb->hide();
}

FaceAttendance::~FaceAttendance()
{
    delete ui;
}

void FaceAttendance::timerEvent(QTimerEvent *e)
{
    // 采集数据
    Mat srcImgae;
    if(cap.grab())
    {
        cap.read(srcImgae);
    }

    // 把图片大小设置为显示窗口大小一样
    cv::resize(srcImgae, srcImgae, Size(ui->vdieoLb->width(), ui->vdieoLb->height()));

    if(srcImgae.data == nullptr) return;
    // 把opencv里面的Mat格式数据（BGR）转为 QT 中的（RGB）
    cvtColor(srcImgae, srcImgae, COLOR_BGR2RGB);
    QImage image(srcImgae.data, srcImgae.cols, srcImgae.rows, srcImgae.step1(), QImage::Format_RGB888);
    QPixmap mmp = QPixmap::fromImage(image);
//    mmp = mmp.scaledToWidth(ui->vdieoLb->width());
    ui->vdieoLb->setPixmap(mmp);

    // 转灰度图加快检测速度
    Mat grayImage;
    cvtColor(srcImgae, grayImage, COLOR_RGB2GRAY);
    // 检测人脸数据
    vector<Rect> faceRects;
    cascade.detectMultiScale(srcImgae, faceRects, 1.1,3,0,cv::Size(150,150)); // 设置最小检测大小，减少性能开支
    ui->headpicLb->show();
    if(faceRects.size() > 0 && flag >= 0)
    {

        Rect rect = faceRects.at(0); // 第一个人脸矩形框
//        rectangle(srcImgae, rect, Scalar(255, 0, 0));

        // 移动人脸框(headpicLb)
        ui->headpicLb->move(rect.x, rect.y);

        if(flag > 2 && isConnect)
        {
//            // 把Mat数据转化为QbyteArray --> 编码成jpg
//            vector<uchar> buf;
//            imencode(".jpg", srcImgae, buf);
//            QByteArray byte((const char*)buf.data(), buf.size());

            // QImage转换为QByteArray
            QByteArray byte;
            QBuffer buffer(&byte);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "jpg");
            buffer.close();

            // 准备发送
            quint64 backsize = byte.size();
            QByteArray sendData;
            // 创建流
            QDataStream stream(&sendData, QIODevice::WriteOnly);
            stream.setVersion(QDataStream::Qt_5_14); // 指定数据流版本
            stream << backsize << byte; // 数据格式：图片大小(quint64 8字节)+图片数据

            // 发送
            msocket.write(sendData);
            flag = -2;
            qDebug() << "send";

            faceMat = srcImgae(rect);
            // 保存
            cvtColor(faceMat, faceMat, COLOR_BGR2RGB);
            imwrite("./face.jpg", faceMat);
        }

        flag++;
    }
    if(faceRects.size() == 0)
    {
        // 把人脸框移动到中心位置
        ui->headpicLb->move(100, 60);
        ui->headpicLb->hide();
        flag = 0;
        ui->certificationWidget->hide();
    }


}

void FaceAttendance::recv_data()
{
    // {"employeeID":"%1", "name":"%2", "department":"软件", "time":"%3"}
    QByteArray array = msocket.readAll();
    qDebug() << array;
    // Json解析
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(array, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug() << "json fomat err";
        return ;
    }

    QJsonObject obj = doc.object();
    QString employeeID = obj.value("employeeID").toString();
    QString name = obj.value("name").toString();
    QString department = obj.value("department").toString();
    QString time = obj.value("time").toString();

    ui->numberEdit->setText(employeeID);
    ui->nameEdit->setText(name);
    ui->departmentEdit->setText(department);
    ui->timeEdit->setText(time);

    // 通过样式显示图片
    ui->headLb->setStyleSheet("border-radius:75px;border-image: url(./face.jpg);");
    if(employeeID.isEmpty())
    {
        ui->certifiedImgLb->setStyleSheet("border-image: url(:/img/no.png);");
        ui->certifiedTextLb->setText("认证失败");
    }
    else
    {
        ui->certifiedImgLb->setStyleSheet("border-image: url(:/img/yes.png);");
        ui->certifiedTextLb->setText("认证成功");
    }
    ui->certificationWidget->show();
}

void FaceAttendance::timer_connect()
{
    // 连接服务器
    qDebug() << "linking...";
    msocket.connectToHost("127.0.0.1",9999);
}

void FaceAttendance::stop_connect()
{
    mtimer.stop();
    qDebug() << "Success!!";
    isConnect = 1;
}

void FaceAttendance::start_connect()
{
    mtimer.start(5000);
    qDebug() << "start to relink...";
    isConnect = 0;
}



