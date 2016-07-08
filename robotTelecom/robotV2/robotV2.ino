#include "CurieIMU.h"
#include <CurieNeurons.h>
#include <CurieBLE.h>



#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

////////////////////////// var accelerometre ///////////////////////:


int ax, ay, az;         // accelerometer values
int gx, gy, gz;         // gyrometer values

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


////////////////////////// var bluetooth ///////////////////////:


BLEPeripheral blePeripheral;
BLEService service("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

////////////////////////// var robot ///////////////////////:


ZumoMotors motors;

void setup(){

  Serial.begin(9600);
  //while(!Serial){}
  

  //////////////////////////// Setup du bluetooth /////////////////////////////////////
  
  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(service.uuid());
  blePeripheral.addAttribute(service);
  blePeripheral.addAttribute(switchCharacteristic);
  switchCharacteristic.setValue(0);
  blePeripheral.begin();

  //////////////////////////// Setup accelerometre /////////////////////////////////////
  
  CurieIMU.begin();

  CurieIMU.autoCalibrateGyroOffset();
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);


  CurieIMU.setAccelerometerRange(2);
  CurieIMU.setGyroRange(125);
  /*
  CurieIMU.setAccelerometerRange(8);
  CurieIMU.setGyroRange(1000);
*/

  //////////////////////////// Setup neurons /////////////////////////////////////

  hNN.Init();
  hNN.Forget(500);

  
}

void loop(){
  
  BLECentral central = blePeripheral.central();

  if (central) {
    while (central.connected()) {
      if (switchCharacteristic.written()) {
        
        if (switchCharacteristic.value() != 0){
          catL = switchCharacteristic.value();

          if(catL == 1){
            motors.setLeftSpeed(400);
            motors.setRightSpeed(400);
            delay(100);
          }
          else if(catL == 2){
            motors.setLeftSpeed(400);
            motors.setRightSpeed(-400);
            delay(100);
          }
  
            
          Serial.println("");

          for (int i=0; i<5; i++)
          {
            getVector(); 
            ncount=hNN.Learn(vector, sampleNbr*signalNbr, catL);
          }

          Serial.println(vector[0]);

          Serial.println("");

          delay(100);
          motors.setLeftSpeed(0);
          motors.setRightSpeed(0);
          



          
        }
        else
        {
          motors.setLeftSpeed(400);
          motors.setRightSpeed(-400);

          delay(100);

          getVector();
          hNN.Classify(vector, sampleNbr*signalNbr,&dist, &cat, &nid);

          Serial.println("");
          Serial.print("prevcat = ");Serial.println(prevcat);
          Serial.print("cat = ");Serial.println(cat);
          Serial.print("0x7FFF = ");Serial.println(0x7FFF);

          if (cat!=prevcat)
          {
            if (cat!=0x7FFF)
            {
              Serial.println(vector[0]);


              switchCharacteristic.setValue(cat);
            }
            else{
              Serial.println("non");
              switchCharacteristic.setValue('n');
            }

            prevcat=cat;
          }

          Serial.println("");

          delay(100);
          motors.setLeftSpeed(0);
          motors.setRightSpeed(0);

        }
         
      }
    }
  }
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


///////////////////////////// fonctions robot ////////////////////////////////////////////////


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
