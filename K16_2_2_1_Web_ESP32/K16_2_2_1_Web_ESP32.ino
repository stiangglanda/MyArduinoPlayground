#define LEDPIN 4                  // = GPIO 4
#define ANALOGPIN ADC1_CHANNEL_4  // = GPIO 32

#define NETZWERKNAME "MeinWLAN"
#define PASSWORT "M.e.i.n)P.a-s/s-wo{rt"

#include "WiFi.h"
#include "driver/adc.h"

WiFiServer Server(80);
WiFiClient Client;
String Request;
 
void setup()
{
  pinMode(LEDPIN, OUTPUT);
  adc1_config_width(ADC_WIDTH_BIT_10); 
  adc1_config_channel_atten(ANALOGPIN,ADC_ATTEN_DB_11);
 
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Verbinde mit: ");
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

  Server.begin();
}
 
void loop() 
{
  Client = Server.available();

  if (Client)
  {
    Serial.println("Neuer Client");
    boolean leereZeile = true;
 
    while (Client.connected())
    {
      if (Client.available())
      {
        char c = Client.read();
        if (Request.length() < 100)
          Request += c;

        if (c == '\n' && leereZeile)
        {
          Serial.print("Request von Client: ");
          Serial.println(Request);
          if(Request.indexOf("ein")>0)
            digitalWrite(LEDPIN,HIGH);

          if(Request.indexOf("aus")>0)
            digitalWrite(LEDPIN,LOW);

          Client.println("HTTP/1.1 200 OK");
          Client.println("Content-Type: text/html");
          Client.println("Connection: close"); // Verbindung wird nach Antwort beendet
          Client.println("Refresh: 2"); // Seite alle 25 Sekunden neu abfragen
          Client.println();
          Client.println("<!DOCTYPE HTML>");
          Client.println("<html>");
          Client.print("Analogwert: ");        
          Client.print(adc1_get_raw(ANALOGPIN));
          Client.println("<br><br>"); 
          Client.println("<a href='?ein'>LED einschalten</a>");
          Client.println("<br><br>");
          Client.println("<a href='?aus'>LED ausschalten</a>");
          Client.println("</html>");
  
          Request = "";
          break;
        }
        
        if (c == '\n')
          leereZeile = true;
        else if (c != '\r')
            leereZeile = false;
      }
    }

    delay(1);
    Client.stop();
    Serial.println("Verbindung mit Client beendet.");
    Serial.println("");
  }
}
