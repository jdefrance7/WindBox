#ifndef ANEMOMETER_H
#define ANEMOMETER_H

// Arduino Library
#include <Arduino.h>

#define ANEMOMETER_PIN A0

#define VOLTAGE_REFERENCE 3.3

#define VOLTAGE_RESOLUTION 1024

class AnemometerC2192
{
public:
  AnemometerC2192(int pin);
  int init();
  float voltage();
  float voltageToWindspeed(float voltage);
  float windspeed();
private:
  int _pin;
};

extern bool ANEMOMETER_ENABLED;

extern AnemometerC2192 anemometer;

int initAnemometer();

#endif // AnemometerC2192_H
