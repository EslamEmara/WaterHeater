/* 
 * File:   timer0.h
 * Author: Eslam
 *
 * Created on July 8, 2020, 8:53 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H
#include "STD_TYPES.h"
#include <xc.h>

#define _XTAL_FREQ 20000000

//counter variable to hold the count
extern u16 timer0_count16 = 0;
typedef enum { PRE2 , PRE4 , PRE8 , PRE16 , PRE32,PRE64,PRE128,PRE256} timer_prescalar_t;

//FUNCTION PROTOYPE
void timer0_init(timer_prescalar_t prescalar,u8 delay_ms);
void timer0_SetPreScalar(timer_prescalar_t prescalar);
#endif	/* TIMER0_H */

