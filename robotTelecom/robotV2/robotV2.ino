#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

#include <CurieBLE.h>

//#include <ZumoBuzzer.h>


BLEPeripheral blePeripheral;
BLEService service("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

ZumoMotors motors;

void setup(){

  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(service.uuid());
  blePeripheral.addAttribute(service);
  blePeripheral.addAttribute(switchCharacteristic);
  switchCharacteristic.setValue(0);

  blePeripheral.begin();
  
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

void loop(){
  
  BLECentral central = blePeripheral.central();

  if (central) {
    while (central.connected()) {
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value() == 1) {
          avant(1000);
          
          demiTour();
      
          avant(1000);
      
          demiTour();

          arret();
        }
        else if (switchCharacteristic.value() == 2) {
          avant(1000);
      
          droit();
      
          avant(1000);
      
          droit();
      
          avant(1000);
      
          droit();
      
          avant(1000);
      
          droit();  

          arret();

        }
      }
    }
  }


}
