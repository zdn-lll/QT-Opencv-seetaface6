#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>
#include <opencv.hpp>

namespace Ui {
class RegisterWin;
}

class RegisterWin : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWin(QWidget *parent = nullptr);
    ~RegisterWin();
    void timerEvent(QTimerEvent *e);

private slots:
    void on_resetBt_clicked();

    void on_addPicBt_clicked();

    void on_registerBt_clicked();

    void on_videoSwitchBt_clicked();

    void on_cameraBt_clicked();

signals:
    void registe_success();

private:
    Ui::RegisterWin *ui;
    int timerID;
    cv::VideoCapture cap;
    cv::Mat image;
};

#endif // REGISTERWIN_H
