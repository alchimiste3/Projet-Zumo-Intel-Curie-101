#ifndef SERIE_H
#define SERIE_H
#include <QList>
#include <QPointF>
#include <QObject>
#include <QDebug>

class Serie
{
    QList <QPointF> listePoints;
    QString nom;
public:
    Serie(QString nom);
    QList<QPointF> getListePoints();
    QString getNom();
public slots:
    void ajouterPoint(QPointF p);
};

#endif // SERIE_H
