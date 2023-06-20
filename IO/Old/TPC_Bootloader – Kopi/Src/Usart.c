/****************************************************************************************
/ Com protocol for USART0 
/
***************************************************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "assembly.h"


/*************************************************************************
*
*  Check the incoming packages
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
    } while (retval && (pointer < (UART[ch].RxPacklen - 2 )));
    if (UART[ch].RxSendReply) {                              //send answer
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

   command = UART[ch].pRxBuffer[pointer] ;
   switch (command) {                                      // check action 
   case ANP1_REQ_STAT :                                    // Regusest status for target
        if (UART[ch].pRxBuffer[pointer+2] == MySecAddress) {           // unit adddress sec
              BuildStatusData(ch) ;
        }                      
        break;
        
    case ANP1_FLASH_ID :                                     // Send flash ID
        if (UART[ch].pRxBuffer[pointer+2] == MySecAddress) {           // unit adddress sec
             BuildFlashID(ch) ;
        }
        break ;
        
    case ANP1_FLASH_ERASE :                                 // Erase flash
        if (UART[ch].pRxBuffer[pointer+2] == MySecAddress) {           // unit adddress sec
            EraseFlash(ch) ;
        }
        break ;
        
    case ANP1_FLASH_PROG :                                   // Prog flash
        if (UART[ch].pRxBuffer[pointer+2] == MySecAddress) {           // unit adddress sec
            ProgramFlash(ch, pointer+3) ;
        }
        break ;
        
    case ANP1_FLASH_READ :                                   // Read flash
        if (UART[ch].pRxBuffer[pointer+2] == MySecAddress) {           // unit adddress sec
           ReadFlash(ch, pointer+3) ;
        }
        break ;
        
    case ANP1_EXIT_BOOTLOADER :                                // Leave bootlaoder
        if (UART[ch].pRxBuffer[pointer+2] == MySecAddress) {           // unit adddress sec
            ExitBootloader(ch) ; 
        }
        break ;
        
    default:
        if (command < ANP1_MAX_ECMD) {                           // handle end commands
            retval = false ;
        }
        break;
        
    }
    return retval;
}

/*************************************************************************
*
* Build send packet header
* *her*AStmark
*************************************************************************/
void Uart_BuildHeader(char ch) {

    UART[ch].RxFirst = 0;                                // Reset pointers
    UART[ch].RxLast  = 0;
    UART[ch].TxLast  = 0;

    UART[ch].pTxBuffer[0] = ANPRO1_SYN ;                        /* Sync */
    UART[ch].pTxBuffer[1] = ANPRO1_SYN ;                        /* Sync */
    UART[ch].pTxBuffer[2] = hostAddress ;                 /* RXID */
    UART[ch].pTxBuffer[3] = MyPriAddress;                 /* Tx address pri*/
    UART[ch].pTxBuffer[4] = 0 ;                          /* packlen HB, don't know yet */
    UART[ch].pTxBuffer[5] = 0 ;                          /* packlen LB, don't know yet */
}

