/********************************************************************************
** Form generated from reading UI file 'faceattendance.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEATTENDANCE_H
#define UI_FACEATTENDANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceAttendance
{
public:
    QWidget *centralwidget;
    QWidget *videoWidget;
    QWidget *certificationWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *headpicLb;
    QLabel *vdieoLb;
    QWidget *widget_3;
    QLabel *titleLb;
    QLabel *headLb;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *numberEdit;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *nameEdit;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *departmentEdit;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *timeEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;

    void setupUi(QMainWindow *FaceAttendance)
    {
        if (FaceAttendance->objectName().isEmpty())
            FaceAttendance->setObjectName(QStringLiteral("FaceAttendance"));
        FaceAttendance->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FaceAttendance->sizePolicy().hasHeightForWidth());
        FaceAttendance->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(FaceAttendance);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        videoWidget = new QWidget(centralwidget);
        videoWidget->setObjectName(QStringLiteral("videoWidget"));
        videoWidget->setGeometry(QRect(0, 0, 480, 480));
        videoWidget->setStyleSheet(QStringLiteral(""));
        certificationWidget = new QWidget(videoWidget);
        certificationWidget->setObjectName(QStringLiteral("certificationWidget"));
        certificationWidget->setGeometry(QRect(105, 360, 270, 60));
        certificationWidget->setStyleSheet(QLatin1String("background-color: rgb(49, 50, 54, 0.8);\n"
"border-radius: 10px;"));
        horizontalLayout_2 = new QHBoxLayout(certificationWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(certificationWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(40, 31));
        label->setStyleSheet(QStringLiteral("border-image: url(:/img/yes.png);"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(certificationWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 25 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221 Light\";\n"
"border:none;\n"
"background-color: rgba(0, 0, 0, 0);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        headpicLb = new QLabel(videoWidget);
        headpicLb->setObjectName(QStringLiteral("headpicLb"));
        headpicLb->setGeometry(QRect(100, 60, 266, 266));
        headpicLb->setStyleSheet(QStringLiteral("border-image: url(:/img/crc.png);"));
        vdieoLb = new QLabel(videoWidget);
        vdieoLb->setObjectName(QStringLiteral("vdieoLb"));
        vdieoLb->setGeometry(QRect(0, 0, 480, 480));
        vdieoLb->raise();
        certificationWidget->raise();
        headpicLb->raise();
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(480, 0, 320, 480));
        widget_3->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border:1px solid #313236;\n"
"	border-radius:4px;\n"
"	background-color: rgba(37, 40, 49, 0.9);\n"
"}\n"
"\n"
"QWidget#titleLb{\n"
"	\n"
"	font: 24pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#headLb{\n"
"	border-radius:75px;\n"
"}"));
        titleLb = new QLabel(widget_3);
        titleLb->setObjectName(QStringLiteral("titleLb"));
        titleLb->setGeometry(QRect(0, 0, 320, 61));
        titleLb->setAlignment(Qt::AlignCenter);
        headLb = new QLabel(widget_3);
        headLb->setObjectName(QStringLiteral("headLb"));
        headLb->setGeometry(QRect(90, 80, 150, 150));
        layoutWidget = new QWidget(widget_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 240, 301, 231));
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(layoutWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border:1px solid #313236;\n"
"	border-radius:4px;\n"
"	background-color: rgba(37, 40, 49, 0.9);\n"
"}\n"
"\n"
"QLabel{\n"
"	border:none;\n"
"	font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(168, 168, 168);\n"
"}\n"
"\n"
"QLineEdit{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        numberEdit = new QLineEdit(widget_4);
        numberEdit->setObjectName(QStringLiteral("numberEdit"));
        numberEdit->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(numberEdit->sizePolicy().hasHeightForWidth());
        numberEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(numberEdit);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(widget_4);

        widget_5 = new QWidget(layoutWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border:1px solid #313236;\n"
"	border-radius:4px;\n"
"	background-color: rgba(37, 40, 49, 0.9);\n"
"}\n"
"\n"
"QLabel{\n"
"	border:none;\n"
"	font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(168, 168, 168);\n"
"}\n"
"\n"
"QLineEdit{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(widget_5);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_10 = new QLabel(widget_5);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_7->addWidget(label_10);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        nameEdit = new QLineEdit(widget_5);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setEnabled(false);
        sizePolicy1.setHeightForWidth(nameEdit->sizePolicy().hasHeightForWidth());
        nameEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(nameEdit);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_5->addWidget(widget_5);

        widget_6 = new QWidget(layoutWidget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border:1px solid #313236;\n"
"	border-radius:4px;\n"
"	background-color: rgba(37, 40, 49, 0.9);\n"
"}\n"
"\n"
"QLabel{\n"
"	border:none;\n"
"	font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(168, 168, 168);\n"
"}\n"
"\n"
"QLineEdit{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(widget_6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_11 = new QLabel(widget_6);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_8->addWidget(label_11);

        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        departmentEdit = new QLineEdit(widget_6);
        departmentEdit->setObjectName(QStringLiteral("departmentEdit"));
        departmentEdit->setEnabled(false);
        sizePolicy1.setHeightForWidth(departmentEdit->sizePolicy().hasHeightForWidth());
        departmentEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(departmentEdit);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_5->addWidget(widget_6);

        widget_7 = new QWidget(layoutWidget);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border:1px solid #313236;\n"
"	border-radius:4px;\n"
"	background-color: rgba(37, 40, 49, 0.9);\n"
"}\n"
"\n"
"QLabel{\n"
"	border:none;\n"
"	font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(168, 168, 168);\n"
"}\n"
"\n"
"QLineEdit{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(widget_7);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_12 = new QLabel(widget_7);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_9->addWidget(label_12);

        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        timeEdit = new QLineEdit(widget_7);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setEnabled(false);
        sizePolicy1.setHeightForWidth(timeEdit->sizePolicy().hasHeightForWidth());
        timeEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(timeEdit);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_5->addWidget(widget_7);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        FaceAttendance->setCentralWidget(centralwidget);

        retranslateUi(FaceAttendance);

        QMetaObject::connectSlotsByName(FaceAttendance);
    } // setupUi

    void retranslateUi(QMainWindow *FaceAttendance)
    {
        FaceAttendance->setWindowTitle(QApplication::translate("FaceAttendance", "FaceAttendance", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("FaceAttendance", "\350\256\244\350\257\201\346\210\220\345\212\237", 0));
        headpicLb->setText(QString());
        vdieoLb->setText(QString());
        titleLb->setText(QApplication::translate("FaceAttendance", "\344\272\272\350\204\270\350\257\206\345\210\253\350\200\203\345\213\244\347\263\273\347\273\237", 0));
        headLb->setText(QString());
        label_6->setText(QApplication::translate("FaceAttendance", "\345\267\245\345\217\267", 0));
        numberEdit->setText(QApplication::translate("FaceAttendance", "001", 0));
        label_10->setText(QApplication::translate("FaceAttendance", "\345\247\223\345\220\215", 0));
        nameEdit->setText(QApplication::translate("FaceAttendance", "001", 0));
        label_11->setText(QApplication::translate("FaceAttendance", "\351\203\250\351\227\250", 0));
        departmentEdit->setText(QApplication::translate("FaceAttendance", "001", 0));
        label_12->setText(QApplication::translate("FaceAttendance", "\346\227\266\351\227\264", 0));
        timeEdit->setText(QApplication::translate("FaceAttendance", "001", 0));
    } // retranslateUi

};

namespace Ui {
    class FaceAttendance: public Ui_FaceAttendance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEATTENDANCE_H
