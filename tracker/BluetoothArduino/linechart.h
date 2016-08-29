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
    /**
     * @param nomSerie
     * @return la série créee
     * Permet de créer une nouvelle série
     */
    Serie* creerSerie(QString nomSerie);
    /**
     * @return view
     * Renvoie la vue associée au graphe
     */
    QWidget* getView();
public slots:
    /**
     * @param nomSerie
     * @param etat
     * Permet de choisir si une série doit êter affichée sur le graphe ou non
     */
    void afficherSerie(QString nomSerie = "", bool etat = false);

    /**
      * Met à jour le graphe
     */
    void afficherChart();

    /**
     * @param nomSerie
     * @return color
     * Renvoie la couleur associée à une série
     */
    QColor getColor(QString nomSerie);

    /**
     * @param nomSerie
     * @param p
     * Ajoute un point à une série
     */
    void ajouterPoint(QString nomSerie, QPointF p);

};

#endif // LINECHART_H
