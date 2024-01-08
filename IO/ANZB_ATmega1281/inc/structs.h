/****************************************************************************************
/       - structs.h
/
/
***************************************************************************************/
#include "constants.h"

/*************************************************************************************
**
**  Struct defining UART parameters
**
*************************************************************************************/
typedef struct {
    /*--- Transmit buffer ---*/
    char  pTxBuffer[ TXSIZE_UART_16552 ] ;
    volatile unsigned short TxFirst;
    volatile unsigned short TxLast;
    volatile unsigned short TxCount;
    volatile char  TxStatus;
    volatile char  TxSeqCnt;

    /*--- Receive buffer ---*/
    char  pRxBuffer[ RXSIZE_UART_16552 ];         
    volatile unsigned short RxFirst;
    volatile unsigned short RxLast;
    volatile unsigned short RxCount;
    volatile char  RxState;
    volatile char  SyncCnt;
    volatile unsigned short RxTimeout;
    volatile unsigned short RxPacklen;
    volatile char RxFaultCnt;
    volatile char RxSendReply;
    char RxByte;
    char RxMailBoxBuf[MBUF_SIZE];
    OS_MAILBOX RxMailBox;
    
} UART16552DataType;
typedef struct {
    /*--- Transmit buffer ---*/
    char  pTxBuffer[ TXSIZE_UART ];
    volatile unsigned short TxFirst;
    volatile unsigned short TxLast;
    volatile unsigned short TxCount;
    volatile char  TxStatus;
    volatile char  TxSeqCnt;

    /*--- Receive buffer ---*/
    char  pRxBuffer[ RXSIZE_UART ];
    volatile unsigned short RxFirst;
    volatile unsigned short RxLast;
    volatile unsigned short RxCount;
    volatile char  RxState;
    volatile char  SyncCnt;
    volatile unsigned short RxTimeout;
    volatile unsigned short RxPacklen;
    volatile char RxFaultCnt;
    volatile char RxSendReply;
    char RxByte;
    char RxMailBoxBuf[MBUF_SIZE];
    OS_MAILBOX RxMailBox;
} UARTCPUDataType;

/*************************************************************************************
**
**  Struct defining Internal AD results
**
*************************************************************************************/
typedef struct {

    short Result[8] ;

} AnalogInt ;

/*************************************************************************************
**
**  Struct defining data on ANZBANA
**
*************************************************************************************/
typedef struct {

    unsigned short  PortUsed;           // used port On / off
    char            Filter[12] ;        // filter for each channel
    char            Status[12] ;
    float           Result[12] ;
    short           Raw[12] ;
    float           Offset[12] ;        // offset pr. channel
    float           Gain[12] ;          // gain pr. channel

} AnZbAna ;

/*************************************************************************************
**
**  Struct defining data on ANZB485
**
*************************************************************************************/
typedef struct {

    char       PortUsed;                   // used port On / off
    char       SensorType[2];              // type of sensor connected to the port (0 = AN-SGCNV, 1 = WIS, 2= Radar)
    char       IOUnitStatus[8];            // Port status
    unsigned short  FailCnt[8][2] ;
    char            TargetStatusSWVer[8];       // Cardstatus on AD (ANPRO1 cmd 47) / WIS ?
    char       TargetStatusAddress[8];     // Cardstatus on AD (ANPRO1 cmd 47)/ WIS  ?
    char       TargetSetup1[8][14];        // Status from AD (ANPRO1 cmd 37 byte 1)/ WIS ?
    char       TargetSetup2[8][14];        // Status from AD (ANPRO1 cmd 37 byte 2)/ WIS ?
    short      Raw[8][14] ;
    short      Cal[8][14] ;
    float      Result[8][14];
    unsigned short WTrackCnt[8][4];        // 4 x Wash track
    char       LevelSwitch[8];             // 8 high levels
    unsigned short WTTime[8];
    char       WHDataAvailable; 
    char       ToTargetBuffer[2][80];         // scratch buffer for communication to AD-card
    char       FromTargetBuffer[2][50];    // scratch buffer for communication to AD-card
    char       EEPROMADChannel[2];
    char       EEPROMPortpair[2];             // Current port pair
    long       SerialNumber[8];
    //char       Buffer[5];                  // Only for checking free memory

} AnZb485 ;


/*************************************************************************************
**
**  Struct defining data for ANZBANA or ANZB485
**
*************************************************************************************/
typedef union  {

    AnZbAna Ana ;
    AnZb485 RS4 ;

} TargetData ;
/*************************************************************************************
**
**  Struct defining data for ANPRO1
**
*************************************************************************************/

typedef struct  {
	char  RxAddress;
	char TxAddress;
	char HiSize;
	char LoSize;
}ANPRO1_PacketHeading;

typedef struct  {	// cmd 0 No ack / 1 with ack
	char ecmd;
	char edata;
	char PCRC;
	char EOT;
}ANPRO1_PacketTail;

