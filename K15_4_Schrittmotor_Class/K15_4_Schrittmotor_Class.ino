class Schrittmotor {
  private:
    byte Modus;
    unsigned long StartZeit; long StartPosition; long ZielPosition;
    long aktuellePosition; int aktuelleGeschwindigkeit; int maxGeschwindigkeit;
    long SchritteProUmdrehung;
    byte p1, p2, p3, p4;
    void Ausgabe(char);
    long Timer;

  public:
    Schrittmotor(byte, byte, byte, byte);
    void bewegePosition(long);
    void bewegeGeschwindigkeit(int);
    void Schleife(void);
    byte gibStatus(void) {return Modus;};
    long gibPosition(void) {return aktuellePosition;};
    long setze0(void) {aktuellePosition = 0; return true;};
    void Stopp(void) {Modus = 0; return true;};
};


Schrittmotor::Schrittmotor(byte a, byte b, byte c, byte d)       // Konstruktor
{
  p1 = a<14 ? a : 1;
  p2 = b<14 ? b : 2;
  p3 = b<14 ? c : 3;
  p4 = b<14 ? d : 4;
  Modus = 0;
  StartPosition = 0L; StartZeit = 0L;
  aktuellePosition = 0L; aktuelleGeschwindigkeit = 0L;
  ZielPosition = 0L; Timer = 0L;
  SchritteProUmdrehung = 2048;
  maxGeschwindigkeit = 15;
  pinMode(p1, OUTPUT); pinMode(p2, OUTPUT); pinMode(p3, OUTPUT); pinMode(p4, OUTPUT);
  Ausgabe(4);
}

void Schrittmotor::Ausgabe(char Phase)
{
 switch(Phase)
  { // Phasen 0-3 stellen die einzelnen Rotationsschritte dar.
    case 0:
      digitalWrite(p1,HIGH); digitalWrite(p2,HIGH); digitalWrite(p3,LOW); digitalWrite(p4,LOW);
    break;
    case 1: case -3:
      digitalWrite(p1,LOW); digitalWrite(p2,HIGH); digitalWrite(p3,HIGH); digitalWrite(p4,LOW);
    break;
    case 2: case -2:
      digitalWrite(p1,LOW); digitalWrite(p2,LOW); digitalWrite(p3,HIGH); digitalWrite(p4,HIGH);
    break;
    case 3: case -1:
      digitalWrite(p1,HIGH); digitalWrite(p2,LOW); digitalWrite(p3,LOW); digitalWrite(p4,HIGH);
    break;
    case 4: // Phase 4 ist vorgesehen, um alle Ausgänge auf LOW zu schalten (Stromsparen im Stillstand).
      digitalWrite(p1,LOW); digitalWrite(p2,LOW); digitalWrite(p3,LOW); digitalWrite(p4,LOW);
    break;
  }
  return true;
}


void Schrittmotor::bewegeGeschwindigkeit(int Geschwindigkeit)
{
  if(abs(Geschwindigkeit) > 0 && abs(Geschwindigkeit) <= maxGeschwindigkeit)
  {
    Modus = 1;
    aktuelleGeschwindigkeit = Geschwindigkeit;
    StartPosition = aktuellePosition;
    StartZeit = millis();
    return true;
  }
  else
    return false;
}

void Schrittmotor::bewegePosition(long Position)
{
  Modus = 2;
  ZielPosition = Position;
}


void Schrittmotor::Schleife(void)
{
  if(!Modus)
    Ausgabe(4);
  if(Modus == 1)
  {
    long Zeitdifferenz = millis() - StartZeit;
    aktuellePosition = StartPosition + (Zeitdifferenz * SchritteProUmdrehung * aktuelleGeschwindigkeit / 60000L);
    Ausgabe(aktuellePosition % 4); 
  }
  if(Modus == 2 && millis() > Timer)
  {
    if(ZielPosition > aktuellePosition)
      aktuellePosition++;
    if(ZielPosition < aktuellePosition)
      aktuellePosition--;
    if(ZielPosition == aktuellePosition)
      Modus = 0;
    Ausgabe(aktuellePosition%4); 
    Timer = millis() + 1;
  }
}



Schrittmotor Zeiger1(9,10,11,12); 
Schrittmotor Zeiger2(4,5,6,7);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Zeiger1.Schleife();
  Zeiger2.Schleife();

  if (Serial.available() > 0) {
    char Eingabe = Serial.read();
    switch(Eingabe)
    {
      case 'r':
        Zeiger1.bewegeGeschwindigkeit(10);
      break;
      case 'R':
        Zeiger2.bewegeGeschwindigkeit(10);
      break;
      case 'l':
        Zeiger1.bewegeGeschwindigkeit(-10);
      break;
      case 'L':
        Zeiger2.bewegeGeschwindigkeit(-10);
      break;
      case 's':
        Zeiger1.Stopp();
        Zeiger2.Stopp();
      break;
      case 't':
        Zeiger1.bewegeGeschwindigkeit(1);
        Zeiger2.bewegeGeschwindigkeit(-1);
      break;
      case '0':
        Zeiger1.bewegePosition(0);
        Zeiger2.bewegePosition(0);
      break;
      
      case 'p':
        Serial.print("aktuelle Position Zeiger 1: ");
        Serial.println(Zeiger1.gibPosition());
        Serial.print("aktuelle Position Zeiger 2: ");
        Serial.println(Zeiger2.gibPosition());
      break;
    }
  }
}
