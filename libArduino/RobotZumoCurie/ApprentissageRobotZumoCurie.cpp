/*
 * ApprentissageRobotZumoCurie.cpp
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 29-07-1016 (Quentin)
 *
 *
 * Cette classe permet d'utiliser le reseau de neurons integrer dans la carte Intel Curie afin d'apprendre
 * des mouvement (actions) avec l'IMU et de sauvegrader les mouvements effectue pour pouvoir les reproduires
 */


#include "ApprentissageRobotZumoCurie.h"


ApprentissageRobot::ApprentissageRobot(){
    init();

}

void ApprentissageRobot::init(){
    hNN.Init();
    hNN.Forget(500);
    nbAction = 0;
}


void ApprentissageRobot::apprendreAvecIMU(int numNeurons){
  Serial.println("apprendreAvecIMU");

  Serial.print("numNeurons = ");Serial.println(numNeurons);
  for (int i = 0 ; i < 5 ; i++){
    //getVectorIMU();
    getVectorIMUSimple();
 
    ncount = hNN.Learn(vector, sampleNbr*signalNbr, numNeurons);
  }
  
}

/*
Permet de reconnaitre un mouvement de la carte en comparent les donnees de l'IMU avec donnees dans le reseau neuronnale.
*/
void ApprentissageRobot::reconnaitre(int * c, int * d){

  Serial.println("reconnaitre");

  // On utilise la version simplifier pour recuperer les donnees de l'IMU.
  getVectorIMUSimple();
    
  // On compare les donnees avec ce qui est contenue dans le reseau de neurons pour trouver une correspondance
  hNN.Classify(vector, sampleNbr*signalNbr,&dist, &cat, &nid);
  
  Serial.println("");

  Serial.print("cat = ");Serial.println(cat);
  Serial.print("dist = ");Serial.println(dist);
  Serial.print("nid = ");Serial.println(nid);

  // Si on a une correspondance
  if (cat!=0x7FFF){
    *c = cat;
    *d = dist;
  }
  // Sinon
  else{
    *c = 0;
    *d = dist;

  }
    
  



}

/*
Permet de reconnaitre un mouvement de la carte en comparent les donnees moyenne de l'IMU avec donnees dans le reseau neuronnale.
On prent 30 échantillons et on trouve celui avec le plus d'occurence. Ici, la distance en sortie est toujours egale a 0 (moyenne).
*/
void ApprentissageRobot::reconnaitreMoyenne(int * c, int * d){
  Serial.println("reconnaitreMoyenne");

  int tab[128] = { 0 };

  for (int i = 0; i < 30; i++){
    getVectorIMUSimple();
    hNN.Classify(vector, sampleNbr*signalNbr,&dist, &cat, &nid);

    if (cat!=0x7FFF){
      //if(dist < sampleNbr*signalNbr){
        tab[cat] += 1;
      //}
    }


  }

  int catMax = 0;

  for (int i = 0; i < 128; i++){
    if(tab[catMax] < tab[i]){
      catMax = i;
    }
  }

  *c = catMax;

}

