/*
 * ActionsRobotZumo.cpp
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 25-07-1016 (Quentin)
 *
 * Cette classe permet de diriger le robot et d'utiliser son capteur de ligne
 */

#include "ActionsRobotZumo.h"


// Constructeur
ActionsRobot::ActionsRobot(){
	speed = 200; // vitesse par default

  immobile = true; // Le robot est immobile par default

  calibrationAuto = 1; // On calibre automatiquement les senseur (capteur de ligne)

  // Vitesse des moteurs
	m1Speed = 0;
	m2Speed = 0;

  // Periode du signal PWM pour le moteur gauche
  // pariodeMoteurGauche = 1020; // µs pour une fréquence de 980Hz
	pariodeMoteurGauche = 2041; // µs pour une fréquence de 490Hz

}

/*
Permet de modifier l'etat des moteur avec une action pres definie qui a un numero
*/
void ActionsRobot::action(char * commande){
    Serial.println("action");

	//char numCommande = commande[0];
	char numCommande = commande[1];

  Serial.print("commande = ");Serial.println(commande);

  Serial.print("numCommande = ");Serial.println(numCommande);

		////////////// changer vitesse ////////////////

	if (numCommande == '0') {

		char * chaine = (char *)commande;
		char * pch;

		pch = strtok (chaine, ",");
		Serial.println(pch);
	  pch = strtok (NULL, ",");
	  Serial.println(pch);
	  speed = atoi(pch);

  	Serial.print("speed = ");Serial.println(speed);

  }

	////////////// Avancer ////////////////
	if (numCommande == '1') {
		if(speed == 0){
			speed = 200;
		}

    vitesseMoteurs(speed, speed);


  }

	////////////// Reculer ////////////////

  if (numCommande == '2') {
		if(speed == 0){
			speed = 200;
		}

    vitesseMoteurs(-speed, -speed);

  }

  	////////////// droite ////////////////
	if (numCommande == '3') {
		if(speed == 0){
			speed = 200;
		}

    vitesseMoteurs(speed, -speed);

  }

	////////////// gauche ////////////////

  if (numCommande == '4') {
		if(speed == 0){
			speed = 200;
		}
		
    vitesseMoteurs(-speed, speed);

  }

  ////////////// stop ////////////////

  if (numCommande == '5') {
		vitesseMoteurs(0, 0);

  }



}

/*
Permet de calibrer le senseur de ligne, soit automatiquement (par dedfaut) soit manuellement.
*/
void ActionsRobot::calibrationSensors(){
	reflectanceSensors.init(2);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);


  delay(1000);

  if(calibrationAuto){
    int i;
    for (i = 0; i < 80; i++)
    {
      if ((i > 10 && i <= 40) || (i > 50 && i <= 80)) {
        vitesseMoteurs(-200, 200);

      }
      else {
        vitesseMoteurs(200, -200);

        reflectanceSensors.calibrate();
        
      }
  
      delay(50);
    }
  
    vitesseMoteurs(0, 0);

  }
  else{
    
    unsigned long startTime = millis();
    
    while(millis() - startTime < 10000)   // make the calibration take 10 seconds
    {
      reflectanceSensors.calibrate();
    }
 
  }

  digitalWrite(13, LOW);

}

/*
Permet de demander au robot de suivre une ligne sur une cercuit (il faut faire la calibration avant)
*/
void ActionsRobot::suivreUneLigne(){


  /*
    On capture 8 fois les donnees du senseur puis on fait la moyenne pour reduire les erreurs de mesure
  */

	unsigned int sensors1[6];
  unsigned int sensors2[6];
  unsigned int sensors3[6];
  unsigned int sensors4[6];
  unsigned int sensors5[6];
  unsigned int sensors6[6];
  unsigned int sensors7[6];
  unsigned int sensors8[6];
  
  int p1 = reflectanceSensors.readLine(sensors1);
  int p2 = reflectanceSensors.readLine(sensors2);
  int p3 = reflectanceSensors.readLine(sensors3);
  int p4 = reflectanceSensors.readLine(sensors4);
  int p5 = reflectanceSensors.readLine(sensors5);
  int p6 = reflectanceSensors.readLine(sensors6);
  int p7 = reflectanceSensors.readLine(sensors7);
  int p8 = reflectanceSensors.readLine(sensors8);

  // Moyenne de 8 position (pour conpenser les erreurs sur la mesure du capteur de ligne)
  int position = (p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8)/8;

  // Moyenne des valeurs des capteurs
  unsigned int sensors[6];

  for(int i = 0; i < 6 ; i++){
    sensors[i] = (sensors1[i] + sensors2[i] + sensors3[i] + sensors4[i] + sensors5[i] + sensors6[i] + sensors7[i] + sensors8[i])/8;
  }


  // Serial.print("sensors 0 = "); Serial.println(sensors[0]);
  // Serial.print("sensors 1 = "); Serial.println(sensors[1]);
  // Serial.print("sensors 2 = "); Serial.println(sensors[2]);
  // Serial.print("sensors 3 = "); Serial.println(sensors[3]);
  // Serial.print("sensors 4 = "); Serial.println(sensors[4]);
  // Serial.print("sensors 5 = "); Serial.println(sensors[5]);

  // Serial.print("position = "); Serial.println(position);

  // Serial.println("");

  /////////////////////////// On suis la ligne //////////////////////////
  suivreLigneV2(position);
  
  /////////////////////////// Croisement //////////////////////////
  detecterCroisement(sensors);
  
  //detecterLigneV2(sensors);

  

}

