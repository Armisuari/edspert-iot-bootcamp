#include <edspert_BMP180.h>

#define BMP180_ADDR 0x77

BMP180_esp32 sensor(BMP180_ADDR);

void setup()
{
  Serial.begin(115200);
  sensor.init();
}

void loop()
{
  Serial.printf("temperature: %.2f C\n pressure: %.2f Pa\n", sensor.readTemp(), sensor.readPress());
  delay(1000);
}

