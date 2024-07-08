#include "faceattendance.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FaceAttendance w;
    w.show();
    return a.exec();
}
