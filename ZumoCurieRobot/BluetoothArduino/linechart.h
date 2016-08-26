#ifndef LINECHART_H
#define LINECHART_H
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QHash>
#include "serie.h"

QT_CHARTS_USE_NAMESPACE

/**
 * @brief The LineChart class
 * Cette classe contient plusieurs séries de données et peut en afficher certaines ou les cacher sur le graphique
 */
class LineChart : public QObject
{
    Q_OBJECT
    QChartView *chartView;
    QChart *chart;
    QHash<QString, Serie*> hashSeries;
    QString nomSerieActuelle;
    QLineSeries *seriesAx;
    QLineSeries *seriesAy;

public:
    LineChart();
    Serie* creerSerie(QString nomSerie);
    QWidget* getView();
public slots:
    void afficherSerie(QString nomSerie = "", bool etat = false);
    void afficherChart();
    QColor getColor(QString nomSerie);
    void ajouterPoint(QString nomSerie, QPointF p);

};

#endif // LINECHART_H
