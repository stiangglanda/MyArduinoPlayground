void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() { 
  digitalWrite(LED_BUILTIN, HIGH);   
  if(millis() < 10000)
    delay(50);      
  else
    delay(1000);                     
  digitalWrite(LED_BUILTIN, LOW);      
  delay(1000);          
}
