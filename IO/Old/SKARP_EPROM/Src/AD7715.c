/****************************************************************************************
/ AD converter handling , AD7715
/
***************************************************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

/*************************************************************************
*   (This is a task)
*  AD7715 task 
*
*************************************************************************/
void AD7715(void) {
    char ch, Rev1 = 0; 
    unsigned int addata ;
    float Tempfloat;

    for (ch = 0; ch<12; ch++) {
        TData.Ana.Filter[ch] = 1.0;
    }
    TData.Ana.PortUsed = ReadEEPROMByte(EEPROM_PORTSETUP) + (ReadEEPROMByte(EEPROM_PORTSETUP+1) <<8); // Get setup from EEPROM
    SetRS4Port();                                           // and set power on ports

     
    WriteAdByte(0xff) ;             // Write 32 1's to reset
    WriteAdByte(0xff) ;
    WriteAdByte(0xff) ;
    WriteAdByte(0xff) ;
    
    // Calibrate and check if the card is layout rev 1?
    WriteAdByte(0x10) ;             // Next write setup reg 
    WriteAdByte(0x4e) ;             //  Ad setup data, unipolar, calibrate
    OS_Delay(250);
    OS_ClearEvents(&TCB_AD7715);
    OS_WaitEventTimed(1, 1000);
    
    ClrBit(PORTE,0xf0);                 // check channel 14 for 2.5 V
    SetBit(PORTE, (14 << 4) & 0xf0);    // check 
    WriteAdByte(0x10) ;                 // Next write data 
    WriteAdByte(0x0e) ;                 // Ad setup data, unipolar
    OS_Delay(85);
    OS_ClearEvents(&TCB_AD7715);
    OS_WaitEventTimed(1, 250);
    WriteAdByte(0x38) ;                 // Next read data 
    addata = ReadAdByte()* 256 ;        // read data 16 bit data from ad 
    addata += ReadAdByte() ;
    if (addata > 60000){
        Rev1 = true;
        for (ch = 0 ; ch < 12 ; ch++) {       // Get the gain and offset from the EEPROM
           TData.Ana.Offset[ch] = 0.0;
           TData.Ana.Gain[ch] = 0.9985;
       }
    } else {
        for (ch = 0 ; ch < 12 ; ch++) {       // Get the gain and offset from the EEPROM
           TData.Ana.Offset[ch] = 0.0;
           TData.Ana.Gain[ch] = 0.9965;
       }
    }
    for (ch = 0 ; ch < 12 ; ch++) {       // Get the gain and offset from the EEPROM
      ReadEEPROMBuffer( (ch | 0x80) * sizeof(float)*2, sizeof(float), (char*)&Tempfloat );
      
      if (IsFloat(Tempfloat) && Tempfloat > -2.0 && Tempfloat < 2.0 ) { 
        *((float*)&TData.Ana.Offset[ch]) = *((float*)&Tempfloat) ;  //offset
      }
      
      ReadEEPROMBuffer( ((ch | 0x80) * sizeof(float)*2) + sizeof(float), sizeof(float), (char*)&Tempfloat );
      
      if (IsFloat(Tempfloat) && Tempfloat > 0.98 && Tempfloat < 1.02) { 
        *((float*)&TData.Ana.Gain[ch]) = *((float*)&Tempfloat) ;  //gain
      }
   }
   
    while (1) {
        if (Rev1) {
           
            ClrBit(PORTE,0xf0); 
            SetBit(PORTE, (15 << 4) & 0xf0); // 0V at ch 16
            WriteAdByte(0x10) ;             // Next write setup reg 
            WriteAdByte(0x8e) ;             //  AStark test zero scale calibrate
            OS_Delay(250);
            OS_ClearEvents(&TCB_AD7715);
            OS_WaitEventTimed(1, 1000);
            
            ClrBit(PORTE,0xf0); 
            SetBit(PORTE, (14 << 4) & 0xf0); // 2.5V at ch 15
            WriteAdByte(0x10) ;             // Next write setup reg 
            WriteAdByte(0xce) ;             //  AStark test full scale calibrate
            OS_Delay(250);
            OS_ClearEvents(&TCB_AD7715);
            OS_WaitEventTimed(1, 1000);
 
        } else {
            WriteAdByte(0x10) ;             // Next write setup reg 
            WriteAdByte(0x4e) ;             //  Internal calibration calibrate
            OS_Delay(250);
            OS_ClearEvents(&TCB_AD7715);
            OS_WaitEventTimed(1, 1000);
        }

        for (ch = 0 ; ch < 12 ; ch++) {
            ClrBit(PORTE,0xf0); 
            SetBit(PORTE, (ch << 4) & 0xf0);
            WriteAdByte(0x10) ;                 // Next write data 
            WriteAdByte(0x0e) ;                          // Ad setup data, unipolar
            OS_Delay(85);
            OS_ClearEvents(&TCB_AD7715);
            OS_WaitEventTimed(1, 250);
            WriteAdByte(0x38) ;             // Next read data 
            addata = ReadAdByte()* 256 ;        // read data 16 bit data from ad 
            addata += ReadAdByte() ;
            TData.Ana.Status[ch] = 0;                   // Result ok
            TData.Ana.Result[ch] += ((((((float)addata / 65535.0) * 25.0) * TData.Ana.Gain[ch])-TData.Ana.Offset[ch] - TData.Ana.Result[ch])
                                     / (TData.Ana.Filter[ch]+1.0))  ;             // readed value / 16bit * 2.5 volt range
        } 
    }
}

/*************************************************************************
*
*  Set ports on or off
*
*************************************************************************/
void SetAnaPort(void) {

    PORTC = (TData.Ana.PortUsed & 0xff) ;         // Set power on ports 0-7
    ClrBit(PORTB, 0xe1);                            // Set power on ports 8-11 off
    SetBit(PORTB, TData.Ana.PortUsed>>8 & 0x01);    // Set power on port 8
    SetBit(PORTB, TData.Ana.PortUsed>>4 & 0xe0);      // Set power on ports 9-11

}

/*************************************************************************
*
*  Read from AD-converter
*
*************************************************************************/
char ReadAdByte(void) {

    char i, readbyte;

    for (i = 0; i <  8; i++) {
        readbyte <<= 1 ;                    // shift to next bit 
        ClrBit(PORTD, ADCLK) ;
        SetBit(PORTD, ADCLK) ;                  // set clock line high 
        if (PING & ADDO) {                  // data  = 1?
            readbyte |= 0x01 ;                    // set bit high 
        } else {
            readbyte &= ~0x01 ;                   // set bit low 
        }
    }
    return readbyte ;
}

/*************************************************************************
*
*  Write to AD-converter
*
*************************************************************************/
void WriteAdByte(char data) {

    char i;

    for (i = 0; i <  8; i++) {
        ClrBit(PORTD, ADCLK) ;                  // set clock line low
        if (data & 0x80) {                  // data bit = 1? 
            SetBit(PORTG,ADDI) ;                  // set data high 
        } else {
            ClrBit(PORTG, ADDI) ;                 // set data low 
        }
        data <<= 1 ;                        // shift to next bit 
        SetBit(PORTD, ADCLK) ;                  // set clock line high 
    }           
}       

