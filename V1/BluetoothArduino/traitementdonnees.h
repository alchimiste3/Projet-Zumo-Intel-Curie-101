#ifndef TRAITEMENTDONNEES_H
#define TRAITEMENTDONNEES_H
#include <QDebug>
#include "MatrixMath/MatrixMath.h"
#include "Madgwick/MadgwickAHRS.h"


class TraitementDonnees
{

    const int tempsCourant = 1;
    float tempsEntreMesure;
    float tabA[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
    float tabV[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
    float tabP[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
    bool immobile;

    Madgwick filter;
    float roll;
    float yaw;
    float pitch;

    const int facteurRoll = 50;
    const int facteurYaw = 50;
    const int facteurPitch = 50;
public:
    TraitementDonnees();
    void setAcceleration(float ax, float ay, float az);
    void calculerVitesse();
    void calculerPosition();
    void miseAJourVal();
    float* getAccelerationCourante();
    float* getVitesseCourante();
    float* getPositionCourante();

    float getRoll();
    float getYaw();
    float getPitch();

    void traitement(float ax, float ay, float az, float gx, float gy, float gz, bool immobile, float intervalle);

    void calculQuaternions(float gx, float gy, float gz, float ax, float ay, float az);
};

#endif // TRAITEMENTDONNEES_H
