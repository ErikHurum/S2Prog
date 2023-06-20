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
    unsigned short TxFirst;
    unsigned short TxLast;
    unsigned short TxCount;
    char  TxStatus;
    char  TxSeqCnt;

    /*--- Receive buffer ---*/
    char  *pRxBuffer;
    unsigned short RxFirst;
    unsigned short RxLast;
    unsigned short RxCount;
    char  RxState;
    char  SyncCnt;
    unsigned short RxTimeout;
    unsigned short RxPacklen;
    char RxFaultCnt;
    char RxSendReply;

    
} UARTDataType;

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
    char            Filter[14] ;        // filter for each channel
    char            Status[14] ;
    float           CalData[14] ;
    float           Result[14] ;
    float           Raw[14] ;
    float           Offset[14] ;        // offset pr. channel
    float           Gain[14] ;          // gain pr. channel
    unsigned short  WTrackCnt[8][4];        // 4 x Wash track
    char       		LevelSwitch[8];             // 8 high levels
    unsigned short 	WTTime[8];
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
    unsigned   FailCnt[8][2] ;
    char       TargetStatusSWVer[8];       // Cardstatus on AD (ANPRO1 cmd 47) / WIS ?
    char       TargetStatusAddress[8];     // Cardstatus on AD (ANPRO1 cmd 47)/ WIS  ?
    char       TargetSetup1[8][14];        // Status from AD (ANPRO1 cmd 37 byte 1)/ WIS ?
    char       TargetSetup2[8][14];        // Status from AD (ANPRO1 cmd 37 byte 2)/ WIS ?
    short      Raw[8][14] ;
    short      Cal[8][14] ;
    float      Result[8][14];
    unsigned   WTrackCnt[8][4];        // 4 x Wash track
    char       LevelSwitch[8];             // 8 high levels
    unsigned   WTTime[8];
    char       WHDataAvailable; 
    char       ToTargetBuffer[2][80];         // scratch buffer for communication to AD-card
    char       FromTargetBuffer[2][50];    // scratch buffer for communication to AD-card
    char       EEPROMADChannel[2];
    char       EEPROMPortpair[2];             // Current port pair

} AnZb485 ;

/*************************************************************************************
**
**  Struct defining data for ANZBANA or ANZB485
**
*************************************************************************************/
typedef union  {

    AnZbAna  Ana ;
    AnZb485  RS4 ;
} TargetData ;

