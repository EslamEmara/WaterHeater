/* 
 * File:   i2c.h
 * Author: Eslam
 *
 * Created on July 9, 2020, 10:58 PM
 */

#ifndef I2C_H
#define	I2C_H
#include <xc.h>
#define _XTAL_FREQ 20000000

void I2C_Initialize(const unsigned long feq_K); //Begin IIC as master
void I2C_Hold();
void I2C_Begin();
void I2C_Begin();
void I2C_Write(unsigned data);
unsigned short I2C_Read(unsigned short ack);
void Write_Byte_To_24LC64_EEPROM(unsigned int Address, unsigned char DataByte);




#define ICLK PORTCbits.RC3

#define IDAT PORTCbits.RC4

#define TIDAT TRISCbits.TRISC4



void i2c_init(void);

void i2c_start(void);

void i2c_stop(void);

void i2c_wb(unsigned char val);

unsigned char i2c_rb(unsigned char ack);

void i2c_acktst(unsigned char val);

#endif	/* I2C_H */

