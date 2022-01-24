#include "TempoManager.h"

#include "Arduino.h"

#include "Definitions.h"

//=====================================
// Public Functions
//=====================================

TempoManager::TempoManager()
    : lcd_(kPinRsLcd, kPinEnLcd, kPinD4Lcd, kPinD5Lcd, kPinD6Lcd, kPinD7Lcd),
      inputter_(kAnalogPinButtons),
      heater_mode_(HeaterMode::HeaterOff),
      average_temp_(0)
{
    Serial.begin(kBps);

    lcd_.begin(16, 2);
    lcd_.createChar(0, kCelsiusDot);

    lower_temp_ = memorier_.ReadLowerTemp();
    upper_temp_ = memorier_.ReadUpperTemp();
    //heater_mode_ = memorier_.ReadHeaterMode();
}

void TempoManager::StartTempo()
{
    IdleWindow();
}

//=====================================
// Private Functions
//=====================================

void TempoManager::IdleWindow()
{
    Timer update_window_timer;
    DisplayIdleWindow();
    while(true)
    {
        if(update_window_timer.check(kUpdateIdleWindowDelay))
        {
            DisplayIdleWindow();
            update_window_timer.reset();
        }
        if(inputter_.GetKeyPressed() == KeyPressed::SELECT)
        {
            SettingsWindow();
        }
    }
}

void TempoManager::SettingsWindow()
{
    Timer idle_timer;
    SettingsLine current_setting = SettingsLine::TempLimits;
    DisplaySettingsWindow(current_setting);
    while(idle_timer.check(kIdleTime) == false)
    {
        KeyPressed x = inputter_.GetKeyPressed();
        switch (x)
        {
        case (KeyPressed::UP):
            if(current_setting == SettingsLine::TempLimits)
            {
                current_setting = SettingsLine::StandByMode;
            } else if(current_setting == SettingsLine::StandByMode)
            {
                current_setting = SettingsLine::HeaterMode;
            } else if(current_setting == SettingsLine::HeaterMode)
            {
                current_setting = SettingsLine::TempLimits;
            }
            DisplaySettingsWindow(current_setting);
            idle_timer.reset();
            break;
        case (KeyPressed::DOWN):
            if(current_setting == SettingsLine::TempLimits)
            {
                current_setting = SettingsLine::HeaterMode;
            } else if(current_setting == SettingsLine::HeaterMode)
            {
                current_setting = SettingsLine::StandByMode;
            } else if(current_setting == SettingsLine::StandByMode)
            {
                current_setting = SettingsLine::TempLimits;
            }
            DisplaySettingsWindow(current_setting);
            idle_timer.reset();
            break;
        case (KeyPressed::SELECT):
            if(current_setting == SettingsLine::TempLimits)
            {
                ChangeTempWindow();
            } else if(current_setting == SettingsLine::HeaterMode)
            {
                HeaterModeWindow();
            } else if(current_setting == SettingsLine::StandByMode)
            {
                StandByWindow();
            }
            DisplaySettingsWindow(current_setting);
            idle_timer.reset();
            break;
        }
    }
}

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
    bool is_upper_temp = true;
    DisplayUpperLowerTemp(is_upper_temp);

    KeyPressed key_pressed;
    do
    {
        key_pressed = inputter_.GetKeyPressed();
        switch (key_pressed)
        {
        case (KeyPressed::UP):
            if (is_upper_temp == false)
            {
                is_upper_temp = true;
                DisplayUpperLowerTemp(is_upper_temp);
            }
            break;
        case (KeyPressed::DOWN):
            if (is_upper_temp == true)
            {
                is_upper_temp = false;
                DisplayUpperLowerTemp(is_upper_temp);
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
            DisplayUpperLowerTemp(is_upper_temp);
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
            DisplayUpperLowerTemp(is_upper_temp);
            break;
        }
    } while (key_pressed != KeyPressed::SELECT);

    memorier_.WriteLowerTemp(lower_temp_);
    memorier_.WriteUpperTemp(upper_temp_);
    Serial.println("ChangeTempWindow ending");
}

//=====================================
// Short functions-helpers
//=====================================

void TempoManager::DisplayUpperLowerTemp(bool is_upper_temp)
{
    lcd_.clear();

    // Upper temperature
    lcd_.setCursor(0, 0);
    lcd_.print("Upper: ");
    lcd_.print(upper_temp_);
    lcd_.print(' ');
    lcd_.write(uint8_t(0));
    lcd_.print('C');
    if(is_upper_temp)
    {
        lcd_.print(" <-");
    }

    // Lower temperature
    lcd_.setCursor(0, 1);
    lcd_.print("Lower: ");
    lcd_.print(lower_temp_);
    lcd_.print(' ');
    lcd_.write(uint8_t(0));
    lcd_.print('C');
    if(is_upper_temp == false)
    {
        lcd_.print(" <-");
    }
}

void TempoManager::DisplayIdleWindow()
{
    lcd_.clear();
    lcd_.setCursor(0, 0);
    lcd_.print("Avr temp: ");
    lcd_.print(average_temp_);
    lcd_.print(' ');
    lcd_.write(uint8_t(0));
    lcd_.print('C');
    lcd_.setCursor(0, 1);
    lcd_.print("Heater mode:");
    switch (heater_mode_)
    {
    case (HeaterMode::HeaterAuto):
        lcd_.print("Auto");
        break;
    case (HeaterMode::HeaterOff):
        lcd_.print(" Off");
        break;
    case (HeaterMode::HeaterOn):
        lcd_.print(" On");
        break;
    }
}

void TempoManager::DisplaySettingsWindow(SettingsLine line)
{
    lcd_.clear();
    lcd_.setCursor(0, 0);
    switch (line)
    {
    case (SettingsLine::TempLimits):
        lcd_.print("Temp limits <-");
        lcd_.setCursor(0, 1);
        lcd_.print("Heater mode");
        break;
    case (SettingsLine::HeaterMode):
        lcd_.print("Heater mode <-");
        lcd_.setCursor(0, 1);
        lcd_.print("Stand-by mode");
        break;
    case (SettingsLine::StandByMode):
        lcd_.print("Stand-by mode <-");
        lcd_.setCursor(0, 1);
        lcd_.print("Temp limits");
        break;
    }
}