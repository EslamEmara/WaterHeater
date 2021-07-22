#include "heater_fan.h"

void heater_fan_init(void)
{
    GPIO_SetPinDir(&PORTC,5,MODE_OUT);      //HEATER
    GPIO_SetPinDir(&PORTC,2,MODE_OUT);      //FAN
}

void heater_mode(operating_t mode)
{
    if (mode == ON)
    {
         GPIO_SetPin(&PORTC,5);
    }
    else 
         GPIO_ClrPin(&PORTC,5);
}
void fan_mode(operating_t mode)
{
    if (mode == ON)
    {
        GPIO_SetPin(&PORTC,2);                      // FAN ON 
    }
    else 
        GPIO_ClrPin(&PORTC,2);                      // FAN ON 
}
