/****************************************************************************************
/ keyboard handling
/
***************************************************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"

/*************************************************************************
*
*  External int 4 (Keyboard ???)
*
*************************************************************************/
#pragma vector=INT4_vect
__interrupt void IntHandler_INT4( void ){


    OS_EnterInterrupt();
    OS_EnterIntStack();

    if (!kbd_delay_cnt) {

      switch (UnitID) {
      case 0x00:                  // TPC140 
        break;
      }
      OS_SignalEvent(1, &TCB_Info);
    }
    OS_LeaveIntStack();
    OS_LeaveInterrupt();

}


/*************************************************************************
*
*  External int 5 (Alarm ack)
*
*************************************************************************/
#pragma vector=INT5_vect
__interrupt void IntHandler_INT5( void ){

    char i ;
    
    OS_EnterInterrupt();
    OS_EnterIntStack();

  
    if (!kbd_delay_cnt) {
      switch (UnitID) {
      case TPC140:           
      case TPC196:           
        if (Disp.disp_vt == ALARM_VT) {
            if (Disp.alarmLED == ALARM_FLASH) {
                Disp.alarmLED =  ALARM_ON ;          // reset alarm
            }
            for (i=0; i < 20; i++) {
                Disp.image[i] &= ~0x80 ;          // disp blink off
            }
            tx_status |= ALARM_SEND ;           // Flag data to send
        } else {
            Disp.disp_vt = ALARM_VT ;
        }
        break;
      }
      OS_SignalEvent(1, &TCB_Info);
    }
    OS_LeaveIntStack();
    OS_LeaveInterrupt();
}

/*************************************************************************
*
*  External int 6 (Arrow up)
*
*************************************************************************/
#pragma vector=INT6_vect
__interrupt void IntHandler_INT6( void ){

    char i, j ;
    OS_EnterInterrupt();
    OS_EnterIntStack();

    if (!kbd_delay_cnt) {  
      switch (UnitID) {
      case TPC140:        
          i = Disp.disp_vt ;
          for (j=0; (j < NO_OF_VT); j++) {
              if (++i >= NO_OF_VT) {
                  i = 0 ;
              }
              if (Disp.window_enable[i] == true) {
                  Disp.disp_vt = i ;
                  j = NO_OF_VT ;                  // terminate for loop
              }
          }
         	RefreshDisplay( Disp.disp_vt );
          break;
      }
      OS_SignalEvent(1, &TCB_Info);
    }
    OS_LeaveIntStack();
    OS_LeaveInterrupt();
}

/*************************************************************************
*
*  External int 7 (Arrow down)
*
*************************************************************************/
#pragma vector=INT7_vect
__interrupt void IntHandler_INT7( void ){

     char i, j ;
    OS_EnterInterrupt();
    OS_EnterIntStack();

    if (!kbd_delay_cnt) {
      switch (UnitID) {
      case TPC140:             
  
          i = Disp.disp_vt ;
          for (j=0; (j < NO_OF_VT); j++) {
              if (--i >= NO_OF_VT) {
                  i = NO_OF_VT -1 ;
              }
              if (Disp.window_enable[i] == true) {
//              if ((Disp.vt_status >> i) & 0x01) {
                  Disp.disp_vt = i ;
                  j = NO_OF_VT ;                  // terminate for loop
              }
          }
    	RefreshDisplay( Disp.disp_vt );
        break;
      }
      OS_SignalEvent(1, &TCB_Info);
    }
    OS_LeaveIntStack();
    OS_LeaveInterrupt();
}
