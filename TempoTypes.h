#ifndef TempoTypes_h
#define TempoTypes_h

enum class HeaterMode
{
    HeaterOff = -1,
    HeaterAuto = 0,
    HeaterOn = 1,
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

#endif