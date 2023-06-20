#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

#include "ModbusConst.h"

#ifdef WIN32
    #include "WinUart.h"
#else
    #include "SC2410Uart.h"
    #include "ST16554Uart.h"
#endif

//---------------------------------------------------------------------------
/***********************************************************************

     Note: All functions used for sending or receiving data via
             modbus return these return values.


    Returns:	string_length if OK
            0 if failed
            Less than 0 for exception errors

***********************************************************************/


///////////////////////////////////////////////////////////////////////
//
//  ModbusPro object routines
//
///////////////////////////////////////////////////////////////////////


ModbusPro::ModbusPro() {
    Initiate();
}

void ModbusPro::Initiate(void) {
}


///////////////////////////////////////////////////////////////////////////////////////


void ModbusPro::ReceiveStatus(TSNUart *Port) {
}


/* Table of CRC values for high-order byte */
static U8 auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

/* Table of CRC values for low-order byte */
static U8 auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

unsigned ModbusPro::FastCalcCRC(U8 *puchMsg, unsigned usDataLen) {
    U8 uchCRCHi = 0xFF;    /* high CRC byte initialized 	*/
    U8 uchCRCLo = 0xFF;    /* low CRC byte  initialized  	*/
    unsigned uIndex;               /* will index into CRC   lookup */
    /* table              			*/
    while ( usDataLen-- ) {          /* pass through message buffer  */
        uIndex   = uchCRCHi ^ *puchMsg++;  /* calculate the CRC  */
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex];
    }
    return ((uchCRCHi << 8) | uchCRCLo);
}




unsigned ModbusPro::CalcCRC(unsigned char *buf, int start, int cnt) {
    int     i, j;
    unsigned    temp, temp2, flag;

    temp = 0xFFFF;

    for ( i = start; i < cnt; i++ ) {
        temp = temp ^ buf[i];

        for ( j = 1; j <= 8; j++ ) {
            flag = temp & 0x0001;
            temp = temp >> 1;
            if ( flag )	temp = temp ^ 0xA001;
        }
    }

    /* Reverse byte order. */

    temp2 = temp >> 8;
    temp = (temp << 8) | temp2;
    temp &= 0xFFFF;

    return (temp);
}






/***********************************************************************

Function to send a query out to a modbus slave.

A checksum is added to the end of a packet.
Please note that the packet array must be at least 3 fields longer than
string_length. Test

************************************************************************/

bool ModbusPro::Send_Query(TSNUart *Port, U8 *Query, U8 Length) {
    bool Status;
    switch ( Port->Device ) {
    case C_UART_DEVICE_MODICON_MASTER_TCP   :
    case C_UART_DEVICE_MODICON_SLAVE_TCP    :
    case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
    case C_UART_DEVICE_MODBUS_MASTER_TCP    :
        Query[MODBUS_INDEX_TCP_TRANSACTION] = Port->TransactionNumber & 0xFF;
        Query[MODBUS_INDEX_TCP_TRANSACTION + 1] = Port->TransactionNumber >> 8;
        Query[MODBUS_INDEX_TCP_PROTOCOL] = 0;
        Query[MODBUS_INDEX_TCP_PROTOCOL   + 1] = 0;
        Query[MODBUS_INDEX_TCP_LENGTH] = 0;
        Query[MODBUS_INDEX_TCP_LENGTH     + 1] = Length - MODBUS_INDEX_TCP_OFFSET;
        Status = Port->Send(Query, (int)Length, 0x1, true);
        switch ( Port->HWProtocol ) {
        case C_UART_HWPRO_485 :
            Port->ClearRxBuffer();
            break;
        case C_UART_HWPRO_232 :
            break;
        }
        break;
    case C_UART_DEVICE_MODICON_MASTER       :
    case C_UART_DEVICE_MODICON_SLAVE        :
    case C_UART_DEVICE_MODBUS_SLAVE_INV     :
    case C_UART_DEVICE_MODBUS_SLAVE         :
    case C_UART_DEVICE_MODBUS_MASTER_INV    :
    case C_UART_DEVICE_MODBUS_MASTER        :
    default:
        {
            unsigned short TmpCRC   = (unsigned short)FastCalcCRC(Query, Length);
            Query[Length++] = TmpCRC >> 8;
            Query[Length++] = TmpCRC & 0x00FF;
        }
        Status = Port->Send(Query, (int)Length, 0x1, true);
        switch ( Port->HWProtocol ) {
        case C_UART_HWPRO_485 :
            Port->ClearRxBuffer();
            break;
        case C_UART_HWPRO_232 :
            break;
        }
        break;
    }
    return (Status);
}


