/*******************************************************
System clock initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

// I/O Registers definitions
#include <avr64db64.h>

// Standard definitions
#include <stddef.h>

void system_clocks_init(void)
{
unsigned char n,s;

// Optimize for speed
#pragma optsize- 
// Save interrupts enabled/disabled state
s=CPU_SREG;
// Disable interrupts
#asm("cli")

// Ensure that the external high-frequency clock source
// is first disabled before modifying its settings
n=0<<CLKCTRL_ENABLE_bp;
CPU_CCP=CCP_IOREG_gc;
CLKCTRL.XOSCHFCTRLA=n;

// Configure the external high-frequency clock source
// External source type: External Clock on XTALHF1 Pin
n=CLKCTRL_SELHF_EXTCLOCK_gc;
CPU_CCP=CCP_IOREG_gc;
CLKCTRL.XOSCHFCTRLA=n;

// Enable the external high-frequency clock source
n|=1<<CLKCTRL_ENABLE_bp;
CPU_CCP=CCP_IOREG_gc;
CLKCTRL.XOSCHFCTRLA=n;

// Main clock source: External Clock
// Peripheral clock output on CLKOUT (PORTA, Pin 7): Off
n=CLKCTRL_CLKSEL_EXTCLK_gc | (0<<CLKCTRL_CLKOUT_bp);
CPU_CCP=CCP_IOREG_gc;
CLKCTRL.MCLKCTRLA=n;

// Main clock prescaler division ratio: 1
// CPU and Peripheral clock: 4000,960 kHz
n=0;
CPU_CCP=CCP_IOREG_gc;
CLKCTRL.MCLKCTRLB=n;

// Configure the Clock Failure Detection
// CFD interrupt: Disabled
n=0<<CLKCTRL_CFD_bp;
CPU_CCP=CCP_IOREG_gc;
CLKCTRL.MCLKINTCTRL=n;

// Clock source to be monitored for a failure condition: Main Clock
// CFD enabled
n=CLKCTRL_CFDSRC_CLKMAIN_gc | (1<<CLKCTRL_CFDEN_bp);
CPU_CCP=CCP_IOREG_gc;
CLKCTRL.MCLKCTRLC=n;

// Restore interrupts enabled/disabled state
CPU_SREG=s;
// Restore optimization for size if needed
#pragma optsize_default
}

