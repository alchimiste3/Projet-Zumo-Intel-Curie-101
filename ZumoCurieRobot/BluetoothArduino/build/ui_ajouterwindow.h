/********************************************************************************
** Form generated from reading UI file 'ajouterwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AJOUTERWINDOW_H
#define UI_AJOUTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AjouterWindow
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QComboBox *comboBoxAction;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *spinBoxDuree;
    QSpacerItem *horizontalSpacer_3;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *spinBoxVitesse;
    QFrame *line;

    void setupUi(QDialog *AjouterWindow)
    {
        if (AjouterWindow->objectName().isEmpty())
            AjouterWindow->setObjectName(QStringLiteral("AjouterWindow"));
        AjouterWindow->resize(400, 143);
        buttonBox = new QDialogButtonBox(AjouterWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(50, 110, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalLayoutWidget = new QWidget(AjouterWindow);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 402, 26));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBoxAction = new QComboBox(horizontalLayoutWidget);
        comboBoxAction->setObjectName(QStringLiteral("comboBoxAction"));

        horizontalLayout->addWidget(comboBoxAction);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        spinBoxDuree = new QDoubleSpinBox(horizontalLayoutWidget);
        spinBoxDuree->setObjectName(QStringLiteral("spinBoxDuree"));

        horizontalLayout->addWidget(spinBoxDuree);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayoutWidget_2 = new QWidget(AjouterWindow);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 60, 381, 40));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        spinBoxVitesse = new QSpinBox(horizontalLayoutWidget_2);
        spinBoxVitesse->setObjectName(QStringLiteral("spinBoxVitesse"));
        spinBoxVitesse->setMaximum(400);

        horizontalLayout_3->addWidget(spinBoxVitesse);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_2);

        line = new QFrame(AjouterWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(140, 50, 118, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget->raise();
        buttonBox->raise();
        horizontalLayoutWidget_2->raise();
        line->raise();

        retranslateUi(AjouterWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), AjouterWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AjouterWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(AjouterWindow);
    } // setupUi

    void retranslateUi(QDialog *AjouterWindow)
    {
        AjouterWindow->setWindowTitle(QApplication::translate("AjouterWindow", "Dialog", 0));
        label->setText(QApplication::translate("AjouterWindow", "Nouvelle action : ", 0));
        label_2->setText(QApplication::translate("AjouterWindow", "Param\303\250tres optionnels: ", 0));
        label_3->setText(QApplication::translate("AjouterWindow", "Vitesse : ", 0));
    } // retranslateUi

};

namespace Ui {
    class AjouterWindow: public Ui_AjouterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AJOUTERWINDOW_H
