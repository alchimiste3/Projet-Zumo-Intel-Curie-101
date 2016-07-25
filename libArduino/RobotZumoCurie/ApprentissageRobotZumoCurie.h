/*
 * ApprentissageRobotZumoCurie.h
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 * Dernier mise a jour: 25-07-1016 (Quentin)
 *
 *
 * Cette classe permet d'utiliser le reseau de neurons integrer dans la carte Intel Curie afin d'apprendre des mouvement avec l'IMU
 * et de sauvegrader les mouvements effectue pour pouvoir les  reproduire
 */

#ifndef ApprentissageRobotZumoCurie_h
#define ApprentissageRobotZumoCurie_h

#include <string.h>
#include <stdlib.h>

#include <Arduino.h>

#include <CurieNeurons.h>

#include <CurieIMU.h>

// On peut enregistrer maximum 100 Actions a la suite avant de pouvoir les reexecuter.
const int nbMaxAction = 100;


class ApprentissageRobot {

  /////////////////////////////// IMU ///////////////////////////////

  int ax, ay, az;
  int gx, gy, gz;


  ////////////////////////// var neurons ///////////////////////:

  CurieNeurons hNN;

  int catL=0; // category to learn
  int prevcat=0; // previously recognized category
  int dist, cat, nid, nsr, ncount; // response from the neurons

  ////////////////////////// var getVector ///////////////////////:

  #define sampleNbr 10  // number of samples to assemble a vector
  #define signalNbr  6  // ax,ay,az,gx,gy,gz

  int raw_vector[sampleNbr*signalNbr]; // vector accumulating the raw sensor data
  byte vector[sampleNbr*signalNbr]; // vector holding the pattern to learn or recognize
  int mina=0xFFFF, maxa=0, ming=0xFFFF, maxg=0, da, dg;


  ////////////////////////// Reconnaissance parcourt ////////////////////


  int nbAction;

  int listeAction[nbMaxAction][2];


  public:

    ApprentissageRobot();
    
  
    void apprendreAvecIMU(int numNeurons);

    void reconnaitre(int * rep);

    void getVectorIMU();


    //////////////////////////// Reconnaissance de trajectoire //////////////////////////////


    int getNbActionReconnue();

    int getActionReconnue(int num);

    int getTempsActionReconnue(int num);

    void viderListeActionReconnue();

    void addActionReconnue(int num, int temps);

    bool listeActionPleine();

    bool listeActionVide();

};

#endif