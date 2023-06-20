/****************************************************************************************
/ Com protocol for USART0 
/
***************************************************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

/*************************************************************************
*   (This is a timer calback)
*  Timout timer USART 0
*
*************************************************************************/
void TimoutUSART0(void) {

    UCSR0B &= ~(__BIT_MASK( UDRIE0)) ;            // transmission end, disable int.
    ClrBit(PORTE, 0x04) ;                              // TXE0 off
    OS_StopTimer(&TimerUSART0);                    // and stop timer
}

/*************************************************************************
*   (This is a task)
*  Usart0 handler
*
*************************************************************************/
void Usart0Handler(void) {
    char stat, FailCount;
    
    
    FailCount = 0 ;
    while (1) {
        stat = OS_WaitEventTimed(1,10000);  // Time out 10 sec
        if (stat & 0x01) {
            OS_Use(&UARTSEND);
            UsartCheckPackage(0) ; 
            OS_Unuse(&UARTSEND);
            FailCount = 0;
        } else if (!stat) {
            if (FailCount++ > 12) {         // More than 2 minutes
              if (!RXTimeout) {
                PrintComError("No Rx", ALARM_FLASH);
                RXTimeout = true;
              }
              FailCount = 0;
            }
            GoToSyncUART(0) ;                                    // go to sync modus for recive
        }
    }
}

/*************************************************************************
*
*  Check the incoming packages (ANPRO1)
*
*************************************************************************/
void UsartCheckPackage(char ch) {

    unsigned short pointer;
    char    retval ;

    UART[ch].RxSendReply = false ;                           // flag for answering set to fault
    UART[ch].TxFirst = 6 ;                                 // Start pos for first TX command
    pointer = 4 ;
    do {
        retval = CheckActionUart(ch, pointer);
        pointer = pointer + UART[ch].pRxBuffer[pointer+1] + 2;        // Point to a command cmd hb/lb
        OS_Delay(0);
    } while (retval && (pointer < (UART[ch].RxPacklen - 2 )));
    if (UART[ch].RxSendReply) {                              //send answer
        Uart_BuildTail(ch);
    }
    GoToSyncUART(ch) ;                                    // go to sync modus for recive
}

