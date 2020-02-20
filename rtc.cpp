#include "rtc.h"

// Status Flag
bool RTC_ENABLED = false;

// RTC_PCF8523 Object
RTC_PCF8523 rtc;

// RTC_PCF8523 Initialization
int initRTC()
{
  // Attempt communication with RTC_PCF8523
  if(!rtc.begin())
  {
    RTC_ENABLED = false;
    return -1;
  }

  // RTC should be initialized, run RTClib PCF8523 example if not
  if(!rtc.initialized())
  {
    RTC_ENABLED = false;
    return -1;
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  RTC_ENABLED = true;
  return 0;
}

long getTime()
{
  if(RTC_ENABLED)
  {
    return ((rtc.now()).unixtime());
  }
  return (millis()/1000);
}

String getTimestamp()
{
  if(RTC_ENABLED)
  {
    return rtc.now().timestamp(DateTime::TIMESTAMP_FULL);
  }
  return String(millis()/1000)+"s";
}
