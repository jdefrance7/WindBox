#ifndef BATTERY_H
#define BATTERY_H

/*
  Library to provide information about the LiPoly battery for Feather M0

  Provides:
    - Function to Read Battery Voltage (getBatteryVoltage())
    - Value to Compare Against for Low Battery (VBATLOW)
*/

// Arduino Library
#include <Arduino.h>

#define VBATPIN A7

#define VBATLOW 3.5

float getBatteryVoltage();

#endif
