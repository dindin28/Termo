#include "Inputter.h"

#include "Arduino.h"

#include "Definitions.h"

Inputter::Inputter(int analog_pin)
    : analog_pin_(analog_pin),
      last_pressed_button_(false),
      last_time_button_(millis())
{}

enum KeyPressed Inputter::GetKeyPressed()
{
  long delay = kInputUpperDelayMillies - kInputAcceleration * (millis() - last_time_button_);
  if(delay < kInputLowerDelayMillies)
  {
    delay = kInputLowerDelayMillies;
  }

  enum KeyPressed return_enum = KeyPressed::NOTHING;
  int x = analogRead(analog_pin_);
  if(x < 800)
  {
    if (x < 60)
    { return_enum = KeyPressed::RIGHT; }
    else if (x < 200)
    { return_enum = KeyPressed::UP; }
    else if (x < 400)
    { return_enum = KeyPressed::DOWN; }
    else if (x < 600)
    { return_enum = KeyPressed::LEFT; }
    else if (x < 800)
    { return_enum = KeyPressed::SELECT; }
    last_pressed_button_ = true;
  }
  else
  {
    if(last_pressed_button_ = true) // last time button released
    {
      last_time_button_ = millis();
    }
    last_pressed_button_ = false; 
  }
  if (input_timer_.check(delay))
  {
    input_timer_.reset();
    return return_enum;
  }
  return KeyPressed::NOTHING;
}
