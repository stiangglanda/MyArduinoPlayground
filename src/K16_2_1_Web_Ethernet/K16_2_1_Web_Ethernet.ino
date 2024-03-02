#define LEDPIN 3
#define ANALOGPIN A0

#include "SPI.h"
#include "Ethernet.h"
 
byte MAC[] = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56};
 
EthernetServer Server(80);
EthernetClient Client;
String Request;
 
void setup()
{
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println("Eigene IP-Adresse: ");  
  Ethernet.begin(MAC); 
  delay(3000);   
  Serial.println(Ethernet.localIP()); 

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
                           
           // HTTP Header 200 an den Browser schicken
          Client.println("HTTP/1.1 200 OK");
          Client.println("Content-Type: text/html");
          Client.println("Connection: close"); // Verbindung wird nach Antwort beendet
          Client.println("Refresh: 2"); // Seite alle 25 Sekunden neu abfragen
          Client.println();
          // Ab hier berginnt der HTML-Code, der an den Browser geschickt wird
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

  Ethernet.maintain();
}
