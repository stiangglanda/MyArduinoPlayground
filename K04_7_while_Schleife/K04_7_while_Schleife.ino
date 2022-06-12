void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() { 
  byte Zaehler = 1; 
  while(Zaehler++ <= 10) 
  {                        // (3)
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(300);  
    digitalWrite(LED_BUILTIN, LOW);      
    delay(300);  
  }
  delay(5000);
}