/***********************************************************************

    receive_response( array_for_data )

     Function to monitor for the reply from the modbus slave.
     This function blocks for timeout seconds if there is no reply.

     Returns:	Total number of characters received.
***********************************************************************/
//#define MODBUS_OLD
int ModbusPro::Receive_Response(TSNUart *Port, U8 *received_string, int TimeOut, int FrameSpaceTime, int FrameTimeOut) {
#ifndef MODBUS_OLD
    int bytes_received = 0;
    switch ( Port->Device ) {
    case C_UART_DEVICE_MODICON_MASTER_TCP   :
    case C_UART_DEVICE_MODICON_MASTER       :
    case C_UART_DEVICE_MODBUS_MASTER:
    case C_UART_DEVICE_MODBUS_MASTER_INV:
    case C_UART_DEVICE_MODBUS_MASTER_TCP:
        {
            bool dataAvailable = false;
            /* wait for a response */
            dataAvailable = Port->Receive(&received_string[bytes_received], sizeof(U8), TimeOut);
            while ( dataAvailable && bytes_received <= 256 ) {
                dataAvailable = Port->Receive(&received_string[++bytes_received], sizeof(U8), FrameTimeOut);
            }
        }
        break;
    case C_UART_DEVICE_MODICON_SLAVE_TCP    :
    case C_UART_DEVICE_MODICON_SLAVE        :
    case C_UART_DEVICE_MODBUS_SLAVE:
    case C_UART_DEVICE_MODBUS_SLAVE_TCP:
    case C_UART_DEVICE_MODBUS_SLAVE_INV:
        {
            bool dataAvailable = false;
            /* wait for a response */
            int LastRxTime = Port->LastRxTime;
            int NoRxTime;
            do {
                dataAvailable = Port->Receive(&received_string[bytes_received], sizeof(U8), TimeOut);
                NoRxTime = Port->LastRxTime - LastRxTime;
            }while ( dataAvailable && NoRxTime < FrameSpaceTime ); // Wait for a quiet time
            if ( NoRxTime >=  FrameSpaceTime ) {
                while ( dataAvailable ) {
                    dataAvailable = Port->Receive(&received_string[++bytes_received], sizeof(U8), FrameTimeOut);
                }
            }
#ifdef S2TXU
            OS_DelayUntil(Port->LastRxTime + FrameSpaceTime);
#endif
            // See if we have a quiet periode
            if ( !Port->Relaxed && Port->HasMore() ) {
                bytes_received = 0;
            }
        }
        break;
    }
    return (bytes_received);
#else
    bool dataAvailable = false;
    int bytes_received = 0;
    /* wait for a response */
    dataAvailable = Port->Receive(&received_string[bytes_received], sizeof(U8), TimeOut);
    while ( dataAvailable ) {
        dataAvailable = Port->Receive(&received_string[++bytes_received], sizeof(U8), FrameTimeOut);
    }

    return (bytes_received);

#endif
}


/*********************************************************************

    modbus_response( response_data_array, query_array )

     Function to the correct response is returned and that the checksum
     is correct.

     Returns:	string_length if OK
        0 if failed
        Less than 0 for exception errors

    Note: All functions used for sending or receiving data via
            modbus return these return values.

**********************************************************************/

