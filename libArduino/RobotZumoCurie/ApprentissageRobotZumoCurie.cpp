/*
 * ApprentissageRobotZumoCurie.cpp
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 29-08-1016 (Quentin)
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
  //hNN.Forget(5);
  nbAction = 0;
}


void ApprentissageRobot::apprendreAvecIMU(int numNeurons){
  Serial.println("apprendreAvecIMU");

  Serial.print("numNeurons = ");Serial.println(numNeurons);
  for (int i = 0 ; i < 5 ; i++){
    getVectorIMUSimple();
 		//getVectorIMU();
    ncount = hNN.Learn(vector, nbEchantillons*nbVals, numNeurons);
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
  hNN.Classify(vector, nbEchantillons*nbVals,&dist, &cat, &nid);
  
  Serial.println("");

  Serial.print("cat = ");Serial.println(cat);
  Serial.print("dist = ");Serial.println(dist);
  Serial.print("nid = ");Serial.println(nid);

  // Si on a une correspondance
  if (cat!=0x7FFF){
    *c = cat;
  }
  // Sinon
  else{
    *c = 0;
  }

  *d = dist;

}

/*
Permet de reconnaitre un mouvement de la carte en comparant les donnees de l'IMU avec donnees dans le reseau neuronal.
On prent 30 échantillons et on trouve celui avec le plus d'occurence. Ici, la distance en sortie est toujours egale a 0.
*/
void ApprentissageRobot::reconnaitreMoyenne(int * c, int * d, int * nb){
  int tab[128] = { 0 };

  for (int i = 0; i < 30; i++){
    getVectorIMUSimple();
    //getVectorIMU();
    hNN.Classify(vector, nbEchantillons*nbVals,&dist, &cat, &nid);

    if (cat!=0x7FFF){
        tab[cat] += 1;
    }
    else{
      tab[0] += 1;
    }
  }

  // On renvoie la classe (la categorie) qui a le plus de resultat positif
  int catMax = 0;
  int nbMax = 0;
  int catMax2 = 0;
  int nbMax2 = 0;

  for (int i = 0; i < 128; i++){
    if(tab[catMax] < tab[i]){
    	catMax2 = catMax;
      catMax = i;
      nbMax2 = nbMax;
      nbMax = tab[i];

    }
  }

  // // Version ou on exclue le 0
  // int catMax = 1;
  // int nbMax = 0;
  // for (int i = 1; i < 128; i++){
  //   if(tab[catMax] < tab[i]){
  //     catMax = i;
  //     nbMax = tab[i];

  //   }
  // }

  Serial.print("Nombre max de reconaissance pour i = ");Serial.print(catMax);Serial.print(" est :");Serial.print(nbMax);Serial.println("/30");
  Serial.print("Nombre max - 1 de reconaissance pour i = ");Serial.print(catMax2);Serial.print(" est :");Serial.print(nbMax2);Serial.println("/30");


  *c = catMax;
  *nb = nbMax;

}

