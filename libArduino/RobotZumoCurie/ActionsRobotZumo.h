/*
 * ActionsRobotZumo.h
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 29-07-1016 (Quentin)
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

  #define MAX_SPEED 200

	//const int MAX_SPEED = 200;

	int m1Speed;
	int m2Speed;

	int pariodeMoteurGauche;

  unsigned int sensors[6];

  public: 

    ActionsRobot();
    
    void action(char * commande);

    bool estImmobile();

		void vitesseMoteurs(int vitesseGauche, int vitesseDroite);

    void calibrationSensors();

    void suivreUneLigne();

    void suivreLigneV2(int position);

    void detecterLigneV2(unsigned int * sensors);

    void detecterCroisement(unsigned int * sensors);

};

#endif