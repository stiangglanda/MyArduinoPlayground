#include "DHT.h"

DHT dht(2, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float Temp = dht.readTemperature();
  float Feuchte = dht.readHumidity();
  float HI = dht.computeHeatIndex(Temp, Feuchte, false);

  Serial.print("Temperatur: ");
  Serial.print(Temp);
  Serial.print("°C  Luftfeuchtigkeit: ");
  Serial.print(Feuchte);
  Serial.print("%  gefühlte Temp.: ");
  Serial.print(HI);
  Serial.println("°C ");
  
  delay(5000);
}
