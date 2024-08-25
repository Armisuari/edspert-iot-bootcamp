#include <Arduino.h>

class LDRModule{
  private:
  int _pin;
  float kecerahan;
  float adcSignal;
  public:
    LDRModule(int pin);
    float bacaADC();
    float intensitas(int mode = 1);
    bool statusLDR(int batas);
};
