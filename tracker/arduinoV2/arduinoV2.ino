/*
 * arduinoV2.ino
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *                      Clement Sibut []

 * Dernier mise a jour: 26-07-1016 (Quentin)
 *
 * lib utiliser : RobotZumoCurie
 * 
 * Ce programme permet a une carte Intel Curie 101 de commander un robot zumo avec un forma Uno. 
 * Le but est d'utiliser les outil et capteur du robot et de la carte (IMU, BLE, Line Sensors et Neurons) pour 
 * fournie a une utilisateur distant un service bluetooth avec divers fonctionnaliter.
 * 
 * Le but est d'automatiser au maximum le robot qu'il puise interagire de lui meme avec l'environnement en se déplacent et en apprenant grace aux neurons.
 * 
 *
 */

 
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


/*
 * L'IMU de la carte fournie 6 valeurs : les aceleration rectiligne (accelerometre) et angulaire (giroscope)
 */
int ax, ay, az;
int gx, gy, gz;


/*
 * Pour miniimiser la taille des paquet envoyer au l'utilisateur par le bluetooth,
 * on ne prent que les accelerations sur x et y et la rotation sur z car le robot évolue pour l'instant sur une map en 2D.
 */
float axConv, ayConv;
float gzConv;

/*
 * On definie le taux de rafraichissement de l'IMU (acc et gyro) et la precision de l'accelerometre et du gyroscope
 */
int accelerometreRange = 2;
int gyroRange = 125;
float IMURate = 200;

/////////////////////////////// BLE ///////////////////////////////

BLEPeripheral blePeripheral;
BLEService ZumoService("3752c0a0-0d25-11e6-97f5-0002a5d5c51c");
BLECharacteristic analogCharacteristique("3752c0a0-0d25-11e6-97f5-0002a5d5c51c", BLERead | BLENotify, 20);
BLECharacteristic analogCharacteristique2("3752c0a0-0d25-11e6-97f5-0002a5d5c51d", BLEWrite | BLENotify, 20);


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

 // while(!Serial){};


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

   blePeripheral.setLocalName("RdWrS2");
   blePeripheral.setAdvertisedServiceUuid(ZumoService.uuid());
   blePeripheral.addAttribute(ZumoService);
   blePeripheral.addAttribute(analogCharacteristique);
   
   blePeripheral.addAttribute(analogCharacteristique2);
   
   blePeripheral.begin();


   ///////////////////////////// reconaissance mouvement ////////////////////////
   
}

/*
 * Boucle principale : Dans la boucle principale, on attend qu'un utilisateur se conncete puis on boucle sur une suite d'instruction tant qu'il est connecte : 
 * On lie les commande sur une des carateristiques du service puis en envoie les informations (demandees et les mise à jours) a l'utilisateur.
 */
void loop() {


  BLECentral central = blePeripheral.central();
  
  if(central){

    Serial.println(central.address());
    
    
    while(central.connected()){ // Si un utilisateur se connecte
            
      //////////////////////////// Communication Bluetooth ////////////////////////////

      // On recupere la commande de l'utilisateur et on  execute l'action demander
      recevoirDonneesBluetooth();

      // On envoie les donnees recueillies par le robot
      envoieDonneesIMU();
    
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
  if(analogCharacteristique2.written()) { 
    
    Serial.println("written");

    const unsigned char * val = analogCharacteristique2.value();

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


 /* 
  *  On execute la commande demander par l'utilisateur si la commande ce renouvelle automatiquement ou si l'utilisateur a entre une nouvelle commande. 
  *  Sinon, on execute la commande par default : m5 → robot immobile.
  */

  
 //////////////////////////// Action Robot ////////////////////////////

  // Permet de modifier les mouvement du robot grace a des actions pres implementees dans la carte
  if (commande[0] == 'm') {
    actionRobot.action(commande);
  }

  //////////////////////////// calibration LineSensors ////////////////////////////

  /*
   * On effectue la calibration du senseur a l'avant du robot qui permet du suivre une ligne
   */
  else if (commande[0] == 'c' && commande[1] == 's') {
    actionRobot.calibrationSensors();
    commandeInit();

  }

  //////////////////////////// Suivre Ligne ////////////////////////////

  /*
   * On demande au robot de suivre une ligne 
   */
  else if (commande[0] == 's' && commande[1] == 'l') {
    actionRobot.suivreUneLigne();

  }

  //////////////////////////// Apprentissage Actions ////////////////////////////

  /*
   * On demande au robot d'apprendre
   */
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

}

/*
 * Permet de reconnaitre des actions simples apprisent precedemment et les enregistrer dans une liste afin de pouvoir les reproduire.
 */
void reconnaitreEtEnregistrerAction(){

  // Lors du de debut de la reconnaissance, on demarre le timer pour enregistrer le temps de chaque action reconnue
  if(neuronsReconnue == neuronsReconnuePres){
    tempsDebut = millis();
  }

  Serial.println("enregistrerAction");
  Serial.println("");

  // On demande aux neurons de reconnaitre l'action actuelle grace a l'IMU
  apprentissageRobot.reconnaitre(&neuronsReconnue);
  
  Serial.print("neuronsReconnuePres = ");Serial.println(neuronsReconnuePres);
  Serial.print("neuronsReconnue = ");Serial.println(neuronsReconnue);

  // Si une action differente de la precedente est reconnue et ... TODO 
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
 * Permet de faire reproduire les actions au robot apres une phase d'apprentisage. Cette partie est bloquant pour l'instant ( avec des delay).
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

/*
 * Permet de recupere les accelarations, la rotation et de les envoyer dans un paquet a l'utilisateur.
 */
void envoieDonneesIMU(){

  getInfoIMU();
  
  String res;

  // On utilise une serialisation tres simple avec des ',' entre chaque donnee.
  res = res + String(axConv,1) + ",";
  res = res + String(ayConv,1) + ",";
  res = res + String(gzConv,2) + ",";
  
  // On rajoute en plus un boolean qui indique si le roobot est immobile ou pas afin de corriger les erreur lors du calcule de la vitesse et de la position du robot.
  bool immobile = actionRobot.estImmobile();
  res = res + String(immobile) + ",";;

  // On ajoute l'acttion reconnue par les neurons TODO changer ca.
  res = res + String(neuronsReconnue);

  // On envoie les informations par le service
  envoieDonneesBluetooth(res);

}

/*
 * Permet d'envoyer un paquet de 20 octets au client du service Bluetooth (20 octet est la limite qui est impose par le BLE)
 */
void envoieDonneesBluetooth(String res){

  //Serial.print("commande a = "); Serial.println(commande);

  char donneesEnvoyer[20];
  String resPaquet = res.substring(0, 19);
  res.remove(0, 19);
  resPaquet.toCharArray(donneesEnvoyer, 20);
  
  analogCharacteristique.setValue((unsigned char*)donneesEnvoyer, 20);
  
  //Serial.print("commande b = "); Serial.println(commande);

}

/*
 * Permet de recuperer le imformation de L'IMU et de convertir l'acceleration en m/s/s et l'acceleration angulaire en °/s
 */
void getInfoIMU() {

  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

  // Conversion en m/s/s
  axConv = ((ax/32768.0)*accelerometreRange * 9.81);
  ayConv = ((ay/32768.0)*accelerometreRange * 9.81);

  // Conversion en °/s
  gzConv = (gz/32768.9)*gyroRange;

}

/*
 * Réinitialise la commande a sa valeur par defaut : m5 → robot immobile
 */
void commandeInit(){

  actionRobot.action("m5");
  
  commande[0] = 'm';
  commande[1] = '5';

}



