/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QSpinBox *spinBox_widthPoints;
    QSpinBox *spinBox_heightPoints;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QDoubleSpinBox *spinBox_chessboardSize;
    QLabel *label_4;
    QGroupBox *groupBox_internal;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_imageFile;
    QLineEdit *lineEdit_imageFile;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_internalCal;
    QGroupBox *groupBox_external;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pushButton_leftCorners;
    QPushButton *pushButton_leftIntrinsic;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_leftCorners;
    QLineEdit *lineEdit_leftIntrinsic;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pushButton_rightCorners;
    QPushButton *pushButton_rightIntrinsic;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *lineEdit_rightCorners;
    QLineEdit *lineEdit_rightIntrinsic;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_savePath;
    QLineEdit *lineEdit_savePath;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_externalCal;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_10;
    QPushButton *pushButton_leftCoords;
    QPushButton *pushButton_rightCoords;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEdit_leftCoords;
    QLineEdit *lineEdit_rightCoords;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_projectionFile;
    QLineEdit *lineEdit_projectionFile;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_reconstuctionCal;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(503, 530);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_11 = new QVBoxLayout(centralWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 70));
        groupBox_3->setMaximumSize(QSize(16777215, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        groupBox_3->setFont(font);
        horizontalLayout_7 = new QHBoxLayout(groupBox_3);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        spinBox_widthPoints = new QSpinBox(groupBox_3);
        spinBox_widthPoints->setObjectName(QString::fromUtf8("spinBox_widthPoints"));
        spinBox_widthPoints->setValue(12);

        verticalLayout->addWidget(spinBox_widthPoints);

        spinBox_heightPoints = new QSpinBox(groupBox_3);
        spinBox_heightPoints->setObjectName(QString::fromUtf8("spinBox_heightPoints"));
        spinBox_heightPoints->setValue(9);

        verticalLayout->addWidget(spinBox_heightPoints);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBox_chessboardSize = new QDoubleSpinBox(groupBox_3);
        spinBox_chessboardSize->setObjectName(QString::fromUtf8("spinBox_chessboardSize"));
        spinBox_chessboardSize->setMaximum(100.000000000000000);
        spinBox_chessboardSize->setValue(16.000000000000000);

        horizontalLayout->addWidget(spinBox_chessboardSize);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);


        horizontalLayout_7->addLayout(horizontalLayout);


        verticalLayout_11->addWidget(groupBox_3);

        groupBox_internal = new QGroupBox(centralWidget);
        groupBox_internal->setObjectName(QString::fromUtf8("groupBox_internal"));
        groupBox_internal->setMinimumSize(QSize(0, 55));
        groupBox_internal->setMaximumSize(QSize(16777215, 55));
        horizontalLayout_3 = new QHBoxLayout(groupBox_internal);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_imageFile = new QPushButton(groupBox_internal);
        pushButton_imageFile->setObjectName(QString::fromUtf8("pushButton_imageFile"));

        horizontalLayout_3->addWidget(pushButton_imageFile);

        lineEdit_imageFile = new QLineEdit(groupBox_internal);
        lineEdit_imageFile->setObjectName(QString::fromUtf8("lineEdit_imageFile"));

        horizontalLayout_3->addWidget(lineEdit_imageFile);

        horizontalSpacer = new QSpacerItem(183, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_internalCal = new QPushButton(groupBox_internal);
        pushButton_internalCal->setObjectName(QString::fromUtf8("pushButton_internalCal"));
        pushButton_internalCal->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 255);\n"
"font: 9pt \"Arial Rounded MT Bold\";"));

        horizontalLayout_3->addWidget(pushButton_internalCal);


        verticalLayout_11->addWidget(groupBox_internal);

        groupBox_external = new QGroupBox(centralWidget);
        groupBox_external->setObjectName(QString::fromUtf8("groupBox_external"));
        groupBox_external->setMinimumSize(QSize(0, 153));
        groupBox_external->setMaximumSize(QSize(16777215, 153));
        groupBox_external->setFont(font);
        verticalLayout_6 = new QVBoxLayout(groupBox_external);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox = new QGroupBox(groupBox_external);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        pushButton_leftCorners = new QPushButton(groupBox);
        pushButton_leftCorners->setObjectName(QString::fromUtf8("pushButton_leftCorners"));

        verticalLayout_9->addWidget(pushButton_leftCorners);

        pushButton_leftIntrinsic = new QPushButton(groupBox);
        pushButton_leftIntrinsic->setObjectName(QString::fromUtf8("pushButton_leftIntrinsic"));

        verticalLayout_9->addWidget(pushButton_leftIntrinsic);


        horizontalLayout_8->addLayout(verticalLayout_9);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lineEdit_leftCorners = new QLineEdit(groupBox);
        lineEdit_leftCorners->setObjectName(QString::fromUtf8("lineEdit_leftCorners"));

        verticalLayout_3->addWidget(lineEdit_leftCorners);

        lineEdit_leftIntrinsic = new QLineEdit(groupBox);
        lineEdit_leftIntrinsic->setObjectName(QString::fromUtf8("lineEdit_leftIntrinsic"));

        verticalLayout_3->addWidget(lineEdit_leftIntrinsic);


        horizontalLayout_8->addLayout(verticalLayout_3);


        horizontalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(groupBox_external);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_2);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        pushButton_rightCorners = new QPushButton(groupBox_2);
        pushButton_rightCorners->setObjectName(QString::fromUtf8("pushButton_rightCorners"));

        verticalLayout_8->addWidget(pushButton_rightCorners);

        pushButton_rightIntrinsic = new QPushButton(groupBox_2);
        pushButton_rightIntrinsic->setObjectName(QString::fromUtf8("pushButton_rightIntrinsic"));

        verticalLayout_8->addWidget(pushButton_rightIntrinsic);


        horizontalLayout_10->addLayout(verticalLayout_8);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lineEdit_rightCorners = new QLineEdit(groupBox_2);
        lineEdit_rightCorners->setObjectName(QString::fromUtf8("lineEdit_rightCorners"));

        verticalLayout_5->addWidget(lineEdit_rightCorners);

        lineEdit_rightIntrinsic = new QLineEdit(groupBox_2);
        lineEdit_rightIntrinsic->setObjectName(QString::fromUtf8("lineEdit_rightIntrinsic"));

        verticalLayout_5->addWidget(lineEdit_rightIntrinsic);


        horizontalLayout_10->addLayout(verticalLayout_5);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButton_savePath = new QPushButton(groupBox_external);
        pushButton_savePath->setObjectName(QString::fromUtf8("pushButton_savePath"));

        horizontalLayout_6->addWidget(pushButton_savePath);

        lineEdit_savePath = new QLineEdit(groupBox_external);
        lineEdit_savePath->setObjectName(QString::fromUtf8("lineEdit_savePath"));

        horizontalLayout_6->addWidget(lineEdit_savePath);


        horizontalLayout_5->addLayout(horizontalLayout_6);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        pushButton_externalCal = new QPushButton(groupBox_external);
        pushButton_externalCal->setObjectName(QString::fromUtf8("pushButton_externalCal"));
        pushButton_externalCal->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 255);\n"
