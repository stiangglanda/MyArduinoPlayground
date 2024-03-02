#define AMPEL1ROT 6
#define AMPEL1GELB 5
#define AMPEL1GRUEN 4
#define AMPEL2ROT 10
#define AMPEL2GELB 9 
#define AMPEL2GRUEN 8

#define TASTE 2

#define AUS 0
#define ROT 1
#define ROTGELB 2
#define GRUEN 3
#define GELB 4

long Timer = 0;
byte Phase = 0;

void setup() {
  pinMode(AMPEL1ROT, OUTPUT);
  pinMode(AMPEL1GELB, OUTPUT);
  pinMode(AMPEL1GRUEN, OUTPUT);
  pinMode(AMPEL2ROT, OUTPUT);
  pinMode(AMPEL2GELB, OUTPUT);
  pinMode(AMPEL2GRUEN, OUTPUT);
  pinMode(TASTE, INPUT_PULLUP);
}

void loop() {
  
  while(millis() < Timer)
  {
    if(!digitalRead(TASTE))
    {
      if(Phase < 10)
        Phase = 10;
      else
        Phase = 0;
      Timer = 0;
      while(!digitalRead(TASTE));
    }
  }

  
  switch(Phase)
  {
    case 0: // Beide Ampeln rot
      setzeAmpel(1, ROT);
      setzeAmpel(2, ROT);
      Timer = millis() + 2000;
      Phase++;
    break;
    
    case 1: // Ampel 1 rotgelb
      setzeAmpel(1, ROTGELB);
      Timer = millis() + 1000;
      Phase++;
    break;

    case 2: // Ampel 1 grün
      setzeAmpel(1, GRUEN);
      Timer = millis() + 8000;
      Phase++;
    break;

    case 3: // Ampel 1 gelb
      setzeAmpel(1, GELB);
      Timer = millis() + 2000;
      Phase++;
    break;

    case 4: // Beide Ampeln rot
      setzeAmpel(1, ROT);
      Timer = millis() + 2000;
      Phase++;
    break;

    case 5: // Ampel 2 rotgelb
      setzeAmpel(2, ROTGELB);
      Timer = millis() + 1000;
      Phase++;
    break;

    case 6: // Ampel 2 grün
      setzeAmpel(2, GRUEN);
      Timer = millis() + 8000;
      Phase++;
    break;

    case 7: // Ampel 2 gelb
      setzeAmpel(2, GELB);
      Timer = millis() + 2000;
      Phase = 0;
    break;

    case 10: // beide Ampeln gelb
      setzeAmpel(1, GELB);
      setzeAmpel(2, GELB);
      Timer = millis() + 1000;
      Phase = 11;
    break;

    case 11: // beide Ampeln aus
      setzeAmpel(1, AUS);
      setzeAmpel(2, AUS);
      Timer = millis() + 1000;
      Phase = 10;
    break;
  }
  
}

void setzeAmpel(byte Ampelnummer, byte Zustand)
{
  byte rotPin = 0; byte gelbPin = 0; byte gruenPin = 0;
  if(Ampelnummer == 1)
  {
    rotPin = AMPEL1ROT;
    gelbPin = AMPEL1GELB;
    gruenPin = AMPEL1GRUEN;
  }
  if(Ampelnummer == 2)
  {
    rotPin = AMPEL2ROT;
    gelbPin = AMPEL2GELB;
    gruenPin = AMPEL2GRUEN;
  }

  switch(Zustand)
  {
    case AUS:
      digitalWrite(rotPin, LOW);
      digitalWrite(gelbPin, LOW);
      digitalWrite(gruenPin, LOW);
    break;
    case GRUEN:
      digitalWrite(rotPin, LOW);
      digitalWrite(gelbPin, LOW);
      digitalWrite(gruenPin, HIGH);
    break;
    case GELB:
      digitalWrite(rotPin, LOW);
      digitalWrite(gelbPin, HIGH);
      digitalWrite(gruenPin, LOW);
    break;
    case ROTGELB:
      digitalWrite(rotPin, HIGH);
      digitalWrite(gelbPin, HIGH);
      digitalWrite(gruenPin, LOW);
    break;
    case ROT: default:
      digitalWrite(rotPin, HIGH);
      digitalWrite(gelbPin, LOW);
      digitalWrite(gruenPin, LOW);
    break;
  }
}
