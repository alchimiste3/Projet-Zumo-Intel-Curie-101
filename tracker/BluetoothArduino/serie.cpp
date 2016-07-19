#include "serie.h"

Serie::Serie(QString nom)
{
    this->nom = nom;
}

void Serie::ajouterPoint(QPoint p)
{
    listePoints.append(p);
}

QList<QPoint> Serie::getListePoints()
{
    return listePoints;
}

QString Serie::getNom()
{
    return nom;
}
