#include "SEG.h"
#include "timer0.h"
#include "STD_TYPES.h"
#include "gpio.h"
void SEG_init(void)
{
    GPIO_SetPortDir(&PORTD,MODE_OUT);        // 7SEGS DISPLAY
    GPIO_SetPinDir(&PORTA,4,MODE_OUT);    //7SEG-1 ENABLE
    GPIO_SetPinDir(&PORTA,5,MODE_OUT);    //7SEG-2 ENABLE
}
void SEG_display (u8 number)                //DISPLAY number on 7segs
{
    u8* temp = convert_to_array (number);
    DISP3 =1 ;
    SEG_PORT = seg[temp[0]];
    __delay_ms(20);
    DISP3=0;
    DISP4 =1 ;
    SEG_PORT = seg[temp[1]];
    __delay_ms(20);
    DISP4 =0;
}
void SEG_blink(u8 number)               //BLINK NUMBER FOR 1s ON 7SEGS
{

     if (timer0_count16>=(1000-(40*4)))       // 1000 ms - delays
              {
           for (int j =0;j<=4;j++)
           {
                SEG_display (number);
           }
             timer0_count16=0;

             }
}
u8* convert_to_array (u8 number)            //SPLIT NUMBER INTO DIGITS
{
         u8 temp[2];
     temp[0] = (number/10);
     temp[1] = (number - (temp[0]*10));
     return temp;
}
