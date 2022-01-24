#ifndef TempoManager_h
#define TempoManager_h

#include <LiquidCrystal.h>

#include "Inputter.h"
#include "TempoTypes.h"

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
  HeaterMode heater_mode_;
  Inputter inputter_;
};

#endif
