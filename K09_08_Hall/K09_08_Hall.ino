#define ANALOGPIN 0
#define DIGITALPIN 15

int SensorWert;
int minWert = 1023;
int maxWert = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
}
void loop()
{
  SensorWert = analogRead(ANALOGPIN);

  if(SensorWert > maxWert)
    maxWert = SensorWert;

  if(SensorWert < minWert)
    minWert = SensorWert;

  Serial.print("Aktueller Messwert: ");
  Serial.print(SensorWert);
  Serial.print(", Maximal-/Minimalwert: ");
  Serial.print(maxWert);
  Serial.print(" / ");
  Serial.println(minWert);

  digitalWrite(LED_BUILTIN,digitalRead(DIGITALPIN));

  delay(1000);
}
