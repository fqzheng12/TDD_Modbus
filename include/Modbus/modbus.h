#ifndef __MODBUS_H
#define	__MODBUS_H

#define	_CPPUTEST_

#include <stdlib.h>
#include <stdint.h>
#ifdef _CPPUTEST_
#include <memory.h>
#else
#include <string.h>
#endif
#include "modbus_request.h"
#include "modbus_response.h"

#define MODBUS_CRC_HI_BYTE		0xFF
#define MODBUS_CRC_LO_BYTE		0xFF

#define MODBUS_REQUEST_SIZE_MAX	5

typedef enum{
	MODBUS_IDLE_STATE,
	MODBUS_PDU_STATE,
	MODBUS_CRC_STATE,
	MODBUS_RESPONSE_STATE,
} modBusState_t;

void modbus_init(uint8_t);
void modbus_check_input_data(uint8_t);
modBusState_t modbus_get_state(void);
uint8_t modbus_check_crc(uint8_t);
uint8_t modbus_response(void);

uint8_t* modbus_get_pdu(void);
void modbus_set_adu_address(uint8_t);
uint8_t modbus_check_adu_address(uint8_t);
#endif
