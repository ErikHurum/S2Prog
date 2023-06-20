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
    /*volatile*/ unsigned short TxCount;
    unsigned short TxPkCnt;
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
    unsigned short RxPkCnt;
    char RxSendReply;

} UARTDataType;


