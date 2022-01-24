#ifndef Memorier_h
#define Memorier_h

#include "TempoTypes.h"

class Memorier
{
public:
    void WriteHeaterMode(HeaterMode);
    HeaterMode ReadHeaterMode();

    void WriteUpperTemp(int);
    int ReadUpperTemp();

    void WriteLowerTemp(int);
    int ReadLowerTemp();

private:
    const int kHeaterModeIter = 0;
    const int kUpperTempIter = 1;
    const int kLowerTempIter = 3;
};

#endif
