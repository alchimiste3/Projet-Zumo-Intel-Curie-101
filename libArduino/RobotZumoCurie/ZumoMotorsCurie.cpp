/*
 * ZumoMotorsCurie.cpp
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 25-07-1016 (Quentin)
 *
 * Adaptation d'un code fournie par le constructeur du robot zumo pour qu'il puis fonctionner avec la carte Intel Curie 101 :
 * Voir : https://github.com/pololu/zumo-shield/tree/master/ZumoMotors
 *
 */

#include "ZumoMotorsCurie.h"

#define PWM_L 10
#define PWM_R 9
#define DIR_L 8
#define DIR_R 7


static boolean flipLeft = false;
static boolean flipRight = false;

ZumoMotors::ZumoMotors(){}


// On initialise les pins sur les moteurs et les diodes
void ZumoMotors::init2()
{
  pinMode(PWM_L,  OUTPUT);
  pinMode(PWM_R,  OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);

}

// enable/disable flipping of left motor
void ZumoMotors::flipLeftMotor(boolean flip)
{
  flipLeft = flip;
}

// enable/disable flipping of right motor
void ZumoMotors::flipRightMotor(boolean flip)
{
  flipRight = flip;
}

// Le Robot Zumo est consue pour des carte de type Uno : notre carte Curie a le meme format mais le type de pin (digital et PWM)
// change. Le pin 10 de la Curie (ou le moteur gauche est brancher) est digital alors que celui de la Uno est en PWM. 
// On doit donc generer un signal PWM sur le  pin 10 avec une frequence qui varie selon les cas (490HZ ou 980Hz)
void ZumoMotors::setLeftSpeedCurie(int speed, int periode)
{

  //Serial.print("speed left curie = ");Serial.println(speed);

  init(); // initialize if necessary
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 400)  // Max 
    speed = 400;


  CurieTimerOne.pwmStart(PWM_L, speed * 0.25, periode);

  if (reverse ^ flipLeft) // flip if speed was negative or flipLeft setting is active, but not both
    digitalWrite(DIR_L, HIGH);
  else
    digitalWrite(DIR_L, LOW);


}

// Version sans le chois de la periode (definie pour une frequence de 980Hz)
void ZumoMotors::setLeftSpeedCurie(int speed)
{

  setLeftSpeedCurie(speed,1020);

}


// methode pour le moteur gauche non modifie 
void ZumoMotors::setRightSpeed(int speed)
{

  init();
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;
    reverse = 1;  
  }
  if (speed > 400)
    speed = 400;

  analogWrite(PWM_R, speed * 0.6375); // 0.6375 = 51 / 80 : on passe la vitesse qui est sur 400 a une vitesse sur 255

  if (reverse ^ flipRight) 
    digitalWrite(DIR_R, HIGH);
  else
    digitalWrite(DIR_R, LOW);

}

// modifier la vittesse de moteur en choisisant la periode PWM du moteur gauche
void ZumoMotors::setSpeeds(int leftSpeed, int rightSpeed, int periode)
{
  setLeftSpeedCurie(leftSpeed, periode);
  setRightSpeed(rightSpeed);
}


void ZumoMotors::setSpeeds(int leftSpeed, int rightSpeed)
{
  setLeftSpeedCurie(leftSpeed);
  setRightSpeed(rightSpeed);
}