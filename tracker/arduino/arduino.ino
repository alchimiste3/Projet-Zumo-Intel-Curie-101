#include <MatrixMath.h>

#include <CurieIMU.h>

#include <MadgwickAHRS.h>
#include <CurieNeurons.h>

#include <CurieBLE.h>



Madgwick filter; // initialise Madgwick object

MatrixMath matrix;


float tabA[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
float tabV[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
float tabP[2][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};


int ax, ay, az;
int gx, gy, gz;

float yaw;             // pour z
float pitch;           // pour y
float roll;            // pour x

int factorX = 6; 
int factorY = 6; 
int factorZ = 1; 

int tempsCourant = 1;

int accelerometreRange = 2;
int gyroRange = 125;

float IMURate = 200;
float tempsEntreMesure = 0.005; // 1/IMURate

BLEPeripheral blePeripheral;
BLEService AnalogService("3752c0a0-0d25-11e6-97f5-0002a5d5c51b");

BLECharacteristic analogCharacteristique("3752c0a0-0d25-11e6-97f5-0002a5d5c51b", BLERead | BLENotify, 1);

void setup() {
  
  Serial.begin(9600);

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

   blePeripheral.setLocalName("RdWrS");
   blePeripheral.setAdvertisedServiceUuid(AnalogService.uuid());
   blePeripheral.addAttribute(AnalogService);
   blePeripheral.addAttribute(analogCharacteristique);
   blePeripheral.begin();

}

void loop() {
  BLECentral central = blePeripheral.central();
  
  if(central){

   Serial.println(central.address());

   while(central.connected()){

    getInfoIMU();

    
 
    accelerationCarte();

    vitesseCarte();
    
    positionCarte();
           
    if (Serial.available() > 0) {
      //Serial.println("salut");
      int val = Serial.read();
      if (val == 's') {
        Serial.print(roll,2);
        Serial.print(","); 
        Serial.print(yaw,2);
        Serial.print(","); 
        Serial.print(pitch,2);
        Serial.print(","); 
        Serial.print(tabA[tempsCourant][0],10);
        Serial.print(","); 
        Serial.print(tabA[tempsCourant][1],10);
        Serial.print(","); 
        Serial.print(tabA[tempsCourant][2],10);
        Serial.print(","); 
        Serial.print(tabV[tempsCourant][0],10);
        Serial.print(","); 
        Serial.print(tabV[tempsCourant][1],10);
        Serial.print(","); 
        Serial.print(tabV[tempsCourant][2],10);
        Serial.print(","); 
        Serial.print(tabP[tempsCourant][0],10);
        Serial.print(","); 
        Serial.print(tabP[tempsCourant][1],10);
        Serial.print(","); 
        Serial.println(tabP[tempsCourant][2],10);
      }
    
    }
 
    miseAjourVal();

   
    
  }
}



}

void getInfoIMU() {

  //Serial.println("\n getInfoIMU");

  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

  gx = (gx/32768.9)*gyroRange;
  gy = (gy/32768.9)*gyroRange;
  gz = (gz/32768.9)*gyroRange;

  filter.updateIMU(gx / factorX, gy / factorY, gz / factorZ, ax, ay, az);



  roll = filter.getRollRadians();
  yaw = filter.getYawRadians();
  pitch = filter.getPitchRadians();
  
}

//TODO 
void supprimerGravite(float* res){
  /*
  Serial.println("\n supprimerGravite");

  float g[3] = {0.0};

  float g0 = filter.getG0();
  float g1 = filter.getG1();
  float g2 = filter.getG2();

  Serial.println(g0,5);
  Serial.println(g1,5);
  Serial.println(g2,5);
  Serial.println("");


  g[0] = 2 * (q1 * q3 - q0 * q2);
  g[1] = 2 * (q0 * q1 + q2 * q3);
  g[2] = (q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3);

  Serial.println(g[0]);
  Serial.println(g[1]);
  Serial.println(g[2]);

  res[0] = (tabA[tempsCourant][0] - g0);
  res[1] = (tabA[tempsCourant][1] - g1);
  res[2] = (tabA[tempsCourant][2] - g2);
  
*/
}


void accelerationCarte() {
  //acc = acc * 9.81;

  //Serial.println("\n accelerationCarte");

  //Serial.println("accelerometreRange = ");Serial.println(accelerometreRange);
  
  //matrix.Print((float*)tabA[tempsCourant], 1, 3, "A");
  //Serial.println(tabA);

  
  tabA[tempsCourant][0] = (int)((ax/32768.0)*accelerometreRange * 9.81);
  tabA[tempsCourant][1] = (int)((ay/32768.0)*accelerometreRange * 9.81);
  tabA[tempsCourant][2] = (int)(-(az/32768.0)*accelerometreRange * 9.81);

   //matrix.Print((float*)tabA, 2, 3, "A");
  
/*

  float res[3] = {0.0};
  supprimerGravite(res);
  matrix.Print((float*)res, 1, 3, "RES");
  
  matrix.Subtract((float*)tabA[tempsCourant], (float*)res, 1, 3, (float*)tabA[tempsCourant]);

*/

  //matrix.Print((float*)tabA[tempsCourant], 1, 3, "A");


}

void vitesseCarte() {

  float tabinter[3] = {0.0};

  //Serial.println("\n vitesseCarte");

    //matrix.Print((float*)tabA[tempsCourant], 1, 3, "A");

    //Serial.print("tempsEntreMesure = ");Serial.println(tempsEntreMesure,6);


    tabinter[0] = tabA[tempsCourant][0] * tempsEntreMesure;
    tabinter[1] = tabA[tempsCourant][1] * tempsEntreMesure;
    tabinter[2] = tabA[tempsCourant][2] * tempsEntreMesure;


    //matrix.Print((float*)tabA[tempsCourant], 1, 3, "A");

    

    matrix.Add((float*)tabV[tempsCourant - 1], (float*)tabinter, 1, 3, (float*)tabV[tempsCourant]);
    




}

void positionCarte() {

  float tabinter[3] = {0.0};

  //Serial.println("\n positionPosition");

    //matrix.Print((float*)tabv[tempsCourant], 1, 3, "V");

    tabinter[0] = tabV[tempsCourant][0] * tempsEntreMesure;
    tabinter[1] = tabV[tempsCourant][1] * tempsEntreMesure;
    tabinter[2] = tabV[tempsCourant][2] * tempsEntreMesure;


    //matrix.Print((float*)tabP[tempsCourant-1], 1, 3, "P");

    matrix.Add((float*)tabP[tempsCourant - 1], (float*)tabinter, 1, 3, (float*)tabP[tempsCourant]);
    
}




void miseAjourVal() {
  Serial.print("");

  matrix.Copy((float*)tabA[1], 1, 3, (float*)tabA[0]);
  
  matrix.Copy((float*)tabV[1], 1, 3, (float*)tabV[0]);
  
  matrix.Copy((float*)tabP[1], 1, 3, (float*)tabP[0]);

  //matrix.Print((float*)tabA[tempsCourant], 1, 3, "A");


}

