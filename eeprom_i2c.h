/* 
 * File:   eeprom.h
 * Author: Eslam
 *
 * Created on July 10, 2020, 12:06 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0

void I2C_Master_Init(const unsigned long baud);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Master_Write(unsigned char);
unsigned char I2C_Read_Byte(void);
//---[ EEPROM Routines ]---
void EEPROM_Write(unsigned char add, unsigned char data);
unsigned char EEPROM_Read(unsigned char add);


#endif	/* EEPROM_H */

