#ifndef MODBUSCONST_H
#define MODBUSCONST_H
//////////////////////////////////////////////////////////////////
//
// Wago, Modbus related constants
//
//
///////////////////////////////////////////////////////////////////


#define COMMS_FAILURE           0
#define ILLEGAL_FUNCTION        -1
#define ILLEGAL_DATA_ADDRESS    -2
#define ILLEGAL_DATA_VALUE      -3
#define SLAVE_DEVICE_FAILURE    -4
#define ACKNOWLEDGE             -5
#define SLAVE_DEVICE_BUSY       -6
#define NEGATIVE_ACKNOWLEDGE    -7
#define MEMORY_PARITY_ERROR     -8

#define PORT_FAILURE            -11

#define MAX_DATA_LENGTH         252
#define MAX_QUERY_LENGTH        255
#define MAX_RESPONSE_LENGTH     1024
#define MAX_REGISTERS           0x7D
#define MAX_COILS	            0x7D0

#define REQUEST_QUERY_SIZE	    6	/* the following packets require          */
#define REQUEST_MULTIPLE_SIZE	7
#define CHECKSUM_SIZE           2		/* 6 unsigned chars for the packet plus   */
/* 2 for the checksum.                    */


#define MODBUS_INDEX_SLAVE_ADDRESS		(0)
#define MODBUS_INDEX_COMMAND			(1)
#define MODBUS_INDEX_BYTE_CNT			(2)
#define MODBUS_INDEX_DATA_START			(3)

#define MODBUS_INDEX_ADDRESS 			(2)
#define MODBUS_INDEX_CNT				(4)
#define MODBUS_INDEX_EXCEPTION_CODE		(2)

#define MODBUS_INDEX_TCP_OFFSET			6
#define MODBUS_INDEX_TCP_TRANSACTION	0
#define MODBUS_INDEX_TCP_PROTOCOL		2
#define MODBUS_INDEX_TCP_LENGTH			4
#define MODBUS_INDEX_TCP_SLAVE_ADDRESS		(0+MODBUS_INDEX_TCP_OFFSET)
#define MODBUS_INDEX_TCP_COMMAND			(1+MODBUS_INDEX_TCP_OFFSET)
#define MODBUS_INDEX_TCP_BYTE_CNT			(2+MODBUS_INDEX_TCP_OFFSET)
#define MODBUS_INDEX_TCP_DATA_START			(3+MODBUS_INDEX_TCP_OFFSET)

#define MODBUS_INDEX_TCP_ADDRESS 			(2+MODBUS_INDEX_TCP_OFFSET)
#define MODBUS_INDEX_TCP_CNT				(4+MODBUS_INDEX_TCP_OFFSET)
#define MODBUS_INDEX_TCP_EXCEPTION_CODE		(2+MODBUS_INDEX_TCP_OFFSET)


#define MBUS_CMD_READ_COIL_STATUS   		0x1
#define MBUS_CMD_READ_INPUT_STATUS   		0x2
#define MBUS_CMD_READ_HOLDING_REGISTER 		0x3
#define MBUS_CMD_READ_INPUT_REGISTER   		0x4
#define MBUS_CMD_WRITE_SINGLE_COIL   		0x5
#define MBUS_CMD_WRITE_SINGLE_REGISTER		0x6
#define MBUS_CMD_READ_EXCEPTION_STATUS 		0x7
#define MBUS_CMD_WRITE_MULTIPLE_COILS  		0xf
#define MBUS_CMD_WRITE_MULTIPLE_REGISTERS   0x10
#define MBUS_CMD_REPORT_SLAVE_ID   			0x11


#define MODBUS_MAX_REGISTERS	0x4000
#define MODBUS_MAX_COILS		0x4000
#define MODBUS_MAX_UNITS		16

#define MBUS_REQUEST_TIMEOUT    500
#define MBUS_REQUEST_DELAY      500
#define MBUS_FRAME_SPACING		3500
#define MBUS_FRAME_TIMEOUT		1500

#define MODBUS_EX_ILLEGAL_FUNCTION							0x01
#define MODBUS_EX_ILLEGAL_ADDRESS                           0x02
#define MODBUS_EX_ILLEGAL_VALUE                             0x03
#define MODBUS_EX_SLAVE_DEV_FAILURE                         0x04
#define MODBUS_EX_ACKNOWLEDGE                               0x05
#define MODBUS_EX_SLAVE_DEVICE_BUSY                         0x06
#define MODBUS_EX_MEMORY_PARITY_ERROR                       0x08
#define MODBUS_EX_GATEWAY_PATH_UNAVAILABLE                  0x0A
#define MODBUS_EX_GATEWAY_TARGET_DEVICE_NO_RESPONSE         0x0B








// returns bit state 0 or 1
#define GetBit(a, b)                ((((U8*)a)[(b)>>3] >> ((b)&7)) & 1)
// set bit Boolean value to 1
#define SetBit(a, b)                (((U8*)a)[(b)>>3] |= (1 << ((b)&7)))
// set bit Boolean value to 0
#define ResetBit(a, b)              (((U8*)a)[(b)>>3] &= ~(1 << ((b)&7)))
// toggle bit Boolean value
#define XOrBit(a, b)                (((U8*)a)[(b)>>3] ^= (1 << ((b)&7)))







#endif
