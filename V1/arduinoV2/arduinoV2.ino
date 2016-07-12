#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

#include <CurieIMU.h>

#include <CurieNeurons.h>

#include <CurieBLE.h>

//#define DEFAULT_DESIRED_MIN_CONN_INTERVAL     10

/////////////////////////////// IMU ///////////////////////////////

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

/////////////////////////////// BLE ///////////////////////////////

BLEPeripheral blePeripheral;
BLEService AnalogService("3752c0a0-0d25-11e6-97f5-0002a5d5c51c");
//BLEService MotionService("3752c0a0-0d25-11e6-97f5-0002a5d5c51d");

BLECharacteristic analogCharacteristique("3752c0a0-0d25-11e6-97f5-0002a5d5c51c", BLERead | BLEWrite | BLENotify, 20);
//BLECharacteristic analogCharacteristique2("3752c0a0-0d25-11e6-97f5-0002a5d5c51d", BLERead | BLENotify, 20);


////////////////////////// var neurons ///////////////////////:

CurieNeurons hNN;

int catL=0; // category to learn
int prevcat=0; // previously recognized category
int dist, cat, nid, nsr, ncount; // response from the neurons

////////////////////////// var getVector ///////////////////////:

#define sampleNbr 10  // number of samples to assemble a vector
#define signalNbr  6  // ax,ay,az,gx,gy,gz
int raw_vector[sampleNbr*signalNbr]; // vector accumulating the raw sensor data
byte vector[sampleNbr*signalNbr]; // vector holding the pattern to learn or recognize
int mina=0xFFFF, maxa=0, ming=0xFFFF, maxg=0, da, dg;

///////////////////////////////Motor///////////////////////////////

ZumoMotors motors;

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

   //////////////////////////// Setup neurons /////////////////////////////////////

    hNN.Init();
    hNN.Forget(500);


  pinMode(13,OUTPUT);

  digitalWrite(13,LOW);
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

     if (analogCharacteristique.written()) {
        if (((const char*)analogCharacteristique.value())[0] == 'm') {
          if (((const char*)analogCharacteristique.value())[1] == '1') {
              motors.setLeftSpeed(400);
              motors.setRightSpeed(400);
            }
          else if (((const char*)analogCharacteristique.value())[1] == '2') {
              motors.setLeftSpeed(400);
              motors.setRightSpeed(-400);
          }
        }
        if (((const char*)analogCharacteristique.value())[0] == 'a') {
          for (int i=0; i<5; i++){
            getVector(); 
            ncount=hNN.Learn(vector, sampleNbr*signalNbr, ((const char*)analogCharacteristique.value())[1]);
            
          }
          
        }
        if (((const char*)analogCharacteristique.value())[0] == 'r') {
          getVector();
          hNN.Classify(vector, sampleNbr*signalNbr,&dist, &cat, &nid);

          if (cat!=prevcat)
          {
            if (cat!=0x7FFF)
            {
              //switchCharacteristic.setValue(cat);
              digitalWrite(13,HIGH);

            }
            else{
              //switchCharacteristic.setValue('n');
              digitalWrite(13,LOW);

            }

            prevcat=cat;
          }


        }
        if (((const char*)analogCharacteristique.value())[0] == '1') {    
          
          demiTour();
        }
        else if (((const char*)analogCharacteristique.value())[0] == '2') {
          
          arret();
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

    Serial.print("a : ");Serial.println(millis());
    analogCharacteristique.setValue((unsigned char*)donneesEnvoyer, 20);
    Serial.print("b : ");Serial.println(millis());
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

void demiTour(){
  motors.setLeftSpeed(400);
  motors.setRightSpeed(-400);
  delay(348);
}

void avant(int temps){
  motors.setLeftSpeed(400);
  motors.setRightSpeed(400);
  delay(temps);
}

void arriere(int temps){
  motors.setLeftSpeed(400);
  motors.setRightSpeed(-400);
  delay(temps);
}

void droit(){
  motors.setLeftSpeed(400);
  motors.setRightSpeed(0);
  delay(305);
}

void gauche(){
  motors.setLeftSpeed(0);
  motors.setRightSpeed(400);
  delay(305);
}

void arret(){
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

void getVector(){

  mina=0xFFFF, maxa=0, ming=0xFFFF, maxg=0, da, dg;
  
  for (int sampleId=0; sampleId<sampleNbr; sampleId++){
    
    CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);
    
    // update the running min/max for the a signals
    if (ax>maxa) maxa=ax; else if (ax<mina) mina=ax;
    if (ay>maxa) maxa=ay; else if (ay<mina) mina=ay;
    if (az>maxa) maxa=az; else if (az<mina) mina=az;    
    da= maxa-mina;
    
    // update the running min/max for the g signals
    if (gx>maxg) maxg=gx; else if (gx<ming) ming=gx;
    if (gy>maxg) maxg=gy; else if (gy<ming) ming=gy;
    if (gz>maxg) maxg=gz; else if (gz<ming) ming=gz;   
    dg= maxg-ming;

    // accumulate the sensor data
    raw_vector[sampleId*signalNbr]= ax;
    raw_vector[(sampleId*signalNbr)+1]= ay;
    raw_vector[(sampleId*signalNbr)+2]= az;
    raw_vector[(sampleId*signalNbr)+3]= gx;
    raw_vector[(sampleId*signalNbr)+4]= gy;
    raw_vector[(sampleId*signalNbr)+5]= gz;
  }
  
  // normalize vector
  for(int sampleId=0; sampleId < sampleNbr; sampleId++)
  {
    for(int i=0; i<3; i++)
    {
      vector[sampleId*signalNbr+i]  = (((raw_vector[sampleId*signalNbr+i] - mina) * 255)/da) & 0x00FF;
      vector[sampleId*signalNbr+3+i]  = (((raw_vector[sampleId*signalNbr+3+i] - ming) * 255)/dg) & 0x00FF;
    }
  }
}