int ModbusPro::Modbus_Response(TSNUart *Port, U8 *ReplyPtr, U8 *query, int QueryLength, int TimeOut, int FrameSpaceTime, int FrameTimeOut) {
    QueryLength += 2;
    U8 tmpData[MAX_RESPONSE_LENGTH];
    //memset(tmpData,0xff,MAX_QUERY_LENGTH);
    int AnswerSize = Receive_Response(Port,  tmpData, TimeOut, FrameSpaceTime, FrameTimeOut);
    if ( AnswerSize ) {
        switch ( Port->HWProtocol ) {
        case C_UART_HWPRO_485 :
        case C_UART_HWPRO_232 :
            QueryLength = 0;
            break;
        }
        AnswerSize -= QueryLength;
        if ( AnswerSize >= 2 ) {
            memcpy(ReplyPtr, &tmpData[QueryLength], AnswerSize);
            switch ( Port->Device ) {
            case C_UART_DEVICE_MODICON_MASTER       :
            case C_UART_DEVICE_MODICON_SLAVE        :
            case C_UART_DEVICE_MODBUS_MASTER        :
            case C_UART_DEVICE_MODBUS_MASTER_INV    :
            case C_UART_DEVICE_MODBUS_SLAVE         :
            case C_UART_DEVICE_MODBUS_SLAVE_INV     :
                {
                    U16 crc_calc = FastCalcCRC(ReplyPtr, AnswerSize - 2);

                    U8 recv_crc_hi = (U8)ReplyPtr[AnswerSize - 2];
                    U8 recv_crc_lo = (U8)ReplyPtr[AnswerSize - 1];

                    U16 crc_received  = (recv_crc_hi << 8) | recv_crc_lo;
                    /*********** check CRC of response ************/
                    if ( crc_calc != crc_received ) {
                        AnswerSize = 0;
                    }
                }
                break;
            case C_UART_DEVICE_MODICON_MASTER_TCP   :
            case C_UART_DEVICE_MODICON_SLAVE_TCP    :
            case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
            case C_UART_DEVICE_MODBUS_MASTER_TCP    :
                break;
            }
        } else {
            AnswerSize = 0;
        }



        /********** check for exception response *****/

        if ( AnswerSize && ReplyPtr[1] != query[1] ) {
            AnswerSize = 0 - ReplyPtr[2];
        }
    }
    return (AnswerSize);
}


/***********************************************************************

    preset_response

    Gets the raw data from the input stream.

***********************************************************************/

int ModbusPro::Preset_Response(TSNUart *Port, U8 *query, int QueryLength, int TimeOut, int FrameSpaceTime, int FrameTimeOut, U8 *Reply) {
    int ResponseLength;
    if ( Reply ) {
        ResponseLength = Modbus_Response(Port, Reply, query, QueryLength, TimeOut, FrameSpaceTime, FrameTimeOut);
    } else {
        U8 DataBuf[MAX_RESPONSE_LENGTH];
        ResponseLength = Modbus_Response(Port, DataBuf, query, QueryLength, TimeOut, FrameSpaceTime, FrameTimeOut);
    }
    return (ResponseLength);
}






/*************************************************************************

    set_single

    sends a value to a register in a slave.

**************************************************************************/

int ModbusPro::Set_Single(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned Value, int TimeOut, int FrameSpaceTime, int FrameTimeOut) {

    int status;
    //SlaveAddress--;
    // Not that the Packet contains 3 times 0x0 to make space for CRC
    U8 Packet[REQUEST_QUERY_SIZE + CHECKSUM_SIZE + 1] = {
        SlaveAddress,
        Function,
        Address >> 8,
        Address & 0xFF,
        Value >> 8,
        Value & 0xff,
    };

    if ( Send_Query(Port, Packet, REQUEST_QUERY_SIZE) ) {
        status = Preset_Response(Port, Packet, REQUEST_QUERY_SIZE, TimeOut, FrameSpaceTime, FrameTimeOut);
    } else {
        status = PORT_FAILURE;
    }

    return (status);
}


/*************************************************************************

    set_multiple

    sends a value to a register in a slave.

**************************************************************************/

int ModbusPro::Set_Multiple(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned NumberOfRegisters, unsigned Size, U16 Value[], int TimeOut, int FrameSpaceTime, int FrameTimeOut) {
    int status;


    // Not that the Packet contains 3 times 0x0 to make space for CRC
    U8 Packet[MAX_QUERY_LENGTH] = {
        SlaveAddress,
        Function,
        Address >> 8,
        Address & 0x00FF,
        NumberOfRegisters >> 8,
        NumberOfRegisters & 0x00FF,
        NumberOfRegisters * 2,
    };

    int Length = REQUEST_MULTIPLE_SIZE;
    for ( unsigned i = 0; i < NumberOfRegisters; i++ ) {
        Packet[Length++] = Value[i] >> 8;
        Packet[Length++] = Value[i] & 0x00FF;
    }
    if ( Send_Query(Port, Packet, Length) ) {
        status = Preset_Response(Port, Packet, Length, TimeOut, FrameSpaceTime, FrameTimeOut);
    } else {
        status = PORT_FAILURE;
    }

    return (status);
}
int ModbusPro::WriteMultipleCoils(TSNUart *Port, unsigned SlaveAddress, unsigned Address, unsigned NumberOfCoils, U8 Value[], int TimeOut, int FrameSpaceTime, int FrameTimeOut) {
    int Status;

    unsigned NumberOfBytes = NumberOfCoils / 8;
    if ( NumberOfCoils % 8 ) {
        NumberOfBytes++;
    }
    // Not that the Packet contains 3 times 0x0 to make space for CRC
    U8 Packet[MAX_QUERY_LENGTH] = {
        SlaveAddress,
        MBUS_CMD_WRITE_MULTIPLE_COILS,
        Address >> 8,
        Address & 0x00FF,
        NumberOfCoils >> 8,
        NumberOfCoils & 0x00FF,
        NumberOfBytes
    };
    memcpy(&Packet[REQUEST_MULTIPLE_SIZE], Value, NumberOfBytes);
    int Length = REQUEST_MULTIPLE_SIZE + NumberOfBytes;
    if ( Send_Query(Port, Packet, Length) ) {
        Status = Preset_Response(Port, Packet, Length, TimeOut, FrameSpaceTime, FrameTimeOut);
    } else {
        Status = PORT_FAILURE;
    }

    return (Status);
}

