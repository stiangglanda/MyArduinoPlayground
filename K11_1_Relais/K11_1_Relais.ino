#define SENSOR 3
#define RELAIS 15

boolean Relaiszustand = false;

void setup() {
  pinMode(RELAIS, OUTPUT);
}

void loop() {
  if(analogRead(SENSOR) < 400)
    Relaiszustand = true;
    
  if(analogRead(SENSOR) > 600)
    Relaiszustand = false;

  digitalWrite(RELAIS, Relaiszustand);
  delay(1000);
}
