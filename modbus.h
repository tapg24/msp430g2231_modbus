#ifndef __MODBUS_MSP430G2231_SOFTUART
#define __MODBUS_MSP430G2231_SOFTUART

#include "msp430g2231.h"
#include "settings.h"

enum {
	MODBUS_STATE_RECV_IN_PROGRESS = 0,
	MODBUS_STATE_RECV_END = 1,
	MODBUS_CRC_IN_PROGRESS,
	MODBUS_CRC_END,
	MODBUS_STATE_TRANS_IN_PROGRESS,
	MODBUS_STATE_TRANS_END,
	MODBUS_STATE_CLEAR
} modbus_state;

// request buffer
uint8_t buffer[8];

// modbus id
//uint8_t modbusId;
#define MODBUS_ID 1

/*
 Read Input Status (FC=02)
 */
//void readInputStatus();

/*
 initial function
 */
void initModbus();

/*
 dispatch requests
 */
void dispatchModbusRequest();

#endif /* #ifndef __MODBUS_MSP430G2231_SOFTUART */
