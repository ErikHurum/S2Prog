/****************************************************************************************
/ Com protocol for USART0 
/
***************************************************************************************/

//#include "iom1280.h"
#include "stdio.h"
//#include "math.h"
#include "externals.h"
#include "assembly.h"

 
 /*************************************************************************
*
*  Check the incoming packages
*
*************************************************************************/
void UsartCheckPackage(char ch) {

    unsigned short pointer;
    char retval ;
    
    My485UART[ch].RxSendReply = false ;                           // flag for answering set to fault
    My485UART[ch].TxFirst = 11 ;                        // Startpos for fist TX command
    pointer = 7 ;
    do {
        retval = CheckActionUart(ch, pointer);
        pointer = pointer + My485UART[ch].pRxBuffer[pointer+2] 
                          + (My485UART[ch].pRxBuffer[pointer+3]*256) + 4;            // Point to a command cmd hb/lb
    } while (retval && (pointer < (My485UART[ch].RxPacklen - 4 )));
    if(My485UART[ch].RxSendReply){                              //send answer
        Uart_BuildTail(ch);
    }
    GoToSyncUART(ch) ;                                    // go to sync modus for recive
}

/*************************************************************************
*
*  Check action on received data
*
*************************************************************************/
char CheckActionUart(char ch, unsigned short pointer) {

    unsigned short   command;
    char    retval = true;

    command = My485UART[ch].pRxBuffer[pointer] | (My485UART[ch].pRxBuffer[pointer+1] <<8);
    switch (command) {                                      // check action 
   case CMD_REQ_STATUS :                                    // Regusest status for target
        BuildStatusData(ch) ;                       
        break;
        
    case CMD_FLASH_ID :                                     // Send flash ID
        BuildFlashID(ch) ;
        break ;
        
    case CMD_FLASH_ERASE :                                 // Erase flash
        EraseFlash(ch) ;
        break ;
        
    case CMD_FLASH_PROG :                                   // Prog flash
        ProgramFlash(ch, pointer+4) ;
        break ;
        
    case CMD_FLASH_READ :                                   // Read flash
        ReadFlash(ch, pointer+4) ;
        break ;
        
    case CMD_EXIT_BOOTLOADER :                                // Leave bootlaoder
        ExitBootloader(ch) ; 
        break ;
        
    default:
        if (command < MAX_ECMD) {                           // handle end commands
            retval = false ;
        }
        break;
        
    }
    return retval;
}

/*************************************************************************
*
* Build send packet header
*
*************************************************************************/
void Uart_BuildHeader(char ch) {

    My485UART[ch].RxFirst = 0;                                // Reset pointers
    My485UART[ch].RxLast  = 0;
    My485UART[ch].TxLast  = 0;

    My485UART[ch].pTxBuffer[0] = ANPRO10_SYN ;                        /* Sync */
    My485UART[ch].pTxBuffer[1] = ANPRO10_SYN ;                        /* Sync */
    My485UART[ch].pTxBuffer[2] = ANPRO10_SYN ;                        /* Sync */
    My485UART[ch].pTxBuffer[3] = ANPRO10_SOH ;                        /* Start of header */
    My485UART[ch].pTxBuffer[4] = My485UART[ch].pRxBuffer[2] ;      /* RXID */
    My485UART[ch].pTxBuffer[5] = My485UART[ch].pRxBuffer[3] ;      /* Rx address */
    My485UART[ch].pTxBuffer[6] = 0x10 + UnitID ;              /* Unit ID */
    My485UART[ch].pTxBuffer[7] = MyAddress();                /* Tx address */
    My485UART[ch].pTxBuffer[8] = 0 ;                         /* packlen HB, don't know yet */
    My485UART[ch].pTxBuffer[9] = 0 ;                         /* packlen LB, don't know yet */
    My485UART[ch].pTxBuffer[10] = 0 ;                        /* header checksum, don't know yet */
}

