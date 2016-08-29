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
/**
 * @brief The MainWindow class
 * Représente la fenêtre principale de l'application,
 * elle permet d'interagir avec le robot
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    Device* d;
    AjouterWindow* ajouterWindow;
    ApprendreWindow* apprendreWindow;
    Mouvement* m;
    QList<Action*> actionsTableau;
    LineChart* chart;
    int indexModifie;
public:
    explicit MainWindow(Device* d, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(bool checked);
    /**
     * @brief redMajValues
     * @param yaw
     * @param ax
     * @param ay
     * @param az
     * @param vx
     * @param vy
     * @param vz
     * @param px
     * @param py
     * @param pz
     * Met à jour les valeurs des données au format texte et ajoute les points sur le graphe
     */
    void redMajValues(float yaw, float ax, float ay, float az, float vx, float vy, float vz, float px, float py, float pz);

    /**
     * @brief on_ajouterButton_clicked
     * Affiche la fenetre d'ajout d'action en mode Ajout
     */
    void on_ajouterButton_clicked();

    /**
     * @brief redAccepted
     * Ce Slot est appelé quand l'utilisateur clique sur OK dans la fenetre d'ajout d'action
     * Il met alors à jour le tableau
     */
    void redAccepted();

    /**
     * @brief on_supprimerButton_clicked
     * Supprimer une action du tableau
     */
    void on_supprimerButton_clicked();

    /**
     * @brief on_envoyerButton_clicked
     * Permet de charger les actions contenues dans le tableau dans le mouvement à effectuer par le robot
     */
    void on_envoyerButton_clicked();

    /**
     * @brief redButtonToggled
     * @param id
     * @param etat
     * Permet d'afficher les séries correspondants aux case cochées
     */
    void redButtonToggled(int id, bool etat);

    /**
     * @brief on_apprendreButton_clicked
     * Permet de démarrer d'envoyer la commande d'apprentissage lors d'un clic sur Apprendre
     */
    void on_apprendreButton_clicked();

    void redAcceptedCommandeApprendre();

    /**
     * @param checked
     */
    void on_reconnaitreButton_clicked(bool checked);

    /**
     * @param checked
     */
    void on_reexucuterActionsButton_clicked(bool checked);

    /**
     * @param value
     * Affiche la valeur reconnue
     */
    void redMajReconaissance(int value);

    /**
     * @param checked
     * Modifier une action après un clic sur le bouton modifier
     */
    void on_modifierButton_clicked(bool checked);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
