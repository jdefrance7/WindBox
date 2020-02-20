#include "logging.h"

int logging()
{
  // Check required modules
  if(!INA260_ENABLED || (!BLUETOOTH_ENABLED && !SERIAL_ENABLED))
  {
    broadcast("\nERROR: Required modules not enabled.\n");
    return -1;
  }

  // Ask user to enter duration
  broadcast("\nINFO: Enter Duration in Seconds: \n");

  // Get duration from user
  long duration = 0;
  while(duration == 0)
  {
    duration = getLong();
  }

  // Check for invalid duration value
  if(duration <= -1)
  {
    broadcast("\nERROR: Invalid duration.\n");
    return -1;
  }

  // Let user know received duration
  broadcast("\nINFO: Duration received '"+String(duration)+"'.\n");

  // Attempt to open log file if possible
  File log;
  if(DATALOGGER_ENABLED)
  {
    broadcast("\nINFO: Attempting to open log file.\n");

    String filename;
    char charName[16];

    // Iterate through log file numbers
    for(int n = 0; n < 1000; n++)
    {
      filename = "LOG_";
      filename.concat(n);
      filename += ".txt";

      filename.toCharArray(charName, 16);

      // Next open log number
      if(!SD.exists(charName));
      {
        break;
      }
    }

    // Try to open log file
    log = SD.open(charName, FILE_WRITE);
    if(!log)
    {
      broadcast("\nERROR: Unable to open log file '"+String(log.name())+"'.\n");
      return -1;
    }
    else
    {
      // Let user know which file is being logged to
      broadcast("\nINFO: Logging to file '"+String(log.name())+"'.\n");
    }
  }
  else
  {
    // Warn user that datalogger is not connected
    broadcast("\nWARNING: Running without datalogger.\n");
  }

  // Inform user how to end logging early
  broadcast("\nINFO: Enter a number to stop recording data early.\n\n");

  // Reusable line variable
  String line;

  // Log start timestamp
  line = "START: ";
  line.concat(getTimestamp());
  logline(log, line);

  // Print data labels
  line = "TIME,WIND,REVOLUTIONS,BATTERY";
  logline(log, line);

  // Data variables
  float wind, rpm, battery;
  long revolutions = 0;
  float winds[8];
  int windex = 0;

  // Loop variables
  long start = getTime();
  long last = start;
  long now = start;

  // Anemometer timing
  long last_wind = millis();

  // Polling time loop
  while(now - start < duration)
  {
    //  Check for user input to end logging early
    if(getInt() != 0)
    {
      logline("INFO: Stop command receivied.");
      break;
    }

    // Update revolutions
    revolutions += long(counter.count());
    counter.clear();

    // Update Anemometer reading
    if(millis() - last > ANEMOMETER_DELAY)
    {
      winds[windex] = anemometer.windspeed();
      windex += 1;
      windex %= 8;
    }

    // Check elapsed time for log condition
    if(now - last > LOG_INTERVAL)
    {
      // Get data
      wind = 0;
      for(int n = 0; n < 8; n++)
      {
        wind += winds[n];
      }
      wind /= 8;

      battery = getBatteryVoltage();

      // Arrange in CSV format
      line  = String(now)+",";
      line += String(wind)+",";
      line += String(revolutions)+",";
      line += String(battery);

      // Log data
      logline(line);

      // Update last log time
      last = getTime();
    }
    // Poll current time
    now = getTime();
  }

  // Log end timestamp
  line = "END: ";
  line.concat(getTimestamp());
  logline(log, line);

  // Close log file if possible
  if(DATALOGGER_ENABLED)
  {
    log.close();

    if(log)
    {
      broadcast("\nERROR: Unable to close log.\n");
      return -1;
    }
  }

  return 0;
}
