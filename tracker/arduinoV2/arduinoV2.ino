#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

#include <Pushbutton.h>

#include <CurieIMU.h>


#include <CurieBLE.h>
#include <ActionsRobotZumo.h>
#include <ApprentissageRobotZumoCurie.h>


/////////////////////////////// IMU ///////////////////////////////

int ax, ay, az;
int gx, gy, gz;

float axConv, ayConv;
float gzConv;

int tempsCourant = 1;

int accelerometreRange = 2;
int gyroRange = 125;

float IMURate = 200;
float tempsEntreMesure = 0.005; // 1/IMURate

/////////////////////////////// BLE ///////////////////////////////

BLEPeripheral blePeripheral;

BLEService AnalogService("3752c0a0-0d25-11e6-97f5-0002a5d5c51c");

BLECharacteristic analogCharacteristique("3752c0a0-0d25-11e6-97f5-0002a5d5c51c", BLERead | BLEWrite | BLENotify, 20);


/////////////////////////////// Neurons ///////////////////////////////

int neuronsReconnue = 0;

/////////////////////////////// Robot ///////////////////////////////

ActionsRobot actionRobot;

ApprentissageRobot apprentissageRobot;

char typeCommande = 'm';
char para = '5';


void setup() {
  
  Serial.begin(9600);

  //while(!Serial){};


  pinMode(13,OUTPUT);

  digitalWrite(13,LOW);

  ///////////////////////// Curie IMU /////////////////////////


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
            
      //////////////////////////// Communication Bluetooth ////////////////////////////
      
      recevoirDonneesBluetooth();
      
      envoieDonneesBluetooth();
    
    }
  }

}

void recevoirDonneesBluetooth(){
  

  Serial.print("typeCommande = ");Serial.println(typeCommande);
  Serial.print("para = ");Serial.println(para);
  Serial.println("");
    
  if(analogCharacteristique.written()) {

    typeCommande = ((const char*)analogCharacteristique.value())[0];

    para = ((const char*)analogCharacteristique.value())[1];

    //////////////////////////// Mouvement Robot ////////////////////////////

    if (typeCommande == 'm') {
      actionRobot.action(((const char*)analogCharacteristique.value()));
  
    }

   //////////////////////////// calibrate Sensors ////////////////////////////

    if (typeCommande == 'c' && para == 's') {
      Serial.println("cs");
      actionRobot.calibrationSensors();
    }

  }

  //////////////////////////// Suivre Ligne ////////////////////////////

  if (typeCommande == 's' && para == 'l') {
    Serial.println("sl");
    actionRobot.suivreUneLigne();

  }

  //////////////////////////// Apprentissage Mouvement ////////////////////////////

  if (typeCommande == 'a') {
    apprentissageRobot.apprendreAvecIMU((int)para);
  }

  //////////////////////////// Reconnaissance Mouvement ////////////////////////////

  if (typeCommande == 'r') {
    apprentissageRobot.reconnaitre(&neuronsReconnue);

    
  }
}


void envoieDonneesBluetooth(){

  getInfoIMU();
  
  String res;

  
  res = res + String(axConv,1) + ",";
  res = res + String(ayConv,1) + ",";
  res = res + String(gzConv,2) + ",";
  
  //Ajout de immobile

  bool immobile = actionRobot.estImmobile();
  res = res + String(immobile) + ",";;

  //Ajout de neuronsReconnue

  res = res + String(neuronsReconnue);

  char donneesEnvoyer[20];
  String resPaquet = res.substring(0, 19);
  res.remove(0, 19);
  resPaquet.toCharArray(donneesEnvoyer, 20);
  
  //Serial.print("a : ");Serial.println(millis());
  analogCharacteristique.setValue((unsigned char*)donneesEnvoyer, 20);
  //Serial.print("b : ");Serial.println(millis());
  analogCharacteristique.setValue((unsigned char*)donneesEnvoyer, 20);
  //Serial.print("c : ");Serial.println(millis());

}

void getInfoIMU() {

  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

  axConv = ((ax/32768.0)*accelerometreRange * 9.81);
  ayConv = ((ay/32768.0)*accelerometreRange * 9.81);
  gzConv = (gz/32768.9)*gyroRange;


}



