#define LEDPIN D3
#define ANALOGPIN A0

#define NETZWERKNAME "MeinWLAN"
#define PASSWORT "M.e.i.n)P.a-s/s-wo{rt"
#define MQTT_BROKER "192.168.0.10"

#include "ESP8266WiFi.h"
#include "PubSubClient.h"
 
WiFiClient espClient;
PubSubClient mqttClient(espClient);

long Timer = 0;
char Zwischenspeicher[50];
 
void setup()
{
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Verbinde mit WLAN: ");
  Serial.println("MeinWLAN");//Serial.println(NETZWERKNAME);

  WiFi.begin(NETZWERKNAME, PASSWORT);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Erfolgreich. Eigene IP-Adresse: ");
  Serial.println(WiFi.localIP());
  
  mqttClient.setServer(MQTT_BROKER, 1883);
}

void loop()
{ 
  if (!mqttClient.connected())
    reconnect();

  mqttClient.loop();

  if(millis() > Timer)
  {
    String Analogwert = String(analogRead(A0));
    Analogwert.toCharArray(Zwischenspeicher, 20);
    mqttClient.publish("Arduino/Analogwert", Zwischenspeicher);

    Serial.println("Wert published: " + Analogwert);
    Timer = millis() + 5000;
  }
}

void subscribeReceive(char* Topic, byte* Nutzdaten, unsigned int Laenge)
{
  Serial.println("### Empfangen ###");
  Serial.print("Topic: ");
  Serial.println(Topic);
  
  Serial.print("Nutzdaten: ");
  for(int i = 0; i < Laenge; i ++)
    Serial.print(char(Nutzdaten[i]));

  Serial.println("");
  byte Helligkeit = (Nutzdaten[0]-'0')*100 + (Nutzdaten[1]-'0')*10 + (Nutzdaten[2]-'0');
  Serial.print("Helligkeit: "); Serial.println(Helligkeit);
  analogWrite(LEDPIN, Helligkeit);

  Serial.println("-----------------");
}

void reconnect()
{
  while (!mqttClient.connected())
  {
    Serial.print("Verbinde mit MQTT.");
    
    if (!mqttClient.connect("ESP8266Client"))
    {
      Serial.print("Fehler: ");
      Serial.print(mqttClient.state());
      Serial.println(" Neuer Versuch in 5 Sekunden.");
      delay(5000);
    }
  }
  mqttClient.setCallback(subscribeReceive);
  mqttClient.subscribe("Arduino/LED");
}
