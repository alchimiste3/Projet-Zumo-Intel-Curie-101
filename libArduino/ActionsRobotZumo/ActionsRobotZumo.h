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


class ActionsRobot {

  int speed;
  bool enAttente;

  public: 

    ActionsRobot();
    
    void action(const char * commande);

};

#endif