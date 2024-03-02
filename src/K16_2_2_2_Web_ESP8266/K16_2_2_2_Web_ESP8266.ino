#define LEDPIN D3
#define ANALOGPIN A0

#define NETZWERKNAME "MeinWLAN"
#define PASSWORT "M.e.i.n)P.a-s/s-wo{rt"

#include "ESP8266WiFi.h"

WiFiServer Server(80);
WiFiClient Client;
String Request;
 
void setup()
{
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Verbinde mit: ");
  Serial.println("MeinWLAN");//Serial.println(NETZWERKNAME);
 
  WiFi.begin(NETZWERKNAME, PASSWORT);

  while (WiFi.status() != WL_CONNECTED) {
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
          Client.println("Connection: close"); 
          Client.println("Refresh: 2"); 
          Client.println();
          Client.println("<!DOCTYPE HTML>");
          Client.println("<html>");
          Client.print("Analogwert: ");        
          Client.print(analogRead(ANALOGPIN));
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
