#include "Edspert_sht20.h"

Edspert_sht20::Edspert_sht20(HardwareSerial *serial, unsigned long baudRate, uint8_t rxPin, uint8_t txPin) {
  _serial = serial;
  _baudRate = baudRate;
  _rxPin = rxPin;
  _txPin = txPin;
}

bool Edspert_sht20::begin() {
  _serial->begin(_baudRate, SERIAL_8N1, _rxPin, _txPin);
  node.begin(1, *_serial);
  return true;
}

uint8_t Edspert_sht20::readSensor() {
  uint8_t result = node.readInputRegisters(0x0001, 2);  // 0x001 - 0x002

  if (result == node.ku8MBSuccess) {
    data[0] = node.getResponseBuffer(0);
    data[1] = node.getResponseBuffer(1);

    _temperatureValue = data[0] / 10.0;
    _humidityValue = data[1] / 10.0;
  }

  return result;
}

float Edspert_sht20::readTemperature() {
  if (readSensor() == node.ku8MBSuccess) {
    return _temperatureValue;
  }

  return NAN;
}

float Edspert_sht20::readHumidity() {
  if (readSensor() == node.ku8MBSuccess) {
    return _humidityValue;
  }

  return NAN;
}