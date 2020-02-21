#ifndef LOGGING_H
#define LOGGING_H

/*
  Library to Handle Logging Functionality
*/

// Project Libraries
#include "battery.h"
#include "timing.h"
#include "anemometer.h"
#include "counter.h"
#include "streams.h"

// Number of Seconds Between Log Entries
#define LOG_INTERVAL 5

// Logs Data for Specified Duration
int logging();

// Buffer size for running average calculations of windspeed
#define AVERAGE_BUFSIZE 8

// Special class for storing float values and getting average
class averageFloatBuffer
{
public:
  averageFloat()
  {
    _index = 0;
    _empty = true;
    _full = false;
  }
  int add(float value)
  {
    _buf[_index++] = value;
    _index %= AVERAGE_BUFSIZE;
    _empty = false;
    if(_index == 0){_full = true;}
    return 0;
  }
  int clear()
  {
    for(int n = 0; n < AVERAGE_BUFSIZE; n++){_buf[n] = 0;}
    _empty = true;
    _full = false;
    _index = 0;
    return 0;
  }
  float average()
  {
    int size;
    if(_full){size = AVERAGE_BUFSIZE;}
    else if(_empty){return -1;}
    else {size = _index;}
    float total = 0;
    for(int n = 0; n < size; n++){total += _buf[n];}
    return total/size;
  }
private:
  bool _empty;
  bool _full;
  int _index;
  float _buf[AVERAGE_BUFSIZE];
};

#endif // LOGGING_H
