/*
 * CurieArduino.ino
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *                      Clement Sibut []

 * Dernier mise a jour: 29-08-1016 (Quentin)
 *
 * lib utiliser : RobotZumoCurie
 * 
 * Ce programme permet a une carte Intel Curie 101 de commander un robot zumo avec un forma Uno. 
 * Le but est d'utiliser les outil et capteur du robot et de la carte (IMU, BLE, Line Sensors et Neurons) pour 
 * fournie a une utilisateur distant un service bluetooth avec divers fonctionnaliter.
 * 
 * Le but est d'automatiser au maximum le robot pour qu'il puise interagire de lui meme avec l'environnement en se déplacent et en apprenant grace aux neurons.
 * 
 *
 */

//Robot Zumo 
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>

//Carte Curie
#include <CurieIMU.h>
#include <CurieBLE.h>

//Nos libraries 
#include <ActionsRobotZumo.h>
#include <ApprentissageRobotZumoCurie.h>

//C++
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

/*
 * On definie les variables pour utiliser le BLE avec un service et deux charactéristique
 */
BLEPeripheral blePeripheral;
BLEService ZumoService("3752c0a0-0d25-11e6-97f5-0002a5d5c51c");
BLECharacteristic characteristiqueEnvoieDonnees("3752c0a0-0d25-11e6-97f5-0002a5d5c51c", BLERead | BLENotify, 20);
BLECharacteristic characteristiqueRecevoirDonnees("3752c0a0-0d25-11e6-97f5-0002a5d5c51d", BLEWrite | BLENotify, 20);


/////////////////////////////// Neurons ///////////////////////////////

int neuronsReconnuePres = 0;
int neuronsReconnue = 0;
int distanceReco = 0;
int tempsReco = -1;

int nbReco = 0; // nombre de reconnaissance sur 30 echantillons (voir reconnaitreMoyenne)

/////////////////////////////// Robot ///////////////////////////////


/*
 * Objet qui permet d'intéragire avec le robot
 */
ActionsRobot actionRobot;

/*
 * Objet qui permet d'utiliser le reseau beuronals  
 */
ApprentissageRobot apprentissageRobot;

char commande[20];
int paras[10];


/////////////////////////////// Enregistrement ///////////////////////////////

int tempsDebut = 0;
int tempsFin = 0;

/////////////////////////////// Robot mode ///////////////////////////////

bool apprentissage = false;
int numNeurons = 0;

bool reconnaissance = false;

bool reconnaissanceAvecTemps = false;

bool enregistrement = false;

/*
 * Parametrege de la carte et du robot
 */
