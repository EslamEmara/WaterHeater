/* 
 * File:   adc.h
 * Author: Eslam
 *
 * Created on July 4, 2020, 5:29 PM
 */

#ifndef ADC_H
#define	ADC_H
#include "STD_TYPES.h"
#include "RegMap.h"

typedef enum { CH0,CH1,CH2,CH3,CH4,CH5,CH6,CH7}adc_channel_no;
//FUNCTION PROTOTYPES
void ADC_init(void);
u16 ADC_Read(adc_channel_no channel);
void ADC_SetFreq(u8 freq);

#endif	/* ADC_H */

