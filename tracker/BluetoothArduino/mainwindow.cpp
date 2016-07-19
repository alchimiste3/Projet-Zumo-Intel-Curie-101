#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Device* d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->d = d;
    ui->actionsTableWidget->setColumnCount(4);
    ui->actionsTableWidget->setColumnHidden(3, true);
    QList<QAbstractButton*> listeBoutons = ui->buttonGroup->buttons();
    for (int i = 0; i < listeBoutons.size();  i++)
    {
        ui->buttonGroup->setId(listeBoutons[i], i);
    }
    connect(ui->buttonGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(redButtonToggled(int, bool)));
    ajouterWindow = new AjouterWindow();
    chart = new LineChart;
    chart->creerSerie("Ax");
    chart->creerSerie("Ay");
    chart->afficherSerie("Ay");
    QObject::connect(this, SIGNAL(ajouterPoint(QString, QPointF)), chart, SLOT(ajouterPoint(QString, QPointF)));
    QObject::connect(this, SIGNAL(afficherSerie(QString)), chart, SLOT(afficherSerie(QString)));
   // connect(this, SIGNAL(afficherSerie(QString)), chart, SLOT(afficherSerie(QString)));
    m = new Mouvement(d, this);
    ui->chartview->setViewport(chart->getView());
    QObject::connect(ajouterWindow, SIGNAL(accepted()), this, SLOT(redAccepted()));
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
    emit ajouterPoint("Ax", QPointF((float)d->getTempsEcoule()/1000, ax));
    emit ajouterPoint("Ay", QPointF((float)d->getTempsEcoule()/1000, ay));
    chart->afficherSerie();
    ui->chartview->setViewport(chart->getView());
}

void MainWindow::on_ajouterButton_clicked()
{
    ajouterWindow->show();
}

void MainWindow::redAccepted()
{
    Action* a = ajouterWindow->getAction();
    actionsTableau.append(a);
    QTableWidgetItem *itemNomAction = new QTableWidgetItem(a->getNomAction());
    QTableWidgetItem *itemDuree = new QTableWidgetItem(QString::number(a->getNbS()));
    QTableWidgetItem *itemTypeAction = new QTableWidgetItem(QString::number(a->getTypeAction()));
    QTableWidgetItem *itemPara = new QTableWidgetItem(QString::number(a->getPara()));
    int row = ui->actionsTableWidget->rowCount();
    ui->actionsTableWidget->setRowCount(ui->actionsTableWidget->rowCount()+1);

    ui->actionsTableWidget->setItem(row, 0, itemNomAction);
    ui->actionsTableWidget->setItem(row, 1, itemDuree);
    ui->actionsTableWidget->setItem(row, 2, itemPara);
    ui->actionsTableWidget->setItem(row, 3, itemTypeAction);

}

void MainWindow::on_supprimerButton_clicked()
{
    QList<QTableWidgetItem *> listeItems = ui->actionsTableWidget->selectedItems();
    while (listeItems.size() > 0) {
       ui->actionsTableWidget->removeRow(listeItems.first()->row());
       listeItems.removeFirst();
    }
}

void MainWindow::on_envoyerButton_clicked()
{
    for (int i = 0; i < ui->actionsTableWidget->rowCount(); i++)
    {
        m->ajouterAction(new Action(static_cast<TypeAction>(ui->actionsTableWidget->item(i, 3)->text().toInt()), ui->actionsTableWidget->item(i, 0)->text(),  ui->actionsTableWidget->item(i, 1)->text().toFloat(), ui->actionsTableWidget->item(i, 2)->text().toInt()));
    }
    m->ajouterAction(new Action(TypeAction::Arreter, "Arret automatique", 0));
    m->start();
}

void MainWindow::redButtonToggled(int id, bool etat)
{
    if (id == 1 && etat)
    {
        emit afficherSerie("Ax");
    }
    else if (id == 0 && etat)
    {
        emit afficherSerie("Ay");
    }
}