void setup() {
  
  Serial.begin(9600);
  
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
   blePeripheral.setAdvertisedServiceUuid(ZumoService.uuid());
   blePeripheral.addAttribute(ZumoService);
   blePeripheral.addAttribute(characteristiqueEnvoieDonnees);
   blePeripheral.addAttribute(characteristiqueRecevoirDonnees);
   
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

    while(central.connected()){ // Si un utilisateur se connecte
            
      //////////////////////////// Communication Bluetooth ////////////////////////////

      Serial.println("Loop");
            
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
  
  Serial.println("");


  lireCommande();

  traiterCommande();
 

}


bool recoCommande(char l1, bool test1, char l2, bool test2){
  if(test1 && test2){
    return (commande[0] == l1 && commande[1] == l2);
  }
  else if(test1 && !test2){
    return (commande[0] == l1 && commande[1] != l2);
  }
  else if(!test1 && test2){
    return (commande[0] != l1 && commande[1] == l2);
  }
  else if(!test1 && !test2){
    return (commande[0] != l1 && commande[1] != l2);
  }

  return false;
}

/*
 * Permet de reseptionner les commande envoyer par l'utilisateur
 */
void lireCommande(){

  // Si l'utilisateur en entrer une nouvelle commande 
  if(characteristiqueRecevoirDonnees.written()) { 
    
    // On initialise la commande et d'autre variable utiliser dans la boucle
    commandeInit();

    const unsigned char * val = characteristiqueRecevoirDonnees.value();
   
    for(int i = 0 ; i < 20 ; i++){
      commande[i] = ((char *)val)[i];
    }

    if(commande[0] == '('){
      char * comm;
  
      comm = strtok(commande, "()");

      int tailleComm = strlen(comm);

      for(int i = 0 ; i < tailleComm ; i++){
        commande[i] = comm[i];
      }
      
      commande[tailleComm] = ' ';
    }

  }

  Serial.print("commande = ");Serial.println(commande);

}



/*
 * Permet de traiter les commande envoyer par l'utilisateur
 */
void traiterCommande(){

  Serial.println("traiterCommande");

  //////////////////////////// Action Robot ////////////////////////////

  // Permet de modifier les mouvement du robot grace a des actions pres implementees dans la carte
  if (commande[0] == 'm') {
    actionRobot.action(commande);
    commandeClean();
  }

  //////////////////////////// calibration LineSensors ////////////////////////////

  /*
   * On effectue la calibration du senseur a l'avant du robot qui permet du suivre une ligne
   */
  if (recoCommande('c', true, 's', true)) {
    actionRobot.calibrationSensors();
    commandeInit();

  }

  //////////////////////////// Suivre Ligne ////////////////////////////

  /*
   * On demande au robot de suivre une ligne 
   */
  if (recoCommande('s', true, 'l', true)) {
    actionRobot.suivreUneLigne();
  }

  //////////////////////////// Apprentissage Actions ////////////////////////////

  /*
   * On demande au robot d'apprendre les donnes actuelle du L'IMU et des les enregistrer sur un emplacement du reseau de neurons. 
   * Le but est de repeter plusieur fois l'appelle de cette methode pour memorise toute les varations d'une meme actions, d'un meme mouvement.
   */
  if (recoCommande('a', true, 'p', false)) {
    numNeurons = (int)commande[1] - '0';
    apprentissageRobot.apprendreAvecIMU(numNeurons); // On fait "- '0'" pour passer du tableau ASCII a un int
  }


  //////////////////////////// Apprentissage ponctuelle Actions ////////////////////////////

  /*
   * On demande au robot d'apprendre les donnes actuelle du L'IMU et des les enregistrer sur un emplacement du reseau de neurons. 
   */
  if (recoCommande('a', true, 'p', true)) {
    numNeurons = (int)commande[2] - '0';
    apprentissageRobot.apprendreAvecIMU(numNeurons); // On fait "- '0'" pour passer du tableau ASCII a un int
    commandeClean();
  }


  //////////////////////////// Reconnaissance Actions avec calcule du temps ////////////////////////////


  // On desactive la commande
  if (recoCommande('r', true, 'a', false) && reconnaissanceAvecTemps) {

    nbReco = 0;
    reconnaissanceAvecTemps  = false;
    commandeClean();
  }

  // On active la commande
  if (recoCommande('r', true, 'a', false) || reconnaissanceAvecTemps) {

    neuronsReconnue = -1;

    reconnaitreAvecTemps();

    reconnaissanceAvecTemps = true;

    if(commande[0] == 'r' && commande[1] != 'a'){
      commandeClean();
    }
  }

  

  //////////////////////////// Reconnaissance Actions avec enregistrement////////////////////////////

  // On desactive la commande
  if (recoCommande('e', true, 'a', true) && enregistrement) {
    enregistrement  = false;
    commandeClean();
  }

  // On active la commande
  if (recoCommande('e', true, 'a', true)  || enregistrement) {
    
    reconnaitreEtEnregistrerAction();
    envoieNeuronsReconnue();

    enregistrement = true;

    if(commande[0] == 'e' && commande[1] == 'a'){
      commandeClean();
    }
  }


  //////////////////////////// Reexecuter Actions ////////////////////////////

  // Ici, le robot ne transmet plus de donner et refait les actions appris avec la reconnaisance 
  if (recoCommande('r', true, 'a', true)) { 
    reproduireActions();

  }

   //////////////////////////// vider liste Action enregistrees ////////////////////////////

  if (recoCommande('v', true, 'l', true)) { 
    apprentissageRobot.viderListeActionReconnue();
  }


    //////////////////////////// Sauvegarder Neurons ////////////////////////////


  /*
   * 
   */
  if (recoCommande('g', true, 'n', true)) {
    apprentissageRobot.getValeursNeuronParId((int)commande[2]);
    commandeClean();
  }
  
  /*
   * 
   */
  if (recoCommande('s', true, 'n', true)) {
    apprentissageRobot.getValeursNeurons();
    commandeClean();
  }

  /*
   * 
   */
  if (recoCommande('i', true, 'n', true)) {
    apprentissageRobot.setValeursNeurons();
    commandeClean();
  }

}


/*
 * Permet de reconnaitre des actions simples apprisent precedemment avec le temps.
 */
void reconnaitreAvecTemps(){

  // Lors du de debut de la reconnaissance, on demarre le timer pour enregistrer le temps de chaque action reconnue
  if(!reconnaissanceAvecTemps){
    Serial.println("debut");
    tempsDebut = millis();
  }

  apprentissageRobot.reconnaitreMoyenne(&neuronsReconnue, &distanceReco, &nbReco);
  
  if(neuronsReconnuePres != neuronsReconnue && neuronsReconnuePres != 0){
    
    tempsFin = millis();
    int deffTemps = tempsFin - tempsDebut;
    tempsDebut = millis();

    Serial.print("deffTemps = ");Serial.println(deffTemps);

    Serial.println("envoie paquet ");

    tempsReco = deffTemps;

    // On envoie la reconnaissance seulement lorsqu'on a fini de reconnaitre le neurone courant (nouveau neurone identifie)
    envoieNeuronsReconnue();
  }

  // On envoie la reconnaissance a chaque tour de boucle
  //envoieNeuronsReconnue();
  
  neuronsReconnuePres = neuronsReconnue;

}

/*
 * Permet de reconnaitre des actions simples apprisent precedemment et les enregistrer dans une liste afin de pouvoir les reproduire.
 */
void reconnaitreEtEnregistrerAction(){

  // Lors du de debut de la reconnaissance, on demarre le timer pour enregistrer le temps de chaque action reconnue
  if(!enregistrement){
    tempsDebut = millis();
  }

  // On demande aux neurons de reconnaitre l'action actuelle grace a l'IMU
  apprentissageRobot.reconnaitreMoyenne(&neuronsReconnue, &distanceReco, &nbReco);
  

  // Si une action differente de la precedente est reconnue et ... TODO 
  if(neuronsReconnuePres != neuronsReconnue && neuronsReconnuePres != 0){

    tempsFin = millis();

    if(apprentissageRobot.listeActionPleine()){
      commandeInit();        
    }
    else{
      int deffTemps = tempsFin - tempsDebut;
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

  for(int i = 1 ; i <= nbAction ; i++){
    
    int numAction = apprentissageRobot.getActionReconnue(i);
    int temps = apprentissageRobot.getTempsActionReconnue(i);

    char numActionChar[2];
    numActionChar[0] = 'm';
    numActionChar[1] = '0' + numAction;

    actionRobot.action(numActionChar);
    
    delay(apprentissageRobot.getTempsActionReconnue(i));

  }
  commandeInit();

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
  res = res + String(immobile);

  // On envoie les informations par le service
  envoieDonneesBluetooth(res);

}

/*
 * Permet d'envoyer le numero de l'emplacement reconnue par le reseau de neurons.
 */
void envoieNeuronsReconnue(){
  String res;

  res = "r," + String(neuronsReconnue) + "," + String(tempsReco); // + "," + String(nbReco);

  // On envoie les informations par le service
  envoieDonneesBluetooth(res);

}

/*
 * Permet d'envoyer un paquet de 20 octets au client du service Bluetooth (20 octet est la limite qui est impose par le BLE)
 */
void envoieDonneesBluetooth(String res){


  char donneesEnvoyer[20];
  String resPaquet = res.substring(0, 19);
  res.remove(0, 19);
  resPaquet.toCharArray(donneesEnvoyer, 20);
  
  characteristiqueEnvoieDonnees.setValue((unsigned char*)donneesEnvoyer, 20);
  

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
  
  commande[0] = 'm';
  commande[1] = '5';
  
}

/*
 * Initialise la commande avec une valeur nulle
 */
void commandeClean(){
  
  commande[0] = 'n';
  commande[1] = 'n';
  
}


