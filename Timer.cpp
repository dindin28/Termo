#include "Timer.h"

#include "Arduino.h"

Timer::Timer()
{
  reset();
}

void Timer::reset()
{
  last_reset_ = millis();
}

bool Timer::check(unsigned long milliseconds)
{
  return (millis() - last_reset_ > milliseconds);
}
