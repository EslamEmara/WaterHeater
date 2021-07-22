/* 
 * File:   heater_fan.h
 * Author: Eslam
 *
 * Created on July 13, 2020, 11:20 PM
 */

#ifndef HEATER_FAN_H
#define	HEATER_FAN_H
#include "gpio.h"

typedef enum {ON,OFF} operating_t;

void heater_fan_init(void);
void heater_mode(operating_t mode);
void fan_mode(operating_t mode);


#endif	/* HEATER_FAN_H */

