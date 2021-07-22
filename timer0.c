
#include "timer0.h"
/* INITIALIZE TIMER WITH SELECTED PRESCALER AND DESIRABLE DELAY 
 INPUTS : OPTIONS FOR PRESCALER : PRE2 ,PRE4 ... PRE256
 */
void timer0_init(timer_prescalar_t prescalar,u8 delay_ms)
{   
    u8 local_prescalar = 0;
    if (prescalar == PRE2)
        local_prescalar = 2;
    else if (prescalar == PRE4)
        local_prescalar = 4;
    else if (prescalar == PRE8)
        local_prescalar = 8;
    else if (prescalar == PRE16)
        local_prescalar = 16;
    else if (prescalar == PRE32)
        local_prescalar = 32;
    else if (prescalar == PRE64)
        local_prescalar = 64;
    else if (prescalar == PRE128)
        local_prescalar = 128;
    else if (prescalar == PRE256)
        local_prescalar = 256;
    
    OPTION_REG = 0x00;
     timer0_SetPreScalar(prescalar);
    //to delay 1ms ,, tmr0 = 256-((1ms * 20Mhz)/(32*4));
    TMR0 = ( 256 - (float)( (float)( (float)(delay_ms/1000) * _XTAL_FREQ) /(local_prescalar*4) ) ) + 1;
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
}
void timer0_SetPreScalar(timer_prescalar_t prescalar)
{
    OPTION_REG |= prescalar ;
}