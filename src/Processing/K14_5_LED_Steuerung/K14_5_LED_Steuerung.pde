import processing.serial.*;
 
Serial seriellerPort;

int LEDwerte[][][];      // deklariert Matrix zur Speicherung der Farbwerte
                         // im setup() muss diese Matrix zusätzlich dimensioniert werden.
int Zeile;               // Matrix-Zeile der Mausposition
int Spalte;              // Matrix-Spalte der Mausposition
int LEDnr;               // LED-Nr der Mausposition  
int ScrollPosition = 0;  // Hilfsvariablen für Lauftext
long LauftextTimer = 0;

  // Variablen für aktuell vom Nutzer vorgewählte Farbe:
int rot = 255; int gruen = 255; int blau = 255;

void setup() {
  size(450,560);
  background(255);
  stroke(160);
  fill(50);
  textSize(20);
  
  // Größe der Matrix: 8 Pixel Breite x 8 Pixel Höhe x 3 Farbwerte
  // Notation erzeugt neue Matrix des angegebenen Typs.
  LEDwerte = new int[8][8][3];    

  // zu Beginn alle Werte der Matrix auf 0 setzen:
  for(byte x = 0; x < 8; x++)
  {  
      for(byte y = 0; y < 8; y++)
      {  
        LEDwerte[x][y][0] = 0;
        LEDwerte[x][y][1] = 0;
        LEDwerte[x][y][2] = 0;
      }
  }

  printArray(Serial.list());
  String portName = Serial.list()[0];  // gegebenefalls ändern, wenn anderer Port genutzt
  seriellerPort = new Serial(this, portName, 57600);
  
  delay(500);        // kurz warten, bis serieller Port aktiviert wurde
  
  allesloeschen();   // alle LEDs auf schwarz setzen und an Arduino senden
  
  // Farbauswahlkästchen am rechten Rand zeichnen
  // (einmalig, diese werden nie überschrieben)
  stroke(0);
  fill(255);             // weiß
  rect(380, 20, 29, 29);  
  fill(255,255,0);       // gelb
  rect(380, 50, 29, 29);
  fill(0,255,255);       // cyan
  rect(380, 80, 29, 29);
  fill(0,255,0);         // grün
  rect(380, 110, 29, 29);
  fill(255,0,255);       // pink
  rect(380, 140, 29, 29);
  fill(255,0,0);         // rot
  rect(380, 170, 29, 29);
  fill(0,0,255);         // blau
  rect(380, 200, 29, 29);
  fill(00);              // schwarz
  rect(380, 230, 29, 29);
  
}
 
 
void draw()
{ 
  if(mouseX >= 20 && mouseX < 260 && mouseY >= 20 && mouseY < 260)
  {                // Falls sich die Maus auf der LED-Matrix befindet
    Spalte = (mouseX-20) / 30;     // aktuelle Spalte berechnen
    Zeile =  (mouseY-20) / 30;     // aktuelle Zeile berechnen
    LEDnr = XYtoNR(Spalte, Zeile); // und daraus LED-Nr berechnen
    if(mousePressed)  // Wird gerade eine Taste gedrückt gehalten?
    {
      if(mouseButton == LEFT)     // linke Taste: Feld einfärben
        faerbe(Spalte, Zeile, rot, gruen, blau);
      else                        // rechte Taste: Feld schwärzen
        faerbe(Spalte, Zeile, 0, 0, 0);
    }
  }
  else
  {               // Falls sich die Maus nicht auf der Matrix befindet,
    Zeile = Spalte = LEDnr = -1;   // werden die zugehörigen Variablen
  }                                // nicht benötigt.
  
  
  if(mousePressed)    // bei gedrückter Maustaste 
  {                   // prüfen, ob sie über einem Farbregler steht
    if(mouseX >= 294 && mouseX <= 310 && mouseY >= 20 && mouseY <= 275)
      rot = 255-(mouseY-20);
    if(mouseX >= 314 && mouseX <= 330 && mouseY >= 20 && mouseY <= 275)
      gruen = 255-(mouseY-20);
    if(mouseX >= 334 && mouseX <= 350 && mouseY >= 20 && mouseY <= 275)
      blau = 255-(mouseY-20);
  }
   
   
  // Farbauswahregler mit weißem Rechteck überdecken
  fill(255); stroke(255);
  rect(293,15,60,280); 
   
  // und nun neu zeichnen:
  fill(255,0,0); 
  rect(300,20,5,256);
  rect(294,274-rot,16,4);
   
  fill(0,255,0); 
  rect(320,20,5,256);
  rect(314,274-gruen,16,4);
   
  fill(0,0,255); 
  rect(340,20,5,256);
  rect(334,274-blau,16,4);   
  
  // Farbvorschaufeld zeichnen
  fill(rot, gruen, blau); stroke(0);
  rect(290,300,64,50);
   
  fill(255); stroke(255);
  rect(360,290,70,70);
  fill(0);
  text("r: " + rot, 360,312);   // Farbwerte anzeigen
  text("g: " + gruen, 360,332); // zur Kontrolle für den
  text("b: " + blau, 360,352);  // Nutzer
   
  // Berechnete LED-Position anzeigen
  fill(255); stroke(0);
  rect(20,380,240,85);
  fill(0);
  text("Mauszeigerposition:", 25,400);
  text("Zeile: " + Zeile, 50,420);
  text("Spalte: " + Spalte, 50,440);
  text("LEDnr: " + LEDnr, 50,460);
   
  // Schaltflächen zeichnen:
  if(MausueberLoeschButton())  // befindet sich die Maus auf der Schaltfläche?
    fill(160);                 // wenn ja: hellere Hintergrundfarbe nutzen
  else
    fill(128);
  stroke(64);
  rect(20,300,100,50);
  fill(0);
  text("löschen", 30,330);  
    
  if(MausueberZufallButton())
    fill(160);
  else
    fill(128);
  stroke(64);
  rect(160,300,100,50);
  fill(0);
  text("Zufall", 180,330);
    
    
  if(MausueberLTButton())
    fill(160);
  else
    fill(128);
  stroke(64);
  rect(290,380,140,65);
  fill(0);
  text("Lauftext", 320,420);
    
  if(MausueberSchachbrettButton())
    fill(160);
  else
    fill(128);
  stroke(64);
  rect(290,475,140,65);
  fill(0);
  text("Schachbrett", 305,515);
    

  // Falls Lauftextmodus aktiv ist, die entsprechende Funktion
  // nach Ablauf des ihres Timers aufrufen:
  if(LauftextTimer > 0 && millis() > LauftextTimer)
    Lauftext(); 
}
 

