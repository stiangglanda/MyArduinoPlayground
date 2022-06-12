void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("### LED-Steuerung ###");
  Serial.println("e: einschalten / a: ausschalten");
}

void loop() {
  if (Serial.available()) {
    char Eingabe = Serial.read();
    if(Eingabe == 'e')
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Die LED wurde eingeschaltet.");
    }
    if(Eingabe == 'a')
    {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Die LED wurde ausgeschaltet.");
    }
  }
}
