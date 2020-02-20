#include "counter.h"

MM74C94 counter = MM74C94(QD, QC, QB, QA, R01, R02);

MM74C94(int qD, int qC, int qB, int qA, int r01, int r02)
{
  // Pin assignments
  _qD = qD;
  _qC = qC;
  _qB = qB;
  _qA = qA;
  _r01 = r01;
  _r02 = r02;
}

int MM74C94::init()
{
  // Check valid pin values
  if(_qD < 0 || _qC < 0 || _qB < 0 || _qA < 0 || _r01 < 0 || _r02 < 0)
  {
    return -1;
  }

  // Setup input pins
  pinMode(_qD, INPUT);
  pinMode(_qC, INPUT);
  pinMode(_qB, INPUT);
  pinMode(_qA, INPUT);

  // Setup output pins
  pinMode(_r01, OUTPUT);
  pinMode(_r02, OUTPUT);

  clear();

  return 0;
}

int MM74C94::count()
{
  byte value = 0;
  value |= digitalRead(_qD);
  value <<= 1;
  value |= digitalRead(_qC);
  value <<= 1;
  value |= digitalRead(_qB);
  value <<= 1;
  value |= digitalRead(_qA);
  return value;
}

int MM74C94::clear()
{
  digitalWrite(_r01, HIGH);
  digitalWrite(_r02, HIGH);
  delay(1);
  digitalWrite(_r01, LOW);
  digitalWrite(_r02, LOW);
}

int initCounter();
{
    return counter.init();
}
