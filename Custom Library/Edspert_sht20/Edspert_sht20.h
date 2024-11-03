#pragma once

#include <Arduino.h>
#include <ModbusMaster.h>

class Edspert_sht20
{
  public:
    Edspert_sht20(HardwareSerial *serial, unsigned long baudRate, uint8_t rxPin, uint8_t txPin);
    bool begin();
    float readTemperature();
    float readHumidity();

  private:
    uint8_t readSensor();
    ModbusMaster node;
    uint8_t _rxPin, _txPin;
    HardwareSerial *_serial;
    unsigned long _baudRate;
    float _temperatureValue;
    float _humidityValue;

    uint16_t data[2];
};