#include "ActionsRobotZumo.h"


ActionsRobot::ActionsRobot(){
	speed = 200;
  enAttente = true;

  calibrationAuto = 1;

	m1Speed = 0;
	m2Speed = 0;

	pariodeMoteurGauche = 1020; // µs pour une fréquence de 980Hz

}


void ActionsRobot::action(const char * commande){

	//char numCommande = commande[0];
	char numCommande = commande[1];

		////////////// changer vitesse ////////////////
	if (numCommande == '0') {

		char * chaine = (char *)commande;
		char * pch;
		char * s;

		pch = strtok (chaine, ",");
		Serial.println(pch);
	  pch = strtok (NULL, ",");
	  Serial.println(pch);
	  speed = atoi(pch);

		// while (pch != NULL){
		// 	Serial.println(pch);
		// 	s = pch;
	 //    pch = strtok (NULL, ",");
	 //  }

  	//speed = atoi(s);
  	Serial.print("speed = ");Serial.println(speed);

  }

	////////////// Avancer ////////////////
	if (numCommande == '1') {
		if(speed == 0){
			speed = 200;
		}

    ZumoMotors::setLeftSpeedCurie(speed);
    ZumoMotors::setRightSpeed(speed);

  }

	////////////// Reculer ////////////////

  if (numCommande == '2') {
		if(speed == 0){
			speed = 200;
		}

    ZumoMotors::setLeftSpeedCurie(-speed);
    ZumoMotors::setRightSpeed(-speed);
  }

  	////////////// droite ////////////////
	if (numCommande == '3') {
		if(speed == 0){
			speed = 200;
		}
		
    ZumoMotors::setLeftSpeedCurie(speed);
    ZumoMotors::setRightSpeed(-speed);

  }

	////////////// gauche ////////////////

  if (numCommande == '4') {
		if(speed == 0){
			speed = 200;
		}
		
    ZumoMotors::setLeftSpeedCurie(-speed);
    ZumoMotors::setRightSpeed(speed);
  }

  ////////////// stop ////////////////

  if (numCommande == '5') {
    ZumoMotors::setLeftSpeedCurie(0);
    ZumoMotors::setRightSpeed(0);
  }



}

void ActionsRobot::calibrationSensors(){
	reflectanceSensors.init(2);

  //button.waitForButton();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);


  delay(1000);

  if(calibrationAuto){
    int i;
    for (i = 0; i < 80; i++)
    {
      if ((i > 10 && i <= 40) || (i > 50 && i <= 80)) {
        //Serial.print("gauche i = ");Serial.println(i);
        ZumoMotors::setSpeeds(-200, 200, pariodeMoteurGauche);
      }
      else {
        //Serial.print("droite i = ");Serial.println(i);
        ZumoMotors::setSpeeds(200, -200, pariodeMoteurGauche);
        reflectanceSensors.calibrate();
        
      }
  
      delay(50);
    }
  
    ZumoMotors::setSpeeds(0, 0, pariodeMoteurGauche);
  }
  else{
    
    unsigned long startTime = millis();
    
    while(millis() - startTime < 10000)   // make the calibration take 10 seconds
    {
      reflectanceSensors.calibrate();
    }
 
  }

  digitalWrite(13, LOW);


/*
  // Wait for the user button to be pressed and released
  button.waitForButton();

  unsigned int sensors[6];

  reflectanceSensors.readCalibrated(sensors);

  Serial.print("sensors 0 = "); Serial.println(sensors[0]);
  Serial.print("sensors 1 = "); Serial.println(sensors[1]);
  Serial.print("sensors 2 = "); Serial.println(sensors[2]);
  Serial.print("sensors 3 = "); Serial.println(sensors[3]);
  Serial.print("sensors 4 = "); Serial.println(sensors[4]);
  Serial.print("sensors 5 = "); Serial.println(sensors[5]);



  button.waitForButton();

  */
}

void ActionsRobot::suivreUneLigne(){

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

  int position = (p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8)/8;

  
  unsigned int sensors[6];

  for(int i = 0; i < 6 ; i++){
    sensors[i] = (sensors1[i] + sensors2[i] + sensors3[i] + sensors4[i] + sensors5[i] + sensors6[i] + sensors7[i] + sensors8[i])/8;
  }

  Serial.print("sensors 0 = "); Serial.println(sensors[0]);
  Serial.print("sensors 1 = "); Serial.println(sensors[1]);
  Serial.print("sensors 2 = "); Serial.println(sensors[2]);
  Serial.print("sensors 3 = "); Serial.println(sensors[3]);
  Serial.print("sensors 4 = "); Serial.println(sensors[4]);
  Serial.print("sensors 5 = "); Serial.println(sensors[5]);

  Serial.print("position = "); Serial.println(position);

  Serial.println("");
  /////////////////////////// On suis la ligne //////////////////////////

  suivreLigneV2(position);
  
  /////////////////////////// Croisement //////////////////////////
  detecterCroisement(sensors);
  
  //detecterLigneV2(sensors);

  

}


void ActionsRobot::suivreLigneV2(int position) {

  Serial.print("position = "); Serial.println(position);

  int error = position - 2500;

  float C = 1;

  // on norme l'erreur avec la vitesse maximum
  int erreurNorm = (((float)error) / 2500.0) * ((float)MAX_SPEED) * C;


  Serial.print("error = "); Serial.println(error);
  Serial.print("erreurNorm = "); Serial.println(erreurNorm);


  //Si l'erreur est plus grande que 1000 (donc avec un "capteur de decalage")
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
  ZumoMotors::setSpeeds(m1Speed, m2Speed, pariodeMoteurGauche);

  

}


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

void ActionsRobot::detecterCroisement(unsigned int * sensors) {

  digitalWrite(13, LOW);

  if((sensors[0] > 950 || sensors[1] > 950) && (sensors[4] > 950 || sensors[5] > 950)){
    digitalWrite(13, HIGH);
    ZumoMotors::setSpeeds(0, 0, pariodeMoteurGauche);
    //suivreLigne = true;
    //button.waitForButton();

  }


}