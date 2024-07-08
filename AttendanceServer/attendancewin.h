#ifndef ATTENDANCEWIN_H
#define ATTENDANCEWIN_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <qfaceobject.h>
#include <QSqlTableModel>
#include <QSqlRecord>

QT_BEGIN_NAMESPACE
namespace Ui { class AttendanceWin; }
QT_END_NAMESPACE

class AttendanceWin : public QMainWindow
{
    Q_OBJECT

public:
    AttendanceWin(QWidget *parent = nullptr);
    ~AttendanceWin();
signals:
    void query(cv::Mat& image);
public slots:
    void reloadFaceDataBase();
protected slots:
    void acceptClient();
    void readData();
    void recv_faceid(int64_t faceid);
private:
    Ui::AttendanceWin *ui;
    QTcpServer mserver;
    QTcpSocket *msocket;
    quint64 bsize;

    QFaceObject fObj;
    QSqlTableModel model;
};
#endif // ATTENDANCEWIN_H
