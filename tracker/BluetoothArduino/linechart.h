#ifndef LINECHART_H
#define LINECHART_H
#include <QLineSeries>
#include <QChartView>
#include "serie.h"

QT_CHARTS_USE_NAMESPACE

class LineChart
{
    QChartView *chartView;
    QChart *chart;
    QList<Serie> listeSeries;
public:
    LineChart();
    void afficherSerie(QString serie);
    void ajouterPoint(QPoint p);
    QWidget* getView();
};

#endif // LINECHART_H
