#include <LiquidCrystal.h>
#include <EEPROM.h>

#include "TempoManager.h"
#include "Memorier.h"

void setup()
{
  Serial.begin(9600);
  TempoManager tempo;
  Memorier memor;
  for(int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
  }
  memor.WriteHeaterMode(HeaterMode::HeaterOn);
  memor.WriteUpperTemp(256);
  Serial.println(memor.ReadUpperTemp());
  for(int i = 0; i < EEPROM.length(); i++)
  {
    Serial.print(i + 1);
    Serial.print(':');
    Serial.println(EEPROM.read(i));
  }
  tempo.StartTempo();
}

void loop()
{}