/*************************************************************************
*
* Build  packet tail
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
       SetBit(PORTG, 0x10) ;                                //Use the alarmled as TXE signal
       SetBit(PORTE, 0x04) ;                                     // TXE0 on
        SendPacketUart(0) ;                                     // send answer
    } else if (ch ==1) {
        // not used
    }

}


/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/
void BuildStatusData(char ch){

    short ntna ;
    UART[ch].RxSendReply = true ;                               // flag for answering 

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_STAT;     
    ntna = UART[ch].TxFirst++ ;                                    // remember index 
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress;           // unit adddress sec
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = PROG_VERSION + PROGTYPE_BOOT ; // software version Bit 7 = bootloader
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = UnitID;                       // unit id
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (RXSIZE_UART & 0xff);         // rx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (( RXSIZE_UART >> 8) & 0xff); // rx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TXSIZE_UART & 0xff);         // tx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((TXSIZE_UART >> 8) & 0xff);  // tx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = RestartStatus ;                  // restart flag
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0; //Ser no1 ;                // Application program
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0; //Ser no2 ;                // Application program
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0; //Ser no3 ;                // Application program
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0; //Ser no4 ;                // Application program

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb

    RestartStatus = 0 ;                                                  // set reset stat to 0 = read    
}

/*************************************************************************
*
* Build datablock for Flash ID
* 
*************************************************************************/
void BuildFlashID(char ch) {

    short ntna;
    UART[ch].RxSendReply = true ;                               // flag for answering 
 
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_FLASH_ID;     
    ntna = UART[ch].TxFirst++ ;               /* remember index */
                                       
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress;           // unit adddress sec
   
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = PARTCODE ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = SIGNATURE_BYTE_1 ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = SIGNATURE_BYTE_2 ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = SIGNATURE_BYTE_3 ;

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Erase Flash 
*
*************************************************************************/
void EraseFlash(char ch) {

    unsigned short ntna, address;
    UART[ch].RxSendReply = true ;                               // flag for answering 
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_FLASH_ERASE;     
    ntna = UART[ch].TxFirst++ ;                                    /* remember index */
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress;           // unit adddress sec
   
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

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = FLASH_ERASE_OK ;                 // Answer that the erase is OK

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Program Flash 
*
*   OBS!! This differ from the ANPRO10 protocol boot loader
*************************************************************************/
void ProgramFlash(char ch, unsigned short pointer) {

    unsigned short ntna, address, Nobytes, i, Addr, intval;
    UART[ch].RxSendReply = true ;                               // flag for answering 
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_FLASH_PROG;     
    ntna = UART[ch].TxFirst++ ;                         /* remember index */
                                      
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress;           // unit adddress sec
   
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = FLASH_PROG_OK;       // OK
   
    address = UART[ch].pRxBuffer[pointer] + (UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    Nobytes = UART[ch].pRxBuffer[pointer] + (UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    if (UART[ch].pRxBuffer[pointer++] == 0x00) {          // copy first part to buffer (128 byte)
        for (i = 0; i < Nobytes; i++){                    // copy data to buffer
            PageBuffer[i] = UART[ch].pRxBuffer[pointer++];  
        }
        UART[ch].pTxBuffer[UART[ch].TxFirst-1] = FLASH_COPYL_OK;       // Copy OK
        NoBLow = Nobytes  ;                               // Number of bytes in low data
    } else {
        for (i = NoBLow; i < NoBLow + Nobytes; i++){                    // copy data to buffer
            PageBuffer[i] = UART[ch].pRxBuffer[pointer++];  
        }
        Nobytes += NoBLow;                                    // toatl no of bytes
        if (Nobytes > PAGESIZE) {
            UART[ch].pTxBuffer[UART[ch].TxFirst++] = FLASH_PROG_PAGEF ;               // Answer with Page fault
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
                fill_temp_buffer(PageBuffer[i] + (PageBuffer[i+1]<< 8),(address)); //call asm routine. 
            }
            write_page(Addr, (1<<PGWRT) + (1<<SPMEN));                  //Perform page write
            write_page(Addr, (1<<REENABLE_RWW_BIT) + (1<<SPMEN));       //Re-enable the RWW section
            
            for (i = 0; i < Nobytes; Addr+=2) {         // check the whole buffer
              intval = read_program_memory(Addr,0x00);
              if (PageBuffer[i++] != (intval & 0xff)) {
                  UART[ch].pTxBuffer[UART[ch].TxFirst-1] = FLASH_PROG_ERROR;       // compare error
              }
              if (PageBuffer[i++] != ((intval>>8) & 0xff)) {
                  UART[ch].pTxBuffer[UART[ch].TxFirst-1] = FLASH_PROG_ERROR;       // compare error
              }
            }
        }  
    }
        
    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
}

/*************************************************************************
*
* Read Flash 
*
*   Not implmented in this bootloader
*
*************************************************************************/
void ReadFlash(char ch, unsigned short pointer) {

    unsigned short ntna, address, Nobytes, i, intval;
    UART[ch].RxSendReply = true ;                               // flag for answering 
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANP1_REP_FLASH_READ;     
    ntna = UART[ch].TxFirst++ ;                               /* remember index */
    
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MySecAddress;           // unit adddress sec
   
    for (i = 0; i<4; i++) {
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = UART[ch].pRxBuffer[pointer+i] ; // ansver with address and nob
    }
  
    address = UART[ch].pRxBuffer[pointer] | (UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    Nobytes = UART[ch].pRxBuffer[pointer] | (UART[ch].pRxBuffer[pointer+1]<<8); // save address
    pointer += 2;
    if (Nobytes > PAGESIZE) {
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = FLASH_PROG_PAGEF ;               // Answer with Page fault
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
         UART[ch].pTxBuffer[UART[ch].TxFirst++] = intval & 0xff;
         UART[ch].pTxBuffer[UART[ch].TxFirst++] = (intval>>8) & 0xff;
      }
    }
    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 1) ;      // length of data block lb
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

    while ( UART[ch].TxCount > 0 ) {               // Any characters to send?
        sendchar(ch, UART[ch].pTxBuffer[ UART[ch].TxLast ]);  // Send a character

        if ((++UART[ch].TxLast)> TXSIZE_UART ) {     // End of buffer?
            UART[ch].TxLast = 0 ;                     // yes, reset pointer
        }
        UART[ch].TxCount--; 
    } 
    if (ch == 0){                                           // Turn on TXE for channel
        PORTE &= ~0x04 ;                                     // TXE0 off
        ClrBit(PORTG, 0x10) ;                 //Light off on alarm lamp
    } else if (ch ==1){
 //       PORTE &= ~0x08 ;                                     // TXE1 off
    }
    cnt = 0;
}

/*************************************************************************
*
*  Receive data on USARTs
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
                  if (UART[ch].pRxBuffer[0] == MyPriAddress) {            // broadcast
                        hostAddress = UART[ch].pRxBuffer[1];            // address to sender (host)
                        UART[ch].RxState = HANDLE ;                     // Package OK
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