/*
Permet de recuperer un vecteur de valeurs qui contient nbEchantillons echantillons des nbVals donnees de l'IMU.
*/
void ApprentissageRobot::getVectorIMU(){

  mina=0xFFFF, maxa=0, ming=0xFFFF, maxg=0;
  
  for (int sampleId=0; sampleId<nbEchantillons; sampleId++){
    
    CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);
    
    // Serial.print("ax = ");Serial.println(ax);
    // Serial.print("ay = ");Serial.println(ay);
    // Serial.print("az = ");Serial.println(az);
    // Serial.print("gx = ");Serial.println(gx);
    // Serial.print("gy = ");Serial.println(gy);
    // Serial.print("gz = ");Serial.println(gz);


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
    raw_vector[sampleId*nbVals]= ax;
    raw_vector[(sampleId*nbVals)+1]= ay;
    raw_vector[(sampleId*nbVals)+2]= az;
    raw_vector[(sampleId*nbVals)+3]= gx;
    raw_vector[(sampleId*nbVals)+4]= gy;
    raw_vector[(sampleId*nbVals)+5]= gz;
  }
  
  // normalize vector
  for(int sampleId=0; sampleId < nbEchantillons; sampleId++)
  {
    for(int i=0; i<3; i++)
    {
      vector[sampleId*nbVals+i]  = (((raw_vector[sampleId*nbVals+i] - mina) * 255)/da) & 0x00FF;
      vector[sampleId*nbVals+3+i]  = (((raw_vector[sampleId*nbVals+3+i] - ming) * 255)/dg) & 0x00FF;
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
Permet de recuperer un vecteur de valeurs simplifiees qui contient nbEchantillons echantillons des nbVals donnees de l'IMU.
Les valeur sont simplifier avec pour chaque donnée une valeur law et high (1 et 10). On choisie une difference de 10 
pour augmenter les chance de retrouve le bon neurons (augmenter la distance).
On transforme une valeur decimale en binaire avec un seuil arbitraire choisie selon la sensibiliter que l'on souaite 
pour la reconnaissance.
*/
void ApprentissageRobot::getVectorIMUSimple(){

  int AX, AY, AZ, GX, GY, GZ;
 
  for (int i=0; i<nbEchantillons; i++){
    
    CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

    transDonneeA(ax, &AX);
    transDonneeA(ay, &AY);
    transDonneeA(az, &AZ);

    transDonneeG(gx, &GX);
    transDonneeG(gy, &GY);
    transDonneeG(gz, &GZ);

    // Serial.println("");
    // Serial.println("");
    // Serial.print("ax = ");Serial.println(ax);
    // Serial.print("ay = ");Serial.println(ay);
    // Serial.print("az = ");Serial.println(az);
    // Serial.print("gx = ");Serial.println(gx);
    // Serial.print("gy = ");Serial.println(gy);
    // Serial.print("gz = ");Serial.println(gz);
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
    vector[i*nbVals]= AX & 0x00FF;
    vector[(i*nbVals)+1]= AY & 0x00FF;
    vector[(i*nbVals)+2]= AZ & 0x00FF;
    vector[(i*nbVals)+3]= GX & 0x00FF;
    vector[(i*nbVals)+4]= GY & 0x00FF;
    vector[(i*nbVals)+5]= GZ & 0x00FF;
  }
  
}


/*
Proto
*/
void transDonnee(int v, int * V){
    
    if(v >= 0){
      *V = 10;
    }
    else{
      *V = 1;
    }

}


/*
Proto
*/
void ApprentissageRobot::getVectorIMUSimpleV2(){

  int AX = 0, AY = 0, AZ = 0, GX = 0, GY = 0, GZ = 0;
 

  for (int i = 0; i < nbEchantillons; i++){

    for(int i = 0 ; i < 10 ; i++){
      CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);
      AX += ax;
      AY += ay;
      AZ += az;
      GX += gx;
      GY += gy;
      GZ += gz;
      
    }

    transDonnee(AX, &AX);
    transDonnee(AY, &AY);
    transDonnee(AZ, &AZ);

    transDonnee(GX, &GX);
    transDonnee(GY, &GY);
    transDonnee(GZ, &GZ);

    Serial.println("");
    Serial.println("");
    Serial.print("AX = ");Serial.println(AX);
    Serial.print("AY = ");Serial.println(AY);
    Serial.print("AZ = ");Serial.println(AZ);
    Serial.print("GX = ");Serial.println(GX);
    Serial.print("GY = ");Serial.println(AX);
    Serial.print("GZ = ");Serial.println(GZ);

    if(GZ == 10){
      digitalWrite(13,HIGH);
      
    }
    else{
      digitalWrite(13,LOW);
    }



    // accumulate the sensor data
    vector[i*nbVals]= AX & 0x00FF;
    vector[(i*nbVals)+1]= AY & 0x00FF;
    vector[(i*nbVals)+2]= AZ & 0x00FF;
    vector[(i*nbVals)+3]= GX & 0x00FF;
    vector[(i*nbVals)+4]= GY & 0x00FF;
    vector[(i*nbVals)+5]= GZ & 0x00FF;
  }
  
}



//////////////////////////////////// Enregistrement des actions /////////////////////////////////////////


/*
Retourne le nombre d'action qui ont ete enregistrees.
*/
int ApprentissageRobot::getNbActionReconnue(){
  return nbAction;
}

/*
On recupere la liste des actions reconnues pendant l'enregistrement.
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
Retourne true si la liste est plein
*/
bool ApprentissageRobot::listeActionPleine(){
  return (nbAction == nbMaxAction);
}

/*
Retourne true si la liste est vide
*/
bool ApprentissageRobot::listeActionVide(){
  return (nbAction == 0);
}



//////////////////////////////////// Sauvegarde neurons /////////////////////////////////////////


/*
Pemet de récuperer la valeur d'un des neuron avec son id
*/
void ApprentissageRobot::getValeursNeuronParId(int id){
  hNN.ReadNeuron(id, neurons);

  int i = 0;

  for(; i < 255 ; i++){
    Serial.print("n");Serial.print(i);Serial.print(" = ");Serial.println(neurons[i]);
  }


}

/*
Pemet de recuperer les valeur des neurons du reseau dans un tableau (neurons). 
Affiche le tableau si on est en mode Serial sur l'IDE Arduino.
*/
void ApprentissageRobot::getValeursNeurons(){
  int nb = hNN.ReadNeurons(neurons);

  // On affiche le nombre d'apprentissage différents affectuer sur le reseaux et qui on été enregistrer.
  Serial.print("nb = ");Serial.println(nb);

  int i = 0;

  Serial.println("Header = ");

  for(; i < 8 ; i++){
    Serial.print("n");Serial.print(i);Serial.print(" = ");Serial.println(neurons[i]);
  }

  Serial.println("Valeurs = ");

  for(int n = 0; n < nb ; n++){
    Serial.print("(");
    for(int y = i ; y < i + 136 ; y++){
      Serial.print(neurons[y]);Serial.print(",");
    }
    Serial.println(")");
    i += 136 * (n + 1);
  }

  // do{
  //   Serial.print("(");
  //   for(int y = i ; y < i + 136 ; y++){
  //     Serial.print(neurons[y]);Serial.print(", ");
  //   }
  //   Serial.println(")");
  //   i += 136;
  // }
  // while(neurons[i - 1] != 6);

  


}


void ApprentissageRobot::setValeursNeurons(){
  hNN.WriteNeurons(neurons);
}