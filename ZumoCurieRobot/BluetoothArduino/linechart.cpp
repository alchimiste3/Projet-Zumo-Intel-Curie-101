#include "linechart.h"

LineChart::LineChart() : QObject()
{
    seriesAx = new QLineSeries();

    seriesAy = new QLineSeries();
    chart = new QChart();
    chart->legend()->hide();
 //   chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Affichage de l'accélération");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void LineChart::afficherChart()
{
    if (!nomSerieActuelle.isEmpty())
    {
     chart->removeAllSeries();

     foreach (Serie* s, hashSeries)
     {
         if (s->isAfficher())
         {
             QLineSeries* serie = new QLineSeries();
             for (int i = 0; i < s->getListePoints().size(); i++)
                 *serie << s->getListePoints()[i];
             chart->addSeries(serie);
             s->setColor(serie->color());
         }

     }
     chart->createDefaultAxes();
     ((QValueAxis)chart->axisX()).setTickCount(2);

    }
}

void LineChart:: afficherSerie(QString nomSerie, bool etat)
{
    if (!nomSerie.isEmpty())
        nomSerieActuelle = nomSerie;
    hashSeries[nomSerie]->setAfficher(etat);
}

Serie* LineChart::creerSerie(QString nomSerie)
{
    Serie* s = new Serie(nomSerie);
    hashSeries[nomSerie] = s;
    return s;
}

void LineChart::ajouterPoint(QString nomSerie, QPointF p)
{
    hashSeries[nomSerie]->ajouterPoint(p);
}

QColor LineChart::getColor(QString nomSerie)
{
    if (hashSeries.contains(nomSerie))
    {
        return hashSeries[nomSerie]->getColor();
    }
    else
    {
        return QColor();
    }
}

QWidget* LineChart::getView()
{
    return chartView;
}