int ModbusPro::WriteMultipleRegisters(TSNUart *Port, unsigned SlaveAddress, unsigned Address, unsigned NumberOfRegisters, U8 Value[], int TimeOut, int FrameSpaceTime, int FrameTimeOut) {
    int Status;

    unsigned Size = NumberOfRegisters * 2;
    // Not that the Packet contains 3 times 0x0 to make space for CRC
    U8 Packet[MAX_QUERY_LENGTH] = {
        SlaveAddress,
        MBUS_CMD_WRITE_MULTIPLE_REGISTERS,
        Address >> 8,
        Address & 0x00FF,
        NumberOfRegisters >> 8,
        NumberOfRegisters & 0x00FF,
        Size,
    };
    memcpy(&Packet[REQUEST_MULTIPLE_SIZE], Value, Size);
    int Length = REQUEST_MULTIPLE_SIZE + Size;
    if ( Send_Query(Port, Packet, Length) ) {
        Status = Preset_Response(Port, Packet, Length, TimeOut, FrameSpaceTime, FrameTimeOut);
    } else {
        Status = PORT_FAILURE;
    }

    return (Status);
}


int ModbusPro::Get_Single(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned NumberOfPoints, U8 *ReplyPtr, int TimeOut, int FrameSpaceTime, int FrameTimeOut) {
    return Get_Multiple(Port, Function, SlaveAddress, Address, 1, ReplyPtr, TimeOut, FrameSpaceTime, FrameTimeOut);
}

int ModbusPro::Get_Multiple(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned NumberOfPoints, U8 *ReplyPtr, int TimeOut, int FrameSpaceTime, int FrameTimeOut) {

    // Note that the Packet contains 3 times 0x0 to make space for CRC
    U8 Packet[REQUEST_QUERY_SIZE + CHECKSUM_SIZE + 1] = {
        SlaveAddress,
        Function,
        Address >> 8,
        Address & 0xFF,
        NumberOfPoints >> 8,
        NumberOfPoints & 0xff,
    };

    int Status;
    if ( Send_Query(Port, Packet, REQUEST_QUERY_SIZE) ) {
        U8 tmpReplyData[MAX_RESPONSE_LENGTH];
        Status = Preset_Response(Port, Packet, REQUEST_QUERY_SIZE, TimeOut, FrameSpaceTime, FrameTimeOut, tmpReplyData);
        if ( Status >= 6 && tmpReplyData[MODBUS_INDEX_SLAVE_ADDRESS] == (U8)SlaveAddress ) {
            switch ( tmpReplyData[MODBUS_INDEX_COMMAND] ) {
            case MBUS_CMD_READ_COIL_STATUS:
                memcpy(ReplyPtr, &tmpReplyData[MODBUS_INDEX_DATA_START], tmpReplyData[MODBUS_INDEX_BYTE_CNT]);
                break;
            case MBUS_CMD_READ_INPUT_REGISTER:
            case MBUS_CMD_READ_HOLDING_REGISTER:
                memcpy(ReplyPtr, &tmpReplyData[MODBUS_INDEX_DATA_START], tmpReplyData[MODBUS_INDEX_BYTE_CNT]);
                break;
            default:
                Status = PORT_FAILURE;
                break;
            }
        } else {
            Status = PORT_FAILURE;
        }
    } else {
        Status = PORT_FAILURE;
    }
    return (Status);
}



