void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);  
  Serial.begin(9600);
}

void loop() { 
  for(byte Zaehler = 1; Zaehler <= 5; Zaehler++)    
  {                        // (2)
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(300);  
    digitalWrite(LED_BUILTIN, LOW);      
    delay(300);  
    Serial.print(" Zähler: ");
    Serial.print(Zaehler);
  }           
  delay(5000);
  Serial.println("--- Loop-Ende ---"); 
}
