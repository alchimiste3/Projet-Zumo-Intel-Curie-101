#include "mouvement.h"

Mouvement::Mouvement(Device *d, QObject *parent) : QThread(parent)
{
    this->d = d;
}

void Mouvement::ajouterAction(Action *a)
{
    listeActions.append(a);
}

void Mouvement::run()
{
    while (listeActions.size() > 0)
    {
        QString commande("m");
        float duree = listeActions.first()->getNbS()*1000;
        commande += QString::number((int)listeActions.first()->getTypeAction());
        listeActions.removeFirst();
        qDebug() << "commande : " << commande;
        d->envoyerCommande(commande);
        msleep(duree);
    }
}
