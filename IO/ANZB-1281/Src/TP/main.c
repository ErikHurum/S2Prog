/*******************************************************
This program was created by the CodeWizardAVR V3.49 
Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*


Chip type               : AVR64DB64
Program type            : Application
AVR Core Clock frequency: 4,000960 MHz
Memory model            : Small
Data Stack size         : 2048
*******************************************************/

// I/O Registers definitions
#include <avr64db64.h>

// USART0 is used as the default input
// device by the 'getchar' function.
#define _ALTERNATE_GETCHAR_
// USART0 is used as the default output
// device by the 'putchar' function.
#define _ALTERNATE_PUTCHAR_
// Standard Input/Output functions
#include <stdio.h>
#include "delay.h"
#include <iobits.h>
#include "math.h"
#include "float.h"
#include "string.h"

// Clock System initialization function
#include "clock_init.h"

// I/O Ports initialization function
#include "ports_init.h"

// Timers/Counters initialization functions
#include "timers_init.h"

// USARTs initialization functions
#include "usarts_init.h"

// SPI initialization functions
#include "spi_init.h"

// PinName Definition of IO with macro
#include "PinName.h"

// Routine alle macro function
#include "Routine.h"

// Routine alle macro function
//#include "AD7715.h"

// Routine from SGcom
#include "SGcom.h"

// Routine from SGeep
#include "SGeep.h"

// routine 1Wire com
#include "1WIRE_COM.h"

// routine EEprom
#include "LocalEEprom.h"

// Declare your global variables here

void main(void)
{
// Declare your local variables here
unsigned char n;

//unsigned char  Buf[] = { 0x02,0x02 ,0xFE ,0x0A ,0x00 ,0x14 ,0x2F ,0x0A ,0x0D ,0x0A ,0x68 ,0x76 ,0x00 ,0x00 ,0xBF ,0x0E ,0x80 ,0x3F ,0x05 ,0x00 };

//int Size = sizeof(Buf);
//
//unsigned char CheckSum = 0;
//unsigned char Cnt;
//unsigned char tmpBuf;
//unsigned char Index;
//unsigned char TmPIndex;
//unsigned char CRC_or;
//
//unsigned char CRCTest;
//unsigned char RunSYS=0;
// Interrupt system initialization
// Optimize for speed
#pragma optsize- 
// Make sure the interrupts are disabled
#asm("cli")
// Round-robin scheduling for level 0 interrupt: Off
// The interrupt vectors will be placed at the start of the Application FLASH section
n=0;
CPU_CCP=CCP_IOREG_gc;
CPUINT.CTRLA=n;
// Restore optimization for size if needed
#pragma optsize_default

// The vectors with lower addresses will have
// higher interrupt level 0 priority (default)
CPUINT.LVL0PRI=0;

// The higher interrupt priority level 1 is not used
CPUINT.LVL1VEC=0;

// System clocks initialization
system_clocks_init();

// Brown-Out Detector and Voltage Level Monitor initialization
// The settings below are applied to the BODCFG fuse
// that will be programmed if the
// Project|Configure|After Build|Action: Program the Chip|Program Fuses
// menu option is enabled in the IDE
// BOD operation in Active or Idle modes: Enabled
// BOD operation in Standby or Power-Down sleep modes: Disabled
// BOD level: 1,90V
// BODCFG=0x04

// The Multi-Voltage I/O is disabled by programming the
// MVSYSCFG bits of the SYSCFG1 fuse to Single-Supply configuration
// SYSCFG1=0x10
// This setting will be applied if the
// Project|Configure|After Build|Action: Program the Chip|Program Fuses
// menu option is enabled in the IDE

// I/O Ports initialization
ports_init();

// Timer/Counter TCA0 initialization
tca0_init();

// Timer/Counter TCA1 initialization
tca1_init();

// USART0 initialization
usart0_init();

// SPI1 initialization
spi1_init();


/*
    InitRegs();  done with Codevision Wizard
*/
// see Routine.c 
    InitVar();
    InitStartup();  
    InitEEprom();   // init EEprom clear if first time
	Led (4,ON);
    ResetADCBySW();
    ADC_CS_LOW;  
    //#asm("sei")
    set_interrupt_mask(0);	/* Enable interrupt */
//    SCI0_SCR = 0x7c;            /* enable rx0/tx0 + rx0 interrupt */

    Led (4,OFF);
    CheckEepChannel()   ;   
/*
while (1)
{   unsigned char testbuf[8];
    unsigned char Testcsum;
	unsigned long	Sn;
    testbuf[0]=0x6D;
    testbuf[1]=0xA6;
    testbuf[2]=0x86;
    testbuf[3]=0x01;
    testbuf[4]=0x1d;
    testbuf[5]=0x30;
    testbuf[6]=0x30; 

    Sn=  (long)testbuf[0];
    Sn|= (long)testbuf[1]<<8;
    Sn|= (long)testbuf[2]<<16;
    Sn|= (long)testbuf[3]<<24;
    
    Testcsum = 0 ;
    for ( n=0 ; n < 7 ; n++ ) {
        Testcsum = crc[Testcsum ^ testbuf[n]] ;
    }
    
    testbuf[4]=Testcsum;
    testbuf[5]=0x6D;
    
}    
*/
    while ( TRUE ) 
    {
        #asm("wdr"); //KickDog();
        /* communication starts here */
        if ( rx_indx > rx_hndx ) 
        {   /* new char in buffer ? */
            if ( ReceiveRxPacket() ) 
            {
                HandleRxPacket() ;          /* Handle here */
                ResetRxPointer() ;          /* reset pointer */
            }
        }
        /* AD convert starts here */
        CheckConvert();
    }                            
}