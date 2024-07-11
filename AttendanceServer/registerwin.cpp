#include "registerwin.h"
#include "ui_registerwin.h"

#include <QFileDialog>
#include <qfaceobject.h>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>
#include "qfaceobject.h"

RegisterWin::RegisterWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWin)
{
    ui->setupUi(this);
}

RegisterWin::~RegisterWin()
{
    delete ui;
}

void RegisterWin::timerEvent(QTimerEvent *e)
{
    // 获取摄像头数据，并显示
    if(cap.isOpened())
    {
        cap >> image;
        if(image.data == nullptr)
            return;
    }
    // Mat --> QImage
    cv::Mat rgbImage;
    cv::cvtColor(image, rgbImage, cv::COLOR_BGR2RGB);
    QImage qImg(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step1(), QImage::Format_RGB888);
    // 在QT界面上显示
    QPixmap mmp = QPixmap::fromImage(qImg);
    mmp = mmp.scaledToWidth(ui->headPicLb->width());
    ui->headPicLb->setPixmap(mmp);
}

void RegisterWin::on_resetBt_clicked()
{
    // 清空数据
    ui->nameEdit->clear();
    ui->birthdayEdit->setDate(QDate::currentDate());
    ui->addressEdit->clear();
    ui->phoneEdit->clear();
    ui->picFileEdit->clear();
}

void RegisterWin::on_addPicBt_clicked()
{
    // 通过文件对话框，选择图片路径
    QString filePath = QFileDialog::getOpenFileName(this);
    ui->picFileEdit->setText(filePath);

    // 显示图片
    QPixmap mmp(filePath);
    mmp = mmp.scaledToWidth(ui->headPicLb->width());
    ui->headPicLb->setPixmap(mmp);
}

void RegisterWin::on_registerBt_clicked()
{
    // 1、通过照片，结合 faceObject 模块得到 faceID
    QFaceObject faceObj;
    cv::Mat image = cv::imread(ui->picFileEdit->text().toUtf8().data());
    int faceID = faceObj.face_register(image);
    qDebug() << faceID;
    // 把头像保存在一个固定路径下
    QString headFile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    cv::imwrite(headFile.toUtf8().data(), image);

    // 2、把个人信息存储到数据库
    QSqlTableModel model;
    model.setTable("employee"); // 设置表名
    QSqlRecord record = model.record();
    // 设置数据
    record.setValue("department", ui->departmentEdit->text());
    record.setValue("name", ui->nameEdit->text());
    record.setValue("sex", ui->maleRb->isChecked()?"男":"女");
    record.setValue("birthday", ui->birthdayEdit->text());
    record.setValue("address", ui->addressEdit->text());
    record.setValue("phone", ui->phoneEdit->text());
    record.setValue("faceID", faceID);
    // 头像路径
    record.setValue("headFile", headFile);
    // 把记录插入到数据库表格中
    bool ret = model.insertRecord(0, record);

    // 3、提示注册成功
    if(ret)
    {
        QMessageBox::information(this, "注册提示", "注册成功");
        // 提交
        model.submitAll();
//        faceObj.loadFaceData();
        emit registe_success();
    }
    else
    {
        QMessageBox::information(this, "注册提示", "注册失败");
    }

}

void RegisterWin::on_videoSwitchBt_clicked()
{
    if(ui->videoSwitchBt->text() == "打开摄像头")
    {
        // 打开摄像头
        if(cap.open(0)) // 0 打开默认摄像头
        {
            ui->videoSwitchBt->setText("关闭摄像头");
            // 启动定时器事件
            timerID = startTimer(100);
        }
    }
    else
    {
        killTimer(timerID); // 关闭定时器
        ui->videoSwitchBt->setText("打开摄像头");
        // 关闭摄像头
        cap.release();
    }
}

void RegisterWin::on_cameraBt_clicked()
{
    // 保存数据
    // 把头像保存在一个固定路径下
    QString headFile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    ui->picFileEdit->setText(headFile);
    cv::imwrite(headFile.toUtf8().data(), image);
    killTimer(timerID); // 关闭定时器
    ui->videoSwitchBt->setText("打开摄像头");
    // 关闭摄像头
    cap.release();
}
