#ifndef WINDBOX_H
#define WINDBOX_H

#include "led.h"
#include "logging.h"
#include "reading.h"

int initModules();
int moduleStatus();
int resetDevice();
int printInfo();

#endif // WINDBOX_H
