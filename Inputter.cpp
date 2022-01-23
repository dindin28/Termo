#include "Inputter.h"

#include "Arduino.h"

enum KeyPressed Inputter::GetKeyPressed(int analog_pin)
{
  enum KeyPressed return_enum = KeyPressed::NOTHING;
  int x = analogRead(0);
  if (x < 60)
  {
    return_enum = KeyPressed::RIGHT;
  }
  else if (x < 200)
  {
    return_enum = KeyPressed::UP;
  }
  else if (x < 400)
  {
    return_enum = KeyPressed::DOWN;
  }
  else if (x < 600)
  {
    return_enum = KeyPressed::LEFT;
  }
  else if (x < 800)
  {
    return_enum = KeyPressed::SELECT;
  }

  return return_enum;
}
