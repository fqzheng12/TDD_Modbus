//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------

extern "C"
{
#include "modbus.h"
}

#include "CppUTest/TestHarness.h"

//uint8_t pdu_request[MODBUS_REQUEST_SIZE_MAX];
//uint8_t adu_address;

TEST_GROUP(ModbusProtocol)
{
    void setup()
    {
		modbus_init(1);
    }

    void teardown()
    {
    }
};
#if 0
TEST(ModbusProtocol, crcCheck)
{
	uint16_t adu_crc;

	adu_address = 0x01;
	
	pdu_request[0] = 0x03;
	pdu_request[1] = 0x00;	
	pdu_request[2] = 0x00;
	pdu_request[3] = 0x00;	
	pdu_request[4] = 0x0A;

	adu_crc = modbus_check_crc(pdu_request, adu_address, MODBUS_REQUEST_SIZE_MAX);
	
	LONGS_EQUAL(0xBC0D, adu_crc);
}
#endif

TEST(ModbusProtocol, addressCheck)
{
	modbus_check_input_data(1);
	
	BYTES_EQUAL(MODBUS_PDU_STATE,modbus_get_state());
}

TEST(ModbusProtocol, pduAcquisition)
{
	uint8_t function;
	
	void* request = NULL;
	modbusRequest_ReadInputs_t* requestInput;
	
	modbus_check_input_data(1);
	
	BYTES_EQUAL(MODBUS_PDU_STATE,modbus_get_state());
	
	modbus_check_input_data(3);
	modbus_check_input_data(0);
	modbus_check_input_data(0);
	modbus_check_input_data(0);
	modbus_check_input_data(10);	
	
	BYTES_EQUAL(MODBUS_CRC_STATE,modbus_get_state());	
	
	modbus_check_input_data(0xC5);
	modbus_check_input_data(0xCD);	

	BYTES_EQUAL(MODBUS_RESPONSE_STATE,modbus_get_state());	

	BYTES_EQUAL(1, modbus_response());
	BYTES_EQUAL(MODBUS_RESPONSE_STATE,modbus_get_state());
	
	request = modbus_RequestCheck(&function);
	BYTES_EQUAL(3, function);
	
	requestInput = (modbusRequest_ReadInputs_t*)request;
	BYTES_EQUAL(0x03, requestInput->function);
	LONGS_EQUAL(0x0A, requestInput->input_quantity);
	
	free(request);
}