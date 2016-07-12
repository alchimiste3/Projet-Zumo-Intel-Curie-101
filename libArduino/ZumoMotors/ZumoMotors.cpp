#include "ZumoMotors.h"

#define PWM_L 10
#define PWM_R 9
#define DIR_L 8
#define DIR_R 7

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega32U4__)
  #define USE_20KHZ_PWM
#endif

static boolean flipLeft = false;
static boolean flipRight = false;

// constructor (doesn't do anything)
ZumoMotors::ZumoMotors()
{
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void ZumoMotors::init2()
{
  pinMode(PWM_L,  OUTPUT);
  pinMode(PWM_R,  OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);

#ifdef USE_20KHZ_PWM
  // Timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;
#endif
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

// Version avec la convertion en PWM du pin 10
void ZumoMotors::setLeftSpeedCurie(int speed)
{

  Serial.print("speed left curie = ");Serial.println(speed);

  init(); // initialize if necessary
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 400)  // Max 
    speed = 400;

  Serial.print("speed * 0.25 = ");Serial.println(speed * 0.25);

    

#ifdef USE_20KHZ_PWM
  OCR1B = speed;
#else 

  // On prend une periode de 2040 µs car la frequence du pin 9 pwm est de 480 Hz
  Serial.print("CurieTimerOne.pwmStart(PWM_L,");Serial.print(speed * 0.25);Serial.println(", 2040)");
  CurieTimerOne.pwmStart(PWM_L, speed * 0.25, 2040); // 12288 = 1/(48*256), mapping 400 to 100

#endif 

  if (reverse ^ flipLeft) // flip if speed was negative or flipLeft setting is active, but not both
    digitalWrite(DIR_L, HIGH);
  else
    digitalWrite(DIR_L, LOW);

  Serial.println("");

}


// set speed for right motor; speed is a number between -400 and 400
void ZumoMotors::setRightSpeed(int speed)
{

  Serial.print("speed rigth = ");Serial.println(speed);

  init(); // initialize if necessary
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

  Serial.print("speed * 51 / 80 = ");Serial.println(speed * 0.6375);
  Serial.print("speed * 51 / 80 = ");Serial.println(((speed * 0.6375)*100)/255.0);

    
#ifdef USE_20KHZ_PWM
  OCR1A = speed;
#else
  Serial.print("analogWrite(PWM_R, ");Serial.print(speed * 0.6375);Serial.println(")");
  analogWrite(PWM_R, speed * 0.6375); // 0.6375 = 51 / 80 
  // default to using analogWrite, mapping 400 to 255
#endif

  if (reverse ^ flipRight) // flip if speed was negative or flipRight setting is active, but not both
    digitalWrite(DIR_R, HIGH);
  else
    digitalWrite(DIR_R, LOW);


  Serial.println("");


}

// set speed for both motors
void ZumoMotors::setSpeeds(int leftSpeed, int rightSpeed)
{
  //setLeftSpeed(leftSpeed);
  setLeftSpeedCurie(leftSpeed);
  setRightSpeed(rightSpeed);
}