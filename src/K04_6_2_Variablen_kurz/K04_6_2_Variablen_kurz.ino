int Wartezeit = 1;

void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() { 
  digitalWrite(LED_BUILTIN, HIGH);            
  delay(Wartezeit);                
  digitalWrite(LED_BUILTIN, LOW);      
  delay(Wartezeit++);
}      
