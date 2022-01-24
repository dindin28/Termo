#ifndef Inputter_h
#define Inputter_h

#include "Timer.h"

#include "TempoTypes.h"

class Inputter
{
public:
  Inputter(int analog_pin);
  KeyPressed GetKeyPressed();

private:
  const int analog_pin_;
  Timer input_timer_;
  bool last_pressed_button_;
  unsigned long last_time_button_;
};

#endif
