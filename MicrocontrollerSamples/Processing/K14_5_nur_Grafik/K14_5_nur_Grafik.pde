void setup() {
  size(450,560);
  background(255);
  textSize(20);
}
 
void draw()
{ 
  // Fläche für LED-Matrix
  stroke(50); fill(150);  
  rect(20, 20, 240, 240);  
  
  // Farbauswahlkästchen am rechten Rand:
  stroke(0);
  fill(255);              // weiß
  rect(380, 20, 29, 29);  
  fill(255,255,0);        // gelb
  rect(380, 50, 29, 29);
  fill(0,255,255);        // cyan
  rect(380, 80, 29, 29);
  fill(0,255,0);          // grün
  rect(380, 110, 29, 29);
  fill(255,0,255);        // pink
  rect(380, 140, 29, 29);
  fill(255,0,0);          // rot
  rect(380, 170, 29, 29);
  fill(0,0,255);          // blau
  rect(380, 200, 29, 29);
  fill(00);               // schwarz
  rect(380, 230, 29, 29);
   
 
  // roter Farbregler:
  fill(255,0,0); stroke(255);
  rect(300,20,5,256);
  rect(294,200,16,4);
 
  // grüner Farbregler:
  fill(0,255,0); 
  rect(320,20,5,256);
  rect(314,200,16,4);
 
  // blauer Farbregler:
  fill(0,0,255); 
  rect(340,20,5,256);
  rect(334,200,16,4);   
 
  // Farbvorschaufeld:
  fill(100, 150, 200); stroke(0);
  rect(290,300,64,50);
 
  // Textanzeige des aktuelle Farbwertes (vor weißem Hintergrund)
  fill(255); stroke(255);
  rect(360,290,70,70);
  fill(0);
  text("r: ", 360,312);
  text("g: ", 360,332);
  text("b: ", 360,352);

  // Raum für Statusinfos (Text vor weißem Hintergrund)
  fill(255); stroke(0);
  rect(20,380,240,85);
  fill(0);
  text("Mauszeigerposition:", 25,400);
  text("Zeile: ", 50,420);
  text("Spalte: ", 50,440);
  text("LEDnr: ", 50,460);
  
  fill(255); rect(20,465,240,75);
  fill(0);
  text("letztes Datenpaket:", 25,490); 

  // Lösch-Button
  fill(128);
  stroke(64);
  rect(20,300,100,50);
  fill(0);
  text("löschen", 30,330);
  
  // Zufall-Button
  fill(128);
  stroke(64);
  rect(160,300,100,50);
  fill(0);
  text("Zufall", 180,330);
  
  // Lauftext-Button 
  fill(128);
  stroke(64);
  rect(290,380,140,65);
  fill(0);
  text("Lauftext", 320,420);
  
  // Schachbrett-Button
  fill(128);
  stroke(64);
  rect(290,475,140,65);
  fill(0);
  text("Schachbrett", 305,515);
}
