char TextA[7] = {'H', 'a', 'l', 'l', 'o', '!'};
char TextB[] = "Hallo";
String TextC = "Hall";
String TextD = "o Welt!";

void setup() {
  Serial.begin(9600); 
}

void loop() { 
  Serial.print("TextA: "); Serial.println(TextA);
  Serial.print("TextB: "); Serial.println(TextB);
  Serial.print("TextC und D: "); Serial.println(TextC + TextD);
  Serial.print("Länge von C: "); Serial.println(TextC.length());
 
  delay(100000);
}
