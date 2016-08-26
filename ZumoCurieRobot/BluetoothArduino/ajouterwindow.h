#ifndef AJOUTERWINDOW_H
#define AJOUTERWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QDebug>

#include "action.h"

namespace Ui {
class AjouterWindow;
}

typedef enum ModeFenetreAjout {
    Ajouter = 0,
    Modifier = 1
} ModeFenetreAjout;

/**
 * @brief The AjouterWindow class
 * Fenetre qui permet d'ajouter une nouvelle action ou de modifier une action existante
 */
class AjouterWindow : public QDialog
{
    Q_OBJECT
    Action* a;
    ModeFenetreAjout mode;

public:
    explicit AjouterWindow(QWidget *parent = 0);
    ~AjouterWindow();
    /**
     * @brief getAction
     * @return
     * Renvoie l'action généré à partir de la fenetre
     */
    Action* getAction();

    void chargerAction(Action* a);

    void setMode(ModeFenetreAjout mode);
    ModeFenetreAjout getMode();

private slots:
    /**
     * @brief on_buttonBox_clicked
     * @param button
     * Génère une action lorsqu'on valide la fenêtre d'ajout
     */
    void on_buttonBox_clicked(QAbstractButton *button);

    /**
     * @brief on_comboBoxAction_currentIndexChanged
     * @param index
     * Ce slot est déclenchée lors d'un choix dans la liste déroulante des actions, permet de désactiver la saisie du paramètre dans certains cas
     */
    void on_comboBoxAction_currentIndexChanged(int index);

private:
    Ui::AjouterWindow *ui;
};

#endif // AJOUTERWINDOW_H
