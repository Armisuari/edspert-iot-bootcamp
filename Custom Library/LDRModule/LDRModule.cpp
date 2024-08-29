#include "LDR.h"

float LDR::bacaADC(){
  adcSignal = analogRead(_pin);
  return adcSignal;
}

void LDR::begin(int resolusi){
  analogReadResolution(resolusi);
}


float LDR::readIntensitas(int mode){
  bacaADC();
  if(_type == 5){
    const float GAMMA = 0.7;
    const float RL10 = 50;
    float voltase = adcSignal / 4096. * 5;
    float resistansi = 2000 * voltase / (1-voltase / 5);
    kecerahan =pow(RL10 * 1e3 * pow(10, GAMMA) /resistansi, (1/GAMMA));
  } 
  else{}
  

  if (mode == 1){
    kecerahan = kecerahan;
  }
  else if(mode == 2){
     kecerahan = kecerahan/1000;
  }
  else{
    Serial.println("Mode yang anda masukkan salah");
  }
  return kecerahan;
}

bool LDR::readStatus(int batas){
  bool state;
  if (kecerahan <= batas){
    state = true;
  }
  else{
    state = false;
  }
  return state;
}

LDR::LDR(int pin, int type){
  _pin = pin;
  _type = type;
}
