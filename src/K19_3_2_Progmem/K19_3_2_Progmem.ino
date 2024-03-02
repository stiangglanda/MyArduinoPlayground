const PROGMEM char Zeichenkette[] = {"Dieser Text steht im Programmspeicher."};
char Zeichen;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (byte k = 0; k < strlen_P(Zeichenkette); k++)
  {
    Zeichen = pgm_read_byte(Zeichenkette + k);
    Serial.print(Zeichen);
  }
  Serial.println();

  Serial.println("Dieser Text wird bei der Ausgabe als lokales Array zwischengespeichert.");
  Serial.println(F("Dieser Text wird direkt aus dem Programmspeicher ausgegeben."));
  
  delay(10000);
}
