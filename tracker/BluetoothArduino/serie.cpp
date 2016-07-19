#include "serie.h"

Serie::Serie(QString nom)
{
    this->nom = nom;
    listePoints.reserve(500);
}

void Serie::ajouterPoint(QPointF p)
{
    qDebug() << "point" << p;
    if (listePoints.size() > 500)
        listePoints.removeFirst();
    listePoints.append(p);
}

QList<QPointF> Serie::getListePoints()
{
    return listePoints;
}

QString Serie::getNom()
{
    return nom;
}
