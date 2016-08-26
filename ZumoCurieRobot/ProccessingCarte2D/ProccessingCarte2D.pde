
import processing.serial.*;




int serialMode = 0; // Bluetooth mode si serialMode = 0

int newLine = 13; // new line character in ASCII

float yaw;
float pitch;
float roll;

float angleRobot;

float ax;
float ay;
float az;

float vx;
float vy;
float vz;

float px = 0.0;
float py = 0.0;
float pz = 0.0;

float pxPres = 0.0;
float pyPres = 0.0;
float pzPres = 0.0;

FloatList listPx;
FloatList listPy;
FloatList listPz;

float X;
float Y;

float angle = 0.0;


String message;
String [] ypr = new String [12];

int tailleX;
int tailleY;

int xMin;
int xMax;
int yMin;
int yMax;



float coofDessinData = 100;

String[] position;

void setup()
{
  size(1000, 600);

  tailleX = 1000;
  tailleY = 600;
  
  xMin = 50;
  xMax =  tailleX - 100;
  yMin = 50;
  yMax = tailleY - 100;
  
    
  listPx = new FloatList();
  listPy = new FloatList();
  listPz = new FloatList();

  frameRate(10);
}


void draw()
{

   ////////////////////////////////////// On lit les donnees dans une fichier //////////////////////////////////////

  readFile();  
  
  ////////////////////////////////////// On prent un fond blanc //////////////////////////////////////

  background(255); 

  // On prend deux axes (x et y) avec l'origine en haut a gauche pour faire la carte.
  
   ////////////////////////////////////// On commence a dessine //////////////////////////////////////

  pushMatrix(); // begin object
  
    ////////////////////////////////////// On dessine la grille //////////////////////////////////////
    
    drawGrille();
        
    ////////////////////////////////////// On dessine les position du robot depuis le debut //////////////////////////////////////

    translate(width/2, height/2); // set position to centre

    for(int i = 0 ; i < listPx.size() ; i++){
      strokeWeight(2);  // Thicker
      point((listPx.get(i) + xMin)*coofDessinData, (listPy.get(i) + yMin)*coofDessinData);
    }
    
    /*
    ////////////////////////////////////// On dessine les fleche des vitesse du robot //////////////////////////////////////

    // On dessine les fleches pour la vitesse
    line(px*coofDessinData, py*coofDessinData, (px + vx)*coofDessinData, py*coofDessinData);
    
    line(px*coofDessinData, py*coofDessinData, px*coofDessinData, (py + vy)*coofDessinData);
    */
    
    
    ////////////////////////////////////// On ecrie les donnees du robot (position, vitesse, acceleration) //////////////////////////////////////

    fill(0, 102, 153);
    text("rotation (en radian) = "+yaw+"\n ax = "+ax+"\t ay = "+ay+"\t az = "+az+"\n vx = "+vx+"\t vy = "+vy+"\t vz = "+vz+"\n px = "+px+"\t py = "+py+"\t pz = "+pz,0, 30); 

    ////////////////////////////////////// On  dessine le robot a la position px, py //////////////////////////////////////

    translate(px*coofDessinData, py*coofDessinData); 
    drawRobot();
   
  popMatrix(); // end of object

}


float distanceParcourue(){
  return px - pxPres;
  //return sqrt(pow((px - pxPres),2) + pow((py - pyPres),2));
}


void calculerCoordonne()
{

  float distance = distanceParcourue();
  
  println("distance = "+distance);
  
  
  X = sin(abs(angle)) * distance;
  Y = - cos(abs(angle)) * distance;
  
  
  println("angle = " + angle);

  println("pxPres = "+pxPres);
  println("pyPres = "+pyPres);
  println("px = "+px);
  println("py = "+py);
  println("X = "+X);
  println("Y = "+Y);

}





void drawGrille() {
  
  strokeWeight(1);
  
  //rect(xMin, yMin, xMax, yMax);
  
  fill(0, 102, 153);

  line(xMin,yMin,xMin,yMax);
  text("x",xMax,yMin-20);
  line(xMin,yMin,xMax,yMin);
  text("y",xMin-20,yMax);

  stroke(153);
  
  int interligne = 10;
  
  for(int i=xMin + interligne; i<xMax; i+=interligne + coofDessinData){
    line(i,yMin,i,yMax);
  }
  for(int w=yMin + interligne; w<yMax; w+=interligne + coofDessinData){
    line(xMin,w,xMax,w);
  }
   
  stroke(0);

}

void drawRobot() {
 
  rotate(angle);
  //triangle(5, - 5, - 10, 0, 0, 10);
  
  fill(255, 255, 255); // red square
  rect(-10, -10, 20, 20);
  rect(-10, -15, 20, 4);

  strokeWeight(2);
}


void readFile()
{
  
  println("readFile");
  
  position = loadStrings("positions.txt");
  message = position[0];

  
  if (message != null) {
    println("message = "+message);
    
    ypr = split(message, ","); 
    
    yaw = float(ypr[0]);
        
    angle = (floor(yaw * 1000)/10.0)%(2*3.14);
    
    ax = float(ypr[1]);
    ay = float(ypr[2]);
    az = float(ypr[3]);
    
    vx = float(ypr[4]);
    vy = float(ypr[5]);
    vz = float(ypr[6]);
    
    pxPres = px;
    pyPres = py;
    pzPres = pz;
    
    px = float(ypr[7]);
    py = float(ypr[8]);
    pz = float(ypr[9]);
    
    
    listPx.append(px);
    listPy.append(py);
    listPz.append(pz);
    
    calculerCoordonne();

    px = X;
    py = Y;
    pz = 0;
    
    
  }
}