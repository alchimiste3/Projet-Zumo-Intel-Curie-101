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
    QList<Action*> listeActions;
    Device* d;

public:
    Mouvement(Device* d, QObject* parent);
    void ajouterAction(Action* a);
    void supprimerAction(int idAction);
    void run();
};

#endif // MOUVEMENT_H
