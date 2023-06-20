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
**  Struct defining My485UART parameters
**
*************************************************************************************/
// externals for USARTs
extern char TxBufferCh0[TXSIZE_UART];
extern char RxBufferCh0[RXSIZE_UART];
extern char MailBufCh0[MBUF_SIZE];


typedef struct {
    /*--- Transmit buffer ---*/
    volatile unsigned TxFirst;
    volatile unsigned TxLast;
    volatile unsigned TxCount;
    char  TxStatus;
    char  TxSeqCnt;
    char TxId     ;
    char TxAddress;

    /*--- Receive buffer ---*/
    OS_MAILBOX		RxMailBox;
    char MailBuf[MBUF_SIZE];
    char pTxBuffer[TXSIZE_UART];
    char pRxBuffer[RXSIZE_UART];
    char RxFaultCnt;
    char RxSendReply;
    unsigned short RxCount;
	char Channel;
	unsigned char SequenceNumber;

    
} My485UARTDataType;

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
    unsigned short  FailCnt[12][2];
    char            TargetStatusSWVer[12][8];       // SW on radar

    unsigned        PortUsed;           // used port On / off
    unsigned        HartSensor;         // Indicates HART sensor
    char	        HartCmd[12];        // Hart command
    char            Filter[12];         // filter for each channel
    float           ADCurrent[12];
    float           HartCurrent[12];
    float           Distance[12];
    float           Level[12];
    float           Offset[12];        // offset pr. channel
    float           Gain[12];          // gain pr. channel

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
    volatile char       rxtypeid;     
    volatile char       rxadr;
    volatile char       txtypeid;
    volatile char       txadr;
    volatile unsigned   nob;
    volatile char       HCRC;
}ANPRO10_PacketHeading;


typedef struct  {
    unsigned   CommandNo;
    unsigned   ndb;
}ANPRO10_CommandHeading;

typedef struct  {
    char        RxTypeId; 
    char        RxAddress;
    char        TxTypeId;
    char        TxAddress;
    unsigned    Size;
    char        CheckSum;
}NetHeading ;


#endif
