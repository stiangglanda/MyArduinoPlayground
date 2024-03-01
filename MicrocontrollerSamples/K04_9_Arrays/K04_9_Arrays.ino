int MessreiheA[5] = {503, 287, 903, 15, 91};
int MessreiheB[] = {63, 48, 720, 612, 102};

void setup()
{
  Serial.begin(9600);
  Serial.println("### Messergebnisanzeige ###");
  Serial.println("a: Messreihe A / b: Messreihe B");
}

void loop() {
  if (Serial.available()) {
    char Eingabe = Serial.read();
    if(Eingabe == 'a')
    {
      Serial.println();
      Serial.println("Datenreihe A:");
      for(byte i=0; i < 5; i++)
      {
        Serial.print(MessreiheA[i]);
        Serial.print("  ");
      }
      Serial.println("# Ende der Datenreihe #");    
    }
    if(Eingabe == 'b')
    {
      Serial.println();
      Serial.println("Datenreihe B:");
      for(byte i=0; i < 5; i++)
      {
        Serial.print(MessreiheB[i]);
        Serial.print("  ");
      }
      Serial.println("# Ende der Datenreihe #");  
    }
  }
}
