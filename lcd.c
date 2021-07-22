#include <xc.h>
#include "lcd.h"
#include "gpio.h"
#define _XTAL_FREQ 20000000

void Lcd_SetBit(u8 data_bit) //Based on the Hex value Set the Bits of the Data Lines
{
	if(data_bit& 1) 
		D4 = 1;
	else
		D4 = 0;

	if(data_bit& 2)
		D5 = 1;
	else
		D5 = 0;

	if(data_bit& 4)
		D6 = 1;
	else
		D6 = 0;

	if(data_bit& 8) 
		D7 = 1;
	else
		D7 = 0;
}

void Lcd_Cmd(u8 a)
{
	RS = 0;           
	Lcd_SetBit(a); //Incoming Hex value
	EN  = 1;         
        __delay_ms(4);
        EN  = 0;         
}

void Lcd_Clear(void)
{
	Lcd_Cmd(0); //Clear the LCD
	Lcd_Cmd(1); //Move the cursor to first position
}

void Lcd_Set_Cursor(u8 a, u8 b)
{
	u8 temp,z,y;
	if(a== 1)
	{
	  temp = 0x80 + b - 1; //80H is used to move the cursor
		z = temp>>4; //Lower 8-bits
		y = temp & 0x0F; //Upper 8-bits
		Lcd_Cmd(z); //Set Row
		Lcd_Cmd(y); //Set Column
	}
	else if(a== 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4; //Lower 8-bits
		y = temp & 0x0F; //Upper 8-bits
		Lcd_Cmd(z); //Set Row
		Lcd_Cmd(y); //Set Column
	}
}

void Lcd_init(void)
{
  GPIO_SetPortDir(&PORTD,MODE_OUT);        // LCD PINS
  GPIO_SetPinDir(&PORTE,1,MODE_OUT);       // LCD ENABLE
  GPIO_SetPinDir(&PORTE,2,MODE_OUT);       // LCD RS

  Lcd_SetBit(0x00);
  Lcd_Cmd(0x03);
	__delay_ms(5);
  Lcd_Cmd(0x03);
	__delay_ms(11);
  Lcd_Cmd(0x03); 
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x08); //Select Row 1
  Lcd_Cmd(0x00); //Clear Row 1 Display
  Lcd_Cmd(0x0C); //Select Row 2
  Lcd_Cmd(0x00); //Clear Row 2 Display
  Lcd_Cmd(0x06);
}

void Lcd_Print_Char(u8 data)  //Send 8-bits through 4-bit mode
{
   u8 Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   RS = 1;             // => RS = 1
   Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
   EN = 1;
   __delay_ms(1);
   EN = 0;
   Lcd_SetBit(Lower_Nibble); //Send Lower half
   EN = 1;
   __delay_ms(1);
   EN = 0;
}

void Lcd_Print_String(u8 *a)
{
	u16 i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
}