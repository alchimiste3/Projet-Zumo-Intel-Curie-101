
import processing.serial.*;




int serialMode = 0; // Bluetooth mode si serialMode = 0

int newLine = 13; // new line character in ASCII

float yaw;
float pitch;
float roll;

float ax;
float ay;
float az;

float vx;
float vy;
float vz;

float px = 0.0;
float py = 0.0;
float pz = 0.0;


FloatList listPx;
FloatList listPy;
FloatList listPz;


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

  readFile();  
  
  
  
  
  background(255); 

  // On prend deux axes (x et y) avec l'origine en haut a gauche pour faire la carte. la voiture est pour l'instant un simple point que se déplace.
  
  pushMatrix(); // begin object
  
    drawGrille();
        
    translate(width/2, height/2); // set position to centre
    
    
    for(int i = 0 ; i < listPx.size() ; i++){
      strokeWeight(2);  // Thicker
      point((listPx.get(i) + xMin)*coofDessinData, (listPy.get(i) + yMin)*coofDessinData);
    }
    
    
    // On dessine les fleches pour la vitesse
    line(px*coofDessinData, py*coofDessinData, (px + vx)*coofDessinData, py*coofDessinData);
    
    line(px*coofDessinData, py*coofDessinData, px*coofDessinData, (py + vy)*coofDessinData);
    
    fill(0, 102, 153);
    
    // On écrie les data
    text("rotation (en radian) = "+yaw+"\n ax = "+ax+"\t ay = "+ay+"\t az = "+az+"\n vx = "+vx+"\t vy = "+vy+"\t vz = "+vz+"\n px = "+px+"\t py = "+py+"\t pz = "+pz,0, 30); 


    translate(px*coofDessinData, py*coofDessinData); // set position to centre

    
    drawRobot();
   
  popMatrix(); // end of object

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
    
    ax = float(ypr[1]);
    ay = float(ypr[2]);
    az = float(ypr[3]);
    
    vx = float(ypr[4]);
    vy = float(ypr[5]);
    vz = float(ypr[6]);
    
    px = float(ypr[7]);
    py = float(ypr[8]);
    pz = float(ypr[9]);

    listPx.append(px);
    listPy.append(py);
    listPz.append(pz);

    
  }
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
 
  rotate(yaw*100);
  //triangle(5, - 5, - 10, 0, 0, 10);
  
  fill(255, 255, 255); // red square
  rect(-10, -10, 20, 20);
  rect(-10, -15, 20, 4);


  strokeWeight(2);
}

void drawArduino() {
  /* function contains shape(s) that are rotated with the IMU */
  stroke(0, 90, 90); // set outline colour to darker teal
  fill(0, 230, 130); // set fill colour to lighter teal
  box(300, 10, 200); // draw Arduino board base shape

  stroke(0); // set outline colour to black
  fill(80); // set fill colour to dark grey

  translate(60, -10, 90); // set position to edge of Arduino box
  box(170, 20, 10); // draw pin header as box

  translate(-20, 0, -180); // set position to other edge of Arduino box
  box(210, 20, 10); // draw other pin header as box
  
}