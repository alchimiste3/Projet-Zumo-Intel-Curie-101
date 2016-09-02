#ifndef TRAITEMENTDONNEES_H
#define TRAITEMENTDONNEES_H
#include <QDebug>
#include "MatrixMath/MatrixMath.h"
#include "Madgwick/MadgwickAHRS.h"


/**
 * @brief The TraitementDonnees class
 */
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

    /**
     * @param ax
     * @param ay
     * @param az
     * Définit les accélérations pour les calculs
     */
    void setAcceleration(float ax, float ay, float az);

    /**
      Calcul des vitesses à partir des accélérations
     */
    void calculerVitesse();
    /**
      Calcul des positions à partir des vitesses
     */
    void calculerPosition();

    /**
     * Met à jour la matrice d'accélérations
     */
    void miseAJourVal();
    float* getAccelerationCourante();
    float* getVitesseCourante();
    float* getPositionCourante();

    /**
     * @return
     * Renvoie roll
     */
    float getRoll();

    /**
     * @return
     * Renvoie yaw
     */
    float getYaw();

    /**
     * @return
     * Renvoie pitch
     */
    float getPitch();

    /**
     * @param ax
     * @param ay
     * @param az
     * @param gx
     * @param gy
     * @param gz
     * @param immobile
     * @param intervalle
     * Permet de calculer les vitesses, positions et les quaternions
     */
    void traitement(float ax, float ay, float az, float gx, float gy, float gz, bool immobile, float intervalle);

    /**
     * @param gx
     * @param gy
     * @param gz
     * @param ax
     * @param ay
     * @param az
     * On utilise l'algorithme de Madgwick pour calculer les quaternions roll yaw pitch à partir des 6 accélérations
     * Les qquaternions donnent la rotation sur les 3 axes de la carte
     */
    void calculQuaternions(float gx, float gy, float gz, float ax, float ay, float az);
};

#endif // TRAITEMENTDONNEES_H
