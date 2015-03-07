
#include "settings.h"
#include "adc10.h"
#include "softuart.h"
#include "modbus.h"

//struct Settings settings;
//settings.TXD_PIN = BIT1;

void main(void) {

	settings.SOFTUART_TXD_PIN = BIT1;
	settings.SOFTUART_RXD_PIN = BIT2;

	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	BCSCTL1 = CALBC1_1MHZ; // Set range
	DCOCTL = CALDCO_1MHZ; // SMCLK = DCO = 1MHz

	P1SEL |= settings.SOFTUART_TXD_PIN; // Connected TXD to timer pin
	P1DIR |= settings.SOFTUART_TXD_PIN;

	P1IES |= settings.SOFTUART_RXD_PIN; // RXD Hi/lo edge interrupt
	P1IFG &= ~settings.SOFTUART_RXD_PIN; // Clear RXD (flag) before enabling interrupt
	P1IE |= settings.SOFTUART_RXD_PIN; // Enable RXD interrupt

	//P1DIR |= BIT0;
	//P1OUT &= ~BIT0; // Turn off LED at P1.0

	initModbus();
	dispatchModbusRequest();
}