// Wenn die Maustaste gedrückt wurde, wird die folgende
// Funktion einmalig aufgerufen:

void mousePressed()  
{
  // Lauftext anhalten, falls aktiv:
  LauftextTimer = 0;
  
  // Prüfen, ob die Maus gerade auf einem Farbauswahlkästchen steht:
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 20 && mouseY < 50)
  {  // weiß
    rot = 255; gruen = 255; blau = 255;
  }
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 50 && mouseY < 80)
  {  // gelb
    rot = 255; gruen = 255; blau = 0;
  }
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 80 && mouseY < 110)
  {  // cyan
    rot = 0; gruen = 255; blau = 255;
  }
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 110 && mouseY < 140)
  {  // grün
    rot = 0; gruen = 255; blau = 0;
  }
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 140 && mouseY < 170)
  {  // magenta
    rot = 255; gruen = 0; blau = 255;
  }
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 170 && mouseY < 200)
  {  // rot
    rot = 255; gruen = 0; blau = 0;
  }
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 200 && mouseY < 230)
  {  // blau
    rot = 0; gruen = 0; blau = 255;
  }
  if(mouseX >= 380 && mouseX < 409 && mouseY >= 230 && mouseY < 260)
  {  // schwarz
    rot = 0; gruen = 0; blau = 0;
  }
  
  
  // prüfen, ob die Maus auf einer Schaltfläche steht:
  
  if(MausueberLoeschButton())
    allesloeschen();
    
  if(MausueberZufallButton())
    Zufallsbild();
    
  if(MausueberSchachbrettButton())
    Schachbrett();
    
  if(MausueberLTButton())
    LauftextTimer = millis();  

}


