#ifndef TRAITEMENTDONNEES_H
#define TRAITEMENTDONNEES_H
#include <QDebug>
#include "MatrixMath/MatrixMath.h"


class TraitementDonnees
{

    const int tempsCourant = 1;
    float tempsEntreMesure;
    float tabA[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
    float tabV[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
    float tabP[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
public:
    TraitementDonnees();
    void setAcceleration(float ax, float ay, float az);
    void calculerVitesse();
    void calculerPosition();
    void miseAJourVal();
    float* getAccelerationCourante();
    float* getVitesseCourante();
    float* getPositionCourante();

    void traitement(float ax, float ay, float az, float intervalle);
};

#endif // TRAITEMENTDONNEES_H
