void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int Zahl = 1; Zahl < 14; Zahl++)
  {
    Serial.print("Die Fakultät von ");
    Serial.print(Zahl);
    Serial.print(" ergibt: ");
    Serial.println(Fakultaet(Zahl));
    delay(5000);
  }
}

long Fakultaet(long x)
{
  long Ergebnis = 1;
  if (x>0)
    Ergebnis = x * Fakultaet(x-1);
  return Ergebnis;
} 
