/*
 * modbus.c
 *
 *  Created on: 01 марта 2015 г.
 *      Author: pavel
 */

#include "modbus.h"
#include "softuart.h"
#include "adc10.h"

#define RECV_SIZE 8
#define SEND_SIZE 1

void initModbus() {
//	modbusId = 1;
}

void dispatchModbusRequest() {
	isReceiving = false; // Set initial values
	hasReceived = false;
//	ADCDone = false;

//	uint8_t c;
	uint8_t recvBuff[RECV_SIZE] = { 0 };
	uint8_t sendBuff[SEND_SIZE] = { 0 };
	uint8_t readBytes = 0;

	__bis_SR_register(GIE); // interrupts enabled

	while (1) {
		// Request
		//
		// HEX: 11 04 0008 0001 B298
		//
		// 11: The Slave Address (17 = 11 hex)
		// 04: The Function Code (read Analog Input Registers)
		// 0008: The Data Address of the first register requested. (30009-30001 = 8)
		// 0001: The total number of registers requested. (read 1 register)
		// B298: The CRC (cyclic redundancy check) for error checking.

		if (hasReceived) {
			uint8_t cnt = softuart_read((uint8_t*) &recvBuff, RECV_SIZE);
//			sendBuff[0] = '3';
//			sendBuff[1] = '1';
//			sendBuff[2] = '3';
//			sendBuff[3] = '1';

			sendBuff[0] = 0x00;
//			sendBuff[1] = 0x11;
//			sendBuff[2] = 0x22;
//			sendBuff[3] = 0x33;
//			sendBuff[4] = 0x44;

//			sendBuff[6] = 0x11;
//			sendBuff[5] = 0x04;
//			sendBuff[7] = 0x02;
//			sendBuff[6] = 0x00;
//			sendBuff[2] = 0x0A;
//			sendBuff[1] = 0xF8;
//			sendBuff[4] = 0x00;
//			sendBuff[3] = 0xF4;
			softuart_write((const uint8_t*) &sendBuff, SEND_SIZE);
//			if (8 == cnt) {
//				if (recvBuff[1] == 0x11) {
//					// Response
//					//
//					// 11 04 02 000A F8F4
//					//
//					// 11: The Slave Address (17 = 11 hex)
//					// 04: The Function Code (read Analog Input Registers)
//					// 02: The number of data bytes to follow (1 registers x 2 bytes each = 2 bytes)
//					// 000A: The contents of register 30009
//					// F8F4: The CRC (cyclic redundancy check).
//
//					sendBuff[1] = 0x11;
//					sendBuff[0] = 0x04;
//					sendBuff[3] = 0x02;
//					sendBuff[2] = 0x00;
//					sendBuff[5] = 0x0A;
//					sendBuff[4] = 0xF8;
//					sendBuff[7] = 0xF4;
//					sendBuff[6] = 0x00;
//					softuart_write((const uint8_t*) &sendBuff, 7);
//
//					//				recvBuff[0] = 0;
//					//				recvBuff[1] = 0;
//					//				recvBuff[2] = 0;
//					//				recvBuff[3] = 0;
//					//				recvBuff[4] = 0;
//					//				recvBuff[5] = 0;
//					//				recvBuff[6] = 0;
//				}
//			}
			memcpy(recvBuff, 0, 8);

//		if(softuart_getc(&c))
//		{
//			if(c == '\r')
//			{
//				softuart_putc('\n');
//				softuart_putc('\r');
//			}
//			else
//			{
//				softuart_putc('[');
//				softuart_putc(c);
//				softuart_putc(']');
//			}
//		}

//		if (hasReceived) // If the device has recieved a value
//		{
//			Receive();
//		}
//		if (ADCDone) // If the ADC is done with a measurement
//		{
//			ADCDone = false; // Clear flag
//			TXByte = ADCValue & 0x00FF; // Set TXByte
//			Transmit(); // Send
//			TXByte = (ADCValue >> 8); // Set TXByte to the upper 8 bits
//			TXByte = TXByte & 0x00FF;
//			Transmit();
//		}
//		if (~(hasReceived && ADCDone)) // Loop again if either flag is set
//			__bis_SR_register(CPUOFF + GIE); // LPM0, the ADC interrupt will wake the processor up.
		}
	}
}
