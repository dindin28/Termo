#include <LiquidCrystal.h>

#include "Inputter.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Electropeak.com");
  lcd.setCursor(0, 1);
  lcd.print("Press Key:");
  Serial.begin(9600);
  lcd.scrollDisplayLeft();
  lcd.scrollDisplayRight();
}

void loop()
{
  KeyPressed x = Inputter::GetKeyPressed(0);
  if (x != KeyPressed::NOTHING)
  {
    lcd.setCursor(10, 1);
    switch (x)
    {
    case (KeyPressed::UP):
      lcd.print("Up    ");
      break;
    case (KeyPressed::RIGHT):
      lcd.print("Right ");
      break;
    case (KeyPressed::DOWN):
      lcd.print("Down  ");
      break;
    case (KeyPressed::LEFT):
      lcd.print("Left  ");
      break;
    case (KeyPressed::SELECT):
      lcd.print("Select");
      break;
    }
  }
}
