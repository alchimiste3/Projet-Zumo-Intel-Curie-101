#ifndef SERIE_H
#define SERIE_H
#include <QList>
#include <QPointF>
#include <QObject>
#include <QLineSeries>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

class Serie
{
    QList <QPointF> listePoints;
    QString nom;
    QLineSeries* series;
    bool afficher;
public:
    Serie(QString nom);
    QList<QPointF> getListePoints();
    QString getNom();
    QLineSeries *getSeries();
    void setAfficher(bool etat);
    bool isAfficher();
public slots:
    void ajouterPoint(QPointF p);
};

#endif // SERIE_H