/*
Permet de recuperer un vecteur de valeurs qui contient sampleNbr echantillons des signalNbr donnees de l'IMU.
*/
void ApprentissageRobot::getVectorIMU(){

  mina=0xFFFF, maxa=0, ming=0xFFFF, maxg=0;
  
  for (int sampleId=0; sampleId<sampleNbr; sampleId++){
    
    CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);
    
    Serial.print("ax = ");Serial.println(ax);
    Serial.print("ay = ");Serial.println(ay);
    Serial.print("az = ");Serial.println(az);
    Serial.print("gx = ");Serial.println(gx);
    Serial.print("gy = ");Serial.println(gy);
    Serial.print("gz = ");Serial.println(gz);


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

// Transforme les acceleration rectiligne decimale en binaire (1 et 10).
void transDonneeA(int v, int * V){
      if(v > seuilAcce && v >= 0){
      *V = 10;
    }
    else if(v < -seuilAcce && v < 0){
      *V = 1;
    }
    else{
      *V = 0;
    }
}

// Transforme les acceleration angulaire decimale en binaire (1 et 10).
void transDonneeG(int v, int * V){
      if(v > seuilGyro && v >= 0){
      *V = 10;
    }
    else if(v < -seuilGyro && v < 0){
      *V = 1;
    }
    else{
      *V = 0;
    }
}

/*
Permet de recuperer un vecteur de valeur simplifier qui contient sampleNbr echantillons des signalNbr donnees de l'IMU.
Les valeur sont simplifier avec pour chaque donnée une valeur law et high (1 et 10). On choisie une difference de 10 
pour augmenter les chance de retrouve le bon neurons.
On transforme une valeur decimale en binaire avec un seuil arbitraire choisie selon la sensibiliter que l'on souaite 
pour la reconnaissance.
*/
void ApprentissageRobot::getVectorIMUSimple(){

  int AX, AY, AZ, GX, GY, GZ;
 
  for (int sampleId=0; sampleId<sampleNbr; sampleId++){
    
    CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

    transDonneeA(ax, &AX);
    transDonneeA(ay, &AY);
    transDonneeA(az, &AZ);

    transDonneeA(gx, &GX);
    transDonneeA(gy, &GY);
    transDonneeA(gz, &GZ);

    // Serial.println("");
    // Serial.println("");
    // Serial.print("AX = ");Serial.println(AX);
    // Serial.print("AY = ");Serial.println(AY);
    // Serial.print("AZ = ");Serial.println(AZ);
    // Serial.print("GX = ");Serial.println(GX);
    // Serial.print("GY = ");Serial.println(AX);
    // Serial.print("GZ = ");Serial.println(GZ);

    if(GZ == 10){
      digitalWrite(13,HIGH);
      
    }
    else{
      digitalWrite(13,LOW);
    }



    // accumulate the sensor data
    vector[sampleId*signalNbr]= AX & 0x00FF;
    vector[(sampleId*signalNbr)+1]= AY & 0x00FF;
    vector[(sampleId*signalNbr)+2]= AZ & 0x00FF;
    vector[(sampleId*signalNbr)+3]= GX & 0x00FF;
    vector[(sampleId*signalNbr)+4]= GY & 0x00FF;
    vector[(sampleId*signalNbr)+5]= GZ & 0x00FF;
  }
  
}








//////////////////////////////////// Enregistrement des actions /////////////////////////////////////////


/*
Return le nombre d'action qu'ont ete enregistre.
*/
int ApprentissageRobot::getNbActionReconnue(){
  return nbAction;
}

/*
On recupere la liste des actions reconnue pendant l'enregistrement.
*/
int ApprentissageRobot::getActionReconnue(int num){
  Serial.println("getActionReconnue");
  Serial.print("listeAction[num][0] = ");Serial.println(listeAction[num][0]);

  return listeAction[num][0];
}

/*
On recupere la liste des temps de chaque actions reconnue pendant l'enregistrement.
*/
int ApprentissageRobot::getTempsActionReconnue(int num){
  return listeAction[num][1];
}

/*
On "vide" la liste des actions.
*/
void ApprentissageRobot::viderListeActionReconnue(){
  nbAction = 0;
}

/*
On ajoute une action avec son numero et son temps
*/
void ApprentissageRobot::addActionReconnue(int num, int temps){
  Serial.println("addActionReconnue");
  Serial.print("nbAction = ");Serial.println(nbAction);


  nbAction++;
  listeAction[nbAction][0] = num;
  listeAction[nbAction][1] = temps;

  Serial.print("num = ");Serial.println(num);
  Serial.print("listeAction[nbAction][0] = ");Serial.println(listeAction[nbAction][0]);


}

/*
Return true si la liste est plein
*/
bool ApprentissageRobot::listeActionPleine(){
  return (nbAction == nbMaxAction);
}

/*
Return true si la liste est vide
*/
bool ApprentissageRobot::listeActionVide(){
  return (nbAction == 0);
}