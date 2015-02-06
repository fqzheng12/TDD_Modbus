#include "modbus.h" 

void* modbus_RequestCheck(uint8_t* function)
{
	void* request;
	uint8_t* pdu;
	
	pdu = modbus_get_pdu();
	switch(pdu[0])
	{
	case MODBUS_READ_COILS:
	case MODBUS_READ_DISCRETE_INPUTS:
	case MODBUS_READ_HOLDING_REGISTERS:
	case MODBUS_READ_INPUT_REGISTERS:
	{
		modbusRequest_ReadInputs_t* requestRead;
		
		requestRead = malloc(sizeof(modbusRequest_ReadInputs_t));
		requestRead->function = pdu[0];
		requestRead->starting_add = (pdu[1] << 8) | (pdu[2]);
		requestRead->input_quantity = (pdu[3] << 8) | (pdu[4]);		
		
		request = (void*)(requestRead);
		break;
	}
	case MODBUS_WRITE_SINGLE_COIL:
	case MODBUS_WRITE_SINGLE_REGISTER:
	{
		modbusRequest_WriteSingle_t* requestWrite;
		
		requestWrite = malloc(sizeof(modbusRequest_WriteSingle_t));
		requestWrite->function = pdu[0];
		requestWrite->address = (pdu[1] << 8) | (pdu[0]);
		requestWrite->value = (pdu[3] << 8) | (pdu[2]);		
		
		request = (void*)(requestWrite);
		break;
	}
	default:
		break;
	}
	*function = pdu[0];
	free(pdu);
	
	return request;
}