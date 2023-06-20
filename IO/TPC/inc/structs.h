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

/*************************************************************************************
**  
**  Struct defining Internal AD results
**
*************************************************************************************/
typedef struct {

  short   image[50] ;                         // Image of the Led Data     
  char    window_enable[NO_OF_VT] ;          // store low data 
  char    lo_data[NO_OF_VT][NO_OF_LOCH+1] ;   // store low data 
  char    hi_data[NO_OF_VT][NO_OF_HICH+1] ;   //store high data
  char    x_data[NO_OF_XDISP][NO_OF_XCH+1] ;  // store X disp data 2 pcs 4 char+despoint
  char    ba_pdata[NO_OF_VT] ;                // store pri. bar data 
  char    ba_sdata[NO_OF_VT] ;                // store sec. bar data 
  char    lo_grdata[NO_OF_LOGR] ;             // store low graph data
  char    alarmLED ;
//  char    vt_status;                          // Status for leds
  char    disp_vt;                            // Current displayed vindow
  char    disp_vt_old;                        // Current displayed vindow
  char    bar_status;                         // status used for bargraph

} DispData ;

