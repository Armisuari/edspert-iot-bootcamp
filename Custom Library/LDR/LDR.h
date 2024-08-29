#include <Arduino.h>

class LDR{
  private:
  int _pin;
  int _type;
  float kecerahan;
  float adcSignal;
  public:
    LDR(int pin, int type = 5);
    void begin(int resolusi = 12);
    float bacaADC();
    float readIntensitas(int mode = 1);
    bool readStatus(int batas);
};