/*************************************************************************
*
*  Check action on received data (ANPRO1)
*
*************************************************************************/
char CheckActionUart(char ch, unsigned short pointer) {

    unsigned short   command;
    char    retval = true;
    float test = 2.0;

    test *= pointer; 
    test = 0;
    
    if (UART[ch].pRxBuffer[pointer+2] == MySecAddress) {	  // reset com error cnt. if lagal address
      if (RXTimeout) {
        PrintComError(" OK", ALARM_OFF) ;
      }
      RXTimeout = false;
    }

    command = UART[ch].pRxBuffer[pointer];
    switch (command) {                                  // check action 

    case ANP1_SND_XTXT :                        // Receive data for X-Displays
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecXText(ch, pointer+3);
      }
      break;

    case ANP1_SND_LOTXT :                        // Receive data for low display
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecLowText(ch, pointer+3);
      }
      break;

    case ANP1_SND_HITXT :                        // Receive data for high display
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecHighText(ch, pointer+3);
      }
      break; 
      
    case ANP1_SND_BAVAL :                        // Receive data for pri bar graph
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecPriBarVal(ch, pointer+3);
      }
      break;
      
    case ANP1_SND_BAVOL :                        // Receive data for sec bar graph
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecSecBarVal(ch, pointer+3);
      }
      break; 
      
    case ANP1_SND_ALSTA :                        // Receive data for alarm status
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecAlStatus(ch, pointer+3);
      }
      break; 
      
     case ANP1_REQ_ACKSTAT :                     // Receive data acknowledge status
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecAckStatus(ch, pointer+3);
      }
      break; 
      
     case ANP1_SND_LOGRA :                     // Receive image for low disp
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecLoGraph(ch, pointer+3);
      }
      break;

     case ANP1_SND_HIIMG :                     // Receive image for bar graph
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecHiImage(ch, pointer+3);
      }
      break;

     case ANP1_SND_DVAL :                     // Receive Display window
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecValDisp(ch, pointer+3);
      }
      break;
      
     case ANP1_SND_DISDVAL :                     // Receive disable window command
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecDisableDisp(ch, pointer+3);
      }
      break;
      
     case ANP1_SND_EEPDATA :                     // Receive Eepromdata
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecEepData(ch, pointer+3);
      }
      break;

     case ANP1_SND_CASET :                     // Receive card setup
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        RecSetupData(ch, pointer+3);
      }
      break;

      //*//
    case ANP1_REQ_TXEEP :                         // Request eepromdata
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        BuildEepData(ch, pointer+3);
      }
      break;
      
    case ANP1_SND_WEEP :                         // Write eeprom (dallas type)
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        BuildEEPWriteData(ch, pointer+3);
      }
      break;

    case ANP1_SND_WAPR :                         // Write AP register
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        BuildAPWriteData(ch, pointer+3);
      }
      break;

    case ANP1_REQ_TXSER :                         // Ask for dallas ID
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        BuildDallasData(ch, pointer+3);
      }
      break;

    case ANP1_REQ_STAT :                         // Request card status
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        BuildStatusData(ch, pointer+3);
      }
      break;

    case ANP1_REQ_STACKSTATUS :                        // Request stck status
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        BuildStackStatus(ch, pointer+3) ;                     // receive package	
      }
      break ;
    case ANP1_GOTO_BOOTLOADER :                        // Goto bootlaoder??
      if (UART[ch].pRxBuffer[pointer+2]== MySecAddress) {
        GetGotoBootloader(ch, pointer+3) ;                     // receive package	
      }
      break ;

    default:
        if (command < ANP1_MAX_ECMD) {                   // handle end commands
           switch (command) {                                  // check action 
              case ANP1_ECMD_SNDOK :								/* OK to send data*/
                if (tx_status & ALARM_SEND) {
                    BuildCardData(ch, pointer+3);
                    tx_status &= ~TX_SENDOK ;       // sent once
                }
              break ;
           }   
           retval = false ;
        }
        break;

    }
    return retval;
}

/*************************************************************************
*
* Build send packet header (ANPRO1)
*
*************************************************************************/
void Uart_BuildHeader(char ch) {

    UART[ch].RxFirst = 0;                                // Reset pointers
    UART[ch].RxLast  = 0;
    UART[ch].TxLast  = 0;

    UART[ch].pTxBuffer[0] = ANPRO1_SYN ;                        /* Sync */
    UART[ch].pTxBuffer[1] = ANPRO1_SYN ;                        /* Sync */
    UART[ch].pTxBuffer[2] = UART[ch].pRxBuffer[1] ;      /* RXID */
    UART[ch].pTxBuffer[3] = MyPriAddress;                 /* Tx address pri*/
    UART[ch].pTxBuffer[4] = 0 ;                          /* packlen HB, don't know yet */
    UART[ch].pTxBuffer[5] = 0 ;                          /* packlen LB, don't know yet */
}

/*************************************************************************
*
* Build  packet tail (ANPRO1)
*
*************************************************************************/
void Uart_BuildTail(char ch) {

    Uart_BuildHeader(ch);                                    // fist build the header

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_ECMD_NMDWOACK ;  // End command 
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0x00 ;                  // End data 

    UART[ch].pTxBuffer[5] = UART[ch].TxFirst;                    // correct length because stx's
    UART[ch].pTxBuffer[4] = (UART[ch].TxFirst) >> 8 ;             // packet len high 

    UART[ch].pTxBuffer[UART[ch].TxFirst] = CalcDSTxChecksum(ch, UART[ch].TxFirst) ; // Get checksum 
    UART[ch].TxFirst++ ;                                        // OBS!! must be inc here due
                                                                // to ANSI standard !!!!

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANPRO1_EOT ;            // End of transmission 
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0x00 ;            //switch off transmitter delay 

    UART[ch].TxCount = UART[ch].TxFirst;                      //bytes to send 
    UART[ch].TxLast = 0;                                     // reset cunter
    UART[ch].TxPkCnt++ ;                                     // Count sent packages
    if (ch == 0) {                                           // Turn on TXE for channel
        OS_RetriggerTimer(&TimerUSART0);                    // and start timeout timer
        SetBit(PORTE, 0x04) ;                                     // TXE0 on
        OS_Delay(20);                                       // Wait (ms) for tx stable
        UCSR0B |= __BIT_MASK( UDRIE0) ;                     // start sending by enableing interrupt
    } else if (ch ==1) {
        // not used
    }
}

