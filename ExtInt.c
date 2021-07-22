#include "ExtInt.h"
#include "gpio.h"
#include "timer0.h"
#include <xc.h>
#include "lcd.h"
void (*RB0_ISR)(void) = '\0';
void (*PORTB_ISR)(void) = '\0';
void (*TIMER0_ISR)(void) = '\0';


void ExtInt_init (void)                         //EXTERNAL INTERRUPT INIT
{
    GPIO_SetPinDir(&PORTB,0,MODE_IN);        // RB0 
    GPIO_SetPinDir(&PORTB,4,MODE_IN);        // RB4 
    GPIO_SetPinDir(&PORTB,5,MODE_IN);        // RB5 

    INTCON |= 0b11011000;              //ENABLE INTERRUPT ON CHANGE AND RB0 INTERRUPT
    TMR0IE=1;                           //ENABLE TMR0 OVF INTERRUPT
}
void Set_RB0_ISR(void (*Local_ISR)(void))
{
    RB0_ISR = Local_ISR;
}
void Set_PORTB_ISR(void (*Local_ISR)(void))
{
    PORTB_ISR = Local_ISR;
}
void Set_TIMER0_ISR(void (*Local_ISR)(void))
{
    TIMER0_ISR = Local_ISR;
}
/*extern void __interrupt() ISR(void)                
{
    
     u8 false_read_PORTB = PORTB; 
     if (RBIF == 1)                                  // INTERRUPT ON CHANGE PINS
     {
        PORTB_ISR();
        RBIF = 0;
     }
      if (INTF)                                  // RB0 INT
     {
              Lcd_Print_String("to adjust");

        RB0_ISR();
        INTF = 0;
     }
     if(TMR0IF)                                     // TIMER0 OVERFLOW 
     {
                       Lcd_Print_String("to adjust");

      TMR0 = 110;
      TIMER0_ISR();
      TMR0IF = 0;
     }

}*/