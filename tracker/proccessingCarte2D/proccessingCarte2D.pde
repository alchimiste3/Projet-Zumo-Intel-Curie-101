import processing.serial.*;

Serial myPort;

int serialMode = 1; // Bluetooth mode si serialMode = 0

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

float px;
float py;
float pz;

String message;
String [] ypr = new String [12];

int tailleX;
int tailleY;

int xMin;
int xMax;
int yMin;
int yMax;

float coofDessinData = 10;

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

  if(serialMode == 1){
    println(Serial.list()[1]);
    myPort = new Serial(this, Serial.list()[1], 9600);
  }

  
  frameRate(10);
}


void draw()
{
  
  if(serialMode == 1){
    serialEvent(); 
  }
  else{
    readFile();  
  }
  
  
  
  background(255); 

  // On prend deux axes (x et y) avec l'origine en haut a gauche pour faire la carte. la voiture est pour l'instant un simple point que se déplace.
  
  pushMatrix(); // begin object
  
    drawGrille();
        
    translate(width/2, height/2); // set position to centre
    
    
    // On dessine le point
    strokeWeight(8);  // Thicker
    point(px*coofDessinData, py*coofDessinData);
    strokeWeight(2);
    
    // On dessine les fleches pour la vitesse
    line(px*coofDessinData, py*coofDessinData, (px + vx)*coofDessinData, py*coofDessinData);
    line(px*coofDessinData, py*coofDessinData, px*coofDessinData, (py + vy)*coofDessinData);
    
    fill(0, 102, 153);
    
    // On écrie les data
    text("roll = "+roll+"\t yaw = "+yaw+"\t pitch = "+pitch+"\n ax = "+ax+"\t ay = "+ay+"\t az = "+az+"\n vx = "+vx+"\t vy = "+vy+"\t vz = "+vz+"\n px = "+px+"\t py = "+py+"\t pz = "+pz,0, 30); 


    translate(px*coofDessinData, py*coofDessinData); // set position to centre

    
    drawCar();
   
  popMatrix(); // end of object

  if(serialMode == 1){
    myPort.write("s"); // write an "s" to receive more data from Arduino
  }
}

void readFile()
{
  
  println("readFile");
  
  position = loadStrings("positions.txt");
  message = position[0];

  
  if (message != null) {
    println("message = "+message);
    
    
    ypr = split(message, ","); 
    roll = float(ypr[0]); 
    yaw = float(ypr[1]);
    pitch = float(ypr[2]);
    
    ax = float(ypr[3]);
    ay = float(ypr[4]);
    az = float(ypr[5]);
    
    vx = float(ypr[6]);
    vy = float(ypr[7]);
    vz = float(ypr[8]);
    
    px = float(ypr[9]);
    py = float(ypr[10]);
    pz = float(ypr[11]);

    
  }
}

void serialEvent()
{
  message = myPort.readStringUntil(newLine); // read from port until new line (ASCII code 13)
  if (message != null) {
    println(message);
    
    
    ypr = split(message, ","); 
    roll = float(ypr[0]); 
    yaw = float(ypr[1]);
    pitch = float(ypr[2]);
    
    ax = float(ypr[3]);
    ay = float(ypr[4]);
    az = float(ypr[5]);
    
    vx = float(ypr[6]);
    vy = float(ypr[7]);
    vz = float(ypr[8]);
    
    px = float(ypr[9]);
    py = float(ypr[10]);
    pz = float(ypr[11]);

    
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
  
  for(int i=xMin + interligne; i<xMax; i+=interligne){
    line(i,yMin,i,yMax);
  }
  for(int w=yMin + interligne; w<yMax; w+=interligne){
    line(xMin,w,xMax,w);
  }
   
  stroke(0);

}

void drawCar() {
  

  strokeWeight(8);  // Thicker
  rotate(-yaw*50);
  triangle(5, - 5, - 10, 0, 0, 10);
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