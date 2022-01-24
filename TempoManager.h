#ifndef TempoManager_h
#define TempoManager_h

#include <LiquidCrystal.h>

#include "Inputter.h"
#include "TempoTypes.h"
#include "Memorier.h"

class TempoManager
{
public:
  TempoManager();
  void StartTempo();

private:
  void IdleWindow();
  void SettingsWindow();
  void StandByWindow();
  void HeaterModeWindow();
  void ChangeTempWindow();

private: // Short functions-helpers
  void DisplayUpperLowerTemp(bool);
  void DisplayIdleWindow();
  void DisplaySettingsWindow(SettingsLine);

private:
  LiquidCrystal lcd_;
  HeaterMode heater_mode_;
  Inputter inputter_;
  Memorier memorier_;

  int lower_temp_;
  int upper_temp_;

  int average_temp_;
};

#endif
