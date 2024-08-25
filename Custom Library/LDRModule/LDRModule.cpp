#include "LDRModule.h"

float LDRModule::bacaADC(){
  adcSignal = analogRead(_pin);
  return adcSignal;
}


float LDRModule::intensitas(int mode){
  bacaADC();
  const float GAMMA = 0.7;
  const float RL10 = 50;
  float voltase = adcSignal / 4096. * 5;
  float resistansi = 2000 * voltase / (1-voltase / 5);
  kecerahan =pow(RL10 * 1e3 * pow(10, GAMMA) /resistansi, (1/GAMMA)); 
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

bool LDRModule::statusLDR(int batas){
  bool state;
  if (kecerahan <= batas){
    state = true;
  }
  else{
    state = false;
  }
  return state;
}

LDRModule::LDRModule(int pin){
  _pin = pin;
}