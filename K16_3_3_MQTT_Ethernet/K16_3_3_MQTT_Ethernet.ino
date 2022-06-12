#define LEDPIN 3
#define ANALOGPIN 0
#define MQTT_BROKER "192.168.0.10"

#include "SPI.h"
#include "Ethernet.h"
#include "PubSubClient.h"
 
byte MAC[] = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56};
 
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

long Timer = 0;
char Zwischenspeicher[50];

void setup()
{
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println("Eigene IP-Adresse: ");  
  Ethernet.begin(MAC); 
  delay(3000);   
  Serial.println(Ethernet.localIP());             
                       
  mqttClient.setServer(MQTT_BROKER, 1883);
}

void loop()
{ 
  if (!mqttClient.connected())
    reconnect();

  mqttClient.loop();

  if(millis() > Timer)
  {
    String Analogwert = String(analogRead(ANALOGPIN));
    Analogwert.toCharArray(Zwischenspeicher, 20);
    mqttClient.publish("Arduino/Analogwert", Zwischenspeicher);

    Serial.println("Wert published: " + Analogwert);
    Timer = millis() + 5000;
  }
  Ethernet.maintain();
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
  
  byte Helligkeit = atoi(Nutzdaten);
  Serial.print("Helligkeit: "); Serial.println(Helligkeit);
  analogWrite(LEDPIN, Helligkeit);

  Serial.println("-----------------");
}

void reconnect()
{
  while(!mqttClient.connected())
  {
    Serial.print("Verbinde mit MQTT.");
    
    if(!mqttClient.connect("EthernetClient"))
    {
      Serial.print("Fehler: ");
      Serial.print(mqttClient.state());
      Serial.println(" Neuer Versuch in 5 Sekunden.");
      delay(5000);
    }
      
    mqttClient.setCallback(subscribeReceive);
    mqttClient.subscribe("Arduino/LED");
  }
}
