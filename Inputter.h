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
  static KeyPressed GetKeyPressed(int analog_pin);
private:
  static Timer input_timer_;
};

#endif
