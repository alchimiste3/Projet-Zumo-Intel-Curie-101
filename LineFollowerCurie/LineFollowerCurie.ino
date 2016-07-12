#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
//#include <ZumoBuzzer.h>
#include <Pushbutton.h>



//ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;

// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 100;




void setup()
{

  Serial.begin(9600);
  //while (!Serial); 


  reflectanceSensors.init(2);

  button.waitForButton();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);


  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70)){
        motors.setSpeeds(-201, 201);
    }
    else{
      motors.setSpeeds(201, -201);
      reflectanceSensors.calibrate();
    }

    delay(50);
  }
  
  motors.setSpeeds(0,0);

  digitalWrite(13, LOW);

  // Wait for the user button to be pressed and released
  button.waitForButton();

  unsigned int sensors[6];

  reflectanceSensors.readCalibrated(sensors);

  Serial.print("sensors 0 = ");Serial.println(sensors[0]);
  Serial.print("sensors 1 = ");Serial.println(sensors[1]);
  Serial.print("sensors 2 = ");Serial.println(sensors[2]);
  Serial.print("sensors 3 = ");Serial.println(sensors[3]);
  Serial.print("sensors 4 = ");Serial.println(sensors[4]);
  Serial.print("sensors 5 = ");Serial.println(sensors[5]);

  button.waitForButton();

}

void loop()
{

  unsigned int sensors[6];

  int position = reflectanceSensors.readLine(sensors);

  Serial.print("position = ");Serial.println(position);
  
  Serial.print("sensors 0 = ");Serial.println(sensors[0]);
  Serial.print("sensors 1 = ");Serial.println(sensors[1]);
  Serial.print("sensors 2 = ");Serial.println(sensors[2]);
  Serial.print("sensors 3 = ");Serial.println(sensors[3]);
  Serial.print("sensors 4 = ");Serial.println(sensors[4]);
  Serial.print("sensors 5 = ");Serial.println(sensors[5]);

  int error = position - 2500;

  // Get motor speed difference using proportional and derivative PID terms
  // (the integral term is generally not very useful for line following).
  // Here we are using a proportional constant of 1/4 and a derivative
  // constant of 6, which should work decently for many Zumo motor choices.
  // You probably want to use trial and error to tune these constants for
  // your particular Zumo and line course.


 

  

  int speedDifference = error / 4 + 10 * (error - lastError);
  lastError = error;
  

  Serial.print("speedDifference= ");Serial.println(speedDifference);


  // Get individual motor speeds.  The sign of speedDifference
  // determines if the robot turns left or right.
  int m1Speed = MAX_SPEED + speedDifference;
  int m2Speed = MAX_SPEED - speedDifference;

  // Here we constrain our motor speeds to be between 0 and MAX_SPEED.
  // Generally speaking, one motor will always be turning at MAX_SPEED
  // and the other will be at MAX_SPEED-|speedDifference| if that is positive,
  // else it will be stationary.  For some applications, you might want to
  // allow the motor speed to go negative so that it can spin in reverse.
  if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
  if (m1Speed > MAX_SPEED)
    m1Speed = MAX_SPEED;
  if (m2Speed > MAX_SPEED)
    m2Speed = MAX_SPEED;

  motors.setSpeeds(m1Speed, m2Speed);
  //motors.setSpeeds(MAX_SPEED, MAX_SPEED);

}
