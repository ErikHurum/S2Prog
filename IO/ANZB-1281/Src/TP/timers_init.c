/*******************************************************
Timers/Counters initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

// I/O Registers definitions
#include <avr64db64.h>
#include "Routine.h"

// Disable a Timer/Counter type A
void tca_disable(TCA_t *ptca)
{
// Timer/Counter TCA is disabled
ptca->SINGLE.CTRLA=0<<TCA_SINGLE_ENABLE_bp;
// Operate in 16-bit mode
ptca->SINGLE.CTRLD=0<<TCA_SINGLE_SPLITM_bp;
// Issue a reset command
ptca->SINGLE.CTRLECLR=TCA_SINGLE_CMD_RESET_gc;
}

// Timer/Counter TCA0 initialization
void tca0_init(void)
{
// First disable and reset the Timer/Counter TCA0
// Use 16-bit mode
tca_disable(&TCA0);

// Clock divider: 1
// Clock frequency: 4000,960 kHz
// TCA0 runs in standby: Off
TCA0.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc+(0<<TCA_SINGLE_RUNSTDBY_bp);

// Operating mode: Frequency Generation 16-bit OVF=TOP (CMP0)
// Set the waveform outputs configuration:
// WO0: Off
// WO1: Off
// WO2: PORTA, Pin 2
TCA0.SINGLE.CTRLB=TCA_SINGLE_WGMODE_FRQ_gc+
    (0<<TCA_SINGLE_CMP0EN_bp)+
    (0<<TCA_SINGLE_CMP1EN_bp)+
    (1<<TCA_SINGLE_CMP2EN_bp);

// Set the waveform outputs mapping
PORTMUX.TCAROUTEA=(PORTMUX.TCAROUTEA & (~PORTMUX_TCA0_gm)) | PORTMUX_TCA0_PORTA_gc;
// Note: The configuration for the waveform output signals
// is set in the ports_init function from ports_init.c

// Set the Timer Counter register
TCA0.SINGLE.CNT=0x00;

// In Frequency Generation mode the Timer Compare 0 register sets the
// specified frequency for the WO0, WO1, WO2 outputs: 1000 kHz
// Obtained frequency: 1000,24 kHz, -0,02 % error
TCA0.SINGLE.CMP0=0x01;

// The Timer Compare 1 register sets the specified
// phase for the WO1 output relative to WO0: 0,00°
TCA0.SINGLE.CMP1=0x00;

// The Timer Compare 2 register sets the specified
// phase for the WO2 output relative to WO0: 50,00°
TCA0.SINGLE.CMP2=0x00;

// Set the Event Control register
// Event input A: No action
// Event input B: No action
TCA0.SINGLE.EVCTRL=(0<<TCA_SINGLE_CNTAEI_bp)+(0<<TCA_SINGLE_CNTBEI_bp);

// Set TCA0 interrupts:
// Overflow interrupt: Off
// Compare Channel 0 interrupt: Off
// Compare Channel 1 interrupt: Off
// Compare Channel 2 interrupt: Off
TCA0.SINGLE.INTCTRL=
    (0<<TCA_SINGLE_OVF_bp)+
    (0<<TCA_SINGLE_CMP0_bp)+
    (0<<TCA_SINGLE_CMP1_bp)+
    (0<<TCA_SINGLE_CMP2_bp);

// Initialization finished, enable TCA0
TCA0.SINGLE.CTRLA|=TCA_SINGLE_ENABLE_bm;
}

// Timer/Counter TCA1 initialization
void tca1_init(void)
{
// First disable and reset the Timer/Counter TCA1
// Use 16-bit mode
tca_disable(&TCA1);

// Clock divider: 1
// Clock frequency: 4000,960 kHz
// TCA1 runs in standby: Off
TCA1.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc+(0<<TCA_SINGLE_RUNSTDBY_bp);

// Operating mode: Normal 16-bit OVF=TOP
TCA1.SINGLE.CTRLB=TCA_SINGLE_WGMODE_NORMAL_gc;

// Set the Timer Counter register
TCA1.SINGLE.CNT=0x00;

// Set the Timer Period register
// Specified period: 1 ms
// Obtained: 1,00001 ms, 0,00 % error
TCA1.SINGLE.PER=0xFA0;

// Set the Event Control register
// Event input A: No action
// Event input B: No action
TCA1.SINGLE.EVCTRL=(0<<TCA_SINGLE_CNTAEI_bp)+(0<<TCA_SINGLE_CNTBEI_bp);

// Set TCA1 interrupts:
// Overflow interrupt: On
// Compare Channel 0 interrupt: Off
// Compare Channel 1 interrupt: Off
// Compare Channel 2 interrupt: Off
TCA1.SINGLE.INTCTRL=
    (1<<TCA_SINGLE_OVF_bp)+
    (0<<TCA_SINGLE_CMP0_bp)+
    (0<<TCA_SINGLE_CMP1_bp)+
    (0<<TCA_SINGLE_CMP2_bp);

// Initialization finished, enable TCA1
TCA1.SINGLE.CTRLA|=TCA_SINGLE_ENABLE_bm;
}

// Timer/Counter TCA1 Overflow/Underflow interrupt service routine
// Overflow each 1 ms
interrupt [TCA1_OVF_vect] void tca1_ovf_isr(void)
{
// Ensure that the Overflow/Underflow interrupt flag is cleared
TCA1.SINGLE.INTFLAGS=TCA_SINGLE_OVF_bm;

// Write your code here
   ms_cnt++;

    if ( ms_delay_cnt ) {                         /* count down 1 ms delay */
        ms_delay_cnt-- ;
    }

    if ( !--sec_cnt ) 
    {               /* counter for 1 sec. */
        sec_cnt = SEC_CNT_INIT;
        if ( time_b_cnt ) {           /* timer for temperature readings */
            time_b_cnt-- ;
        }
        if ( time_e_cnt ) {           /* timer for eed check*/
            time_e_cnt-- ;
        }
    }

    if ( ad_settling ) {                          /* count down ad setling time */
        if ( !--ad_settling ) {
            ad_mode |= 0x20;                        /* Ok for int 1 */
        }
    }
    /* timeout ad converter */
    if ( ad_timeout_cnt ) 
	{
        if ( !--ad_timeout_cnt ) 
		{
            ad_state = IDLE ;
			ResetADCBySW() ;
		}
    }

    if ( rx_timeout ) {                               /* check timeout on tx0  */
        if ( !--rx_timeout )
		{
            ResetRxPointer();
        }
    }


    if ( tx_tail ) {                                  /* check tx0 driver */
        if ( !--tx_tail ) {
            TxDriver(OFF);
            tx_complete = TRUE;
            ResetRxPointer() ;          /* reset pointer */
            Led(1, OFF) ;
        }
    }

    if ( wait_for_pc ) {                          /* delay before sending ch0 */
        ad_mode |= 0x01 ;                /* mark that byte as sent */
        if ( !--wait_for_pc ) 
        {
//            SCI0_TDR = tx_buff[tx_indx++];
//            SCI0_SSR &= ~SSR_TDRE;              /* clear TDRE-flag */
//            SCI0_SCR |= SCR_TIE;                    /*  enable  tx int */
            Led(1, ON) ;
        }
    }
}

