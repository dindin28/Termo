#include "Memorier.h"

#include <EEPROM.h>

//=============
// Heater mode
//=============
void Memorier::WriteHeaterMode(HeaterMode heater)
{
    EEPROM.write(kHeaterModeIter, static_cast<uint8_t>(heater));
}

HeaterMode Memorier::ReadHeaterMode()
{
    return static_cast<HeaterMode>(EEPROM.read(kHeaterModeIter));
}

//===================
// Upper temperature
//===================
void Memorier::WriteUpperTemp(int upper_temp)
{
    if (upper_temp <= 255)
    {
        EEPROM.write(kUpperTempIter, upper_temp);
        EEPROM.write(kUpperTempIter + 1, 0);
    }
    else
    {
        EEPROM.write(kUpperTempIter, 255);
        EEPROM.write(kUpperTempIter + 1, upper_temp - 255);
    }
}

int Memorier::ReadUpperTemp()
{
    int return_value = 0;

    return_value += EEPROM.read(kUpperTempIter);
    return_value += EEPROM.read(kUpperTempIter + 1);

    return return_value;
}

//===================
// Lower temperature
//===================

void Memorier::WriteLowerTemp(int lower_temp)
{
    if (lower_temp <= 255)
    {
        EEPROM.write(kLowerTempIter, lower_temp);
        EEPROM.write(kLowerTempIter + 1, 0);
    }
    else
    {
        EEPROM.write(kLowerTempIter, 255);
        EEPROM.write(kLowerTempIter + 1, lower_temp - 255);
    }
}

int Memorier::ReadLowerTemp()
{
    int return_value = 0;

    return_value += EEPROM.read(kLowerTempIter);
    return_value += EEPROM.read(kLowerTempIter + 1);

    return return_value;
}