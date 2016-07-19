#ifndef SERIE_H
#define SERIE_H
#include <QList>
#include <QPoint>
#include <QObject>
#include <QDebug>

class Serie
{
    QList <QPoint> listePoints;
    QString nom;
public:
    Serie(QString nom);
    QList<QPoint> getListePoints();
    QString getNom();
public slots:
    void ajouterPoint(QPoint p);
};

#endif // SERIE_H
