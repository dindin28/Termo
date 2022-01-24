#ifndef Definitions_h
#define Definitions_h

//================
// Inputter class
//================
const unsigned long kInputDelayMillies = 200;

//====================
// TempoManager class
//====================
const int kPinRsLcd = 8;
const int kPinEnLcd = 9;
const int kPinD4Lcd = 4;
const int kPinD5Lcd = 5; 
const int kPinD6Lcd = 6;
const int kPinD7Lcd = 7;

const int kAnalogPinButtons = 0;

//=======
// Extra
//=======
const uint8_t kCelsiusDot[8] =
{
0b00000,
0b00110,
0b00110,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};

#endif
