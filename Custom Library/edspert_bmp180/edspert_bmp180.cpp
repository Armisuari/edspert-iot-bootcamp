#include "edspert_BMP180.h"


BMP180_esp32::BMP180_esp32(byte addr)
  : BMP180_ADDR(addr) {
}

bool BMP180_esp32::init() {
  Wire.begin(21, 22);  // SDA = 21, SCL = 22
  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(0xD0);  // Register to read the chip ID
  Wire.endTransmission();
  Wire.requestFrom(BMP180_ADDR, 1);
  if (Wire.available()) {
    uint8_t chipID = Wire.read();
    if (chipID == 0x55) {  // BMP180 chip ID is 0x55
      Serial.println("BMP180 initialized successfully.");
      readCalibrationData();
      return true;
    }
  }
  return false;
}

float BMP180_esp32::readTemp() {
  int32_t UT;
  int32_t X1, X2, B5;

  // Request temperature measurement
  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(0xF4);  // Control register
  Wire.write(0x2E);  // Temperature measurement command
  Wire.endTransmission();
  delay(5);  // Wait for conversion

  // Read raw temperature value
  UT = read16(0xF6);

  // Calculate true temperature
  X1 = ((UT - bmp_AC6) * bmp_AC5) >> 15;
  X2 = (bmp_MC << 11) / (X1 + bmp_MD);
  B5 = X1 + X2;
  float temperature = ((B5 + 8) >> 4) / 10.0;
  return temperature;
}

// Function to read pressure from the sensor
float BMP180_esp32::readPress() {
  int32_t UT, UP, B3, B5, B6, X1, X2, X3, B4;
  uint32_t B7;
  uint32_t pressure;

  // Request temperature measurement
  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(0xF4); // Control register
  Wire.write(0x2E); // Temperature measurement command
  Wire.endTransmission();
  delay(5); // Wait for conversion
  UT = read16(0xF6);
  
  // Calculate true temperature
  X1 = ((UT - bmp_AC6) * bmp_AC5) >> 15;
  X2 = (bmp_MC << 11) / (X1 + bmp_MD);
  B5 = X1 + X2;

  // Request pressure measurement
  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(0xF4); // Control register
  Wire.write(0x34); // Pressure measurement command (OSS = 0)
  Wire.endTransmission();
  delay(8); // Wait for conversion
  UP = read16(0xF6) << 8;
  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(0xF8); // Read the least significant bits
  Wire.endTransmission();
  Wire.requestFrom(BMP180_ADDR, 1);
  if (Wire.available() == 1) {
    UP |= Wire.read();
  }
  UP >>= 8;

  // Calculate true pressure
  B6 = B5 - 4000;
  X1 = (bmp_B2 * (B6 * B6 >> 12)) >> 11;
  X2 = bmp_AC2 * B6 >> 11;
  X3 = X1 + X2;
  B3 = (((bmp_AC1 * 4 + X3) << 0) + 2) >> 2;
  X1 = bmp_AC3 * B6 >> 13;
  X2 = (bmp_B1 * (B6 * B6 >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  B4 = bmp_AC4 * (unsigned long)(X3 + 32768) >> 15;
  B7 = ((unsigned long)UP - B3) * (50000 >> 0);
  if (B7 < 0x80000000) {
    pressure = (B7 * 2) / B4;
  } else {
    pressure = (B7 / B4) * 2;
  }
  X1 = (pressure >> 8) * (pressure >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * pressure) >> 16;
  pressure += (X1 + X2 + 3791) >> 4;

  return pressure;
}

// Function to read 16-bit values from the sensor
int16_t BMP180_esp32::read16(uint8_t addr) {
  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(BMP180_ADDR, 2);
  if (Wire.available() == 2) {
    return (Wire.read() << 8) | Wire.read();
  }
  return 0;
}

// Function to read calibration data from the sensor
void BMP180_esp32::readCalibrationData() {
  bmp_AC1 = read16(0xAA);
  bmp_AC2 = read16(0xAC);
  bmp_AC3 = read16(0xAE);
  bmp_AC4 = read16(0xB0);
  bmp_AC5 = read16(0xB2);
  bmp_AC6 = read16(0xB4);
  bmp_B1 = read16(0xB6);
  bmp_B2 = read16(0xB8);
  bmp_MB = read16(0xBA);
  bmp_MC = read16(0xBC);
  bmp_MD = read16(0xBE);
}
