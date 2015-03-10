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

uint8_t BitCnt; // Bit count, used when transmitting byte
//uint16_t TXByte; // Value sent over UART when Transmit() is called
char TXByte; // Value sent over UART when Transmit() is called
//uint16_t RXByte; // Value recieved once hasRecieved is set
char RXByte; // Value recieved once hasRecieved is set

uint8_t i; // 'for' loop variable

bool isReceiving; // Status for when the device is receiving
bool hasReceived; // Lets the program know when a byte is received
bool isTimeout;

/**
 * Transmits the value currently in TXByte. The function waits till it is
 * finished transmiting before it returns.
 **/
//void Transmit(void);

/**
 * Handles the received byte and calls the needed functions.\
**/
//void Receive(void);

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
void Timer_A0_ISR(void);

bool softuart_getc(uint16_t *c);
void softuart_putc(const uint8_t c);

void softuart_puts(const uint8_t *str);
void softuart_read(uint8_t *buf, uint8_t bufSize);
void softuart_write(const uint8_t *buf, uint8_t bufSize);

#endif /* SOFTUART_H_ */
