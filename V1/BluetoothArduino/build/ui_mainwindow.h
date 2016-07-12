/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *labelYaw;
    QLabel *label_4;
    QLabel *labelAx;
    QLabel *label_6;
    QLabel *labelAy;
    QLabel *label_8;
    QLabel *labelAz;
    QFormLayout *formLayout_4;
    QLabel *label_10;
    QLabel *labelVx;
    QLabel *label_14;
    QLabel *labelVy;
    QLabel *label_18;
    QLabel *labelVz;
    QFormLayout *formLayout_2;
    QLabel *label_20;
    QLabel *labelPx;
    QLabel *label_16;
    QLabel *labelPy;
    QLabel *label_12;
    QLabel *labelPz;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(377, 145);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 361, 101));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignCenter);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        labelYaw = new QLabel(gridLayoutWidget);
        labelYaw->setObjectName(QStringLiteral("labelYaw"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelYaw);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        labelAx = new QLabel(gridLayoutWidget);
        labelAx->setObjectName(QStringLiteral("labelAx"));

        formLayout->setWidget(1, QFormLayout::FieldRole, labelAx);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        labelAy = new QLabel(gridLayoutWidget);
        labelAy->setObjectName(QStringLiteral("labelAy"));

        formLayout->setWidget(2, QFormLayout::FieldRole, labelAy);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        labelAz = new QLabel(gridLayoutWidget);
        labelAz->setObjectName(QStringLiteral("labelAz"));

        formLayout->setWidget(3, QFormLayout::FieldRole, labelAz);


        gridLayout->addLayout(formLayout, 0, 0, 1, 2);

        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setLabelAlignment(Qt::AlignCenter);
        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_10);

        labelVx = new QLabel(gridLayoutWidget);
        labelVx->setObjectName(QStringLiteral("labelVx"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, labelVx);

        label_14 = new QLabel(gridLayoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_14);

        labelVy = new QLabel(gridLayoutWidget);
        labelVy->setObjectName(QStringLiteral("labelVy"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, labelVy);

        label_18 = new QLabel(gridLayoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_18);

        labelVz = new QLabel(gridLayoutWidget);
        labelVz->setObjectName(QStringLiteral("labelVz"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, labelVz);


        gridLayout->addLayout(formLayout_4, 0, 2, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setLabelAlignment(Qt::AlignCenter);
        label_20 = new QLabel(gridLayoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_20);

        labelPx = new QLabel(gridLayoutWidget);
        labelPx->setObjectName(QStringLiteral("labelPx"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, labelPx);

        label_16 = new QLabel(gridLayoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_16);

        labelPy = new QLabel(gridLayoutWidget);
        labelPy->setObjectName(QStringLiteral("labelPy"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, labelPy);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_12);

        labelPz = new QLabel(gridLayoutWidget);
        labelPz->setObjectName(QStringLiteral("labelPz"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, labelPz);


        gridLayout->addLayout(formLayout_2, 0, 3, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 0));
        lineEdit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEdit, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 1, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 377, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Commander le robot \303\240 distance", 0));
        label_2->setText(QApplication::translate("MainWindow", "Yaw : ", 0));
        labelYaw->setText(QApplication::translate("MainWindow", "0", 0));
        label_4->setText(QApplication::translate("MainWindow", "ax : ", 0));
        labelAx->setText(QApplication::translate("MainWindow", "0", 0));
        label_6->setText(QApplication::translate("MainWindow", "ay : ", 0));
        labelAy->setText(QApplication::translate("MainWindow", "0", 0));
        label_8->setText(QApplication::translate("MainWindow", "az : ", 0));
        labelAz->setText(QApplication::translate("MainWindow", "0", 0));
        label_10->setText(QApplication::translate("MainWindow", "vx : ", 0));
        labelVx->setText(QApplication::translate("MainWindow", "0", 0));
        label_14->setText(QApplication::translate("MainWindow", "vy : ", 0));
        labelVy->setText(QApplication::translate("MainWindow", "0", 0));
        label_18->setText(QApplication::translate("MainWindow", "vz : ", 0));
        labelVz->setText(QApplication::translate("MainWindow", "0", 0));
        label_20->setText(QApplication::translate("MainWindow", "px : ", 0));
        labelPx->setText(QApplication::translate("MainWindow", "0", 0));
        label_16->setText(QApplication::translate("MainWindow", "py : ", 0));
        labelPy->setText(QApplication::translate("MainWindow", "0", 0));
        label_12->setText(QApplication::translate("MainWindow", "pz : ", 0));
        labelPz->setText(QApplication::translate("MainWindow", "0", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Envoyer", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
