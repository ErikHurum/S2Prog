/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     LocalEEprom.h
     * @brief    Routine Header File
     * @version  V0.00
     * @date     14. December 2022
     * @note
*

*******************************************************/


#ifndef ___LOCALEEPROM_H_
#define ___LOCALEEPROM_H_

#define LOCK_BYTE   0x55
#define UNLOCK_BYTE   0xAA
#define DEFAULT_EEPROM_STATUS   0xff
#define PROGRAMED_EEPROM_STATUS   0x0F

extern eeprom unsigned char FirtByteEEprom;         // can be corrupt
extern eeprom unsigned char EEpromInitByte;         // set when start program first time
extern eeprom unsigned char SerielNummerLock;       // if == LOCK_BYTE not avable to write SN
extern eeprom unsigned char EEpromScratchpad [32];  // scratchPAD to be compatible to all program
extern eeprom unsigned char EESerielNummer[8];      // Seriel Nummer Buffer one time program
extern eeprom unsigned char EESerielNummerCRC;      // CRC of Seriel Nummer to control if corrupt SN.
extern eeprom unsigned char EEpromStatusByte;       // eeprom status 
extern eeprom unsigned char EEpromDallasSN[8];      // to be compatible <8bit CRC><48 SN=data> <8bit Familiy code>

void InitEEprom (void);
#endif 
