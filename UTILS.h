/* 
 * File:   UTILS.h
 * Author: Eslam
 *
 * Created on July 4, 2020, 2:31 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#define SETBIT(num, bit) (num) |= (1<<bit)

#define CLRBIT(num, bit) (num) &= ~(1<<bit)

#define TOGGLEBIT(num, bit) (num) ^= (1<<bit)

#define GETBIT(num, bit) (((num)>>(bit)) & 0x01)		//((((num) & (1 << bit)) != 0) ? 1:0)

#endif	/* UTILS_H */

