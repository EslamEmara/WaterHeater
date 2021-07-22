/* 
 * File:   SEG.h
 * Author: Eslam
 *
 * Created on July 8, 2020, 7:35 PM
 */

#ifndef SEG_H
#define	SEG_H
#include <xc.h>
#include "STD_TYPES.h"

#define _XTAL_FREQ 20000000

//PIN CONFIG
#define DISP1 RA2
#define DISP2 RA3
#define DISP3 RA4
#define DISP4 RA5

#define SEG_PORT PORTD 

unsigned int seg[]={0X3F, //Hex value to display the number 0
                    0X06, //Hex value to display the number 1
                    0X5B, //Hex value to display the number 2
                    0X4F, //Hex value to display the number 3
                    0X66, //Hex value to display the number 4
                    0X6D, //Hex value to display the number 5
                    0X7C, //Hex value to display the number 6
                    0X07, //Hex value to display the number 7
                    0X7F, //Hex value to display the number 8
                    0X6F  //Hex value to display the number 9
                   }; 

//FUNCTIONS PROTOTYPES
void SEG_display (u8 number);
void SEG_blink(u8 number);
u8* convert_to_array (u8 number);
void SEG_init(void);


#endif	/* SEG_H */

