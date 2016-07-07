
#include <CurieIMU.h>

#include <CurieNeurons.h>

#include <CurieBLE.h>

//#define DEFAULT_DESIRED_MIN_CONN_INTERVAL     10

float tabA[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
float tabV[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
float tabP[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};

int ax, ay, az;
int gx, gy, gz;

String incomingBytes;
bool immobile = false;


int tempsCourant = 1;

int accelerometreRange = 2;
int gyroRange = 125;

float IMURate = 200;
float tempsEntreMesure = 0.005; // 1/IMURate

BLEPeripheral blePeripheral;
BLEService AnalogService("3752c0a0-0d25-11e6-97f5-0002a5d5c51c");
//BLEService MotionService("3752c0a0-0d25-11e6-97f5-0002a5d5c51d");

BLECharacteristic analogCharacteristique("3752c0a0-0d25-11e6-97f5-0002a5d5c51c", BLERead | BLENotify, 20);
//BLECharacteristic analogCharacteristique2("3752c0a0-0d25-11e6-97f5-0002a5d5c51d", BLERead | BLENotify, 20);

void setup() {
  
  Serial.begin(9600);

 // while(!Serial){};

  CurieIMU.begin();

  // parametrage de l'accelerometre
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
  CurieIMU.setAccelerometerRate(IMURate);

  // parametrage du gyroscope
  CurieIMU.autoCalibrateGyroOffset();
  CurieIMU.setGyroRange(gyroRange);
  CurieIMU.setGyroRate(IMURate);


   ///////////////////////// Curie BLE /////////////////////////

   blePeripheral.setLocalName("RdWrS2");
   blePeripheral.setAdvertisedServiceUuid(AnalogService.uuid());
   blePeripheral.addAttribute(AnalogService);
   blePeripheral.addAttribute(analogCharacteristique);
 //  blePeripheral.addAttribute(MotionService);
 //  blePeripheral.addAttribute(analogCharacteristique2);
   blePeripheral.begin();

}

void loop() {
  BLECentral central = blePeripheral.central();
  
  if(central){

   Serial.println(central.address());

   while(central.connected()){
    
    if (Serial.available() > 0) {
      incomingBytes = Serial.readString();
      Serial.print("i = ");Serial.println(incomingBytes);
      if (incomingBytes == "i") {
        immobile = true;
      }
      else if (incomingBytes == "m") {
        immobile = false;
      }
    }

    getInfoIMU();

    String res;
    String chaine;

   // Serial.print(ax);
    res = res + String(ax) + ",";
    
   // Serial.print(","); 
   // Serial.print(ay);
    res = res + String(ay) + ",";
    
   // Serial.print(","); 
   // Serial.print(az);
    res = res + String(az) + ",";

   // Serial.print(","); 
   // Serial.println(gz);
    res = res + String(gz) + ",";

    //Ajout de immobile
    res = res + String(immobile);
    chaine = chaine + String(gz);

  /*  char donneesEnvoyer2[20];
    chaine.toCharArray(donneesEnvoyer2, 20);*/
    
      
    char donneesEnvoyer[20];
    String resPaquet = res.substring(0, 19);
    res.remove(0, 19);
    resPaquet.toCharArray(donneesEnvoyer, 20);

    analogCharacteristique.setValue((unsigned char*)donneesEnvoyer, 20);
   // analogCharacteristique2.setValue((unsigned char*)donneesEnvoyer2, 20);
  }
}



}

void getInfoIMU() {

  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

  gx = (gx/32768.9)*gyroRange;
  gy = (gy/32768.9)*gyroRange;
  gz = (gz/32768.9)*gyroRange;

  ax = (int)((ax/32768.0)*accelerometreRange * 9.81);
  ay = (int)((ay/32768.0)*accelerometreRange * 9.81);
  az = (int)(-(az/32768.0)*accelerometreRange * 9.81);
}


