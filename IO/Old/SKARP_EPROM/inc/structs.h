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
    char  *pTxBuffer;
    unsigned int TxFirst;
    unsigned int TxLast;
    unsigned int TxCount;
    unsigned int TxPkCnt;
    char  TxStatus;
    char  TxSeqCnt;

    /*--- Receive buffer ---*/
    char  *pRxBuffer;
    unsigned int RxFirst;
    unsigned int RxLast;
    unsigned int RxCount;
    char  RxState;
    char  SyncCnt;
    unsigned int RxTimeout;
    unsigned int RxPacklen;
    unsigned int RxPkCnt;
    char RxFaultCnt;
    char RxSendReply;

} UARTDataType;

/*************************************************************************************
**
**  Struct defining Internal AD results
**
*************************************************************************************/
typedef struct {

    int Result[8] ;

} AnalogInt ;

/*************************************************************************************
**
**  Struct defining data on ANZBANA
**
*************************************************************************************/
typedef struct {

    unsigned int  PortUsed;           // used port On / off
    char            Filter[12] ;        // filter for each channel
    char            Status[12] ;
    float           Result[12] ;
    int           Raw[12] ;
    float           Offset[12] ;        // offset pr. channel
    float           Gain[12] ;          // gain pr. channel

} AnZbAna ;

/*************************************************************************************
**
**  Struct defining data on ANZB485
**
*************************************************************************************/
typedef struct {

    char            PortUsed;                   // used port On / off
    char            SensorType;                 // type of sensor connected to the port (0 = AN-SGCNV, 1 = WIS)
    char            IOUnitStatus[8];            // Port status
    unsigned int  FailCnt[8][2] ;
    char            TargetStatusSWVer[8];       // Cardstatus on AD (ANPRO1 cmd 47) / WIS ?
    char            TargetStatusAddress[8];     // Cardstatus on AD (ANPRO1 cmd 47)/ WIS  ?
    char            TargetSetup1[8][14];        // Status from AD (ANPRO1 cmd 37 byte 1)/ WIS ?
    char            TargetSetup2[8][14];        // Status from AD (ANPRO1 cmd 37 byte 2)/ WIS ?
    int           Raw[8][14] ;
    int           Cal[8][14] ;
    float           Result[8][14] ;
    char            ToTargerBuffer[1];         // scratch buffer for communication to AD-card
    char            FromTargetBuffer[2][2];    // scratch buffer for communication to AD-card
    char            EEPROMADChannel[2];
    char            EEPROMPortpair[2];             // Current port pair
    char            Buffer[1];                  // Only for checking free memory

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
