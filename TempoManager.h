#ifndef TempoManager_h
#define TempoManager_h

#include <LiquidCrystal.h>

#include "Inputter.h"

class TempoManager
{
public:
  TempoManager();
  void StartTempo();

private:
  void StandByWindow();
  void HeaterModeWindow();

private:
  LiquidCrystal lcd_;
  enum class HeaterMode
  {
    HeaterOff = -1,
    HeaterAuto = 0,
    HeaterOn = 1,
  } heater_mode_;
  Inputter inputter_;
  
};

#endif
