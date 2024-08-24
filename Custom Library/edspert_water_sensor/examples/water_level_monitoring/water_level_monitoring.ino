#include "edspert_water_sensor.h"

#define WATER_SENSOR_PIN 35

WaterSensor waterSensor(WATER_SENSOR_PIN);

setLevelWater banjir(90, 100);
setLevelWater siaga(70, 90);
setLevelWater normal(50, 70);
setLevelWater kurang(10, 50);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  waterSensor.calMaxVal();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("raw data = %d\n percentage = %d %\n", waterSensor.readRaw(), waterSensor.getPercentage());
  
  auto monitor_level = waterSensor.monitorLevel(banjir, siaga, normal, kurang);

  Serial.printf("monitor : %d\n", (uint32_t) monitor_level);
  delay(500);
}
