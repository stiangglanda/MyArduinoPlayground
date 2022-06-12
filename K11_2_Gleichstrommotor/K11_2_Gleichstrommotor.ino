#define POTI 3
#define M_PWM 11
#define M_IN1 10
#define M_IN2 9

int PotiWert = 0;
byte MotorLeistung = 0;
boolean rueckwaerts = false;

void setup() {
  pinMode(M_PWM, OUTPUT);
  pinMode(M_IN1, OUTPUT);
  pinMode(M_IN1, OUTPUT);
}

void loop() {
  PotiWert = analogRead(POTI);

  if(PotiWert >= 512)
  {
    rueckwaerts = false;
    MotorLeistung = (PotiWert-512) / 2;
  }
  else
  {
    rueckwaerts = true;
    MotorLeistung = (511-PotiWert) / 2;
  } 

  if(rueckwaerts)
  {
    digitalWrite(M_IN1, HIGH);
    digitalWrite(M_IN2, LOW);
  }
  else
  {
    digitalWrite(M_IN1, LOW);
    digitalWrite(M_IN2, HIGH);    
  }

  analogWrite(M_PWM, MotorLeistung);
}
