#ifndef SERIE_H
#define SERIE_H
#include <QList>
#include <QPointF>
#include <QObject>
#include <QLineSeries>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE
/**
 * @brief The Serie class
 * Les séries sont prévues pour être affichés sur un QChart, elles contiennent une listes de points
 */
class Serie
{
    QList <QPointF> listePoints;
    QString nom;
    QLineSeries* series;
    bool afficher;
    QColor color;
public:
    Serie(QString nom);
    QList<QPointF> getListePoints();
    QString getNom();
    QLineSeries *getSeries();
    void setAfficher(bool etat);
    bool isAfficher();
    void setColor(QColor color);
    QColor getColor();
public slots:
    void ajouterPoint(QPointF p);
};

#endif // SERIE_H