"font: 9pt \"Arial Rounded MT Bold\";"));

        horizontalLayout_5->addWidget(pushButton_externalCal);


        verticalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout_11->addWidget(groupBox_external);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFont(font);
        verticalLayout_7 = new QVBoxLayout(groupBox_5);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox_4 = new QGroupBox(groupBox_5);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_13 = new QHBoxLayout(groupBox_4);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        pushButton_leftCoords = new QPushButton(groupBox_4);
        pushButton_leftCoords->setObjectName(QString::fromUtf8("pushButton_leftCoords"));

        verticalLayout_10->addWidget(pushButton_leftCoords);

        pushButton_rightCoords = new QPushButton(groupBox_4);
        pushButton_rightCoords->setObjectName(QString::fromUtf8("pushButton_rightCoords"));

        verticalLayout_10->addWidget(pushButton_rightCoords);


        horizontalLayout_9->addLayout(verticalLayout_10);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lineEdit_leftCoords = new QLineEdit(groupBox_4);
        lineEdit_leftCoords->setObjectName(QString::fromUtf8("lineEdit_leftCoords"));

        verticalLayout_4->addWidget(lineEdit_leftCoords);

        lineEdit_rightCoords = new QLineEdit(groupBox_4);
        lineEdit_rightCoords->setObjectName(QString::fromUtf8("lineEdit_rightCoords"));

        verticalLayout_4->addWidget(lineEdit_rightCoords);


        horizontalLayout_9->addLayout(verticalLayout_4);


        horizontalLayout_13->addLayout(horizontalLayout_9);


        verticalLayout_7->addWidget(groupBox_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        pushButton_projectionFile = new QPushButton(groupBox_5);
        pushButton_projectionFile->setObjectName(QString::fromUtf8("pushButton_projectionFile"));

        horizontalLayout_11->addWidget(pushButton_projectionFile);

        lineEdit_projectionFile = new QLineEdit(groupBox_5);
        lineEdit_projectionFile->setObjectName(QString::fromUtf8("lineEdit_projectionFile"));

        horizontalLayout_11->addWidget(lineEdit_projectionFile);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_3);


        horizontalLayout_12->addLayout(horizontalLayout_11);

        pushButton_reconstuctionCal = new QPushButton(groupBox_5);
        pushButton_reconstuctionCal->setObjectName(QString::fromUtf8("pushButton_reconstuctionCal"));
        pushButton_reconstuctionCal->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 255);\n"
