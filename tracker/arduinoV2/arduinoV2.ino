#include <QueueArray.h>

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

#include <Pushbutton.h>

#include <CurieIMU.h>


#include <CurieBLE.h>
#include <ActionsRobotZumo.h>
#include <ApprentissageRobotZumoCurie.h>

#include <string.h>
#include <stdlib.h>

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

int neuronsReconnuePres = 0;

int neuronsReconnue = 0;

/////////////////////////////// Robot ///////////////////////////////

ActionsRobot actionRobot;

ApprentissageRobot apprentissageRobot;

char commande[20];
int paras[10];


int tempsDebut = 0;

int tempsFin = 0;



/*
 * Parametrege de la carte et du robot
 */
void setup() {
  
  Serial.begin(9600);

  while(!Serial){};


  pinMode(13,OUTPUT);

  digitalWrite(13,LOW);

  ///////////////////////// Curie IMU /////////////////////////


  CurieIMU.begin();

  // parametrage de l'accelerometre
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1); // indication pour la gravite : inutile ici car on utilise uniquement x et y
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


   ///////////////////////////// reconaissance mouvement ////////////////////////
   
}

/*
 * Bouble principale
 */
void loop() {


  BLECentral central = blePeripheral.central();
  
  if(central){

    Serial.println(central.address());
    
    
    while(central.connected()){ // Si un utilisateur se connecte
            
      //////////////////////////// Communication Bluetooth ////////////////////////////

      recevoirDonneesBluetooth(); // On recupere la commande de l'utilisateur et on  execute l'action demander
      
      envoieDonneesIMU(); // On envoie les donnees recueillies par le robot
    
    }
  }

}


/*
 * Permet de gerer les resption des paquets bluetooth.
 */
void recevoirDonneesBluetooth(){
      
  gestionCommandes();

    
}

/*
 * Permet de gerer les commandes envoyer par l'utilisateur : tantque une nouvelle commande n'est pas entrer c'est soit la précédente commande qui continue 
 * ou la commande par default qui s'execute (m5).
 */
void gestionCommandes(){


  // Si l'utilisateur en entrer une nouvelle commande 
  if(analogCharacteristique.written()) { 
    
    Serial.println("written");

    const unsigned char * val = analogCharacteristique.value();

    Serial.print("val = ");Serial.println((char *)val);
   
    for(int i = 0 ; i < 20 ; i++){
      commande[i] = ((char *)val)[i];
    }

    
    Serial.print("commande[0] = ");Serial.println((char)commande[0]);

    if(commande[0] == '('){
      char * comm;
  
      comm = strtok(commande, "()");


      int tailleComm = strlen(comm);
      
      Serial.print("tailleComm = ");Serial.println(tailleComm);

      for(int i = 0 ; i < tailleComm ; i++){
        commande[i] = comm[i];
      }
      /*
      for(int i = tailleComm ; i < 20 ; i++){
        commande[i] = ';';
      }
      */

      /*
      Serial.println("Boucle");
      
    
      while(comm[0] != ';' && comm != NULL){
        
        String s =  String("");  

        int tailleComm = strlen(comm);
        for(int i = 0 ; i < tailleComm ; i++){
          Serial.print("i = ");Serial.println(i);
          Serial.print("comm[i] = ");Serial.println((char)comm[i]);

          s += String((char)comm[i]);
        }

        Serial.print("s = ");Serial.println(s);
        listeCommande.enqueue(String(""));
        
        Serial.print("listeCommande.front() = ");Serial.println(listeCommande.front());

        comm = strtok (NULL, "()");
      }
  
      //char * premiereCommande = listeCommande.dequeue();
      */

    }


  }

  Serial.print("commande = ");Serial.println(commande);


 ////////////////////////////////////////////////////////  On execute la commande //////////////////////////////////////////////////////// 

  
 //////////////////////////// Action Robot ////////////////////////////

  // Permet de modifier les mouvement du robot grace a des actions pres implementees dans la carte
  if (commande[0] == 'm') {
    actionRobot.action(commande);
  }

  //////////////////////////// calibration LineSensors ////////////////////////////

  else if (commande[0] == 'c' && commande[1] == 's') {
    actionRobot.calibrationSensors();
    commandeInit();

  }

  //////////////////////////// Suivre Ligne ////////////////////////////

  else if (commande[0] == 's' && commande[1] == 'l') {
    actionRobot.suivreUneLigne();

  }

  //////////////////////////// Apprentissage Actions ////////////////////////////

  else if (commande[0] == 'a') {
    apprentissageRobot.apprendreAvecIMU((int)commande[1]);

  }

  //////////////////////////// Reconnaissance Actions ////////////////////////////

  else if (commande[0] == 'r' && commande[1] != 'a') {
    apprentissageRobot.reconnaitre(&neuronsReconnue);

  }

  //////////////////////////// Reconnaissance Actions avec enregistrement////////////////////////////

  else if (commande[0] == 'e' && commande[1] == 'a') {
    reconnaitreEtEnregistrerAction();     
  }


  //////////////////////////// Reexecuter Actions ////////////////////////////

  // Ici, le robot ne transmet plus de donner et refait les actions appris avec la reconnaisance 
  else if (commande[0] == 'r' && commande[1] == 'a') { 
    reproduireActions();

  }

   //////////////////////////// vider liste Action enregistrees ////////////////////////////

  else if (commande[0] == 'v' && commande[1] == 'l') { 
    apprentissageRobot.viderListeActionReconnue();
  }


  //////////////////////////// Sinon ////////////////////////////

  // Si la commande n'est pas valide alors en renvoie null et on revient à la commande initiale (m5 : immobile)
  else{
    envoieDonneesBluetooth("null");
    commandeInit();
  }


  Serial.print("commande 3 = "); Serial.println(commande);

  Serial.println("");

}

