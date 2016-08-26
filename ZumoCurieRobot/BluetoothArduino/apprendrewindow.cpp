#include "apprendrewindow.h"
#include "ui_apprendrewindow.h"

ApprendreWindow::ApprendreWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApprendreWindow)
{
    ui->setupUi(this);
}

ApprendreWindow::~ApprendreWindow()
{
    delete ui;
}

void ApprendreWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    commandeApprendre = "a"+ QString::number(ui->spinBoxNeuron->value());
}

QString ApprendreWindow::getCommandeApprendre()
{
    return commandeApprendre;
}
