#ifndef EDSPERT_BMP180_H
#define EDSPERT_BMP180_H

#include <Arduino.h>
#include <Wire.h>

class BMP180_esp32 {
public:
  BMP180_esp32(byte addr);
  bool init();
  float readTemp();
  float readPress();

private:
  byte BMP180_ADDR;

  int16_t read16(uint8_t addr);
  void readCalibrationData();

  // Calibration values
  int16_t bmp_AC1, bmp_AC2, bmp_AC3, bmp_B1, bmp_B2, bmp_MB, bmp_MC, bmp_MD;
  uint16_t bmp_AC4, bmp_AC5, bmp_AC6;
};


#endif