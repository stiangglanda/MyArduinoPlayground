#define WARTEZEIT 1000 

void setup() {      
  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() { 
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(WARTEZEIT);  
  digitalWrite(LED_BUILTIN, LOW);      
  delay(WARTEZEIT);          
} 
