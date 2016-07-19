#include "linechart.h"

LineChart::LineChart() : QObject()
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

void LineChart:: afficherSerie(QString nomSerie)
{
    if (!nomSerie.isEmpty())
        nomSerieActuelle = nomSerie;

    if (!nomSerieActuelle.isEmpty())
    {
    QLineSeries *series = new QLineSeries();
        for (int i = 0; i < hashSeries[nomSerieActuelle]->getListePoints().size(); i++)
            *series << hashSeries[nomSerieActuelle]->getListePoints()[i];
        chart->removeAllSeries();
        chart->addSeries(series);
        chart->createDefaultAxes();
    }
}

Serie* LineChart::creerSerie(QString nomSerie)
{
    Serie* s = new Serie(nomSerie);
    hashSeries[nomSerie] = s;
    return s;
}

void LineChart::ajouterPoint(QString nomSerie, QPoint p)
{
    hashSeries[nomSerie]->ajouterPoint(p);
}

QWidget* LineChart::getView()
{
    return chartView;
}
