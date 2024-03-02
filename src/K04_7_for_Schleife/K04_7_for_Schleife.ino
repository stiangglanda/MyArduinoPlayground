void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() { 
  for(byte Zaehler = 1; Zaehler <= 10; Zaehler++) 
  {
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(300);  
    digitalWrite(LED_BUILTIN, LOW);      
    delay(300);  
  } 
  delay(5000);
}
