/********************************************************************************
** Form generated from reading UI file 'apprendrewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPRENDREWINDOW_H
#define UI_APPRENDREWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApprendreWindow
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxNeuron;

    void setupUi(QDialog *ApprendreWindow)
    {
        if (ApprendreWindow->objectName().isEmpty())
            ApprendreWindow->setObjectName(QStringLiteral("ApprendreWindow"));
        ApprendreWindow->resize(373, 87);
        buttonBox = new QDialogButtonBox(ApprendreWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 50, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalLayoutWidget = new QWidget(ApprendreWindow);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 301, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBoxNeuron = new QSpinBox(horizontalLayoutWidget);
        spinBoxNeuron->setObjectName(QStringLiteral("spinBoxNeuron"));
        spinBoxNeuron->setMaximum(127);

        horizontalLayout->addWidget(spinBoxNeuron);


        retranslateUi(ApprendreWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), ApprendreWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ApprendreWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(ApprendreWindow);
    } // setupUi

    void retranslateUi(QDialog *ApprendreWindow)
    {
        ApprendreWindow->setWindowTitle(QApplication::translate("ApprendreWindow", "Apprendre un mouvement", 0));
        label->setText(QApplication::translate("ApprendreWindow", "Num\303\251ro neurone : ", 0));
    } // retranslateUi

};

namespace Ui {
    class ApprendreWindow: public Ui_ApprendreWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPRENDREWINDOW_H
