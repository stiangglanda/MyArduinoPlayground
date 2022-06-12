void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() { 
  byte Zaehler = 1;
  do {  
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(300);  
    digitalWrite(LED_BUILTIN, LOW);      
    delay(300);  
  } while(Zaehler++ <= 9);
  delay(5000);
}
