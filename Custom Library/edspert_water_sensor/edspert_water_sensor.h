#ifndef EDSPERT_WATER_SENSOR_H
#define EDSPERT_WATER_SENSOR_H

#include <Arduino.h>

enum levelCondition
{
  KURANG,
  NORMAL,
  SIAGA,
  BANJIR
};

class setLevelWater
{
  public:
    setLevelWater(int loVal, int hiValue)
    {
      this->loVal = loVal;
      this->hiVal = hiVal;
    }

    int loVal, hiVal;
};

class WaterSensor
{
  public:
    WaterSensor(uint8_t pin);
    uint32_t readRaw();
    void calMaxVal();
    uint32_t getPercentage();
    levelCondition monitorLevel
    (
      setLevelWater banjir,
      setLevelWater siaga,
      setLevelWater normal,
      setLevelWater kurang
    );

  private:
    uint8_t _pin;
    uint32_t maxVal;
};


#endif