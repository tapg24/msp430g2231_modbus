/*
 * settings.h
 *
 *  Created on: 01 марта 2015 г.
 *      Author: pavel
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "msp430g2231.h"
#include <stdint.h>
#include "stdbool.h"

// CPU

// SOFTUART
#define	TXD	BIT1 // TXD on P1.1
#define	RXD	BIT2 // RXD on P1.2

#define BAUD_RATE 9600
#define	BIT_TIME	(1000000 / 9600) // 9600 Baud, SMCLK=1MHz (1MHz/9600)=104
#define	HALF_BIT_TIME	(BIT_TIME / 2) // Time for half a bit.

// ASCII values for the commands
#define	TEST_SPEED	0x31
#define	M_A3	0x32
//#define STREAM 0x33
//#define STOP 0x34
#define	M_TEMP	0x35
#define	M_VCC	0x36

// ADC10

// initial struct
struct Settings
{
	uint32_t SOFTUART_TXD_PIN;
	uint32_t SOFTUART_RXD_PIN;
} settings;


#endif /* SETTINGS_H_ */
