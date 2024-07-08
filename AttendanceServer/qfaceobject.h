#ifndef QFACEOBJECT_H
#define QFACEOBJECT_H

#include <QObject>
#include <seeta/FaceEngine.h>
#include <opencv.hpp>

// 人脸数据存储，人脸检测，人脸识别
class QFaceObject : public QObject
{
    Q_OBJECT
public:
    explicit QFaceObject(QObject *parent = nullptr);
    ~QFaceObject();


public slots:
    int64_t face_register(cv::Mat& faceImgae);
    int face_query(cv::Mat& faceImgae);
    void loadFaceData(QString faceDataBase = "./face.db");

signals:
    void send_faceid(int64_t faceid);

private:
    seeta::FaceEngine *fEnginePtr;
};

#endif // QFACEOBJECT_H
