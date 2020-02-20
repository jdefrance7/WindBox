#ifndef ANEMOMETER_H
#define ANEMOMETER_H

#include <Arduino.h>

#define ANEMOMETER_PIN A0

#define ANEMOMETER_BUFFER_SIZE 8

#define ANEMOMETER_DELAY 1

class C2192_Anemometer
{
public:
  C2192_Anemometer(int pin);
  int init();
  float windspeed();
private:
  int _pin;
};

extern C2192_Anemometer anemometer;

int initAnemometer();

#endif // C2192_ANEMOMETER_H
