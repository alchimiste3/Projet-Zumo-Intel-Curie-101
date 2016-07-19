#ifndef LINECHART_H
#define LINECHART_H
#include <QLineSeries>
#include <QChartView>
#include <QHash>
#include "serie.h"

QT_CHARTS_USE_NAMESPACE

class LineChart : public QObject
{
    Q_OBJECT
    QChartView *chartView;
    QChart *chart;
    QHash<QString, Serie*> hashSeries;
    QString nomSerieActuelle;
public:
    LineChart();
    Serie* creerSerie(QString nomSerie);
    QWidget* getView();
public slots:
    void afficherSerie(QString nomSerie = "");
    void ajouterPoint(QString nomSerie, QPoint p);

};

#endif // LINECHART_H
