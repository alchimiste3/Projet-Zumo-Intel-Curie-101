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
    /**
     * La liste des points
     */
    QList <QPointF> listePoints;

    /**
     * Nom de la série
     */
    QString nom;

    /**
     * Les lignes qui composent la série
     */
    QLineSeries* series;

    bool afficher;

    /**
     * Couleur associée
     */
    QColor color;
public:
    Serie(QString nom);

    /**
     * @return liste de points
     * Renvoie la liste des points de la série
     */
    QList<QPointF> getListePoints();

    /**
     * @return nom
     * Renvoie le nom associé à la série
     */
    QString getNom();

    /**
     * @param etat
     * Définit si la série doit être affichée ou non
     */
    void setAfficher(bool etat);

    /**
     * @return
     * Renvoie vrai si la série est actuellement affichée sur le graphe
     */
    bool isAfficher();

    /**
     * @param color
     * Définit la couleur associé à la série
     */
    void setColor(QColor color);

    /**
     * @return color
     * Renvoie la couleur associée à la série
     */
    QColor getColor();
public slots:
    /**
     * @param p
     * Permet d'ajouter un point à la série
     */
    void ajouterPoint(QPointF p);
};

#endif // SERIE_H
