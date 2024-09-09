#pragma once

#include <Arduino.h>

class Edspert_soil_moisture
{
  public:
    Edspert_soil_moisture(uint8_t dPin, uint8_t aPin);
    Edspert_soil_moisture(uint8_t aPin);
    void begin();
    bool readDigital();
    uint32_t readRaw();
    uint32_t readPercent();

  private:
    uint8_t _dPin;
    uint8_t _aPin;
};