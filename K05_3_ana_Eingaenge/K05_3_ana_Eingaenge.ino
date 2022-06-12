void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int Wartezeit = analogRead(2);
  Serial.println(Wartezeit);  
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(Wartezeit);          
  digitalWrite(LED_BUILTIN, LOW);  
  delay(Wartezeit);              
}
