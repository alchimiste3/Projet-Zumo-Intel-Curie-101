/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCharts/chartsnamespace.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
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
    QLabel *label;
    QLabel *labelRSSI;
    QFormLayout *formLayout_2;
    QLabel *label_20;
    QLabel *labelPx;
    QLabel *label_16;
    QLabel *labelPy;
    QLabel *label_12;
    QLabel *labelPz;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *actionsTableWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *envoyerButton;
    QPushButton *supprimerButton;
    QPushButton *modifierButton;
    QPushButton *ajouterButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLabel *labelR;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *apprendreButton;
    QPushButton *reconnaitreButton;
    QPushButton *reexucuterActionsButton;
    QFrame *line;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBoxAy;
    QCheckBox *checkBoxAx;
    QCheckBox *checkBoxVy;
    QCheckBox *checkBoxVx;
    QCheckBox *checkBoxPx;
    QCheckBox *checkBoxPy;
    QtCharts::QChartView *chartview;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(796, 546);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 421, 111));
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

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_4->setWidget(4, QFormLayout::LabelRole, label);

        labelRSSI = new QLabel(gridLayoutWidget);
        labelRSSI->setObjectName(QStringLiteral("labelRSSI"));

        formLayout_4->setWidget(4, QFormLayout::FieldRole, labelRSSI);


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

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 3, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 0));
        lineEdit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEdit, 1, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 120, 421, 437));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        actionsTableWidget = new QTableWidget(verticalLayoutWidget);
        if (actionsTableWidget->columnCount() < 3)
            actionsTableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        actionsTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        actionsTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        actionsTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        actionsTableWidget->setObjectName(QStringLiteral("actionsTableWidget"));
        actionsTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        actionsTableWidget->horizontalHeader()->setDefaultSectionSize(140);
        actionsTableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(actionsTableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        envoyerButton = new QPushButton(verticalLayoutWidget);
        envoyerButton->setObjectName(QStringLiteral("envoyerButton"));

        horizontalLayout->addWidget(envoyerButton);

        supprimerButton = new QPushButton(verticalLayoutWidget);
        supprimerButton->setObjectName(QStringLiteral("supprimerButton"));

        horizontalLayout->addWidget(supprimerButton);

        modifierButton = new QPushButton(verticalLayoutWidget);
        modifierButton->setObjectName(QStringLiteral("modifierButton"));

        horizontalLayout->addWidget(modifierButton);

        ajouterButton = new QPushButton(verticalLayoutWidget);
        ajouterButton->setObjectName(QStringLiteral("ajouterButton"));

        horizontalLayout->addWidget(ajouterButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_7);

        labelR = new QLabel(verticalLayoutWidget);
        labelR->setObjectName(QStringLiteral("labelR"));

        horizontalLayout_2->addWidget(labelR);


        verticalLayout->addLayout(horizontalLayout_2);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        apprendreButton = new QPushButton(verticalLayoutWidget);
        apprendreButton->setObjectName(QStringLiteral("apprendreButton"));

        horizontalLayout_4->addWidget(apprendreButton);

        reconnaitreButton = new QPushButton(verticalLayoutWidget);
        reconnaitreButton->setObjectName(QStringLiteral("reconnaitreButton"));

        horizontalLayout_4->addWidget(reconnaitreButton);

        reexucuterActionsButton = new QPushButton(verticalLayoutWidget);
        reexucuterActionsButton->setObjectName(QStringLiteral("reexucuterActionsButton"));

        horizontalLayout_4->addWidget(reexucuterActionsButton);


        verticalLayout->addLayout(horizontalLayout_4);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        checkBoxAy = new QCheckBox(verticalLayoutWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->setExclusive(false);
        buttonGroup->addButton(checkBoxAy);
        checkBoxAy->setObjectName(QStringLiteral("checkBoxAy"));

        horizontalLayout_5->addWidget(checkBoxAy);

        checkBoxAx = new QCheckBox(verticalLayoutWidget);
        buttonGroup->addButton(checkBoxAx);
        checkBoxAx->setObjectName(QStringLiteral("checkBoxAx"));

        horizontalLayout_5->addWidget(checkBoxAx);

        checkBoxVy = new QCheckBox(verticalLayoutWidget);
        buttonGroup->addButton(checkBoxVy);
        checkBoxVy->setObjectName(QStringLiteral("checkBoxVy"));

        horizontalLayout_5->addWidget(checkBoxVy);

        checkBoxVx = new QCheckBox(verticalLayoutWidget);
        buttonGroup->addButton(checkBoxVx);
        checkBoxVx->setObjectName(QStringLiteral("checkBoxVx"));

        horizontalLayout_5->addWidget(checkBoxVx);

        checkBoxPx = new QCheckBox(verticalLayoutWidget);
        buttonGroup->addButton(checkBoxPx);
        checkBoxPx->setObjectName(QStringLiteral("checkBoxPx"));

        horizontalLayout_5->addWidget(checkBoxPx);

        checkBoxPy = new QCheckBox(verticalLayoutWidget);
        buttonGroup->addButton(checkBoxPy);
        checkBoxPy->setObjectName(QStringLiteral("checkBoxPy"));

        horizontalLayout_5->addWidget(checkBoxPy);


        verticalLayout->addLayout(horizontalLayout_5);

        chartview = new QtCharts::QChartView(verticalLayoutWidget);
        chartview->setObjectName(QStringLiteral("chartview"));

        verticalLayout->addWidget(chartview);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 796, 20));
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
        label->setText(QApplication::translate("MainWindow", "RSSI : ", 0));
        labelRSSI->setText(QApplication::translate("MainWindow", "0", 0));
        label_20->setText(QApplication::translate("MainWindow", "px : ", 0));
        labelPx->setText(QApplication::translate("MainWindow", "0", 0));
        label_16->setText(QApplication::translate("MainWindow", "py : ", 0));
        labelPy->setText(QApplication::translate("MainWindow", "0", 0));
        label_12->setText(QApplication::translate("MainWindow", "pz : ", 0));
        labelPz->setText(QApplication::translate("MainWindow", "0", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Envoyer", 0));
        label_3->setText(QApplication::translate("MainWindow", "Saisir une commande : ", 0));
        QTableWidgetItem *___qtablewidgetitem = actionsTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Action", 0));
        QTableWidgetItem *___qtablewidgetitem1 = actionsTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Dur\303\251e", 0));
        QTableWidgetItem *___qtablewidgetitem2 = actionsTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Param\303\250tre", 0));
        envoyerButton->setText(QApplication::translate("MainWindow", "Envoyer", 0));
        supprimerButton->setText(QApplication::translate("MainWindow", "Supprimer action", 0));
        modifierButton->setText(QApplication::translate("MainWindow", "Modifier action", 0));
        ajouterButton->setText(QApplication::translate("MainWindow", "Ajouter action", 0));
        label_7->setText(QApplication::translate("MainWindow", "Apprentissage : ", 0));
        labelR->setText(QString());
        apprendreButton->setText(QApplication::translate("MainWindow", "Apprendre", 0));
        reconnaitreButton->setText(QApplication::translate("MainWindow", "Reconnaitre", 0));
        reexucuterActionsButton->setText(QApplication::translate("MainWindow", "Reexecuter actions", 0));
        label_5->setText(QApplication::translate("MainWindow", "Affichage des donn\303\251es : ", 0));
        checkBoxAy->setText(QApplication::translate("MainWindow", "Ay", 0));
        checkBoxAx->setText(QApplication::translate("MainWindow", "Ax", 0));
        checkBoxVy->setText(QApplication::translate("MainWindow", "Vy", 0));
        checkBoxVx->setText(QApplication::translate("MainWindow", "Vx", 0));
        checkBoxPx->setText(QApplication::translate("MainWindow", "Px", 0));
        checkBoxPy->setText(QApplication::translate("MainWindow", "Py", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
