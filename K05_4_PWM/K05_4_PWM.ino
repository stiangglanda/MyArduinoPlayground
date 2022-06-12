void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  for(int Helligkeit = 0; Helligkeit <= 255; Helligkeit++)
  {
    analogWrite(10, Helligkeit);              // (3)
    delay(5);                   // (4)
  }
  for(int Helligkeit = 255; Helligkeit >= 0; Helligkeit--)
  {
    analogWrite(10, Helligkeit);   
    delay(5);
  }             
}