// Die folgenden Funktionen testen lediglich, ob sich die Maus
// gerade auf einer bestimmten Schaltfläche befindet
// und geben entsprechend true oder false zurück.
// Die Zahlenwerte wurden aus den Koordinaten der Zeichnungsbefehle
// abgeleitet.

boolean MausueberLoeschButton()
{
  if(mouseX >= 20 && mouseX <= 120 && mouseY >= 300 && mouseY <= 350)
    return true;
  else
    return false;
}

boolean MausueberZufallButton()
{
  if(mouseX >= 160 && mouseX <= 260 && mouseY >= 300 && mouseY <= 350)
    return true;
  else
    return false;
}

boolean MausueberLTButton()
{
  if(mouseX >= 290 && mouseX <= 430 && mouseY >= 380 && mouseY <= 445)
    return true;
  else
    return false;
}

boolean MausueberSchachbrettButton()
{
  if(mouseX >= 290 && mouseX <= 430 && mouseY >= 475 && mouseY <= 540)
    return true;
  else
    return false;
}


// Die folgende Funktion berechnet aus einer gegebenen Spalten- (x)
// und Zeilennummer (y) die Adresse einer LED
// entsprechend des Layouts der 8x8-LED-Matrix
int XYtoNR(int x, int y)
{
  if(y % 2 == 1)        // ungerade Zeile?
    return y * 8 + (7-x);
  else
    return y * 8 + x; 
}


// Die folgende Funktion färbt das Matrix-Pixel
// an der übergebenen Position mit den übergebenen
// Farbwerten und sendet diese Information direkt
// an den Arduino.

void faerbe(int x, int y, int r, int g, int b)
{
  fill(r,g,b); stroke(0);
  rect(20+x*30, 20+y*30, 29, 29);
  LEDwerte[x][y][0] = r;
  LEDwerte[x][y][1] = g;
  LEDwerte[x][y][2] = b;
  sende_aktuelle_LED();
  delay(10);
}


// Die folgende Funktion sendet nur die Information über das aktuelle
// Pixel an den Arduino.

void sende_aktuelle_LED()
{
  String Datenpaket;
  Datenpaket = "A" +nf(LEDnr,2) + nf(rot,3) + nf(gruen,3) + nf(blau,3) + "E\n";
      // nf() formatiert die übergebene Zahl auf die gewünschte Stellenanzahl;
      // gegebenenfalls mit führenden Nullen.
      
  // Statusfeld mit weißem Rechteck überdecken und neu schreiben:
  fill(255); rect(20,465,240,75);
  fill(0);
  text("letztes Datenpaket:\n"+Datenpaket, 25,490); 
  print(Datenpaket);    // Daten zur Veranschaulichung auch in der Konsole ausgeben
  
  seriellerPort.write(Datenpaket);
}


// Die folgende Funktion sendet alle 64 Datensätze
// an den Arduino.

void sende_alle_LEDs()
{
  String Datenpaket = "";
  String Endzeichen = "N\n";
  
  for(byte x = 0; x < 8; x++)
  {  
      for(byte y = 0; y < 8; y++)
      {
        if(x == 7 && y == 7)    // letztes Datenpaket?
          Endzeichen = "E\n";   // falls ja: Endzeichen "E" statt "N"
        Datenpaket = "A"
                    + nf(XYtoNR(x,y),2)
                    + nf(LEDwerte[x][y][0],3)
                    + nf(LEDwerte[x][y][1],3)
                    + nf(LEDwerte[x][y][2],3) 
                    + Endzeichen;
       
        print(Datenpaket);      // Datenpaket zur Kontrolle auch auf der Konsole ausgeben
        seriellerPort.write(Datenpaket);
      }
  }
  
  // Statusfeld mit weißem Rechteck überdecken und neu schreiben:
  fill(255); rect(20,465,240,75);
  fill(0);
  text("letztes Datenpaket:\n"+Datenpaket, 25,490);
 
}


