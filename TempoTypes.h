#ifndef TempoTypes_h
#define TempoTypes_h

enum class HeaterMode
{
    HeaterAuto = 0,
    HeaterOn = 1,
    HeaterOff = 2,
};

enum class KeyPressed
{
    NOTHING = 0,
    RIGHT,
    UP,
    DOWN,
    LEFT,
    SELECT,
};

enum class SettingsLine
{
    TempLimits = 0,
    HeaterMode,
    StandByMode,
};

#endif