#ifndef Inputter_h
#define Inputter_h

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
};

#endif
