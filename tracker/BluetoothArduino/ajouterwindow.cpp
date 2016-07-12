#include "ajouterwindow.h"
#include "ui_ajouterwindow.h"

AjouterWindow::AjouterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterWindow)
{
    ui->setupUi(this);
    ui->comboBoxAction->addItem(QString("Avancer"), TypeAction::Avancer);
    ui->comboBoxAction->addItem(QString("Reculer"), TypeAction::Reculer);
    ui->comboBoxAction->addItem(QString("Tourner à droite"), TypeAction::TournerDroite);
    ui->comboBoxAction->addItem(QString("Tourner à gauche"), TypeAction::TournerGauche);
}

AjouterWindow::~AjouterWindow()
{
    delete ui;
}

Action *AjouterWindow::getAction()
{
    return a;
}

void AjouterWindow::on_buttonBox_accepted()
{
    a = new Action(static_cast<TypeAction>(ui->comboBoxAction->currentData().toInt()), ui->spinBoxDuree->value());
}
