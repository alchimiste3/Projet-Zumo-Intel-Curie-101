#include "ajouterwindow.h"
#include "ui_ajouterwindow.h"

AjouterWindow::AjouterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterWindow)
{
    ui->setupUi(this);
    ui->comboBoxAction->addItem(QString("Changer la vitesse"), TypeAction::ChangerVitesse);
    ui->comboBoxAction->addItem(QString("Avancer"), TypeAction::Avancer);
    ui->comboBoxAction->addItem(QString("Reculer"), TypeAction::Reculer);
    ui->comboBoxAction->addItem(QString("Tourner à droite"), TypeAction::TournerDroite);
    ui->comboBoxAction->addItem(QString("Tourner à gauche"), TypeAction::TournerGauche);
    ui->comboBoxAction->addItem(QString("Arreter"), TypeAction::Arreter);
    ui->comboBoxAction->addItem(QString("Accélérer"), TypeAction::Accelerer);
    ui->comboBoxAction->addItem(QString("Ralentir"), TypeAction::Ralentir);
    ui->spinBoxVitesse->setDisabled(true);
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
    qDebug() << "sa";
}

void AjouterWindow::on_buttonBox_rejected()
{
    qDebug() << "sc";
}

void AjouterWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug() << "sd" << ui->spinBoxDuree->value();
    a = new Action(static_cast<TypeAction>(ui->comboBoxAction->currentData().toInt()), ui->comboBoxAction->currentText(), ui->spinBoxDuree->value(), ui->spinBoxVitesse->value());
}

void AjouterWindow::on_comboBoxAction_currentIndexChanged(int index)
{
    if (ui->comboBoxAction->currentData() == TypeAction::ChangerVitesse) {
        ui->spinBoxVitesse->setDisabled(false);
    }
    else
        ui->spinBoxVitesse->setDisabled(true);
}