/*
 * Cette fonction permet de reconnaitre des actions simples apprisent precedemment et les enregistrer dans une liste afin de pouvoir les reproduire.
 */
void reconnaitreEtEnregistrerAction(){

  // Premier tour, on prent le temps
  if(neuronsReconnue == neuronsReconnuePres){
    tempsDebut = millis();
  }

  Serial.println("enregistrerAction");
  Serial.println("");

  apprentissageRobot.reconnaitre(&neuronsReconnue);
  
  Serial.print("neuronsReconnuePres = ");Serial.println(neuronsReconnuePres);
  Serial.print("neuronsReconnue = ");Serial.println(neuronsReconnue);


  if(neuronsReconnuePres != neuronsReconnue && neuronsReconnuePres != 0){

    tempsFin = millis();

    if(apprentissageRobot.listeActionPleine()){
      commandeInit();        
    }
    else{
      
      Serial.print("tempsDebut = ");Serial.println(tempsDebut);

      int deffTemps = tempsFin - tempsDebut;
      Serial.print("addActionReconnue(");Serial.print(neuronsReconnuePres);Serial.println(", ");Serial.print(deffTemps);Serial.println(")");
      apprentissageRobot.addActionReconnue(neuronsReconnuePres, tempsFin - tempsDebut);

      Serial.print("apprentissageRobot.getNbActionReconnue() = ");Serial.println(apprentissageRobot.getNbActionReconnue());
    }
    

    
    tempsDebut = millis();
  }
  
  neuronsReconnuePres = neuronsReconnue;



}


/*
 * Cette fonction fait reproduire les actions au robot avec  un phase d'apprentisage. Cette est partie est bloquant pour l'instant
 */
void reproduireActions(){

  Serial.println("reproduireActions");
  
  int nbAction = apprentissageRobot.getNbActionReconnue();
  Serial.print("nbAction = ");Serial.println(nbAction);


  for(int i = 1 ; i <= nbAction ; i++){
    
    Serial.print("Pour i = ");Serial.println(i);


    int numAction = apprentissageRobot.getActionReconnue(i) - 48;
    int temps = apprentissageRobot.getTempsActionReconnue(i);

    Serial.print("numAction = ");Serial.println(numAction);
    Serial.print("temps = ");Serial.println(temps);

    char numActionChar[2];
    numActionChar[0] = 'm';
    numActionChar[1] = '0' + numAction;

    Serial.print("numActionChar = ");Serial.println(numActionChar);
    actionRobot.action(numActionChar);
    delay(apprentissageRobot.getTempsActionReconnue(i));

    Serial.println("");

  }


  
  commandeInit();

  Serial.println("sortie reproduireActions");
}


void envoieDonneesIMU(){

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

  envoieDonneesBluetooth(res);

}

void envoieDonneesBluetooth(String res){

  Serial.print("commande a = "); Serial.println(commande);

  char donneesEnvoyer[20];
  String resPaquet = res.substring(0, 19);
  res.remove(0, 19);
  resPaquet.toCharArray(donneesEnvoyer, 20);
  
  analogCharacteristique.setValue((unsigned char*)donneesEnvoyer, 20);
  
  Serial.print("commande b = "); Serial.println(commande);

}

void getInfoIMU() {

  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

  axConv = ((ax/32768.0)*accelerometreRange * 9.81);
  ayConv = ((ay/32768.0)*accelerometreRange * 9.81);
  gzConv = (gz/32768.9)*gyroRange;

}


void commandeInit(){

  actionRobot.action("m5");
  
  commande[0] = 'm';
  commande[1] = '5';

}



