#include "TempoManager.h"

#include "Arduino.h"

#include "Definitions.h"

//=====================================
// Public Functions
//=====================================

TempoManager::TempoManager()
    : lcd_(kPinRsLcd, kPinEnLcd, kPinD4Lcd, kPinD5Lcd, kPinD6Lcd, kPinD7Lcd),
      inputter_(kAnalogPinButtons),
      heater_mode_(HeaterMode::HeaterAuto)
{
    Serial.begin(kBps);

    lcd_.begin(16, 2);
    lcd_.createChar(0, kCelsiusDot);

    lower_temp_ = memorier_.ReadLowerTemp();
    upper_temp_ = memorier_.ReadUpperTemp();
    heater_mode_ = memorier_.ReadHeaterMode();
}

void TempoManager::StartTempo()
{
    ChangeTempWindow();
    HeaterModeWindow();
    StandByWindow();
}

//=====================================
// Private Functions
//=====================================

void TempoManager::StandByWindow()
{
    Serial.println("StandByWindow starting");
    lcd_.clear();
    lcd_.setCursor(0, 0);
    lcd_.print("Stand-by Mode");
    lcd_.setCursor(0, 1);
    lcd_.print("Press Select");
    while (inputter_.GetKeyPressed() != KeyPressed::SELECT)
        ;
    Serial.println("StandByWindow ending");
}

void TempoManager::HeaterModeWindow()
{
    Serial.println("HeaterModeWindow starting");
    lcd_.clear();
    lcd_.setCursor(0, 0);
    Serial.println("Here");
    Serial.println(static_cast<int>(heater_mode_));
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
            if (heater_mode_ == HeaterMode::HeaterOn)
            {
                heater_mode_ = HeaterMode::HeaterAuto;
                lcd_.setCursor(0, 0);
                lcd_.print("OFF - AUTO - ON ");
                lcd_.setCursor(0, 1);
                lcd_.print("     <-  ->     ");
            }
            else if (heater_mode_ == HeaterMode::HeaterAuto)
            {
                heater_mode_ = HeaterMode::HeaterOff;
                lcd_.setCursor(0, 0);
                lcd_.print("      OFF - AUTO");
                lcd_.setCursor(0, 1);
                lcd_.print("         ->     ");
            }
            break;
        case (KeyPressed::RIGHT):
            if (heater_mode_ == HeaterMode::HeaterOff)
            {
                heater_mode_ = HeaterMode::HeaterAuto;
                lcd_.setCursor(0, 0);
                lcd_.print("OFF - AUTO - ON ");
                lcd_.setCursor(0, 1);
                lcd_.print("     <-  ->     ");
            }
            else if (heater_mode_ == HeaterMode::HeaterAuto)
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

    memorier_.WriteHeaterMode(heater_mode_);
    Serial.println("HeaterModeWindow ending");
}

void TempoManager::ChangeTempWindow()
{
    Serial.println("ChangeTempWindow starting");
    lcd_.blink();
    DisplayUpperLowerTemp();

    KeyPressed key_pressed;
    bool is_upper_temp = true;
    lcd_.setCursor(0, 0);
    do
    {
        key_pressed = inputter_.GetKeyPressed();
        switch (key_pressed)
        {
        case (KeyPressed::UP):
            if (is_upper_temp == false)
            {
                is_upper_temp = true;
                lcd_.setCursor(0, 0);
            }
            break;
        case (KeyPressed::DOWN):
            if (is_upper_temp == true)
            {
                is_upper_temp = false;
                lcd_.setCursor(0, 1);
            }
            break;
        case (KeyPressed::RIGHT):
            if (is_upper_temp == true)
            {
                if ((upper_temp_ + 1) <= 510)
                {
                    upper_temp_++;
                }
            }
            else
            {
                if ((lower_temp_ + 2) <= 510)
                {
                    lower_temp_++;
                    if (lower_temp_ >= upper_temp_)
                    {
                        upper_temp_ = lower_temp_ + 1;
                    }
                }
            }
            DisplayUpperLowerTemp();
            (is_upper_temp) ? (lcd_.setCursor(0, 0)) : (lcd_.setCursor(0, 1));
            break;
        case (KeyPressed::LEFT):
            if (is_upper_temp == true)
            {
                if (upper_temp_ - 2 >= 0)
                {
                    upper_temp_--;
                    if (upper_temp_ <= lower_temp_)
                    {
                        lower_temp_ = upper_temp_ - 1;
                    }
                }
            }
            else
            {
                if (lower_temp_ - 1 >= 0)
                {
                    lower_temp_--;
                }
            }
            DisplayUpperLowerTemp();
            (is_upper_temp) ? (lcd_.setCursor(0, 0)) : (lcd_.setCursor(0, 1));
            break;
        }
    } while (key_pressed != KeyPressed::SELECT);

    memorier_.WriteLowerTemp(lower_temp_);
    memorier_.WriteUpperTemp(upper_temp_);
    lcd_.noBlink();
    Serial.println("ChangeTempWindow ending");
}

//=====================================
// Short functions-helpers
//=====================================

void TempoManager::DisplayUpperLowerTemp()
{
    lcd_.clear();

    // Upper temperature
    lcd_.setCursor(0, 0);
    lcd_.print("Upper: ");
    lcd_.print(upper_temp_);
    lcd_.print(' ');
    lcd_.write(uint8_t(0));
    lcd_.print('C');

    // Lower temperature
    lcd_.setCursor(0, 1);
    lcd_.print("Lower: ");
    lcd_.print(lower_temp_);
    lcd_.print(' ');
    lcd_.write(uint8_t(0));
    lcd_.print('C');
}