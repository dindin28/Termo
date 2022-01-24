#include "TempoManager.h"

#include "Definitions.h"

TempoManager::TempoManager()
 : lcd_(kPinRsLcd, kPinEnLcd, kPinD4Lcd, kPinD5Lcd, kPinD6Lcd, kPinD7Lcd),
   inputter_(kAnalogPinButtons),
   heater_mode_(HeaterMode::HeaterAuto)
{
    lcd_.begin(16, 2);
    lcd_.createChar(0, kCelsiusDot);
}

void TempoManager::StandByWindow()
{
    lcd_.clear();
    lcd_.setCursor(0, 0);
    lcd_.print("Stand-by Mode");
    lcd_.setCursor(0, 1);
    lcd_.print("Press Select");
    while(inputter_.GetKeyPressed() != KeyPressed::SELECT);
}

void TempoManager::HeaterModeWindow()
{
    lcd_.clear();
    lcd_.setCursor(0, 0);
    switch (heater_mode_)
    {
    case (HeaterMode::HeaterOff):
        lcd_.print("      OFF - AUTO");
        lcd_.setCursor(0, 1);
        lcd_.print("         ->     ");
        break;
    case (HeaterMode::HeaterAuto):
        lcd_.print("OFF - AUTO - ON ");
        lcd_.setCursor(0, 1);
        lcd_.print("     <-  ->     ");
        break;
    case (HeaterMode::HeaterOn):
        lcd_.print("AUTO - ON       ");
        lcd_.setCursor(0, 1);
        lcd_.print("     <-         ");
        break;
    }
    KeyPressed pressed_key;
    do
    {
        pressed_key = inputter_.GetKeyPressed();
        switch (pressed_key)
        {
        case (KeyPressed::LEFT):
            if(heater_mode_ == HeaterMode::HeaterOn)
            {
                heater_mode_ = HeaterMode::HeaterAuto;
                lcd_.setCursor(0, 0);
                lcd_.print("OFF - AUTO - ON ");
                lcd_.setCursor(0, 1);
                lcd_.print("     <-  ->     ");
            } else if (heater_mode_ == HeaterMode::HeaterAuto)
            {
                heater_mode_ = HeaterMode::HeaterOff;
                lcd_.setCursor(0, 0);
                lcd_.print("      OFF - AUTO");
                lcd_.setCursor(0, 1);
                lcd_.print("         ->     ");
            }
            break;
        case (KeyPressed::RIGHT):
            if(heater_mode_ == HeaterMode::HeaterOff)
            {
                heater_mode_ = HeaterMode::HeaterAuto;
                lcd_.setCursor(0, 0);
                lcd_.print("OFF - AUTO - ON ");
                lcd_.setCursor(0, 1);
                lcd_.print("     <-  ->     ");
            } else if (heater_mode_ == HeaterMode::HeaterAuto)
            {
                heater_mode_ = HeaterMode::HeaterOn;
                lcd_.setCursor(0, 0);
                lcd_.print("AUTO - ON       ");
                lcd_.setCursor(0, 1);
                lcd_.print("     <-         ");
            }
            break;
        }
    } while (pressed_key != KeyPressed::SELECT);
    
    
}

void TempoManager::StartTempo()
{
    HeaterModeWindow();
    StandByWindow();
}