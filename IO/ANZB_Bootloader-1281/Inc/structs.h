/****************************************************************************************
/       - structs.h 
/
/ Sportline project
/
***************************************************************************************/
#include "constants.h"

/*************************************************************************************
**  
**  Struct defining myUART parameters
**
*************************************************************************************/

typedef struct {
    /*--- Transmit buffer ---*/
    unsigned short TxFirst;
    unsigned short TxLast;
    /*volatile*/ unsigned short TxCount;
    unsigned short TxPkCnt;
    char  TxStatus;
    char  TxSeqCnt;
    
    /*--- Receive buffer ---*/
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



