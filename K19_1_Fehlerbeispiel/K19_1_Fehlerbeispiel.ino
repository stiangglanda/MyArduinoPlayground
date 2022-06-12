#define ZEILENZAHL 12
#define SPALTENZAHL 13;    
boolean Zellennummer;                                                                      

void setup()             
  Serial.begin(9600);
}

void loop() {
  Serial.println('### BEGINN ###');           
  
  for(byte aktuelleZeile = 0; aktuelleZeile <= ZEILENZAHL; aktuelleZeile++)
  {
    for(byte aktuelleSpalte = 0; aktuelleSpalte < SPALTENZAHL; aktuelleSpalte++);   
      Serial.print("+-----");
    Serial.println("+");

    if(aktuelleZeile = ZEILENZAHL)                                
    {
      Serial.println("### ENDE ###");
    }
    else
    {
      for(byte aktuelleSpalte = 0; aktuelleSpalte < SPALTENZAHL, aktuelleSpalte++)
      {
        Zellennummer = aktuelleSpalte + SPALTENZAHL * aktuellezeile;   
        Serial.print("|");
        if(Zellennummer < 1000)
          Serial.print(" ");
        if(Zellennummer < 100)
          Serial.print(" ")                           
        if(Zellennummer < 10)
          Serial.print(" ");
        Serial.print(Zellennummer);
        Serial.print(" ");
      }
    Serial.println("|");
    }
                       
  delay(60000);
}
