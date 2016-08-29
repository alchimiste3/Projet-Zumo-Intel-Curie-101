#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include <QList>
#include <QThread>
#include <QDebug>
#include "action.h"
#include "device.h"

/**
 * @brief The Mouvement class
 * La classe mouvement contient un ensemble d'actions
 */
class Mouvement : public QThread
{
    Q_OBJECT
    /**
      La liste des actions associées au mouvement
     */
    QList<Action*> listeActions;
    Device* d;

public:
    Mouvement(Device* d, QObject* parent);
    /**
     * @brief ajouterAction
     * @param a L'action à ajouter au mouvement
     * Permet d'ajouter une nouvelle action au mouvement
     */
    void ajouterAction(Action* a);

    /**
     * @brief supprimerAction
     * @param idAction
     * Supprimer une action à partir de l'id de l'action dans la liste des actions du mouvement
     */
    void supprimerAction(int idAction);
    /**
     * @brief run
     * Execute le mouvement, toutes les actions qui le compose sont éxécutées les unes après les autres en respectant le délai lié à chaque action
     */
    void run();
};

#endif // MOUVEMENT_H
