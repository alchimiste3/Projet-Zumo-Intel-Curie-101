#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>


ZumoReflectanceSensorArray reflectanceSensors;

#define NUM_SENSORS 6
unsigned int sensorValues[NUM_SENSORS];

int lastError = 0;


void setup()
{

  
  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  while(!Serial){}

  Serial.println("reflectanceSensors.init()");
  reflectanceSensors.init();

  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);        // turn on LED to indicate we are in calibration mode

  Serial.println("reflectanceSensors.calibrate()");

  unsigned long startTime = millis();
  while(millis() - startTime < 10000)   // make the calibration take 10 seconds
  {
    reflectanceSensors.calibrate();
  }
  digitalWrite(13, LOW);         // turn off LED to indicate we are through with calibration

  for (byte i = 0; i < NUM_SENSORS; i++)
  {
    Serial.println("calibratedMinimumOn");
    Serial.print(reflectanceSensors.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (byte i = 0; i < NUM_SENSORS; i++)
  {
    Serial.println("calibratedMaximumOn");
    Serial.print(reflectanceSensors.calibratedMaximumOn[i]);
    Serial.println(' ');
  }
  Serial.println();
  delay(1000);
  

}
void loop()
{
  // read calibrated sensor values and obtain a measure of the line position.
  // Note: the values returned will be incorrect if the sensors have not been properly
  // calibrated during the calibration phase.
  unsigned int position = reflectanceSensors.readLine(sensorValues);

  // To get raw sensor values instead, call:  
  //reflectanceSensors.read(sensorValues);

  Serial.print("sensor val = ");

  for (byte i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(' ');
  }
  Serial.print("position = ");
  Serial.println(position);

  int error = position - 2500;

  Serial.print("error = ");Serial.println(error);

  
  int speedDifference = error / 4 + 6 * (error - lastError);
  lastError = error;
  
  Serial.print("speedDifference= ");Serial.println(speedDifference);

  
  delay(250);
}
