#include "Inputter.h"

#include "Arduino.h"

#include "Definitions.h"

Inputter::Inputter(int analog_pin)
    : analog_pin_(analog_pin)
{
}

enum KeyPressed Inputter::GetKeyPressed()
{
  enum KeyPressed return_enum = KeyPressed::NOTHING;
  if (input_timer_.check(kInputDelayMillies))
  {
    int x = analogRead(analog_pin_);
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
