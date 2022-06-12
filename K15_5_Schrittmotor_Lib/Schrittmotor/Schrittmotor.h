#ifndef Schrittmotor_h
#define Schrittmotor_h

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

#endif