/*
 * ActionsRobotZumo.h
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 25-07-1016 (Quentin)
 *
 * Cette classe permet de diriger le robot et d'utiliser son capteur de ligne
 */

#ifndef ActionsRobotZumo_h
#define ActionsRobotZumo_h

#include <string.h>
#include <stdlib.h>

#include <Arduino.h>
#include <ZumoMotorsCurie.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>

class ActionsRobot {

  //////////////////////// Motors ////////////////////////

  int speed;
  bool immobile;

  //////////////////////// Sensors ////////////////////////

  ZumoReflectanceSensorArray reflectanceSensors;

	Pushbutton button;

	int calibrationAuto;

	const int MAX_SPEED = 200;

	int m1Speed;
	int m2Speed;

	int pariodeMoteurGauche;

  unsigned int sensors[6];

  public: 

    ActionsRobot();
    
    // Execution de la commande par le robot
    void action(char * commande);

    // Verifier si le robot est immobile (speed == 0)
    bool estImmobile();

    // Changer la vitesse des moteurs gauche et droit du robot.
		void vitesseMoteurs(int vitesseGauche, int vitesseDroite);

    // Calibration du capteur de ligne (automatique par default)
    void calibrationSensors();

    // Demander au robot de suivre une ligne 
    void suivreUneLigne();

    // Demander au robot de suivre une ligne 
    void suivreLigneV2(int position);

    void detecterLigneV2(unsigned int * sensors);

    void detecterCroisement(unsigned int * sensors);

};

#endif