/*! \file ZumoMotors.h
 *
 * See the ZumoMotors class reference for more information about this library.
 *
 * \class ZumoMotors ZumoMotors.h
 * \brief Control motor speed and direction
 * 
 */

#ifndef ActionsRobotZumo_h
#define ActionsRobotZumo_h

#include <string.h>
#include <stdlib.h>
//#include <vector>

#include <Arduino.h>
#include <ZumoMotorsCurie.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>

class ActionsRobot {

  //////////////////////// Motors ////////////////////////

  int speed;
  bool enAttente;

  //////////////////////// Sensors ////////////////////////

  ZumoReflectanceSensorArray reflectanceSensors;

	Pushbutton button;

	int calibrationAuto;

	const int MAX_SPEED = 300;

	int m1Speed;
	int m2Speed;

	int pariodeMoteurGauche;

  unsigned int sensors[6];

  public: 

    ActionsRobot();
    
    void action(const char * commande);


    void calibrationSensors();

    void suivreUneLigne();

    void suivreLigneV2(int position);

    void detecterLigneV2(unsigned int * sensors);

    void detecterCroisement(unsigned int * sensors);

};

#endif