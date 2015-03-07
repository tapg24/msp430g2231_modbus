/*
 * softuart.c
 *
 *  Created on: 01 марта 2015 г.
 *      Author: pavel
 */

#include "settings.h"
#include "softuart.h"
#include "adc10.h"

/**
 * Handles the received byte and calls the needed functions.\
**/
void Receive() {
	hasReceived = false; // Clear the flag
	switch (RXByte) // Switch depending on command value received
	{
	case TEST_SPEED:
		P1OUT |= BIT0; // Turn on LED while testing
		for (i = 0; i != 0x100; i++) // Loop 256 times
				{
			TXByte = i; // Sends the counter as if it were a 16 bit value
			Transmit();
			TXByte = 0;
			Transmit();
		}
		P1OUT &= ~BIT0; // Turn off the LED
		break;
	case M_A3:
		Single_Measure(INCH_3); // Reads A3 only once
		break;
	case M_TEMP:
		Single_Measure_REF(INCH_10, 0); // Reads the temperature sensor once
		break;
	case M_VCC:
		Single_Measure_REF(INCH_11, REF2_5V); // Reads VCC once (VCC/2 internally)
		break;
	default:
		;
	}
}

/**
 * Transmits the value currently in TXByte. The function waits till it is
 * finished transmiting before it returns.
 **/
void Transmit() {
	while (isReceiving)
		; // Wait for RX completion
	TXByte |= 0x100; // Add stop bit to TXByte (which is logical 1)
	TXByte = TXByte << 1; // Add start bit (which is logical 0)
	BitCnt = 0xA; // Load Bit counter, 8 bits + ST/SP

	CCTL0 = OUT; // TXD Idle as Mark
	TACTL = TASSEL_2 + MC_2; // SMCLK, continuous mode
	CCR0 = TAR; // Initialize compare register
	CCR0 += BIT_TIME; // Set time till first bit
	CCTL0 = CCIS0 + OUTMOD0 + CCIE; // Set signal, intial value, enable interrupts
	while ( CCTL0 & CCIE)
		; // Wait for previous TX completion
}

/**
 * Starts the receive timer, and disables any current transmission.
 **/
#pragma vector=PORT1_VECTOR
__interrupt
void Port_1_ISR(void) {
	isReceiving = true;
	P1IE &= ~settings.SOFTUART_RXD_PIN; // Disable RXD interrupt
	P1IFG &= ~settings.SOFTUART_RXD_PIN; // Clear RXD IFG (interrupt flag)
	TACTL = TASSEL_2 + MC_2; // SMCLK, continuous mode
	CCR0 = TAR; // Initialize compare register
	CCR0 += HALF_BIT_TIME; // Set time till first bit
	CCTL0 = OUTMOD1 + CCIE; // Dissable TX and enable interrupts
	RXByte = 0; // Initialize RXByte
	BitCnt = 0x9; // Load Bit counter, 8 bits + ST
}

/**
 * Timer interrupt routine. This handles transmiting and receiving bytes.
 **/
#pragma vector=TIMERA0_VECTOR
__interrupt
void Timer_A_ISR(void) {
	if (!isReceiving) {
		CCR0 += BIT_TIME; // Add Offset to CCR0
		if (BitCnt == 0) // If all bits TXed
				{
			TACTL = TASSEL_2; // SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE; // Disable interrupt
		} else {
			CCTL0 |= OUTMOD2; // Set TX bit to 0
			if (TXByte & 0x01)
				CCTL0 &= ~ OUTMOD2; // If it should be 1, set it to 1
			TXByte = TXByte >> 1;
			BitCnt--;
		}
	} else {
		CCR0 += BIT_TIME; // Add Offset to CCR0
		if (BitCnt == 0) {
			TACTL = TASSEL_2; // SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE; // Disable interrupt
			isReceiving = false;
			P1IFG &= ~settings.SOFTUART_RXD_PIN; // clear RXD IFG (interrupt flag)
			P1IE |= settings.SOFTUART_RXD_PIN; // enabled RXD interrupt
			if ((RXByte & 0x201) == 0x200) // Validate the start and stop bits are correct
					{
				RXByte = RXByte >> 1; // Remove start bit
				RXByte &= 0xFF; // Remove stop bit
				hasReceived = true;
			}
			__bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues
		} else {
			if ((P1IN & settings.SOFTUART_RXD_PIN) == settings.SOFTUART_RXD_PIN) // If bit is set?
				RXByte |= 0x400; // Set the value in the RXByte
			RXByte = RXByte >> 1; // Shift the bits down
			BitCnt--;
		}
	}
}

//bool uart_getc(uint8_t *c) {
//	if (!hasReceived)
//	{
//		return false;
//	}
//	*c = RXByte;
//	hasReceived = false;
//	return true;
//}
//void uart_putc(uint8_t c) {
//	TXByte = c;
//	while (isReceiving)
//		; // Wait for RX completion
//	CCTL0 = OUT; // TXD Idle as Mark
//	TACTL = TASSEL_2 + MC_2; // SMCLK, continuous mode
//	BitCnt = 0xA; // Load Bit counter, 8 bits + ST/SP
//	CCR0 = TAR; // Initialize compare register
//	CCR0 += BIT_TIME; // Set time till first bit
//	TXByte |= 0x100; // Add stop bit to TXByte (which is logical 1)
//	TXByte = TXByte << 1; // Add start bit (which is logical 0)
//	CCTL0 = CCIS_0 + OUTMOD_0 + CCIE + OUT; // Set signal, intial value, enable interrupts
//	while ( CCTL0 & CCIE)
//		; // Wait for previous TX completion
//}
//void uart_puts(const char *str)
//{
//	if (*str != 0)
//		uart_putc(*str++);
//	while (*str != 0)
//		uart_putc(*str++);
//}
/**
 * ISR for RXD
 */
//interrupt(PORT1_VECTOR) PORT1_ISR(void)
//{
//	isReceiving = true;
//	P1IE &= ~settings.SOFTUART_RXD_PIN; // Disable RXD interrupt
//	P1IFG &= ~settings.SOFTUART_RXD_PIN;// Clear RXD IFG (interrupt flag)
//	TACTL = TASSEL_2 + MC_2;// SMCLK, continuous mode
//	CCR0 = TAR;// Initialize compare register
//	CCR0 += HALF_BIT_TIME;// Set time till first bit
//	CCTL0 = OUTMOD_1 + CCIE;// Disable TX and enable interrupts
//	RXByte = 0;// Initialize RXByte
//	bitCount = 9;// Load Bit counter, 8 bits + start bit
//}
