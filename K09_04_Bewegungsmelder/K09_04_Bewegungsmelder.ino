#define SENSOR 16

boolean letzterZustand = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Initialisiere Sensor...");
  delay(60000);
  Serial.println("Fertig.");
}

void loop() {
  if(digitalRead(SENSOR))
  {
    digitalWrite(LED_BUILTIN, HIGH);
    
    if(letzterZustand == false)
    {
      Serial.print("Bewegung erkannt! Zeitpunkt: ");
      Serial.print(millis()/1000);
      Serial.println(" Sekunden nach dem Einschalten.");
      letzterZustand = true;
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    letzterZustand = false;
  }
}
