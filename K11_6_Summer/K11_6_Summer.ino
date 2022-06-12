#define SENSOR 3
#define AVTIVERBUZZER 10
#define PASSIVERBUZZER 11

int letzterWert = 0;
int aktuellerWert = 0;

void setup() {
  pinMode(AVTIVERBUZZER, OUTPUT);
  pinMode(PASSIVERBUZZER, OUTPUT);
  digitalWrite(AVTIVERBUZZER, LOW);
  analogWrite(PASSIVERBUZZER, 0);
  Serial.begin(9600);
  letzterWert = analogRead(SENSOR);
}

void loop() {
  aktuellerWert = analogRead(SENSOR);

  Serial.print("aktueller Wert: ");
  Serial.println(aktuellerWert);
  
  if(abs(aktuellerWert - letzterWert) > 10)
  {
    Serial.println("ALARM");
    digitalWrite(AVTIVERBUZZER, HIGH);
    analogWrite(PASSIVERBUZZER, 128);
    delay(500);
    digitalWrite(AVTIVERBUZZER, LOW);
    analogWrite(PASSIVERBUZZER, 0);
    aktuellerWert = analogRead(SENSOR);
  }
  letzterWert = aktuellerWert;
  delay(500);
}
