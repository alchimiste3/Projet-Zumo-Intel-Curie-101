#include "linechart.h"

LineChart::LineChart()
{
    QLineSeries *series = new QLineSeries();
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Affichage de l'accélération");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void LineChart:: afficherSerie(QString serie)
{
    chart->removeAllSeries();
    chart->addSeries();
}

void LineChart::ajouterPoint(QPoint p)
{
    listePoints.append(p);
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < listePoints.size(); i++)
        *series << listePoints[i];
    chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
}

QWidget* LineChart::getView()
{
    return chartView;
}