/*
Permet de demander au robot de suivre une ligne sur une cercuit (il faut faire la calibration avant).
Version 2 plus stable
*/
void ActionsRobot::suivreLigneV2(int position) {

  // On prent une erreur par rapport au centre du robot (centre du capteur de ligne)
  int error = position - 2500;

  // Constante pour tester la sensibiliter de la correction
  float C = 1;

  // on norme l'erreur avec la vitesse maximum
  int erreurNorm = (((float)error) / 2500.0) * ((float)MAX_SPEED) * C;

  //Si l'erreur est plus grande que 500 (donc avec un "demi-capteur de decalage" par rapport au centre du robot)
  if((error > 500) || (error < -500)){


    int DIFF = 2;

    // Si le robot est trop a gauche
    if(erreurNorm > 0){
      m1Speed = (MAX_SPEED + erreurNorm);
      m2Speed = (MAX_SPEED - erreurNorm)/DIFF;
    }
    // Si le robot est trop a droite
    else if(erreurNorm < 0){
      m1Speed = (MAX_SPEED + erreurNorm)/DIFF;
      m2Speed = (MAX_SPEED - erreurNorm);
    }


    // On borne les vitesse entre 0 et MAX_SPEED
    if (m1Speed < 0)
      m1Speed = 0;
    if (m2Speed < 0)
      m2Speed = 0;
    if (m1Speed > MAX_SPEED)
      m1Speed = MAX_SPEED;
    if (m2Speed > MAX_SPEED)
      m2Speed = MAX_SPEED;
  

  }
  else{
    m1Speed = MAX_SPEED;
    m2Speed = MAX_SPEED;
    
  }

  // On modifie les vitesses des moteurs du robot 
  vitesseMoteurs(m1Speed, m2Speed);

}

/*
Permet de modifier la vitesse des moteurs du robot.
*/
void ActionsRobot::vitesseMoteurs(int vitesseGauche, int vitesseDroite) {


	Serial.println("en mouvement");

	if(vitesseGauche == 0 && vitesseDroite == 0){
		immobile = true;
	}
	else{
		Serial.println("en mouvement");
		immobile = false;
	}

  ZumoMotors::setSpeeds(vitesseGauche, vitesseDroite, pariodeMoteurGauche);

}


/*
!!!! Ne fonctionne pas encore !!!!
Permet de detecter une ligne qui se trouve en face du robot
*/
void ActionsRobot::detecterLigneV2(unsigned int * sensors) {

  digitalWrite(13, LOW);

  int somme = 0;
  int sommeDroite = 0;
  int sommeGauche = 0;

  for(int i = 0; i < 6 ; i++){
    somme += sensors[i];

    if(i < 3){
      sommeGauche += sensors[i];
      
    }
    else{
      sommeDroite += sensors[i];
    }
  }


  if(sommeDroite > 1500 || sommeGauche > 1500){
    Serial.println("sur la ligne");
    digitalWrite(13, HIGH);

    if(sommeDroite > sommeGauche){
      Serial.println("Droite");
    }
    else{
      Serial.println("Gauche");
    }
    
  }


}

/*
!!!! Ne fonctionne pas encore !!!!
Permet de un croissement et de le signale avec une LED
*/
void ActionsRobot::detecterCroisement(unsigned int * sensors) {

  digitalWrite(13, LOW);

  if((sensors[0] > 950 || sensors[1] > 950) && (sensors[4] > 950 || sensors[5] > 950)){
    digitalWrite(13, HIGH);
    //ZumoMotors::setSpeeds(0, 0, pariodeMoteurGauche);
    vitesseMoteurs(0, 0);

    //suivreLigne = true;
    //button.waitForButton();

  }


}

/*
Return true si le robot est immobile : vitesse nulle pour les deux moteurs.
*/
bool ActionsRobot::estImmobile(){
	return immobile;
}