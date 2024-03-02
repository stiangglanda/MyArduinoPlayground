#define LATCHPIN 3
#define CLOCKPIN 4
#define DATAPIN 2

byte sieben_seg_ziffern[10] = {
  B11111100,  // = 0
  B01100000,  // = 1
  B11011010,  // = 2
  B11110010,  // = 3
  B01100110,  // = 4
  B10110110,  // = 5
  B10111110,  // = 6
  B11100000,  // = 7
  B11111110,  // = 8
  B11100110   // = 9      
};
  
void setup() {
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(DATAPIN, OUTPUT);
}
 
void sevenSegWrite(byte ziffer) {
  digitalWrite(LATCHPIN, LOW);
  shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, sieben_seg_ziffern[ziffer]);  
  digitalWrite(LATCHPIN, HIGH);
}
 
void loop() {       
  for (byte zahl = 0; zahl < 10; zahl++) {
    delay(1000);
    sevenSegWrite(zahl); 
  }
}
