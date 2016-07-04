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
String [] ypr = new String [12];

void setup()
{
  size(1500, 800, P3D);
 
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

  translate(200, 0); // set position to centre

  pushMatrix(); // begin object

  
  fill(0, 102, 153);
  text("roll = "+roll+"\t yaw = "+yaw+"\t pitch = "+pitch+"\n ax = "+ax+"\t ay = "+ay+"\t az = "+az+"\n vx = "+vx+"\t vy = "+vy+"\t vz = "+vz+"\n px = "+px+"\t py = "+py+"\t pz = "+pz,0, 30); 

  strokeWeight(4);  // Thicker
  
  text("roll : ",400,200);
  line(405, 210, 405 + roll, 210);

  text("yaw : ",400,240);
  line(405, 250, 405 + yaw, 250);
  
  text("pitch : ",400,280);
  line(405, 290, 405 + pitch, 290);
  
  text("ax : ",400,320);
  line(405, 330, 405 + ax, 330);

  text("ay : ",400,360);
  line(405, 370, 405 + ay, 370);
  
  text("az : ",400,400);
  line(405, 410, 405 + az, 410);
  
  text("vx : ",400,440);
  line(405, 450, 405 + vx, 450);
  
  text("vy : ",400,480);
  line(405, 490, 405 + vy, 490);
  
  text("vz : ",400,520);
  line(405, 530, 405 + vz, 530);
  
  text("px : ",400,560);
  line(405, 570, 405 + px, 570);
  
  text("py : ",400,600);
  line(405, 610, 405 + py, 610);
  
  text("pz : ",400,640);
  line(405, 650, 405 + pz, 650);
  
  translate(800, 200); // set position to centre

  strokeWeight(1);  

  rotateX(-roll); 
  rotateY(yaw); 
  rotateZ(pitch);
  
  
  drawArduino();
  

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