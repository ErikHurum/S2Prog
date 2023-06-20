/*******************************************************
This program was created by the CodeWizardAVR V3.49 
Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
Version : 
Date    : 08.06.2022
Author  : 
Company : 
Comments: 


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

// Declare your global variables here

void main(void)
{
// Declare your local variables here
unsigned char n;

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

// Globally enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
