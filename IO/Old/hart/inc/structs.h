#ifndef __STRUCTS_H__
#define __STRUCTS_H__

/****************************************************************************************
/       - structs.h
/
/
***************************************************************************************/
#include "constants.h"
#include "RTOS.h"

/*************************************************************************************
**
**  Struct defining UART parameters
**
*************************************************************************************/
typedef struct {
    /*--- Transmit buffer ---*/
    char  *pTxBuffer;
    unsigned short TxFirst;
    unsigned short TxLast;
    unsigned short TxCount;
    char  TxStatus;
    char  TxSeqCnt;
	char TxId     ;
	char TxAddress;

    /*--- Receive buffer ---*/
    OS_MAILBOX		RxMailBox;
    char  *pRxBuffer;
    char RxFaultCnt;
    char RxSendReply;
    unsigned short RxCount;
	char Channel;
	unsigned char SequenceNumber;

    
} UARTDataType;

/*************************************************************************************
**
**  Struct defining Internal AD results
**
*************************************************************************************/
typedef struct {

    short Result[16] ;

} AnalogInt ;

/*************************************************************************************
**
**  Struct defining data on ANZBHART
**
*************************************************************************************/
typedef struct {
    unsigned   FailCnt[12][2];
    char       TargetStatusSWVer[12][8];       // SW on radar

    unsigned   PortUsed;           // used port On / off
    char       Filter[12];        // filter for each channel
    float      ADCurrent[12];
    float      HartCurrent[12];
    float      Distance[12];
    float      Level[12];
    short      Raw[12];
    float      Offset[12];        // offset pr. channel
    float      Gain[12];          // gain pr. channel

} AnZbHart;

/*************************************************************************************
**
**  Struct defining data for ANZBANA or ANZB485
**
*************************************************************************************/
typedef union  {
    AnZbHart Hart;
} TargetData; 


/*************************************************************************************
**
**  Struct defining data for ANPRO10
**
*************************************************************************************/


typedef struct  {
    unsigned char  rxtypeid,
    rxadr,
    txtypeid,
    txadr;
    unsigned short nob;
    unsigned char  HCRC;
}ANPRO10_PacketHeading;


typedef struct  {
    unsigned short   CommandNo;
    unsigned short   ndb;
}ANPRO10_CommandHeading;

typedef struct  {
    unsigned char  RxTypeId,
    RxAddress,
    TxTypeId,
    TxAddress;
    unsigned short Size;
    unsigned char  CheckSum;
}NetHeading ;


#endif
