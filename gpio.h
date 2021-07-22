/* 
 * File:   gpio.h
 * Author: Eslam
 *
 * Created on July 4, 2020, 2:09 PM
 */
#ifndef GPIO_H
#define	GPIO_H
#include "gpio.h"
#include "RegMap.h"
#include "STD_TYPES.h"
#include <xc.h>

typedef enum {  MODE_OUT = 0,
                MODE_IN = 1 } gpio_mode_t;

//typedef enum {HIGH =0xff,LOW=0x00} gpio_data_t;

//FUNCTIONS PROTOTYPES
void GPIO_SetPin(u8* port,u8 pin);
void GPIO_ClrPin(u8* port,u8 pin);
void GPIO_SetPinDir(u8* port,u8 pin,gpio_mode_t mode);
u8 GPIO_GetPin(u8* port,u8 pin);
void GPIO_SetPortDir ( u8* port , gpio_mode_t mode);
//void GPIOWritePins(u8* port, u8 pins, u8 gpio_data);



#endif	/* GPIO_H */

