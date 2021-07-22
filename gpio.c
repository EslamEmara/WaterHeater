#include "gpio.h"
#include "UTILS.h"

/* INPUT PORT MUST BE THE ADRESS OF THE PORT 
 EX : &PORTA , &PORTB
 INPUT PIN IS THE NUMBER OF THE PORT PIN FROM 0-7*/

void GPIO_SetPin(u8* port,u8 pin)                       // SET THE PIN
{
    if (pin<=7)
    SETBIT(*port , pin);
    
}
void GPIO_ClrPin( u8* port,u8 pin)                      //CLEAR THE PIN
{
    if (pin<=7)
        CLRBIT(*port, pin);
    
}

/*
 INPUT MODE OPTION : MODE_IN , MODE_OUT */
void GPIO_SetPinDir(u8* port,u8 pin,gpio_mode_t mode)       //SET PIN DIRECTION
{
    if (mode == MODE_IN)
        SETBIT( (*(volatile u8*)(port+0x80)) , pin);  //TRIS REGISTERS ADRESS= PORT +0x80
    else  
        CLRBIT( (*(volatile u8*)(port+0x80)) , pin);
}
u8 GPIO_GetPin(u8* port,u8 pin)                     //GET VALUE OF PIN 
{
    if(pin<=7)
    return (!GETBIT(*port,pin));
    
    return 0;           //IF CONDIION NOT MET
}
/*
 INPUT MODE OPTION : MODE_IN , MODE_OUT */
void GPIO_SetPortDir ( u8* port , gpio_mode_t mode)         //SET ALL PORT DIRECTION
{
    if (mode == MODE_IN)
      (*(volatile u8*)(port+0x80)) = 0xff;  //TRIS REGISTERS ADRESS= PORT +0x80
    else 
      (*(volatile u8*)(port+0x80)) = 0x00;   
}
/*void GPIOWritePins(u8* port, u8 pins, u8 gpio_data)
{
        u8 data = *port;
        data &= ~(pins);
        if (gpio_data == HIGH)
        {
            data |= (0xff & pins);
            (*(volatile u8*)(port+0x80)) = data;
        }
        else if (gpio_data == LOW)
        {
            data |= (0x00 & pins);
            (*(volatile u8*)(port+0x80)) = data;
        }
}*/