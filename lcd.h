/* 
 * File:   lcd.h
 * Author: Eslam
 *
 * Created on July 4, 2020, 6:40 PM
 */

#ifndef LCD_H
#define	LCD_H
#include <xc.h>
#include "STD_TYPES.h"
//PIN CONFIGURATIONS
#define RS RE2
#define EN RE1
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

//FUNCTIONS PROTOTYPES
void Lcd_SetBit(u8 data_bit); 
void Lcd_Cmd(u8 a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(u8 a, u8 b);
void Lcd_init(void);
void Lcd_Print_Char(u8 data);  
void Lcd_Print_String(u8 *a);

#endif	/* LCD_H */

