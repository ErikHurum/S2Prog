/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     LocalEEprom.c
     * @brief    Routine Header File
     * @version  V0.00
     * @date     14. December 2022
     * @note
*

*******************************************************/

#include "Routine.h"
#include "PinName.h"
#include "SGcom.h"
#include "SGeep.h"
#include "LocalEEprom.h"

// I/O Registers definitions
#include <avr64db64.h>
#include <stdio.h>
#include "delay.h"
#include <iobits.h>
#include "math.h"
#include "float.h"
// Standard definitions
#include <stddef.h>

// SPI initialization functions
#include "spi_init.h"
#include "usarts_init.h"


// define EEprom variable
// 
//first byte of EEprom will not be used in the program 
eeprom unsigned char FirtByteEEprom=0xAA;    // can be corrupt
eeprom unsigned char EEpromInitByte=0xAA;;    // set when start program first time
eeprom unsigned char SerielNummerLock=0xAA;;      // if == LOCK_BYTE not avable to write SN
eeprom unsigned char EEpromScratchpad [32]; // scratchPAD to be compatible to all program
eeprom unsigned char EESerielNummer[8];     // Seriel Nummer Buffer one time program
eeprom unsigned char EESerielNummerCRC=0xAA;;     // CRC of Seriel Nummer to control if corrupt SN.
eeprom unsigned char EEpromStatusByte=0xAA;;      // eeprom status 
eeprom unsigned char EEpromDallasSN[8];     // to be compatible <8bit CRC><48 SN=data> <8bit Familiy code>


void InitEEprom (void)
{   unsigned char data;
    unsigned char buffer[8];
    unsigned char localCRC=0;  
    unsigned char i;
    data= EEpromInitByte;
	//data=0;	// debugg
    if ( data != LOCK_BYTE )
    {   EEpromInitByte = LOCK_BYTE;  // set eeprom to lock byte
        FirtByteEEprom = LOCK_BYTE;  // set eeprom to lock byte
        EEpromStatusByte=DEFAULT_EEPROM_STATUS;
        for (i=0; i < 8; i++)   // clear Serial nummer
        {   EESerielNummer[i]=0xFF;
            //EESerielNummer[i]=0x00; // test 250123
        }
        EESerielNummerCRC=0xFF;    // clear CRC
        for (i=0; i < 32; i++)
        { EEpromScratchpad[i]=0xFF;    // clear ScratchPad
        } 
        SerielNummerLock= UNLOCK_BYTE;
        // Make EEpromDallesSN
        buffer[0]= 0;    //crc
        buffer[1]= 1;   // write 14 01 22 
        buffer[2]= 4;
        buffer[3]= 1;
        buffer[4]= 2;
        buffer[5]= 2;
        buffer[6]= 2;
        buffer[7]= 0x14; 
        localCRC=0;         // 25.01.23 Clr localCRC & "for loop" to 8 , 7 before       
        for ( i =1; i < 8;i++)
        {   data=buffer[i];
            localCRC= crc[ localCRC ^ data ];
        } 
        buffer[0]=localCRC;   
        // save data to EEprom
        for ( i =0; i < 8;i++)
        {   EEpromDallasSN[i]= buffer[i];
        } 
        delay_ms(10);       
    } 
}