#define LEDPIN 4
#define PWM_CHANNEL 0  
#define ANALOGPIN ADC1_CHANNEL_4 

#define NETZWERKNAME "MeinWLAN"
#define PASSWORT "M.e.i.n)P.a-s/s-wo{rt"
#define MQTT_BROKER "192.168.0.10"

#include "WiFi.h"
#include "driver/adc.h"
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
  Serial.println(NETZWERKNAME);

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

  ledcSetup(PWM_CHANNEL, 5000, 8); 
  ledcAttachPin(LEDPIN, PWM_CHANNEL);
  adc1_config_width(ADC_WIDTH_BIT_10);  
  adc1_config_channel_atten(ANALOGPIN,ADC_ATTEN_DB_11); 
}
 
void loop()
{
  if (!mqttClient.connected())
    reconnect();

  mqttClient.loop();

  if(millis() > Timer)
  {
    String Analogwert = String(adc1_get_raw(ANALOGPIN));
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
  
  Serial.print("Message: ");
  for(int i = 0; i < Laenge; i ++)
    Serial.print(char(Nutzdaten[i]));
  Serial.println("");

  byte Helligkeit = (Nutzdaten[0]-'0')*100 + (Nutzdaten[1]-'0')*10 + (Nutzdaten[2]-'0');
  Serial.print("Helligkeit: "); Serial.println(Helligkeit);
  ledcWrite(PWM_CHANNEL, Helligkeit);
 
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