void allesloeschen()
{
  // schwärzt die Matrix-Fläche:
  stroke(0);fill(0);
  rect(20,20,240,240);
  
  for(byte j = 0; j < 8; j++)
  {  
      for(byte k = 0; k < 8; k++)
      {  
        for(byte l = 0; l < 3; l++)
          LEDwerte[j][k][l] = 0;
      }
  }
  sende_alle_LEDs();
  rot = gruen = blau = 255;  // weiß vorwählen
  LauftextTimer = 0;         // Lauftext anhalten, falls aktiv
}


void Lauftext()
{
  int Zeiger = 0;
  int Helligkeit = 0;
  String Vorlage[] = {
    " XXX                                           ",
    "X   X            X          X                  ",
    "X   X            X                             ",
    "XXXXX  X XX   XXXX  X   X  XX   XXXX    XXX    ",
    "X   X  XX    X   X  X   X   X   X   X  X   X   ",
    "X   X  X     X   X  X   X   X   X   X  X   X   ",
    "X   X  X      XXXX   XXXX  XXX  X   X   XXX    ",
    "                                                "};
                      
  // Matrixfläche schwärzen
  stroke(0);fill(0);
  rect(20,20,240,240);
  
  
  // alle Pixel durchlaufen, um aktuelle Scroll-Bild zu erzeugen:
  for(byte j = 0; j < 8; j++)
  {  
      for(byte k = 0; k < 8; k++)
      {  
        Zeiger = j + ScrollPosition;
        if(Zeiger > 46)
          Zeiger -= 47;
          
        // Befindet sich in der Vorlage an entsprechender Stelle ein X?
        if(Vorlage[k].charAt(Zeiger) == 'X')
          Helligkeit = 128;    // Falls ja, Helligkeit zuweisen
        else
          Helligkeit = 0;      // sonst schwarz.
          
        // Alle drei Farbwerte setzen:
        for(byte l = 0; l < 3; l++)
          LEDwerte[j][k][l] = Helligkeit;
        
        // Pixel in die Matrix zeinen
        fill(Helligkeit);
        rect(20+j*30, 20+k*30, 29, 29);
      }
  }
  
  sende_alle_LEDs();
  
  ScrollPosition++;  // Scrollposition weiterrücken
  if(ScrollPosition > 47)
    ScrollPosition = 0;
    
  // nächste Aktualisierung in 200 Millisekunden
  LauftextTimer = millis() + 200;
}


void Zufallsbild()
{  
  stroke(0);
  for(byte j = 0; j < 8; j++)
  {  
      for(byte k = 0; k < 8; k++)
      {  
        for(byte l = 0; l < 3; l++)
          LEDwerte[j][k][l] = (int)random(256);
        
        fill(LEDwerte[j][k][0],LEDwerte[j][k][1],LEDwerte[j][k][2]);
        rect(20+j*30, 20+k*30, 29, 29);
      }
  }
  sende_alle_LEDs();
}


void Schachbrett()
{  
  stroke(0);
  for(byte j = 0; j < 8; j++)
  {  
      for(byte k = 0; k < 8; k++)
      {  
        for(byte l = 0; l < 3; l++)
          LEDwerte[j][k][l] = (XYtoNR(j,k)%2) * 255; // jede zweite LED weiß, die anderen schwarz
        
        fill(LEDwerte[j][k][0],LEDwerte[j][k][1],LEDwerte[j][k][2]);
        rect(20+j*30, 20+k*30, 29, 29);
      }
  }
  sende_alle_LEDs();
}
