/* 
 * File:   RegMap.h
 * Author: Eslam
 *
 * Created on July 4, 2020, 2:33 PM
 */

#ifndef REGMAP_H
#define	REGMAP_H

#include "STD_TYPES.h"

//gpio regs
#define PORTA_ADRESS               0x05
#define TRISA_ADRESS               0x85
#define PORTB_ADRESS               0x06
#define TRISB_ADRESS               0x86
#define PORTC_ADRESS               0x07
#define TRISC_ADRESS               0x87
#define PORTD_ADRESS               0x08
#define TRISD_ADRESS               0x88
#define PORTE_ADRESS               0x09
#define TRISE_ADRESS               0x89

//adc regs
#define ADCON0_ADRESS              0x1F
#define ADCON1_ADRESS              0x9F
//#define ADCON2_ADRESS              0x1F

#define ADRESH_ADRESS               0x1E
#define ADRESL_ADRESS                0x9E

#endif	/* REGMAP_H */

