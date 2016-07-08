#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

//#include <ZumoBuzzer.h>


/*
 * This example uses the ZumoMotors library to drive each motor on the Zumo
 * forward, then backward. The yellow user LED is on when a motor should be
 * running forward and off when a motor should be running backward. If a
 * motor on your Zumo has been flipped, you can correct its direction by
 * uncommenting the call to flipLeftMotor() or flipRightMotor() in the setup()
 * function.
 */

#define LED_PIN 13


ZumoMotors motors;

void setup(){


  Serial.begin(9600);
  while(!Serial) {}
  
  pinMode(LED_PIN, OUTPUT);

  
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);
}

void loop(){

    for (int speed = 50; speed <= 300; speed += 10){
      motors.setLeftSpeed(speed);
      motors.setRightSpeed(speed);
      Serial.println("");
      delay(2000);
    }

/*
    for (int speed = 201; speed <= 300; speed++){
      motors.setSpeeds(speed,speed);
      delay(10);
    }

    motors.setSpeeds(0,0);

    delay(1000);

    motors.flipLeftMotor(true);
    motors.flipRightMotor(true);

    for (int speed = 201; speed <= 300; speed++){
      motors.setSpeeds(speed,speed);
      delay(10);
    }

    
    motors.setSpeeds(0,0);

    delay(1000);

    motors.flipLeftMotor(false);
    motors.flipRightMotor(false);

*/


}
