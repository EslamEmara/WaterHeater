#include "adc.h"
#include "UTILS.h"
#include "xc.h"
#define _XTAL_FREQ 20000000

void ADC_init(void)
{
    SETBIT(ADCON0,0);               //ADON ENABLE
    PCFG1=1;                        //ANALOG/DIGITAL CHANNELS

}
void ADC_SetFreq(u8 freq)
{
    if (freq == 2)
    {
        CLRBIT( ADCON0 , 6);
        CLRBIT( ADCON0 , 7);
        CLRBIT( ADCON1 , 6);
    }
    else if (freq == 4)
    {
        CLRBIT( ADCON0 , 6);
        CLRBIT( ADCON0 , 7);
        SETBIT( ADCON1 , 6);
    }
    else if (freq == 8)
    {
        SETBIT( ADCON0 , 6);
        CLRBIT( ADCON0 , 7);
        CLRBIT( ADCON1 , 6);
    }
    else if (freq == 16)
    {
        SETBIT( ADCON0 , 6);
        CLRBIT( ADCON0 , 7);
        SETBIT( ADCON1 , 6);
    }
    else if (freq == 32)
    {
        CLRBIT( ADCON0 , 6);
        SETBIT( ADCON0 , 7);
        CLRBIT( ADCON1 , 6);
    }
    else if (freq == 64)
    {
        SETBIT( ADCON0 , 6);
        SETBIT( ADCON0 , 7);
        CLRBIT( ADCON1 , 6);
    }
}

u16 ADC_Read(adc_channel_no channel)
{
         ADCON0 &= 0b11000101;              //Clearing the Channel Selection Bits
         ADCON0 |= channel<<3;              //SETTING THE CHANNEL
          SETBIT( ADCON0 , 2);              //Start Conversion
          while (GETBIT(ADCON0,2));         //WAIT FOR CONVERSION
   return (((ADRESH)<<2)|(ADRESL>>6));      //READ 10 bit DATA
}
