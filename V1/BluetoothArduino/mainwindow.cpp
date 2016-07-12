#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Device* d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->d = d;
    QObject::connect(d, SIGNAL(majValues(float, float, float, float,float,float,float,float,float,float)), this, SLOT(redMajValues(float, float, float, float,float,float,float,float,float,float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    d->envoyerCommande(ui->lineEdit->text());
}

void MainWindow::redMajValues(float yaw, float ax, float ay, float az, float vx, float vy, float vz, float px, float py, float pz)
{
    ui->labelYaw->setText(QString::number(yaw));
    ui->labelAx->setText(QString::number(ax));
    ui->labelAy->setText(QString::number(ay));
    ui->labelAz->setText(QString::number(az));
    ui->labelVx->setText(QString::number(vx));
    ui->labelVy->setText(QString::number(vy));
    ui->labelVz->setText(QString::number(vz));
    ui->labelPx->setText(QString::number(px));
    ui->labelPy->setText(QString::number(py));
    ui->labelPz->setText(QString::number(pz));
}
