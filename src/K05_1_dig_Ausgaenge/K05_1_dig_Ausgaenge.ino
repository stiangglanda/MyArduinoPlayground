void setup() {
  pinMode(10, OUTPUT);                        // (1)
}   
void loop() {   
  digitalWrite(10, HIGH);                       // (2)
  delay(1000);        
  digitalWrite(10, LOW);   
  delay(1000);             
}
