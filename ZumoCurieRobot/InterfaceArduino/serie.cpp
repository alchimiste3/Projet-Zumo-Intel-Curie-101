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

void Serie::setColor(QColor color)
{
    this->color = color;
}

QColor Serie::getColor()
{
    return color;
}
