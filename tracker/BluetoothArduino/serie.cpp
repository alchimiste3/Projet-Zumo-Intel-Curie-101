#include "serie.h"

Serie::Serie(QString nom)
{
    this->nom = nom;
    series = new QLineSeries();
    afficher = false;
}

void Serie::ajouterPoint(QPointF p)
{
    if (listePoints.size() > 100)
        listePoints.removeFirst();
    listePoints.append(p);
}

QList<QPointF> Serie::getListePoints()
{
    return listePoints;
}

QLineSeries * Serie::getSeries()
{
    series = new QLineSeries();
    for (int i = 0; i < listePoints.size(); i++)
        *series << listePoints[i];
}

QString Serie::getNom()
{
    return nom;
}

void Serie::setAfficher(bool etat)
{
    this->afficher = etat;
}

bool Serie::isAfficher()
{
    return afficher;
}
