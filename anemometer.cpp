#include "anemometer.h"

bool ANEMOMETER_ENABLED = false;

AnemometerC2192 anemometer = AnemometerC2192(ANEMOMETER_PIN);

AnemometerC2192::AnemometerC2192(int pin)
{
  // Pin assignment
  _pin = pin;
}

int AnemometerC2192::init()
{
  // Check valid pin
  if(_pin < 0)
  {
    ANEMOMETER_ENABLED = false;
    return -1;
  }

  // Set Pin to Input
  pinMode(_pin, INPUT);

  ANEMOMETER_ENABLED = true;

  // Return Success
  return 0;
}

float AnemometerC2192::voltage()
{
  // Check valid pin
  if(_pin < 0)
  {
    return -1;
  }

  // Read digital voltage value
  float voltage = float(analogRead(_pin));

  // Multiply digital value by voltage reference
  voltage *= VOLTAGE_REFERENCE;

  // Divide by voltage digital resolution
  voltage /= VOLTAGE_RESOLUTION;

  // Return analog voltage
  return voltage;
}

float AnemometerC2192::windspeed()
{
  // Check valid pin
  if(_pin < 0)
  {
    return -1;
  }

  // Return windspeed in m/s
  return voltageToWindspeed(voltage());
}

float AnemometerC2192::voltageToWindspeed(float voltage)
{
  // See datasheet
  return (((voltage-0.4)/1.6)*32.4);
}

int initAnemometer()
{
  return anemometer.init();
}
