#ifndef SERIE_H
#define SERIE_H
#include <QList>
#include <QPoint>

class Serie
{
    QList <QPoint> listePoints;
    QString nom;
public:
    Serie(QString nom);
    void ajouterPoint(QPoint p);
    QList<QPoint> getListePoints();
    QString getNom();
};

#endif // SERIE_H
