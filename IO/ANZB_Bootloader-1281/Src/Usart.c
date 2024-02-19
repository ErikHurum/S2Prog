/****************************************************************************************
/ Com protocol for USART0 
/
***************************************************************************************/

#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __AVR_ATmega1281__
#include	"iom1281.h"
#endif
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "externals.h"
#include "assembly.h"
#include <intrinsics.h>
__near char TxBufferCh0[TXSIZE_UART];            // set up buffer size
__near char RxBufferCh0[RXSIZE_UART];


/*************************************************************************
*
*  Check the incoming packages
*
*************************************************************************/
void UsartCheckPackage(void) {

    unsigned short pointer;
    char retval;

    myUART.RxSendReply = false;                           // flag for answering set to fault
    myUART.TxFirst = 11;                        // Startpos for fist TX command
    pointer = 7;
    do {
        retval = CheckActionUart(pointer);
        pointer = pointer + RxBufferCh0[pointer + 2]
            + (RxBufferCh0[pointer + 3] * 256) + 4;            // Point to a command cmd hb/lb
    } while ( retval && (pointer < (myUART.RxPacklen - 4)) );
    if ( myUART.RxSendReply ) {                              //send answer
        Uart_BuildTail();
    }
    GoToSyncUART();                                    // go to sync modus for recive
}

/*************************************************************************
*
*  Check action on received data
*
*************************************************************************/
char CheckActionUart(unsigned short pointer) {

    const char ch = 0;
    unsigned short   command;
    char    retval = true;

    command = RxBufferCh0[pointer] | (RxBufferCh0[pointer + 1] << 8);
    switch ( command ) {                                      // check action
    case CMD_REQ_STATUS :                                    // Regusest status for target
        BuildStatusData(ch);
        break;

    case CMD_FLASH_ID :                                     // Send flash ID
        BuildFlashID(ch);
        break;

    case CMD_FLASH_ERASE :                                 // Erase flash
        EraseFlash();
        break;

    case CMD_FLASH_PROG :                                   // Prog flash
        ProgramFlash(pointer + 4);
        break;

    case CMD_FLASH_READ :                                   // Read flash
        ReadFlash(pointer + 4);
        break;

    case CMD_EXIT_BOOTLOADER :                                // Leave bootlaoder
        ExitBootloader(ch);
        break;

    default:
        if ( command < MAX_ECMD ) {                           // handle end commands
            retval = false;
        }
        break;

    }
    return retval;
}

//#include <intrinsics.h>

/*************************************************************************
*
* Build send packet header
*
*************************************************************************/
void Uart_BuildHeader(void) {
    //__disable_interrupt();
    myUART.RxFirst = 0;                                // Reset pointers
    myUART.RxLast  = 0;
    myUART.TxLast  = 0;


    TxBufferCh0[0] = ANPRO10_SYN;                        /* Sync */
    TxBufferCh0[1] = ANPRO10_SYN;                        /* Sync */
    TxBufferCh0[2] = ANPRO10_SYN;                        /* Sync */
    TxBufferCh0[3] = ANPRO10_SOH;                        /* Start of header */
    TxBufferCh0[4] = RxBufferCh0[2];      /* RXID */
    TxBufferCh0[5] = RxBufferCh0[3];      /* Rx address */
    TxBufferCh0[6] = 0x10 + UnitID;              /* Unit ID */
    TxBufferCh0[7] = MyAddress();                /* Tx address */
    TxBufferCh0[8] = 0;                         /* packlen HB, don't know yet */
    TxBufferCh0[9] = 0;                         /* packlen LB, don't know yet */
    TxBufferCh0[10] = 0;                        /* header checksum, don't know yet */

    //__enable_interrupt();
}

/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void Uart_BuildTail(void) {
    Uart_BuildHeader();                                    // fist build the header

    TxBufferCh0[myUART.TxFirst++] = ECMD_NMDWOACK & 0xff;  // End command lb
    TxBufferCh0[myUART.TxFirst++] = ECMD_NMDWOACK >> 8;    // End command hb
    TxBufferCh0[myUART.TxFirst++] = 0x00;                  // End data

    TxBufferCh0[myUART.TxFirst++] = myUART.TxSeqCnt++;   // Sequence counter

    TxBufferCh0[8] = myUART.TxFirst - 2;                // correct length because stx's
    TxBufferCh0[9] = (myUART.TxFirst - 2) >> 8;           // packet len high

    TxBufferCh0[10] = CalcDSTxChecksum(10);         // Get header checksum

    TxBufferCh0[myUART.TxFirst] = CalcDSTxChecksum(myUART.TxFirst); // Get checksum
    myUART.TxFirst++;                                       // OBS!! must be inc here

    TxBufferCh0[myUART.TxFirst++] = ANPRO10_EOT;            // End of transmission
    TxBufferCh0[myUART.TxFirst++] = 0x00;            //switch off transmitter delay

    myUART.TxCount = myUART.TxFirst;                      //bytes to send
    myUART.TxLast = 0;                                     // reset cunter
    myUART.TxPkCnt++;                                     // Count sent packages
    PORTE |= 0x04;                                     // TXE0 on
    SendPacketUart();                                     // send answer
}


