class SpielKonto {
  private:
    long Kontostand;
    float Zinssatz;
  public:
    long gibKontostand(void) {return Kontostand;};
    boolean zahleEin(long);
    boolean zahleAus(long);
    void verzinse(void) {Kontostand+= Kontostand*Zinssatz/100.0;};
    boolean setzeZinssatz(float);
    SpielKonto(void);
};

boolean SpielKonto::zahleEin(long Betrag)
{
  if(Betrag > 0 && Betrag <= 10000)
  {
    Kontostand+= Betrag;
    return true;
  } else
      return false;  
}

boolean SpielKonto::zahleAus(long Betrag)
{
  if(Kontostand >= Betrag && Betrag <= 10000)   
  {
    Kontostand-= Betrag;
    return true;
  } else
      return false;  
}

boolean SpielKonto::setzeZinssatz(float neuerSatz)
{
  if(neuerSatz >= 0 && neuerSatz <= 10)
  {
    Zinssatz = neuerSatz;
    return true;
  } else
      return false;  
}

SpielKonto::SpielKonto(void)            // Konstruktor
{
  Kontostand = 5000;
  Zinssatz = 2.0;
}


SpielKonto KontoA;
SpielKonto KontoB;
SpielKonto KontoC;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Kontostand A: "); Serial.println(KontoA.gibKontostand());
  Serial.print("Kontostand B: "); Serial.println(KontoB.gibKontostand());
  Serial.print("Kontostand C: "); Serial.println(KontoC.gibKontostand());
  Serial.println("----------------------------");
  
  if(KontoA.zahleAus(1000))
    KontoB.zahleEin(1000);

  KontoA.verzinse();
  KontoB.verzinse();    
  KontoC.verzinse();

  delay(10000);
}
