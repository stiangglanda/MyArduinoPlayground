import processing.serial.*;
 
Serial seriellerPort;
String Datenpaket;
 
int Knopf1 = 0;
int Knopf2 = 0;
int Sensorwert = 0;

void setup() {
  size(380,500);
  background(255);
  stroke(160);
  textSize(20);
  
  printArray(Serial.list());
  String PortName = Serial.list()[0];

  seriellerPort = new Serial(this, PortName, 9600);
  seriellerPort.bufferUntil('\n');
}
  
void draw() {

  if(Datenpaket != null) {
    if (Datenpaket.length() == 10 && Datenpaket.charAt(0) == 'A' && Datenpaket.charAt(7) == 'E') {

      Knopf1 = int(Datenpaket.substring(1,2)); 
      Knopf2 = int(Datenpaket.substring(2,3));  
       
      Sensorwert = int(Datenpaket.substring(3,7));
      
      if (Knopf1 == 1) {
        fill(0,255,0);
        rect(20,20,160,160);
        
        fill(0,0,0);
        text("Knopf 1\ngedrückt!", 60,90);
      }
      else {
        fill(255,0,0);
        rect(20,20,160,160);
        
        fill(255,255,255);
        text("Knopf 1", 60,108);
      }      

      if (Knopf2 == 1) {
        fill(0,255,0);
        rect(200,20,160,160);
        
        fill(0,0,0);
        text("Knopf 2\ngedrückt!", 240,90);
      }
      else {
        fill(255,0,0);
        rect(200,20,160,160);
        
        fill(255,255,255);
        text("Knopf 2", 240,108);
      } 
      
      
      fill(0,0,128);
      rect(20,200,340,160);
      
      fill(0,200,255);
      rect(20,200,map(Sensorwert,0,1023,0,340),160);
      
      fill(255);
      text("Sensorwert: " + Sensorwert, 100,280);
    }
  }
  
  
  if(MausueberEinschaltknopf())
    fill(150,150,200);
  else
    fill(20,20,100);
  rect(20,380,160,100);
  
  if(MausueberAusschaltknopf())
    fill(150,150,200);
  else
    fill(20,20,100);
  rect(200,380,160,100);
  
  fill(255);
  text("LED an", 68,435);
  text("LED aus", 245,435);
 
}
 
 
void serialEvent(Serial seriellerPort) {
  Datenpaket = seriellerPort.readString();
}


boolean MausueberEinschaltknopf()
{
  if(mouseX >= 20 && mouseX <= 180 && mouseY >= 380 && mouseY <= 480)
    return true;
  else
    return false;
}

boolean MausueberAusschaltknopf()
{
  if(mouseX >= 200 && mouseX <= 360 && mouseY >= 380 && mouseY <= 480)
    return true;
  else
    return false;
}

void mousePressed()
{
  if(MausueberEinschaltknopf())
    seriellerPort.write('e');
  if(MausueberAusschaltknopf())
    seriellerPort.write('a');
}
