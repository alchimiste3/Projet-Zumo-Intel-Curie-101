import processing.serial.*;

Serial myPort;

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
String [] ypr = new String [9];

void setup()
{
  size(1000, 800, P3D);
 
  /*Set my serial port to same as Arduino, baud rate 9600*/
  
 
  println(Serial.list()[1]);
  myPort = new Serial(this, Serial.list()[1], 9600); // if you have only ONE COM port active
  //myPort = new Serial(this, "COM5", 9600);  // if you know the 101 COM port

  textSize(16); // set text size
  textMode(SHAPE); // set text mode to shape
  
  frameRate(10);
}

void draw()
{
  serialEvent();  // read and parse incoming serial message
  background(255); // set background to white

  pushMatrix(); // begin object

  
  fill(0, 102, 153);
  text("roll = "+roll+"\t yaw = "+yaw+"\t yaw = "+yaw+"\t pitch = "+pitch+"\t vx = "+vx+"\t xy = "+vy+"\t vz = "+vz+"\t px = "+px+"\t py = "+py+"\t pz = "+pz,0, 30); 
 
  popMatrix(); // end of object

  myPort.write("s"); // write an "s" to receive more data from Arduino
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
    
    vx = float(ypr[3]);
    vy = float(ypr[4]);
    vz = float(ypr[5]);
    
    px = float(ypr[6]);
    py = float(ypr[7]);
    pz = float(ypr[8]);

    
  }
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