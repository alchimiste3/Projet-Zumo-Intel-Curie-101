#include "traitementdonnees.h"

TraitementDonnees::TraitementDonnees()
{

}

void TraitementDonnees::setAcceleration(float ax, float ay, float az)
{
    tabA[tempsCourant][0] = ax;
    tabA[tempsCourant][1] = ay;
    tabA[tempsCourant][2] = az;
}

void TraitementDonnees::calculerVitesse() {

    float tabinter[3] = {0.0};

    tabinter[0] = tabA[tempsCourant][0] * tempsEntreMesure;
    tabinter[1] = tabA[tempsCourant][1] * tempsEntreMesure;
    tabinter[2] = tabA[tempsCourant][2] * tempsEntreMesure;

    Matrix.Add((float*)tabV[tempsCourant - 1], (float*)tabinter, 1, 3, (float*)tabV[tempsCourant]);
}

void TraitementDonnees::calculerPosition()
{
    float tabinter[3] = {0.0};

    tabinter[0] = tabV[tempsCourant][0] * tempsEntreMesure;
    tabinter[1] = tabV[tempsCourant][1] * tempsEntreMesure;
    tabinter[2] = tabV[tempsCourant][2] * tempsEntreMesure;

    Matrix.Add((float*)tabP[tempsCourant - 1], (float*)tabinter, 1, 3, (float*)tabP[tempsCourant]);
}

void TraitementDonnees::miseAJourVal()
{
  Matrix.Copy((float*)tabA[1], 1, 3, (float*)tabA[0]);

  Matrix.Copy((float*)tabV[1], 1, 3, (float*)tabV[0]);

  Matrix.Copy((float*)tabP[1], 1, 3, (float*)tabP[0]);
}

float *TraitementDonnees::getAccelerationCourante()
{
    return tabA[tempsCourant];
}

float *TraitementDonnees::getVitesseCourante()
{
    return tabV[tempsCourant];
}

float *TraitementDonnees::getPositionCourante()
{
    return tabP[tempsCourant];
}

void TraitementDonnees::traitement(float ax, float ay, float az)
{
    setAcceleration(ax,ay,az);

    calculerVitesse();

    calculerPosition();
}

