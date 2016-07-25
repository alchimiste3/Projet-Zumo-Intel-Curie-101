#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "device.h"
#include "ajouterwindow.h"
#include "apprendrewindow.h"
#include "mouvement.h"
#include "linechart.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Device* d;
    AjouterWindow* ajouterWindow;
    ApprendreWindow* apprendreWindow;
    Mouvement* m;
    QList<Action*> actionsTableau;
    LineChart* chart;
public:
    explicit MainWindow(Device* d, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(bool checked);
    void redMajValues(float yaw, float ax, float ay, float az, float vx, float vy, float vz, float px, float py, float pz);

    void on_ajouterButton_clicked();
    void redAccepted();

    void on_supprimerButton_clicked();

    void on_envoyerButton_clicked();

    void redButtonToggled(int id, bool etat);

    void on_apprendreButton_clicked();

    void redAcceptedCommandeApprendre();

signals:
    void ajouterPoint(QString nomSerie, QPointF point);
    void afficherSerie(QString nomSerie);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
