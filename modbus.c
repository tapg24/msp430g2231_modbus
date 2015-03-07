/*
 * modbus.c
 *
 *  Created on: 01 марта 2015 г.
 *      Author: pavel
 */

#include "modbus.h"
#include "softuart.h"
#include "adc10.h"

void initModbus()
{
//	modbusId = 1;
}

void dispatchModbusRequest() {
	isReceiving = false; // Set initial values
	hasReceived = false;
	ADCDone = false;
	__bis_SR_register(GIE); // interrupts enabled

	while (1) {
		if (hasReceived) // If the device has recieved a value
		{
			Receive();
		}
		if (ADCDone) // If the ADC is done with a measurement
		{
			ADCDone = false; // Clear flag
			TXByte = ADCValue & 0x00FF; // Set TXByte
			Transmit(); // Send
			TXByte = (ADCValue >> 8); // Set TXByte to the upper 8 bits
			TXByte = TXByte & 0x00FF;
			Transmit();
		}
		if (~(hasReceived && ADCDone)) // Loop again if either flag is set
			__bis_SR_register(CPUOFF + GIE); // LPM0, the ADC interrupt will wake the processor up.
	}
}