"font: 9pt \"Arial Rounded MT Bold\";"));

        horizontalLayout_12->addWidget(pushButton_reconstuctionCal);


        verticalLayout_7->addLayout(horizontalLayout_12);


        verticalLayout_11->addWidget(groupBox_5);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 503, 23));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "MainWindow", nullptr));
        groupBox_3->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindowClass", "Points in width direction:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindowClass", "Points in height direction:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindowClass", "Chess board size:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindowClass", "mm", nullptr));
        groupBox_internal->setTitle(QCoreApplication::translate("MainWindowClass", "Intrinsic parameters calibration", nullptr));
        pushButton_imageFile->setText(QCoreApplication::translate("MainWindowClass", "Image file", nullptr));
        pushButton_internalCal->setText(QCoreApplication::translate("MainWindowClass", "Calculate", nullptr));
        groupBox_external->setTitle(QCoreApplication::translate("MainWindowClass", "Extrinsic parameters calibration", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindowClass", "Left camera", nullptr));
        pushButton_leftCorners->setText(QCoreApplication::translate("MainWindowClass", "Corner files", nullptr));
        pushButton_leftIntrinsic->setText(QCoreApplication::translate("MainWindowClass", "Intrinsic file", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindowClass", "Right camera", nullptr));
        pushButton_rightCorners->setText(QCoreApplication::translate("MainWindowClass", "Corner files", nullptr));
        pushButton_rightIntrinsic->setText(QCoreApplication::translate("MainWindowClass", "Intrinsic file", nullptr));
        pushButton_savePath->setText(QCoreApplication::translate("MainWindowClass", "Save path", nullptr));
        pushButton_externalCal->setText(QCoreApplication::translate("MainWindowClass", "Calculate", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindowClass", "Reconstruction", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindowClass", "2D correspodences for both cameras", nullptr));
        pushButton_leftCoords->setText(QCoreApplication::translate("MainWindowClass", "Left ", nullptr));
        pushButton_rightCoords->setText(QCoreApplication::translate("MainWindowClass", "Right", nullptr));
        pushButton_projectionFile->setText(QCoreApplication::translate("MainWindowClass", "Projection file", nullptr));
        pushButton_reconstuctionCal->setText(QCoreApplication::translate("MainWindowClass", "Calculate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