/*************************************************************************
*
* Build datablock for eeprom data
*
*************************************************************************/
void BuildEepData(char ch, short pointer){

	short i, ntna;
    UART[ch].RxSendReply = true ;                               // flag for answering 
	
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_EEP;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */

	  UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress ;			// Secondary address
	  for (i = 0; i < PACKED_DATA_SIZE; i++) {
		  UART[ch].pTxBuffer[UART[ch].TxFirst++] = packed_data[i]; /* data */
	  }
    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Build answer for writing eeprom (Dallas type)
*
*************************************************************************/
void BuildEEPWriteData(char ch, short pointer){

    char retval = true;
	short i, ntna;
    UART[ch].RxSendReply = true ;                               // flag for answering 
	
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_ACKWEEP;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */
    
    for (i = 0; i < PACKED_DATA_SIZE; i++) {          //copy data from eeprom to ram
       WriteEEPROMByte(EEPROM_EEPROMDATA+i, packed_data[i]);
    }

    for (i = 0; i < PACKED_DATA_SIZE; i++) {          //verify data from eeprom to ram
       if (ReadEEPROMByte(EEPROM_EEPROMDATA+i) != packed_data[i]) {
          retval = false ;
       }
    }
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress ;			// Secondary address
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = retval ;			// Secondary address
    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Build answer for writing AP register
*
*************************************************************************/
void BuildAPWriteData(char ch, short pointer){

    char retval = true;
	short i, ntna;
    UART[ch].RxSendReply = true ;                               // flag for answering 
	
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_ACKWAPR;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */
    
    for (i = 0; i < PACKED_DATA_SIZE; i++) {          //copy data from eeprom to ram
       WriteEEPROMByte(EEPROM_EEPROMDATA+i, packed_data[i]);
    }

    for (i = 0; i < PACKED_DATA_SIZE; i++) {          //verify data from eeprom to ram
       if (ReadEEPROMByte(EEPROM_EEPROMDATA+i) != packed_data[i]) {
          retval = false ;
       }
    }
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress ;			// Secondary address
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = retval ;			// Secondary address
    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Build answer for Dallas EEprom 
*   !OBS: Does not have Dallas her, dummy for protocol matching with older products
*
*************************************************************************/
void BuildDallasData(char ch, short pointer){

	short i, ntna;
    UART[ch].RxSendReply = true ;                               // flag for answering 
	
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_EEPSER;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress ;			// Secondary address
    for (i = 0; i < 10; i++) {                                       //Send 10 0-es for fault
       UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0;
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/
void BuildStatusData(char ch, short pointer){

    short ntna ;
    UART[ch].RxSendReply = true ;                               // flag for answering 

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_STAT;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress;           // unit adddress sec
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = PROG_VERSION ;       // software version */
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = UnitID ;       // software version */
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (RXSIZE_UART & 0xff);         // rx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (( RXSIZE_UART >> 8) & 0xff); // rx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TXSIZE_UART & 0xff);         // tx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((TXSIZE_UART >> 8) & 0xff);  // tx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = RestartStatus ;               // restart flag
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = packed_data[0];              //Ser no1 ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = packed_data[1];              //Ser no2 ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = packed_data[2];              //Ser no3 ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = packed_data[3];              //Ser no4 ;

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb

    RestartStatus = 0 ;                                                  // set reset stat to 0 = read    
}

/*************************************************************************
*
* Build send package for card data 
*
*************************************************************************/
void BuildCardData(char ch, short pointer){
    
    unsigned char ntna ;

    UART[ch].RxSendReply = true ;                               // flag for answering 
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_DATA;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress ;			// Secondary address
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = Disp.alarmLED;				// status of led 
	UART[ch].pTxBuffer[UART[ch].TxFirst++]  = 0x00 ;

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Build stack status package 
*
*************************************************************************/
void BuildStackStatus(char ch, short pointer){
  unsigned char ntna;
  unsigned short stack ;

    UART[ch].RxSendReply = true ;                               // flag for answering 
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_STACKSTATUS;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress;           // unit adddress sec
    stack = OS_GetStackSpace(&TCB_USART0);                            // USART 0
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
    stack = OS_GetStackSpace(&TCB_Blink);                            // Blink
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
    stack = OS_GetStackSpace(&TCB_WATCHDOG);                            // watchdog
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
    stack = OS_GetStackSpace(&TCB_Info);                              // Info
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
    stack = OS_GetStackSpace(&TCB_DispCtl);                            // Diaplay
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;

   UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Build datablock for ??
*
*************************************************************************/
/*void Build??(char ch){

    short ntna ;
    UART[ch].RxSendReply = true ;                               // flag for answering 

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ??;     
    ntna = UART[ch].TxFirst++ ;                                    // remember index 

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ?? ;               // restart flag

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb

}*/


//////////////////////////////////////////////////////////////////////////////
// Receiving data to IO module here
/////////////////////////////////////////////////////////////////////////////
/*************************************************************************
*
* Receive data for tPC196 displays
*
*************************************************************************/
void RecXText(char ch, short pointer){
	char i, disno;
	disno = UART[ch].pRxBuffer[pointer] ;					        // display no 0 high (green), 1 low yellow)
	if (disno < NO_OF_XDISP) {
		Disp.x_data[disno][0] = (UART[ch].pRxBuffer[pointer-2] - 2);	// no of char
		if (Disp.x_data[disno][0] > NO_OF_XCH) {
			Disp.x_data[disno][0] = NO_OF_XCH ;
		}
		for (i = 1; i <= Disp.x_data[disno][0]; i++) {
			Disp.x_data[disno][i] = UART[ch].pRxBuffer[pointer+i] ;		// store
		}
		printXDi(disno) ;        
	}
}


/*************************************************************************
*
* Receive data for low display
*
*************************************************************************/
void RecLowText(char ch, short pointer){
	char i, set;

	set = UART[ch].pRxBuffer[pointer] ;					// value set
	if (set < NO_OF_VT) {
		Disp.window_enable[set] = true ;			// mark as legal for display
	//	Disp.vt_status |= (0x01 << set) ;			// mark as legal for display
		Disp.lo_data[set][0] = (UART[ch].pRxBuffer[pointer-2] - 2);	// no of char
		if (Disp.lo_data[set][0] > NO_OF_LOCH) {
			Disp.lo_data[set][0] = NO_OF_LOCH ;
		}
		for (i = 1; i <= Disp.lo_data[set][0]; i++) {
			Disp.lo_data[set][i] = UART[ch].pRxBuffer[pointer+i] ;		// store
		}

		if (Disp.lo_grdata[20] == set) {
			Disp.lo_grdata[20] = ALARM_VT ;			// do not show graph data any more
		}
		if (Disp.disp_vt == set) { // New data to display
			printLoDi(set) ;        
		}
	}
}


/*************************************************************************
*
* Receive data for High display
*
*************************************************************************/
void RecHighText(char ch, short pointer){
	char i, set;

	set = UART[ch].pRxBuffer[pointer] ;					        // value set
	if (set < NO_OF_VT) {
		Disp.window_enable[set] = true ;			// mark as legal for display
//		Disp.vt_status |= (0x01 << set) ;		            // mark as legal for display
		Disp.hi_data[set][0] = (UART[ch].pRxBuffer[pointer-2] - 2); 	// no of char
		if (Disp.hi_data[set][0] > NO_OF_HICH) {
			Disp.hi_data[set][0] = NO_OF_HICH ;
		}
		for (i = 0; i < Disp.hi_data[set][0]; i++) {
			Disp.hi_data[set][i+1] = UART[ch].pRxBuffer[pointer+i+1] ; 	// store
		}

		if (Disp.disp_vt == set) {                           // New data to display
		//AStmark not defined 	Write2416Data(set) ;        
		}
	}
}

/*************************************************************************
*
* Receive data for pri. bar graph         
*
*************************************************************************/
void RecPriBarVal(char ch, short pointer){
	char set;

	set = UART[ch].pRxBuffer[pointer] ;					// value set
	if (set < NO_OF_VT) {
		Disp.window_enable[set] = true ;			// mark as legal for display
//		Disp.vt_status |= (0x01 << set) ;			// mark as legal for display
		Disp.ba_pdata[set] = UART[ch].pRxBuffer[pointer+1] ;
		if (Disp.ba_pdata[set] > 100) {
			Disp.ba_pdata[set] = 100 ;
		}
		if (Disp.disp_vt == set) { // New data to display
			// AStmark not defined yet  printBar(set) ;
		}
	}
}
/*************************************************************************
*
* Receive data for bar sec. graph         
*
*************************************************************************/
void RecSecBarVal(char ch, short pointer){
	char set;

	Disp.bar_status |= SECBARUSED ;					  // data to second bar
	set = UART[ch].pRxBuffer[pointer] ;					// value set
	if (set < NO_OF_VT) {
		Disp.window_enable[set] = true ;			// mark as legal for display
//		Disp.vt_status |= (0x01 << set) ;			// mark as legal for display
		Disp.ba_sdata[set] = UART[ch].pRxBuffer[pointer+1] ;
		if (Disp.ba_sdata[set] > 100) {
			Disp.ba_sdata[set] = 100 ;
		}
		if (Disp.disp_vt == set) {				// New data to display
			// AStmark not defined yet printBarSec(set) ;
		}
	}
}

/*************************************************************************
*
* Receive alarm status         
*
*************************************************************************/
void RecAlStatus(char ch, short pointer){

	Disp.alarmLED = UART[ch].pRxBuffer[pointer];
	if (Disp.disp_vt == ALARM_VT) {	 // new value set to display
		RefreshDisplay(Disp.disp_vt) ;
	}
}

/*************************************************************************
*
* Receive ack status  from host        
*
*************************************************************************/
void RecAckStatus(char ch, short pointer){   

	tx_status &= ~ALARM_SEND ;			// Received ok by host
}


/*************************************************************************
*
* Receive data for low graphic         
*
*************************************************************************/
void RecLoGraph(char ch, short pointer){
	int i, j, k;

	if (UART[ch].pRxBuffer[pointer] < NO_OF_VT) {
		Disp.lo_grdata[20] = UART[ch].pRxBuffer[pointer++] ;	// value type
		Disp.window_enable[Disp.lo_grdata[20]] = true ;			// mark as legal for display
//		Disp.vt_status |= (0x01 << Disp.lo_grdata[20]) ;	// mark as legal for display

		if (UART[ch].pRxBuffer[pointer++]) {			  // Clear display
			for (i=0; i<20; i++) {
				Disp.lo_grdata[i] = 0x00 ;
			}
		}
		j = (UART[ch].pRxBuffer[pointer-4]-3);				// bytes to display
		if (j >20) {						  // Check for legal image pos.
			j = 20 ;
		}
		for (i =0 ;i < j; i++) {
			for (k=19; k>0; k--) {
				Disp.lo_grdata[k] = Disp.lo_grdata[k-1] ;
			}
			Disp.lo_grdata[0] = UART[ch].pRxBuffer[pointer++] ; //ASTmark invert graf
		}
		printLoDi(Disp.disp_vt) ;        
	}
}

/*************************************************************************
*
* Receive data for Bar Image         
*
*************************************************************************/
void RecHiImage(char ch, short pointer){
	int i, j;
	
	j=20+UART[ch].pRxBuffer[pointer-2]-2;		// packet size
	if (j >50) {					// Check for legal image pos.
		j = 50 ;
	}
	for (i =20;i < j; i++) {
		Disp.image[i] = UART[ch].pRxBuffer[pointer++] ;
	}
}

/*************************************************************************
*
* Receive data for value set to display         
*
*************************************************************************/
void RecValDisp(char ch, short pointer){

  if (UART[ch].pRxBuffer[pointer] < NO_OF_VT) {
     if (Disp.window_enable[UART[ch].pRxBuffer[pointer]] == true) {
//    if ((Disp.vt_status >> UART[ch].pRxBuffer[pointer]) & 0x01) {
    	Disp.disp_vt = UART[ch].pRxBuffer[pointer] ;	
    	RefreshDisplay( Disp.disp_vt );
    }
  }
}

/*************************************************************************
*
* Receive data to disable a window         
*
*************************************************************************/
void RecDisableDisp(char ch, short pointer){

  if (UART[ch].pRxBuffer[pointer] < NO_OF_VT) {
     if (Disp.window_enable[UART[ch].pRxBuffer[pointer]] == true) {
      Disp.window_enable[UART[ch].pRxBuffer[pointer]] = false;
    }
  }
}

/*************************************************************************
*
* Receive eeprom data
*
*************************************************************************/
void RecEepData(char ch, short pointer){

//	unsigned char temp_data[PACKED_DATA_SIZE];
	char   *e_data, *a_data, i ;

	a_data = &UART[ch].pRxBuffer[pointer] ;
	e_data = &UART[ch].pRxBuffer[pointer + 8] ;

	if (CheckEepData(e_data) && CheckADData(a_data) &&
		(UART[ch].pRxBuffer[pointer + PACKED_DATA_SIZE] & 0x01)) {	// check legale packet 
		for (i = 0; i < PACKED_DATA_SIZE; i++) {
			packed_data[i] = UART[ch].pRxBuffer[pointer++];			// copy data
		}
	//	eep_type &= ~0x0f ;
		//eep_type |= 0x09 ;				 // use PC data 
	} else {
//		eep_type &= ~0x0f ;
	//	eep_type |= 0x02 ;				 // fail from pc 
	}
}


/*************************************************************************
*
* Receive setup
*
*************************************************************************/
void RecSetupData(char ch, short pointer){

    WriteEEPROMByte(EEPROM_PRI_ADDR, UART[ch].pRxBuffer[pointer]);
    WriteEEPROMByte(EEPROM_SEC_ADDR, UART[ch].pRxBuffer[pointer+1]);

    // AStmark don't saved for brightness tpc350
}

/*************************************************************************
*
* Receive Command to go to the bootloader program
*
*************************************************************************/
void GetGotoBootloader(char ch, short pointer) {   

//    void (*BootApp)(void) = (void(*)())0xF000;

    while ( (EECR & 1<<EEWE) != 0 ) //chech if EEPROM is ready
        ;
    EEARL = (0x0fff & 0xff);
    EEARH = (0x0fff >> 8);
    EEDR = 0xff;
    EECR |= (1<<EEMWE);
    EECR |= (1<<EEWE);
    while (EECR & (1<<EEWE))
        ;

    WDTCR = 0x18;               //Start watchdog to genetate restart
    WDTCR = 0x08;               //Start watchdog to genetate restart
}


/*************************************************************************
*
*  Receive data on USARTs (ANPRO1)
*
*************************************************************************/
void ReceivePacketUart(char ch) {

    switch (UART[ch].RxState) {                  // check status 
    case SYNC :
        // all functionallity in inerrupt routine 
        break ;
    case HEADER :
         if (UART[ch].RxLast >= 3) {             // receive header 
          UART[ch].RxPacklen = (UART[ch].pRxBuffer[2] * 256)+ UART[ch].pRxBuffer[3] ; // Find length of package
          if (UART[ch].RxPacklen >= MIN_PACK_LEN) {
            UART[ch].RxState = RECEIVE ;       // Header ok go to data receive state
            UART[ch].RxCount = UART[ch].RxLast + 1 ;    // Set receive counter
          } else {
            GoToSyncUART(ch) ;                        // go to sync modus for recive
          }
        }
        break ;
    case RECEIVE :
        if (++UART[ch].RxCount >= UART[ch].RxPacklen) {
           if ((UART[ch].pRxBuffer[UART[ch].RxPacklen -1]) == ANPRO1_EOT) {
                if (CalcDSRxChecksum(ch, UART[ch].RxPacklen-2)) {
                    if ((UART[ch].pRxBuffer[0] == MyPriAddress)||      // message to tpc140 or
                        (UART[ch].pRxBuffer[0] == 0xff)) {            // broadcast
                        HostAddress = UART[ch].pRxBuffer[1];            // address to sender (host)
                        UART[ch].RxState = HANDLE ;                     // Package OK
                        if (ch == 0) {
                            OS_SignalEvent(1, &TCB_USART0);
                        } else if (ch == 1) {
                             //Not used
                        }
                    } else {
                        GoToSyncUART(ch) ;                             // go to sync modus for recive
                    }
                } else {
                    GoToSyncUART(ch) ;                                // go to sync modus for recive
                }
            } else {
                GoToSyncUART(ch) ;                                    // go to sync modus for recive
            }
        }
        break ;
    case HANDLE :
        break;
    default :
        GoToSyncUART(ch) ;                                            // go to sync modus for recive
        break ;
    }                                                           // end switch 
    if (++UART[ch].RxLast >= RXSIZE_UART) {                     // check pointer 
        UART[ch].RxLast = 0;                                     // reset pointer
    }
}


/*************************************************************************
*
* Calculate tx checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
char CalcDSTxChecksum(char ch, unsigned short len) {

    unsigned short  cnt ;
    unsigned char   csum ;

    csum = 0 ;
    for (cnt = 2 ; cnt < len ; cnt++) {
        csum = crc[csum ^ UART[ch].pTxBuffer[cnt]] ;
    }
    return csum ;
}

/*************************************************************************
*
* Calculate rx packet checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
short CalcDSRxChecksum(char ch, unsigned short len) {

    unsigned short  cnt ;
    unsigned char   csum ;

    csum = 0 ;
    for (cnt=0 ; cnt < len ; cnt++) {
        csum = crc[csum ^ UART[ch].pRxBuffer[cnt]] ;
    }
    if (csum == UART[ch].pRxBuffer[len]) {
        return true ;
    } else {
        return false ; 
    }
}
/*************************************************************************
*
* Check AppData checksum
*
*************************************************************************/
char CheckADData(char *data)
{

	int             cnt ;
	unsigned char   csum, ok ;

	ok = false ;
	csum = 0 ;
	for (cnt = 0 ; cnt < 7 ; cnt++) {
		if (*data != 0x00) {
			ok = true ;
		}
		csum = crc[csum ^ *data++] ;
	}
	if ((csum == *data) && (ok == true)) {
		return true ;
	} else {
		return false ;

	}
}


/*************************************************************************
*
* Check Eepdata checksum
*
*************************************************************************/
char CheckEepData(char *data)
{

	int             cnt ;
	unsigned char   csum ;

	csum = 0 ;
	for (cnt = 8 ; cnt < (PACKED_DATA_SIZE -1) ; cnt++) {
		csum = crc[csum ^ *data++] ;
	}
	if (csum == *data) {
		return true ;
	} else {
		return false ;
	}
}


/*************************************************************************
*
* Goes to sync mode
*
*************************************************************************/
__monitor void GoToSyncUART(char ch) {

    if (ch < 2) {
        UART[ch].SyncCnt = 0 ;                        // ready for sync
        UART[ch].RxState = SYNC ;
        UART[ch].RxFirst = 0 ;
    }
}
