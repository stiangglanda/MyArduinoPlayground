#define TASTER1 9
#define TASTER2 8
#define LEDPIN 6
 
boolean Knopf1gedrueckt = false;
boolean Knopf2gedrueckt = false;
int Sensorwert = 0;
char Empfangsdaten;
 
char Datenpaket[] = "A000000E";

 
void setup() {
  Serial.begin(9600);
  pinMode(TASTER1, INPUT_PULLUP);
  pinMode(TASTER2, INPUT_PULLUP);
  pinMode(6, OUTPUT);
}
 
 
void loop()
{  
  Knopf1gedrueckt = !digitalRead(TASTER1);
  Knopf2gedrueckt = !digitalRead(TASTER2); 
  Sensorwert = analogRead(3); 

  sprintf(Datenpaket, "A%1d%1d%04dE",Knopf1gedrueckt,Knopf2gedrueckt,Sensorwert);

  Serial.println(Datenpaket);
 
  delay(50);

  if(Serial.available())
  {
    char Empfangsdaten = Serial.read();

    if(Empfangsdaten == 'e')
      digitalWrite(LEDPIN, HIGH);
      
    if(Empfangsdaten == 'a')
      digitalWrite(LEDPIN, LOW); 
   }
}
 
