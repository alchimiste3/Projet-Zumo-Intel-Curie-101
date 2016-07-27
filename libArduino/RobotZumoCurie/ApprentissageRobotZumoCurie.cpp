/*
 * ApprentissageRobotZumoCurie.cpp
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 25-07-1016 (Quentin)
 *
 *
 * Cette classe permet d'utiliser le reseau de neurons integrer dans la carte Intel Curie afin d'apprendre des mouvement avec l'IMU
 * et de sauvegrader les mouvements effectue pour pouvoir les  reproduire
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
  
  for (int i = 0 ; i < 5 ; i++){
    getVectorIMU(); 
    ncount = hNN.Learn(vector, sampleNbr*signalNbr, numNeurons);
  }
  
}

void ApprentissageRobot::reconnaitre(int * rep){
  getVectorIMU();
    
  hNN.Classify(vector, sampleNbr*signalNbr,&dist, &cat, &nid);
  
  Serial.println("");

  Serial.print("cat = ");Serial.println(cat);
  Serial.print("dist = ");Serial.println(dist);
  Serial.print("nid = ");Serial.println(nid);

  if (cat!=0x7FFF){
    Serial.println("salut");

    //switchCharacteristic.setValue(cat);
    digitalWrite(13,HIGH);
    *rep = cat;

    Serial.print("*rep = ");Serial.println(*rep);


  }
  else{
    //switchCharacteristic.setValue('n');
    digitalWrite(13,LOW);
    *rep = 0;

  }
    
  



}



void ApprentissageRobot::getVectorIMU(){

  mina=0xFFFF, maxa=0, ming=0xFFFF, maxg=0;
  
  for (int sampleId=0; sampleId<sampleNbr; sampleId++){
    
    CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);
  /*  
    Serial.print("ax = ");Serial.println(ax);
    Serial.print("ay = ");Serial.println(ay);
    Serial.print("az = ");Serial.println(az);
    Serial.print("gx = ");Serial.println(gx);
    Serial.print("gy = ");Serial.println(gy);
    Serial.print("gz = ");Serial.println(gz);
*/

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

    gx = (gx < 100 && gx > 100)? 0 : gx;
    gy = (gy < 100 && gy > 100)? 0 : gy;
    gz = (gz < 100 && gz > 100)? 0 : gz;

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

      /*
      Serial.print("vector[sampleId*signalNbr + ");Serial.print(i);Serial.print(" ] = ");Serial.println(vector[sampleId*signalNbr+i]);
      Serial.print("vector[sampleId*signalNbr + 3 + ");Serial.print(i);Serial.print(" ] = ");Serial.println(vector[sampleId*signalNbr + 3 + i ]);
      */
    }

  }

}


int ApprentissageRobot::getNbActionReconnue(){
  return nbAction;
}


int ApprentissageRobot::getActionReconnue(int num){
  Serial.println("getActionReconnue");
  Serial.print("listeAction[num][0] = ");Serial.println(listeAction[num][0]);

  return listeAction[num][0];
}

int ApprentissageRobot::getTempsActionReconnue(int num){
  return listeAction[num][1];
}

void ApprentissageRobot::viderListeActionReconnue(){
  nbAction = 0;
}

void ApprentissageRobot::addActionReconnue(int num, int temps){
  Serial.println("addActionReconnue");
  Serial.print("nbAction = ");Serial.println(nbAction);


  nbAction++;
  listeAction[nbAction][0] = num;
  listeAction[nbAction][1] = temps;

  Serial.print("num = ");Serial.println(num);
  Serial.print("listeAction[nbAction][0] = ");Serial.println(listeAction[nbAction][0]);


}

bool ApprentissageRobot::listeActionPleine(){
  return (nbAction == nbMaxAction);
}

bool ApprentissageRobot::listeActionVide(){
  return (nbAction == 0);
}