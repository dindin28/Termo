#ifndef Inputter_h
#define Inputter_h

#include "Timer.h"

enum class KeyPressed
{
  NOTHING = 0,
  RIGHT,
  UP,
  DOWN,
  LEFT,
  SELECT,
};

class Inputter
{
public:
  Inputter(int analog_pin);
  KeyPressed GetKeyPressed();

private:
  const int analog_pin_;
  Timer input_timer_;
};

#endif
