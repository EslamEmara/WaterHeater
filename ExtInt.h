/* 
 * File:   ExtInt.h
 * Author: Eslam
 *
 * Created on July 14, 2020, 8:35 PM
 */

#ifndef EXTINT_H
#define	EXTINT_H

void ExtInt_init (void);                        //EXTERNAL INTERRUPT INIT
void Set_RB0_ISR(void (*Local_ISR)(void));
void Set_PORTB_ISR(void (*Local_ISR)(void));
void Set_TIMER0_ISR(void (*Local_ISR)(void));
//extern void __interrupt () ISR(void);
void (*RB0_ISR)(void);
void (*PORTB_ISR)(void);
void (*TIMER0_ISR)(void);


#endif	/* EXTINT_H */

