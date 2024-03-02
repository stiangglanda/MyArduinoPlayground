int Wartezeit; 

void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);
  Wartezeit = 1; 
}

void loop() { 
  digitalWrite(LED_BUILTIN, HIGH);            
  delay(Wartezeit);                 
  digitalWrite(LED_BUILTIN, LOW);      
  delay(Wartezeit);    
  Wartezeit = Wartezeit + 1;
}      
