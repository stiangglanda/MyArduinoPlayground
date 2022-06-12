void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  analogWrite(3, random(256));
  analogWrite(5, random(256));
  analogWrite(6, random(256));
  delay(1000);
}
