void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Eingelesener Analogwert: ");
  Serial.println(analogRead(3));
  delay(1000);
}
