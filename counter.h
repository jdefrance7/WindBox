#ifndef COUNTER_H
#define COUNTER_H

#include <Arduino.h>

class MM74C94
{
  public:
    MM74C94(int qD, int qC, int qB, int qA, int r01, int r02);
    int init();
    byte count();
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

extern MM74C94 counter;

#endig // MM74C93_H
