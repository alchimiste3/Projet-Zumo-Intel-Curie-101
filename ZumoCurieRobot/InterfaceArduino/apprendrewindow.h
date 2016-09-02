#ifndef APPRENDREWINDOW_H
#define APPRENDREWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>

namespace Ui {
class ApprendreWindow;
}
/**
 * @brief The ApprendreWindow class
 * Cette classe permet de choisir sur quel neurone on veut apprendre un mouvement
 */
class ApprendreWindow : public QDialog
{
    Q_OBJECT
    QString commandeApprendre;

public:
    explicit ApprendreWindow(QWidget *parent = 0);
    ~ApprendreWindow();

    /**
     * @return la commande
     * Permet de récupérer la commande d'aprentissage
     */
    QString getCommandeApprendre();

private slots:
    /**
     * @param button
     * Génère la commande lorsque l'on valide le choix du mouvement/neurone
     */
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ApprendreWindow *ui;
};

#endif // APPRENDREWINDOW_H
