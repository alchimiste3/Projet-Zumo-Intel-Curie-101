/*
 * ZumoMotorsCurie.h
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 25-07-1016 (Quentin)
 *
 * Adaptation d'un code fournie par le constructeur du robot zumo pour qu'il puis fonctionner avec la carte Intel Curie 101 :
 * Voir : https://github.com/pololu/zumo-shield/tree/master/ZumoMotors
 *
 */


#ifndef ZumoMotors_h
#define ZumoMotors_h

#include "CurieTimerOne.h"

#include <Arduino.h>

class ZumoMotors
{
  public:  
  
    // constructor (doesn't do anything)
    ZumoMotors();
    
    static void flipLeftMotor(boolean flip);
    static void flipRightMotor(boolean flip);
    

    static void setRightSpeed(int speed);

    static void setSpeeds(int leftSpeed, int rightSpeed, int periode);
    static void setLeftSpeedCurie(int speed, int periode);

    static void setSpeeds(int leftSpeed, int rightSpeed);
    static void setLeftSpeedCurie(int speed);
    
  private:

    static inline void init()
    {
      static boolean initialized = false;

      if (!initialized)
      {
        initialized = true;
        init2();
      }
    }
    
    static void init2();
};

#endif