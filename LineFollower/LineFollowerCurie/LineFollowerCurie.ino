#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotorsCurie.h>
#include <Pushbutton.h>
#include <CurieBLE.h>


ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;

const int MAX_SPEED = 200;


int pariodeMoteurGauche = 1020; // µs pour une fréquence de 980Hz
//int pariodeMoteurGauche = 2040; // µs pour une fréquence de 490Hz



BLEPeripheral blePeripheral;

BLEService AnalogService("3752c0a0-0d25-11e6-97f5-0002a5d5c51c");

BLEUnsignedCharCharacteristic analogCharacteristique("3752c0a0-0d25-11e6-97f5-0002a5d5c51c", BLERead | BLEWrite | BLENotify);


void setup()
{

  Serial.begin(9600);
  while (!Serial);


  ///////////////////////// Curie BLE /////////////////////////

  blePeripheral.setLocalName("RdWrS");
  blePeripheral.setAdvertisedServiceUuid(AnalogService.uuid());
  blePeripheral.addAttribute(AnalogService);
  blePeripheral.addAttribute(analogCharacteristique);
  blePeripheral.begin();

  ///////////////////////// Sensors /////////////////////////

  reflectanceSensors.init(2);

  button.waitForButton();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);


  delay(1000);
  int i;
  for (i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70)) {
      motors.setSpeeds(-200, 200, pariodeMoteurGauche);
    }
    else {
      motors.setSpeeds(200, -200, pariodeMoteurGauche);
      reflectanceSensors.calibrate();
    }

    delay(50);
  }

  motors.setSpeeds(0, 0, pariodeMoteurGauche);

  digitalWrite(13, LOW);



  // Wait for the user button to be pressed and released
  button.waitForButton();

  unsigned int sensors[6];

  reflectanceSensors.readCalibrated(sensors);

  Serial.print("sensors 0 = "); Serial.println(sensors[0]);
  Serial.print("sensors 1 = "); Serial.println(sensors[1]);
  Serial.print("sensors 2 = "); Serial.println(sensors[2]);
  Serial.print("sensors 3 = "); Serial.println(sensors[3]);
  Serial.print("sensors 4 = "); Serial.println(sensors[4]);
  Serial.print("sensors 5 = "); Serial.println(sensors[5]);



  button.waitForButton();


}

void loop() {
  /*
    BLECentral central = blePeripheral.central();

    if (central) {
      while (central.connected()) {

  */


  unsigned int sensors[6];

  int position = reflectanceSensors.readLine(sensors);

  Serial.print("position = "); Serial.println(position);

  Serial.print("sensors 0 = "); Serial.println(sensors[0]);
  Serial.print("sensors 1 = "); Serial.println(sensors[1]);
  Serial.print("sensors 2 = "); Serial.println(sensors[2]);
  Serial.print("sensors 3 = "); Serial.println(sensors[3]);
  Serial.print("sensors 4 = "); Serial.println(sensors[4]);
  Serial.print("sensors 5 = "); Serial.println(sensors[5]);


  /////////////////////////// On suis la ligne //////////////////////////

  //suivreLigne(position);
  suivreLigneV2(position);
  /////////////////////////// Croisement //////////////////////////


  //motors.setSpeeds(MAX_SPEED, MAX_SPEED, pariodeMoteurGauche);

  /*
    }
    }*/

}




void suivreLigne(int position) {


  int error = position - 2500;

  int speedDifference = error / 4 + 6 * (error - lastError);

  Serial.print("error = "); Serial.println(error);

  lastError = error;

  Serial.print("speedDifference= "); Serial.println(speedDifference);

  int m1Speed = MAX_SPEED + speedDifference;
  int m2Speed = MAX_SPEED - speedDifference;

  if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
  if (m1Speed > MAX_SPEED)
    m1Speed = MAX_SPEED;
  if (m2Speed > MAX_SPEED)
    m2Speed = MAX_SPEED;

  motors.setSpeeds(m1Speed, m2Speed, pariodeMoteurGauche);

}

void suivreLigneV2(int position) {


  int error = position - 2500;

  float C = 0.5;

  int diffNorm = (((float)error) / 2500.0) * ((float)MAX_SPEED) * C;


  Serial.print("error = "); Serial.println(error);

  Serial.print("diffNorm = "); Serial.println(diffNorm);


  int m1Speed = MAX_SPEED;
  int m2Speed = MAX_SPEED;

 /* // Si la diff de vitesse est plus grande que 10% de la vitesse max
  if (abs(diffNorm) >= ((MAX_SPEED * 10) / 100)) {
   */ 


  if(diffNorm > 0){
    m1Speed = (MAX_SPEED + diffNorm * diffNorm)/4;
    m2Speed = (MAX_SPEED - diffNorm * diffNorm)/4;
  }
  else if(diffNorm < 0){
    m1Speed = (MAX_SPEED - diffNorm * diffNorm)/4;
    m2Speed = (MAX_SPEED + diffNorm * diffNorm)/4;
  }

  if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
  if (m1Speed > MAX_SPEED)
    m1Speed = MAX_SPEED;
  if (m2Speed > MAX_SPEED)
    m2Speed = MAX_SPEED;

    

  
  
  motors.setSpeeds(m1Speed, m2Speed, pariodeMoteurGauche);


}

