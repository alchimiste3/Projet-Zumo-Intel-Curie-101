#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include <QList>
#include "action.h"


class Mouvement
{
    QList<Action> listeActions;
    int idMouvement;

public:
    Mouvement(int idMouvement);
    void ajouterAction(Action a);
    void supprimerAction(int idAction);
};

#endif // MOUVEMENT_H
