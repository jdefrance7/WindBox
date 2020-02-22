#ifndef COUNTER_H
#define COUNTER_H

// Arduino Library
#include <Arduino.h>

#define QD 1
#define QC 2
#define QB 3
#define QA 4

#define R01 5
#define R02 6

class MM74C94
{
  public:
    MM74C94(int qD, int qC, int qB, int qA, int r01, int r02);
    int init();
    int count();
    int clear();
  private:
    int _qD;
    int _qC;
    int _qB;
    int _qA;
    int _r01;
    int _r02;
};

int initCounter();

extern bool COUNTER_ENABLED;

extern MM74C94 counter;

#endif // MM74C93_H
