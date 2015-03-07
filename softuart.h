/*
 * softuart.h
 *
 *  Created on: 01 марта 2015 г.
 *      Author: pavel
 */

#ifndef SOFTUART_H_
#define SOFTUART_H_

#include "msp430g2231.h"
#include "stdbool.h"
#include "settings.h"

unsigned char BitCnt; // Bit count, used when transmitting byte
unsigned int TXByte; // Value sent over UART when Transmit() is called
unsigned int RXByte; // Value recieved once hasRecieved is set

unsigned int i; // 'for' loop variable

bool isReceiving; // Status for when the device is receiving
bool hasReceived; // Lets the program know when a byte is received

/**
 * Transmits the value currently in TXByte. The function waits till it is
 * finished transmiting before it returns.
 **/
void Transmit(void);

/**
 * Handles the received byte and calls the needed functions.\
**/
void Receive(void);

/**
 * Starts the receive timer, and disables any current transmission.
 **/
//#pragma vector=PORT1_VECTOR
//__interrupt
void Port_1_ISR(void);

/**
 * Timer interrupt routine. This handles transmiting and receiving bytes.
 **/
//#pragma vector=TIMERA0_VECTOR
//__interrupt
void Timer_A_ISR(void);

#endif /* SOFTUART_H_ */