/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/
void BuildStatusData(char ch) {

    short ntna;
    myUART.RxSendReply = true;                               // flag for answering

    TxBufferCh0[myUART.TxFirst++] = CMD_REP_STATUS & 0xff;
    TxBufferCh0[myUART.TxFirst++] = CMD_REP_STATUS >> 8;
    ntna = myUART.TxFirst;                                    /* remember index */
    myUART.TxFirst += 2;                                      // two byte length
    TxBufferCh0[myUART.TxFirst++] = ch;                // channel
    TxBufferCh0[myUART.TxFirst++] = 0x10 + UnitID;               // Product ID
    TxBufferCh0[myUART.TxFirst++] = MyAddress();           // unit address				/* get the address */
    TxBufferCh0[myUART.TxFirst++] = PROG_VERSION;       // software version */
    TxBufferCh0[myUART.TxFirst++] = COMP_VERSION;        // cpmpability version
    TxBufferCh0[myUART.TxFirst++] = STORE_VERSION;        // cpmpability version
    TxBufferCh0[myUART.TxFirst++] = (RXSIZE_UART & 0xff);         // rx buffer size
    TxBufferCh0[myUART.TxFirst++] = ((RXSIZE_UART >> 8) & 0xff); // rx buffer size
    TxBufferCh0[myUART.TxFirst++] = (TXSIZE_UART & 0xff);         // tx buffer size
    TxBufferCh0[myUART.TxFirst++] = ((TXSIZE_UART >> 8) & 0xff);  // tx buffer size
    TxBufferCh0[myUART.TxFirst++] = ResetStatus;                  // restart flag
    TxBufferCh0[myUART.TxFirst++] = PROGTYPE_BOOT;                // Boot program

    TxBufferCh0[ntna] = (myUART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
    TxBufferCh0[ntna + 1] = ((myUART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

    ResetStatus = 0;                                                       // set reset stat to 0 = read
}

/*************************************************************************
*
* Build datablock for Flash ID
*
*************************************************************************/
void BuildFlashID(char ch) {

    short ntna;
    myUART.RxSendReply = true;                               // flag for answering

    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_ID & 0xff;
    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_ID >> 8;
    ntna = myUART.TxFirst;                                    // remember index
    myUART.TxFirst += 2;                                      // two byte length

    TxBufferCh0[myUART.TxFirst++] = PARTCODE;
    TxBufferCh0[myUART.TxFirst++] = SIGNATURE_BYTE_1;
    TxBufferCh0[myUART.TxFirst++] = SIGNATURE_BYTE_2;
    TxBufferCh0[myUART.TxFirst++] = SIGNATURE_BYTE_3;


    TxBufferCh0[ntna] = (myUART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
    TxBufferCh0[ntna + 1] = ((myUART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

}

/*************************************************************************
*
* Erase Flash 
*
*************************************************************************/
void EraseFlash(void) {

    unsigned short ntna, address;
    myUART.RxSendReply = true;                               // flag for answering

    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_ERASE & 0xff;
    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_ERASE >> 8;
    ntna = myUART.TxFirst;                                    // remember index
    myUART.TxFirst += 2;                                      // two byte length

#ifdef LARGE_MEMORY               //SPM uses Z pointer but the pointer is only 16bit and
    RAMPZ = 0x00;                     //can only address up to 64Kbytes FLASH to adresse higher
    //location it require the use of RAMPZ

    for ( address = 0; ((address < (unsigned int)(APP_END & 0xFFFF)) | (RAMPZ == 0x00)); address += PAGESIZE ) {
        write_page(address, (1 << PGERS) + (1 << SPMEN));              //Perform page erase
        write_page(address, (1 << REENABLE_RWW_BIT) + (1 << SPMEN));  //Re-enable the RWW section

        if ( address >= (0xFFFF - PAGESIZE) ) //Last section on lower 64k segment is erased
            RAMPZ = (1 << RAMPZ0);         //RAMPZ has to incremented into upper 64k segment
    }
    RAMPZ = 0x00;                     //Clear RAMPZ pointer

#else

    for ( address = 0; address < APP_END; address += PAGESIZE ) {  //Application section = 60 pages
        write_page(address, (1 << PGERS) + (1 << SPMEN));       //Perform page erase
        write_page(address, (1 << REENABLE_RWW_BIT) + (1 << SPMEN));  //Re-enable the RWW section
    }

#endif
    TxBufferCh0[myUART.TxFirst++] = FLASH_ERASE_OK;                 // Answer that the erase is OK

    TxBufferCh0[ntna] = (myUART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
    TxBufferCh0[ntna + 1] = ((myUART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

}

/*************************************************************************
*
* Program Flash 
*
*************************************************************************/
void ProgramFlash(unsigned Pointer) {
    __watchdog_reset();

    unsigned ntna;
    myUART.RxSendReply = true;                               // flag for answering

    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_PROG & 0xff;
    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_PROG >> 8;
    ntna = myUART.TxFirst;                                    // remember index
    myUART.TxFirst += 2;                                      // two byte length

    unsigned Address = RxBufferCh0[Pointer + 0] + (RxBufferCh0[Pointer + 1] << 8); // save address
    unsigned Nobytes = RxBufferCh0[Pointer + 2] + (RxBufferCh0[Pointer + 3] << 8); // save address
    Pointer += 4;
    unsigned Ptr = Pointer;
    if ( Nobytes > PAGESIZE ) {
        TxBufferCh0[myUART.TxFirst++] = FLASH_PROG_PAGEF;               // Answer with Page fault
    } else {
#ifdef LARGE_MEMORY
        if ( Address >= 0x7FFF ) {
            RAMPZ = (1 << RAMPZ0);
        } else {
            RAMPZ = 0;
        }
#endif
        Address = Address << 1;                                     // convert from byte address to word address
        unsigned Addr = Address;                                             // mirror the address
        for ( unsigned i = 0; i < Nobytes; i += 2, Address += 2, Pointer += 2 ) {              // write data to flash
            fill_temp_buffer(RxBufferCh0[Pointer] + (RxBufferCh0[Pointer + 1] << 8), (Address)); //call asm routine.
        }
        write_page(Addr, (1 << PGWRT) + (1 << SPMEN));                  //Perform page write
        write_page(Addr, (1 << REENABLE_RWW_BIT) + (1 << SPMEN));       //Re-enable the RWW section
        TxBufferCh0[myUART.TxFirst++] = FLASH_PROG_OK;       // OK

        for ( unsigned i = 0; i < Nobytes; i += 2, Addr += 2 ) {         // check the whole buffer
            unsigned intval = read_program_memory(Addr, 0x00);
            if ( RxBufferCh0[Ptr++] != (intval & 0xff) ) {
                TxBufferCh0[myUART.TxFirst - 1] = FLASH_PROG_ERROR;       // compare error
            }
            if ( RxBufferCh0[Ptr++] != ((intval >> 8) & 0xff) ) {
                TxBufferCh0[myUART.TxFirst - 1] = FLASH_PROG_ERROR;       // compare error
            }
        }
    }

    TxBufferCh0[ntna] = (myUART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
    TxBufferCh0[ntna + 1] = ((myUART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

}

/*************************************************************************
*
* Read Flash 
*
*************************************************************************/
void ReadFlash(unsigned Pointer) {
    __watchdog_reset();

    unsigned short ntna;
    myUART.RxSendReply = true;                               // flag for answering

    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_READ & 0xff;
    TxBufferCh0[myUART.TxFirst++] = CMD_REP_FLASH_READ >> 8;
    ntna = myUART.TxFirst;                                    // remember index
    myUART.TxFirst += 2;                                      // two byte length

    for ( unsigned i = 0; i < 4; i++ ) {
        TxBufferCh0[myUART.TxFirst++] = RxBufferCh0[Pointer + i]; // ansver with address and nob
    }

    unsigned Address = RxBufferCh0[Pointer + 0] + (RxBufferCh0[Pointer + 1] << 8); // save address
    unsigned Nobytes = RxBufferCh0[Pointer + 2] + (RxBufferCh0[Pointer + 3] << 8); // save address
    if ( Nobytes > PAGESIZE ) {
        TxBufferCh0[myUART.TxFirst++] = FLASH_PROG_PAGEF;               // Answer with Page fault
    } else {
#ifdef LARGE_MEMORY
        if ( Address >= 0x7FFF ) {
            RAMPZ = (1 << RAMPZ0);
        } else {
            RAMPZ = 0;
        }
#endif
        Address = Address << 1;             // convert from byte address to word address
        for ( unsigned i = 0; i < Nobytes; i += 2, Address += 2 ) {   // receive the whole buffer
            unsigned intval = read_program_memory(Address, 0x00);
            TxBufferCh0[myUART.TxFirst++] = intval & 0xff;
            TxBufferCh0[myUART.TxFirst++] = (intval >> 8) & 0xff;
        }
    }

    TxBufferCh0[ntna] = (myUART.TxFirst  - ntna - 2) & 0xff;      // length of data block lb
    TxBufferCh0[ntna + 1] = ((myUART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

}

/*************************************************************************
*
*  Exit bootloader program
*
*************************************************************************/
void ExitBootloader(char ch) {


    while ( (EECR & 1 << EEPE) != 0 ) //chech if EEPROM is ready
    ;
    EEARL = (0x0fff & 0xff);
    EEARH = (0x0fff >> 8);
    EEDR = 0xaa;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
    while ( EECR & (1 << EEPE) );
    WDTCSR = 0x08;               //Start watchdog to genetate restart
    while (1) {
        // Dummy loop!
    }
    //AppStart();        					// Jump to Reset vector 0x0000 in Application Section

}


/*************************************************************************
*
*  Transmitting data on USARTs
*
*************************************************************************/
void SendPacketUart(void) {
    unsigned cnt = 0;

    for ( unsigned delay = 0; delay < 0xffff; delay++ ) {
        asm("nop");
        cnt++;
    }
    __watchdog_reset();
    while ( myUART.TxCount > 0 ) {               // Any characters to send?
        sendchar(TxBufferCh0[myUART.TxLast]);  // Send a character

        if ( (++myUART.TxLast) > TXSIZE_UART ) {     // End of buffer?
            myUART.TxLast = 0;                     // yes, reset pointer
        }
        myUART.TxCount--;
    }
    PORTE &= ~0x04;                                     // TXE0 off
    cnt = 0;
}

/*************************************************************************
*
*  Receive data on USARTs
*
*************************************************************************/
void ReceivePacketUart(char ch) {
    __watchdog_reset();

    switch ( myUART.RxState ) {                  // check status
    case SYNC :
        // all functionallity in inerrupt routine
        break;
    case HEADER :
        if ( myUART.RxLast >= 6 ) {             // receive header
            myUART.RxPacklen = (RxBufferCh0[4] +
                                (RxBufferCh0[5] * 256));    // Find length of package
            if ( CalcDSRxChecksum(ch, 6) && (RxBufferCh0[0] == (0x10 + UnitID)) ) {
                // header checksum OK and to me
                if ( (myUART.RxPacklen < ((short)RXSIZE_UART - myUART.RxLast)) &&    /* chk. header */
                     (myUART.RxPacklen >= MIN_PACK_LEN) ) {
                    myUART.RxState = RECEIVE;       // Header ok og to data receive state
                    myUART.RxCount = myUART.RxLast + 1;    // Set receive counter
                } else {
                    GoToSyncUART();                        // go to sync modus for recive
                }
            } else {
                GoToSyncUART();                            // go to sync modus for recive
            }
        }
        break;
    case RECEIVE :
        if ( ++myUART.RxCount >= myUART.RxPacklen ) {
            if ( (RxBufferCh0[myUART.RxPacklen - 1]) == ANPRO10_EOT ) {
                if ( CalcDSRxChecksum(ch, myUART.RxPacklen - 2) ) {
                    if ( (RxBufferCh0[1] == MyAddress()) ||       // message to me? or
                         (RxBufferCh0[1] == 0xff) ) {            // broadcast
                        hostAddress = RxBufferCh0[3];            // address to sender (host)
                        myUART.RxState = HANDLE;                     // Package OK
                    } else {
                        GoToSyncUART();                             // go to sync modus for recive
                    }
                } else {
                    GoToSyncUART();                                // go to sync modus for recive
                }
            } else {
                GoToSyncUART();                                    // go to sync modus for recive
            }
        }
        break;
    case HANDLE :
        break;
    default :
        GoToSyncUART();                                            // go to sync modus for recive
        break;
    }                                                           // end switch
    if ( ++myUART.RxLast >= RXSIZE_UART ) {                     // check pointer
        myUART.RxLast = 0;                                     // reset pointer
    }
}
/*************************************************************************
*
* Calculate tx checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
char CalcDSTxChecksum(unsigned short len) {

    unsigned short  cnt;
    unsigned char   csum;

    csum = 0;
    for ( cnt = 4; cnt < len; cnt++ ) {
        csum = crc[csum ^ TxBufferCh0[cnt]];
    }
    return csum;
}

/*************************************************************************
*
* Calculate rx packet checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
short CalcDSRxChecksum(char ch, unsigned short len) {

    unsigned short  cnt;
    unsigned char   csum;

    csum = 0;
    for ( cnt = 0; cnt < len; cnt++ ) {
        csum = crc[csum ^ RxBufferCh0[cnt]];
    }
    if ( csum == RxBufferCh0[len] ) {
        return true;
    } else {
        return false;
    }
}

/*************************************************************************
*
* Goes to sync mode
*
*************************************************************************/
__monitor void GoToSyncUART() {
    __watchdog_reset();

    myUART.SyncCnt = 0;                        // ready for sync
    myUART.RxState = SYNC;
    myUART.RxFirst = 0;
}
