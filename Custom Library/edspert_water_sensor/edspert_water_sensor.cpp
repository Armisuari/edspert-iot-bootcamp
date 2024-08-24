#include "edspert_water_sensor.h"

WaterSensor::WaterSensor(uint8_t pin)
: _pin(pin)
{
}

uint32_t WaterSensor::readRaw()
{
  return analogRead(_pin);
}

void WaterSensor::calMaxVal()
{
  Serial.println("[WaterSensor] put the sensor to maximum sensing limit !");
  delay(2000);
  Serial.println("[WaterSensor] wait for a few second...");
  delay(3000);
  maxVal = readRaw();
  Serial.printf("[WaterSensor] maxVal = %d\n", maxVal);
  Serial.println("[WaterSensor] calibration done.");
}

uint32_t WaterSensor::getPercentage()
{
  return map(readRaw(), 0, maxVal, 0, 100);
}

levelCondition WaterSensor::monitorLevel
(
  setLevelWater banjir,
  setLevelWater siaga,
  setLevelWater normal,
  setLevelWater kurang
)
{
  if (getPercentage() >= banjir.loVal /*&& getPercentage() <= banjir.hiVal*/)
  {
    Serial.println("[WaterSensor] Banjir");
    return BANJIR;
  }
  else if (getPercentage() >= siaga.loVal && getPercentage() <= (siaga.hiVal - 1))
  {
    Serial.println("[WaterSensor] Siaga");
    return SIAGA;
  }
  else if (getPercentage() >= normal.loVal && getPercentage() <= (normal.hiVal - 1))
  {
    Serial.println("[WaterSensor] Normal");
    return NORMAL;
  }
  else if (getPercentage() > 0 && getPercentage() <= kurang.hiVal)
  {
    Serial.println("[WaterSensor] Kurang");
    return KURANG;
  }
}