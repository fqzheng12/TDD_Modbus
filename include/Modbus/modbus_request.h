#ifndef __MODBUS_REQUEST_H
#define	__MODBUS_REQUEST_H

#define	_CPPUTEST_

#include <stdlib.h>
#include <stdint.h>
#ifdef _CPPUTEST_
#include <memory.h>
#else
#include <string.h>
#endif

#define MODBUS_READ_COILS 				0x01
#define MODBUS_READ_DISCRETE_INPUTS		0x02
#define MODBUS_READ_HOLDING_REGISTERS	0x03
#define MODBUS_READ_INPUT_REGISTERS		0x04
#define MODBUS_WRITE_SINGLE_COIL		0x05
#define MODBUS_WRITE_SINGLE_REGISTER	0x06

typedef struct
{
	uint16_t function;
	uint16_t starting_add;
	uint16_t input_quantity;
}modbusRequest_ReadInputs_t;

typedef struct
{
	uint16_t function;
	uint16_t address;
	uint16_t value;
}modbusRequest_WriteSingle_t;

void* modbus_RequestCheck(uint8_t*);

#endif