/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void Uart_BuildTail(char ch) {

    Uart_BuildHeader(ch);                                    // fist build the header

    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = ECMD_NMDWOACK & 0xff ;  // End command lb
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = ECMD_NMDWOACK >> 8 ;    // End command hb 
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = 0x00 ;                  // End data 
    
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = My485UART[ch].TxSeqCnt++ ;   // Sequence counter 

    My485UART[ch].pTxBuffer[8] = My485UART[ch].TxFirst -2;                // correct length because stx's
    My485UART[ch].pTxBuffer[9] = (My485UART[ch].TxFirst-2) >> 8 ;           // packet len high 

    My485UART[ch].pTxBuffer[10] = CalcDSTxChecksum(ch, 10) ;         // Get header checksum 

    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst] = CalcDSTxChecksum(ch, My485UART[ch].TxFirst) ; // Get checksum 
    My485UART[ch].TxFirst++ ;                                       // OBS!! must be inc here

    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = ANPRO10_EOT ;            // End of transmission 
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = 0x00 ;            //switch off transmitter delay 

    My485UART[ch].TxCount = My485UART[ch].TxFirst;                      //bytes to send 
    My485UART[ch].TxLast = 0;                                     // reset cunter
    My485UART[ch].TxPkCnt++ ;                                     // Count sent packages
    if (ch == 0){                                           // Turn on TXE for channel
        PORTE |= 0x04 ;                                     // TXE0 on
        SendPacketUart(0) ;                                     // send answer
    } else if (ch ==1){
        PORTE |= 0x08 ;                                     // TXE1 on
        SendPacketUart(1) ;                                     // send answer

    }
}


