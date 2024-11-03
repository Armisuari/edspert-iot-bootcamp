#include "Edspert_soil_moisture.h"

Edspert_soil_moisture::Edspert_soil_moisture(uint8_t dPin, uint8_t aPin) : _dPin(dPin), _aPin(aPin)
{
}

Edspert_soil_moisture::Edspert_soil_moisture(uint8_t aPin) : _aPin(aPin)
{
}

void Edspert_soil_moisture::begin()
{
  pinMode(_dPin, INPUT);
}

bool Edspert_soil_moisture::readDigital()
{
  return digitalRead(_dPin);
}

uint32_t Edspert_soil_moisture::readRaw()
{
  return analogRead(_aPin);
}

uint32_t Edspert_soil_moisture::readPercent()
{
  uint32_t value;
  return map(value, 0, 4096, 0, 100);
}