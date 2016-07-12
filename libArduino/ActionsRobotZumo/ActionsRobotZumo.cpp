#include "ActionsRobotZumo.h"


ActionsRobot::ActionsRobot(){
	speed = 200;
  enAttente = true;

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
		while (pch != NULL){
			Serial.println(pch);
			s = pch;
	    pch = strtok (NULL, ",");
	  }

  	speed = atoi(s);
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