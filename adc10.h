/*
 * adc10.h
 *
 *  Created on: 01 марта 2015 г.
 *      Author: pavel
 */

#ifndef ADC10_H_
#define ADC10_H_

#include "msp430g2231.h"
#include "stdbool.h"
#include "settings.h"

bool ADCDone; // ADC Done flag
uint16_t ADCValue; // Measured ADC Value

/**
 * Reads ADC 'chan' once using AVCC as the reference.
 **/
void Single_Measure(uint16_t);

/**
 * Reads ADC 'chan' once using an internal reference, 'ref' determines if the
 * 2.5V or 1.5V reference is used.
 **/
void Single_Measure_REF(uint16_t, uint16_t);

/**
 * ADC interrupt routine. Pulls CPU out of sleep mode for the main loop.
 **/
//#pragma vector=ADC10_VECTOR
__interrupt
void ADC10_ISR(void);

#endif /* ADC10_H_ */
