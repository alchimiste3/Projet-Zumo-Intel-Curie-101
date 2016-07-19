/*! \file ZumoMotors.h
 *
 * See the ZumoMotors class reference for more information about this library.
 *
 * \class ZumoMotors ZumoMotors.h
 * \brief Control motor speed and direction
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
    
    // initializes timer1 for proper PWM generation
    static void init2();
};

#endif