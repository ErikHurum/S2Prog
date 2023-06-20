/****************************************************************************************
/ AD converter handling , AD7715
/
***************************************************************************************/

#include "iom128a.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"


/*************************************************************************
*
*  External int 0 (UART PC16554 on AN-ZB485 or ADready on AN-ZBANA)
*
*************************************************************************/
void OS_ISR_IntHandler_INT0( void ){               //Int handler for ext int 0

    // OBS!!!
    // Uses UART16552[].TxStatus as intreason and
    // UART16552[].TxSeqCnt as counter because these needs to be globale 
    // by using OS_EnterIntStack()

    
    switch (UnitID) {
    case AN_SGCNV:                  // AN-ZBANA ADready
        //
        break;
    }
}

void OS_ISR_IntHandler_INT1( void ){               //Int handler for Ext int 1

    // OBS!!!
    // Uses UART16552[].TxStatus as intreason and
    // UART16552[].TxSeqCnt as counter because these needs to be globale 
    // by using OS_EnterIntStack()
    
  
    IntCnt++;
    switch (UnitID) {
	case AN_SGCNV:                  // AN-ZBANA Not connected!
		OS_SignalEvent(1, &TCB_AD7715);
        break;
    }
}



#pragma vector=INT0_vect
__interrupt void OS_ISR_INT0( void ){               //Int handler for ext int 0
    OS_CallISR(OS_ISR_IntHandler_INT0);
}


/*************************************************************************
*
*  External int 1 (UART PC16554 on AN-ZB485)
*
*************************************************************************/
long IntCnt  = 0;

#pragma vector=INT1_vect

__interrupt void OS_ISR_INT1( void ){               //Int handler for Ext int 1
    OS_CallISR(OS_ISR_IntHandler_INT1);
}
