#include "qfaceobject.h"
#include <QDebug>

QFaceObject::QFaceObject(QObject *parent) : QObject(parent)
{
    // 初始化
    seeta::ModelSetting FD_model("C:/SeetaFace/bin/model/fd_2_00.dat", seeta::ModelSetting::GPU, 0);
    seeta::ModelSetting PD_model("C:/SeetaFace/bin/model/pd_2_00_pts5.dat", seeta::ModelSetting::GPU, 0);
    seeta::ModelSetting FR_model("C:/SeetaFace/bin/model/fr_2_10.dat", seeta::ModelSetting::GPU, 0);
    this->fEnginePtr = new seeta::FaceEngine(FD_model, PD_model, FR_model);

    // 导入已有的人脸数据库
    this->fEnginePtr->Load("./face.db");
}

QFaceObject::~QFaceObject()
{
    delete  fEnginePtr;
}

void QFaceObject::loadFaceData(QString faceDataBase)
{
//     导入已有的人脸数据库
    this->fEnginePtr->Clear();
    this->fEnginePtr->Load(faceDataBase.toUtf8());
}

int64_t QFaceObject::face_register(cv::Mat &faceImgae)
{
    // 将opencv的Mat数据转换为seetaface的数据
    SeetaImageData sImage;
    sImage.data = faceImgae.data;
    sImage.width = faceImgae.cols;
    sImage.height = faceImgae.rows;
    sImage.channels = faceImgae.channels();
    int64_t faceId =  this->fEnginePtr->Register(sImage); // 注册返回人脸id
    if(faceId >= 0)
    {
        fEnginePtr->Save("./face.db");
    }
    return  faceId;
}

int QFaceObject::face_query(cv::Mat &faceImgae)
{
    // 将opencv的Mat数据转换为seetaface的数据
    SeetaImageData sImage;
    sImage.data = faceImgae.data;
    sImage.width = faceImgae.cols;
    sImage.height = faceImgae.rows;
    sImage.channels = faceImgae.channels();
    float similarity = 0;
    int64_t faceId = fEnginePtr->Query(sImage, &similarity); // 运行时间较长
    qDebug() << faceId << ": " << similarity;
    if(similarity > 0.7)
        emit send_faceid(faceId);
    else
        emit send_faceid(-1);
    return  faceId;
}
