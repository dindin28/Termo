#include "Inputter.h"

#include "Arduino.h"

#include "Definitions.h"

Timer Inputter::input_timer_;

enum KeyPressed Inputter::GetKeyPressed(int analog_pin)
{
  enum KeyPressed return_enum = KeyPressed::NOTHING;
  if (input_timer_.check(kInputDelayMillies))
  {
    int x = analogRead(0);
    if (x < 60)
    {
      return_enum = KeyPressed::RIGHT;
      input_timer_.reset();
    }
    else if (x < 200)
    {
      return_enum = KeyPressed::UP;
      input_timer_.reset();
    }
    else if (x < 400)
    {
      return_enum = KeyPressed::DOWN;
      input_timer_.reset();
    }
    else if (x < 600)
    {
      return_enum = KeyPressed::LEFT;
      input_timer_.reset();
    }
    else if (x < 800)
    {
      return_enum = KeyPressed::SELECT;
      input_timer_.reset();
    }
  }
  return return_enum;
}
