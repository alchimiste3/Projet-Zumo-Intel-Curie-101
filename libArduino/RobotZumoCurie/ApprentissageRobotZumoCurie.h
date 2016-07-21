#ifndef ApprentissageRobotZumoCurie_h
#define ApprentissageRobotZumoCurie_h

#include <string.h>
#include <stdlib.h>

#include <Arduino.h>

#include <CurieNeurons.h>

#include <CurieIMU.h>

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


  public: 

    ApprentissageRobot();
    
    void apprendreAvecIMU(int numNeurons);

    void reconnaitre(int * rep);

    void getVectorIMU();

};

#endif