int a = 12345;
int b = 10000;

void setup() {
  Serial.begin(9600); 
}

void loop() { 
  Serial.print("Wert von a: "); Serial.println(a);
  int adresse_a = &a; 
  Serial.print("Adresse von a: "); Serial.println(adresse_a);

  Serial.print("Wert von b: "); Serial.println(b);
  int* adresse_b = &b;
  Serial.print("Adresse von b: "); Serial.println((int)adresse_b);
  Serial.print("Wert von b: "); Serial.println(*adresse_b);

  delay(100000);
}