/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/
void BuildStatusData(char ch){

    short ntna ;
    My485UART[ch].RxSendReply = true ;                               // flag for answering 
    
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_STATUS & 0xff;     
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_STATUS >> 8;     
    ntna = My485UART[ch].TxFirst ;                                    /* remember index */
    My485UART[ch].TxFirst += 2 ;                                      // two byte length
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = ch ;                // channel
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = 0x10 +UnitID ;               // Product ID
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = MyAddress();           // unit address				/* get the address */
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = PROG_VERSION ;       // software version */
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = COMP_VERSION;        // cpmpability version
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = STORE_VERSION;        // cpmpability version
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = (RXSIZE_UART & 0xff);         // rx buffer size
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = (( RXSIZE_UART >> 8) & 0xff); // rx buffer size
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = (TXSIZE_UART & 0xff);         // tx buffer size
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = ((TXSIZE_UART >> 8) & 0xff);  // tx buffer size
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = ResetStatus ;                  // restart flag
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = PROGTYPE_BOOT ;                // Boot program

    My485UART[ch].pTxBuffer[ntna] = (My485UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    My485UART[ch].pTxBuffer[ntna+1]   = ((My485UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb
    
    ResetStatus = 0 ;                                                       // set reset stat to 0 = read
}

/*************************************************************************
*
* Build datablock for Flash ID
*
*************************************************************************/
void BuildFlashID(char ch) {

    short ntna;
    My485UART[ch].RxSendReply = true ;                               // flag for answering 
    
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_ID & 0xff;     
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_ID >> 8;     
    ntna = My485UART[ch].TxFirst ;                                    // remember index 
    My485UART[ch].TxFirst += 2 ;                                      // two byte length
    
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = PARTCODE ;
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = SIGNATURE_BYTE_1 ;
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = SIGNATURE_BYTE_2 ;
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = SIGNATURE_BYTE_3 ;

        
    My485UART[ch].pTxBuffer[ntna] = (My485UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    My485UART[ch].pTxBuffer[ntna+1] = ((My485UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
* Erase Flash 
*
*************************************************************************/
void EraseFlash(char ch) {

    unsigned short ntna, address;
    My485UART[ch].RxSendReply = true ;                               // flag for answering 
    
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_ERASE & 0xff;     
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_ERASE >> 8;     
    ntna = My485UART[ch].TxFirst ;                                    // remember index 
    My485UART[ch].TxFirst += 2 ;                                      // two byte length
    
    #ifdef LARGE_MEMORY               //SPM uses Z pointer but the pointer is only 16bit and
    RAMPZ = 0x00;                     //can only address up to 64Kbytes FLASH to adresse higher 
                                    //location it require the use of RAMPZ
    
    for(address=0;((address < (unsigned int)(APP_END&0xFFFF))|(RAMPZ == 0x00));address += PAGESIZE) {
        write_page(address,(1<<PGERS) + (1<<SPMEN));              //Perform page erase
        write_page(address, (1<<REENABLE_RWW_BIT) + (1<<SPMEN));  //Re-enable the RWW section
    
        if(address >=(0xFFFF-PAGESIZE)) //Last section on lower 64k segment is erased
           RAMPZ = (1<<RAMPZ0);         //RAMPZ has to incremented into upper 64k segment
    }
    RAMPZ = 0x00;                     //Clear RAMPZ pointer
    
    #else
    
    for(address=0;address < APP_END;address += PAGESIZE){  //Application section = 60 pages
        write_page(address,(1<<PGERS) + (1<<SPMEN));       //Perform page erase
        write_page(address, (1<<REENABLE_RWW_BIT) + (1<<SPMEN));  //Re-enable the RWW section
    }
    
    #endif          

    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = FLASH_ERASE_OK ;                 // Answer that the erase is OK

    My485UART[ch].pTxBuffer[ntna] = (My485UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    My485UART[ch].pTxBuffer[ntna+1] = ((My485UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
* Program Flash 
*
*************************************************************************/
void ProgramFlash(char ch, unsigned short pointer) {

    unsigned short ntna, address, Nobytes, i, Addr, intval, Ptr;
    My485UART[ch].RxSendReply = true ;                               // flag for answering 
    
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_PROG & 0xff;     
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_PROG >> 8;     
    ntna = My485UART[ch].TxFirst ;                                    // remember index 
    My485UART[ch].TxFirst += 2 ;                                      // two byte length
    
    address = My485UART[ch].pRxBuffer[pointer] + (My485UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    Nobytes = My485UART[ch].pRxBuffer[pointer] + (My485UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    Ptr = pointer;
    if (Nobytes > PAGESIZE) {
        My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = FLASH_PROG_PAGEF ;               // Answer with Page fault
    } else {
        #ifdef LARGE_MEMORY
        if(address >= 0x7FFF){
            RAMPZ = (1<<RAMPZ0);
        } else {
            RAMPZ = 0;
        }
        #endif            
        address = address << 1;                                     // convert from byte address to word address
        Addr = address;                                             // mirror the address
        for (i = 0; i < Nobytes; i+=2, address+=2, pointer+=2) {              // write data to flash
            fill_temp_buffer(My485UART[ch].pRxBuffer[pointer] + (My485UART[ch].pRxBuffer[pointer+1]<< 8),(address)); //call asm routine. 
        }
        write_page(Addr, (1<<PGWRT) + (1<<SPMEN));                  //Perform page write
        write_page(Addr, (1<<REENABLE_RWW_BIT) + (1<<SPMEN));       //Re-enable the RWW section
        My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = FLASH_PROG_OK;       // OK
        
        for (i = 0; i < Nobytes; i+=2, Addr+=2) {         // check the whole buffer
          intval = read_program_memory(Addr,0x00);
          if (My485UART[ch].pRxBuffer[Ptr++] != (intval & 0xff)) {
              My485UART[ch].pTxBuffer[My485UART[ch].TxFirst-1] = FLASH_PROG_ERROR;       // compare error
          }
          if (My485UART[ch].pRxBuffer[Ptr++] != ((intval>>8) & 0xff)) {
              My485UART[ch].pTxBuffer[My485UART[ch].TxFirst-1] = FLASH_PROG_ERROR;       // compare error
          }
        }
    }  
        
    My485UART[ch].pTxBuffer[ntna] = (My485UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    My485UART[ch].pTxBuffer[ntna+1] = ((My485UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
* Read Flash 
*
*************************************************************************/
void ReadFlash(char ch, unsigned short pointer) {

    unsigned short ntna, address, Nobytes, i, intval;
    My485UART[ch].RxSendReply = true ;                               // flag for answering 
    
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_READ & 0xff;     
    My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = CMD_REP_FLASH_READ >> 8;     
    ntna = My485UART[ch].TxFirst ;                                    // remember index 
    My485UART[ch].TxFirst += 2 ;                                      // two byte length
    
    for (i = 0; i<4; i++) {
        My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = My485UART[ch].pRxBuffer[pointer+i] ; // ansver with address and nob
    }
  
    address = My485UART[ch].pRxBuffer[pointer] | (My485UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    Nobytes = My485UART[ch].pRxBuffer[pointer] | (My485UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    if (Nobytes > PAGESIZE) {
        My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = FLASH_PROG_PAGEF ;               // Answer with Page fault
    } else {
      #ifdef LARGE_MEMORY
      if(address >= 0x7FFF){
        RAMPZ = (1<<RAMPZ0);
      } else {
        RAMPZ = 0;
      }
      #endif            
      address = address<<1;             // convert from byte address to word address
      for (i = 0; i < Nobytes; i+=2, address+=2) {   // receive the whole buffer
         intval = read_program_memory(address,0x00);
         My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = intval & 0xff;
         My485UART[ch].pTxBuffer[My485UART[ch].TxFirst++] = (intval>>8) & 0xff;
      }
    }

    My485UART[ch].pTxBuffer[ntna] = (My485UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    My485UART[ch].pTxBuffer[ntna+1] = ((My485UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
*  Exit bootloader program
*
*************************************************************************/
void ExitBootloader(char ch) {   


    while ( (EECR & 1<<EEWE) != 0 ) //chech if EEPROM is ready
        ;
    EEARL = (0x0fff & 0xff);
    EEARH = (0x0fff >> 8);
    EEDR = 0xaa;
    EECR |= (1<<EEMWE);
    EECR |= (1<<EEWE);
    while (EECR & (1<<EEWE))
      ;
      
    WDTCR = 0x08;               //Start watchdog to genetate restart
}


/*************************************************************************
*
*  Transmitting data on USARTs
*
*************************************************************************/
void SendPacketUart(char ch) {
    unsigned short delay, cnt;
    
    for (delay = 0; delay < 0xffff; delay++) {
        asm("nop") ;
        cnt++;
    }

    while ( My485UART[ch].TxCount > 0 ) {               // Any characters to send?
        sendchar(ch, My485UART[ch].pTxBuffer[ My485UART[ch].TxLast ]);  // Send a character

        if ((++My485UART[ch].TxLast)> TXSIZE_UART ) {     // End of buffer?
            My485UART[ch].TxLast = 0 ;                     // yes, reset pointer
        }
        My485UART[ch].TxCount--; 
    } 
    if (ch == 0){                                           // Turn on TXE for channel
        PORTE &= ~0x04 ;                                     // TXE0 off
    } else if (ch ==1){
        PORTE &= ~0x08 ;                                     // TXE1 off
    }
    cnt = 0;
}

/*************************************************************************
*
*  Receive data on USARTs
*
*************************************************************************/
void ReceivePacketUart(char ch) {

    switch (My485UART[ch].RxState) {                  // check status 
    case SYNC :
        // all functionallity in inerrupt routine 
        break ;
    case HEADER :
        if (My485UART[ch].RxLast >= 6) {             // receive header 
            My485UART[ch].RxPacklen = (My485UART[ch].pRxBuffer[4] +
                                 (My485UART[ch].pRxBuffer[5] * 256) ) ;    // Find length of package
            if (CalcDSRxChecksum(ch, 6) && (My485UART[ch].pRxBuffer[0] == (0x10 + UnitID))) { 
                                                 // header checksum OK and to me
                if ((My485UART[ch].RxPacklen < ((short) RXSIZE_UART-My485UART[ch].RxLast)) &&    /* chk. header */
                    (My485UART[ch].RxPacklen >= MIN_PACK_LEN)) {
                    My485UART[ch].RxState = RECEIVE ;       // Header ok og to data receive state
                    My485UART[ch].RxCount = My485UART[ch].RxLast + 1 ;    // Set receive counter
                } else {
                    GoToSyncUART(ch) ;                        // go to sync modus for recive
                }
            } else {
                GoToSyncUART(ch) ;                            // go to sync modus for recive
            }
        }
        break ;
    case RECEIVE :
        if (++My485UART[ch].RxCount >= My485UART[ch].RxPacklen) {
            if ((My485UART[ch].pRxBuffer[My485UART[ch].RxPacklen -1]) == ANPRO10_EOT) {
                if (CalcDSRxChecksum(ch, My485UART[ch].RxPacklen-2)) {
                    if ((My485UART[ch].pRxBuffer[1] == MyAddress())||       // message to me? or
                         (My485UART[ch].pRxBuffer[1] == 0xff)) {            // broadcast
                        hostAddress = My485UART[ch].pRxBuffer[3];            // address to sender (host)
                        My485UART[ch].RxState = HANDLE ;                     // Package OK
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
    if (++My485UART[ch].RxLast >= RXSIZE_UART) {                     // check pointer 
        My485UART[ch].RxLast = 0;                                     // reset pointer
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
    for (cnt = 4 ; cnt < len ; cnt++) {
        csum = crc[csum ^ My485UART[ch].pTxBuffer[cnt]] ;
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
        csum = crc[csum ^ My485UART[ch].pRxBuffer[cnt]] ;
    }
    if (csum == My485UART[ch].pRxBuffer[len]) {
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
        My485UART[ch].SyncCnt = 0 ;                        // ready for sync
        My485UART[ch].RxState = SYNC ;
        My485UART[ch].RxFirst = 0 ;
    }
}
