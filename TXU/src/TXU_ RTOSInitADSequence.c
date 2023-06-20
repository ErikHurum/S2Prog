/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************

File        : RTOSInit.c
Purpose     : Initializes and handles the hardware for embOS as far
				as required by embOS.
				Feel free to modify this file acc. to your
				target system.
---------------------------END-OF-HEADER------------------------------
*/

/*
	Please note:
	We do automatic release tests for embOS. These tests are done with the
	CPU_KS32C50100. You will find drivers for additional CPUs, which are used
	by our customers. These drivers have also been   tested at least one time,
	but they are not part of our periodic automatic release tests. Therefore
	it might happen, that you encounter a problem with these additional drivers.
*/

#include "RTOS.H"
#include "2410addr.h"
#include "2410lib.h"
#include "ANPRO10Const.h"
#include "TSNConstants.h"
#include "Def.h"
#include "FixedVariables.h"
#include <time.h>

extern short CurrentDeviceId;

volatile U16  TXUADData[8];
U8    ADChannel = 0 ;

volatile U16   Inc1CntUp   =0;
volatile U16   Inc1CntDown =0;
volatile U16   Inc2CntUp   =0;
volatile U16   Inc2CntDown =0;


typedef struct
{
	unsigned EnableStart:1;
	unsigned ReadStart:1;
	unsigned StdBM:1;
	unsigned SelMux:3;
	unsigned PrScVl:8;
	unsigned PrScEn:1;
	unsigned ECFlg:1;
	//unsigned Dummy:16;
}ADCConStruct;

unsigned KbdIntCnt = 0;
unsigned ADIntCnt = 0;
volatile unsigned char TouchKeyPressed = 0;					//status for the touch key
ADCConStruct *ADCCon = (ADCConStruct*)&rADCCON;

extern void HandleUARTInterrupt(int Port);
//#ifndef ANBOOTLOADER
extern OS_TASK *ReadTouchKey;								/* Task control blocks */
//#endif


void OS_USER_irq_func(void);

/*
**********************************************************************
*
*                    Configuration
*
**********************************************************************
*/

/* Select UART for embOSView, set baudrate,
	 define clock frequency for CPU used

	 If you do not want (or can not due to hardware limitations) to dedicate
	 a UART to embOSView, please define OS_UART to -1
*/

#ifndef CPU_S3C2410
//#error "This file is for S3C2410 CPU"
#endif


/*********************************************************************
*
*         Non HW dependent configuration defaults
*
**********************************************************************
*/

#ifndef OS_TICK_FREQ
	#define OS_TICK_FREQ 1000
#endif

#ifndef USE_CACHE
	#define USE_CACHE 1   /* 0: No chache */
#endif



#ifndef OS_BAUDRATE
	#define OS_BAUDRATE 38400
#endif

#ifndef OS_RAMVECT
	#define OS_RAMVECT 0
#endif



#define TIMER_PRESCALE0  1              /* prescaler for timer frequency */
#define TIMER_PRESCALE1  5            /* prescaler for timer frequency */
#define TIMER_RELOAD       (OS_FSYS/8/(TIMER_PRESCALE0+1)/OS_TICK_FREQ)
#define TIMER0_START  ( ( 1 << 3 ) | 1 ) // Reload and start
#define TIMER0_UPDATE ( ( 1 << 1 ) )


#define TIMER2_START  ( ( 0 << 15 ) | (1 << 12 )) // One shot and start
#define TIMER2_UPDATE ( ( 1 << 13 ) )
#define TIMER3_START  ( ( 0 << 19 ) | (1 << 16 )) // One shot and start
#define TIMER3_UPDATE ( ( 1 << 17 ) )

/*
**********************************************************************
*
*                    OS_InitHW
*
**********************************************************************

Initialize the hardware required for the OS to run. This will work
on any target hardware, but may have to be tailored a little
(regarding the clock frequency). Of course the same holds true
if for some reason you choose to use an other timer.
*/

void OS_InitHW(void) {
	rINTMSK    = 0xffffffff;	 // Mask timer interrupt
	rINTSUBMSK = 0x7ff;
	rSUBSRCPND = 0;




#if OS_RAMVECT
	{
		unsigned int vec;
		unsigned int *vector;
		extern void OS_IRQ_SERVICE(void);
		OS_DI();
		vector = (unsigned int*) 0x18;
		vec = (((unsigned int)&OS_IRQ_SERVICE - (unsigned int)vector - 8) >> 2);
		vec |= 0xea000000; /* add opcode for B instruction */
		*vector = vec;
		OS_EI();
	}
#endif



	rTCFG0  = TIMER_PRESCALE0 | ( TIMER_PRESCALE1 << 8 ) | ( 0 << 16 );
	rTCNTB0 = TIMER_RELOAD;
	rTCNTB2 = 0xFFFF;
	rTCMPB2 = 0xFFFF;
	rTCNTB3 = 0xFFFF;
	rTCMPB3 = 0xFFFF;
	//rTCMPB0 = TIMER_RELOAD;
	switch ( CurrentDeviceId ) {
		case DEVICE_TCU:	// TCU
			rTCON   = TIMER0_UPDATE | TIMER2_UPDATE | TIMER3_UPDATE;
			rTCON   = TIMER0_START | TIMER2_START | TIMER3_START;	// Start timer 0,2,3.  0 shall be in reload mode
			break;
		case DEVICE_TDU:	// TDU
			rTCON   = TIMER0_UPDATE;
			rTCON   = TIMER0_START;	// Start timer 0 in reload mode
			break;
	}


	rINTPND = 0x00000000;	 /* Clear pending interrupts */


	//*((unsigned*)0x1c) = (unsigned)OS_fiq_handler;                   //Timer0 FIQ interrupt

	//*((unsigned*)0x1c) |= 0xea000000; /* add opcode for B instruction */
	rINTMOD = 0x00000000;
	//rINTMOD |= BIT_TIMER0;
	rINTMSK &= ~(BIT_TIMER0);	// Mask timer interrupt

	// Start con to embOSView
	OS_COM_Init();
	// start AD for touchscreen //AStmark ADU/TCU must be checked for int setup AD/touch
	//rADCDLY=(50000);	// ADC Start or Interval Delay
	rADCDLY=(5000);	// ADC Start or Interval Delay
	// Enable Prescaler,Prescaler,AIN5/7 fix,Normal,Disable read start,No operation
	rADCTSC = (0<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(0<<3)|(0<<2)|3;//Original
	rADCCON = (1<<14)|(255<<6)|(0<<3)|(0<<2)|(0<<1)|(1); // Was befor rADCTSC


	// Down,YM:GND,YP:AIN5,XM:Hi-z,XP:AIN7,XP pullup En,Normal,Waiting for interrupt mode
	//pISR_ADC=(unsigned)Adc_or_TsAuto;
	rINTMSK &= ~(BIT_ADC);
	switch ( GlobalDeviceHWId ) {
		case TDU_R1:
		case TDU_R2:
			rINTSUBMSK &= ~(BIT_SUB_TC | BIT_SUB_ADC);
			break;
		case TCU_R1:
		case TCU_R2:
			rINTSUBMSK &= ~BIT_SUB_ADC;
	}

	rINTMSK &= ~(BIT_EINT4_7 | BIT_EINT8_23);
	rEINTMASK &=  ~(BIT_SUB_EINT5 | BIT_SUB_EINT6 | BIT_SUB_EINT7 | BIT_SUB_EINT8 );

}



/*
**********************************************************************
*
*                     Idle task  (OS_Idle)
*
**********************************************************************

 Please note:
 This is basically the "core" of the idle task.
 This core loop can be changed, but:
 The idle task does not have a stack of its own, therefor no
 functionality should be implemented that relies on the stack
 to be preserved. However, a simple program loop can be programmed
 (like toggeling an output or incrementing a counter)
*/

void OS_Idle(void) {	 // Idle task: No task is ready to exec
	while ( 1 ) {
	}
}

/*
**********************************************************************
*
*                    Get time [cycles]
*
**********************************************************************

	This routine is required for task-info via embOS Viewer.
	It returns the system time in clock cycles.
*/

#define HW_TIMER rTCNTB0
#define HW_TIMER_INTERRUPT_PENDING() (rINTPND & BIT_TIMER0)

OS_U32 OS_GetTime_Cycles(void) {
	unsigned int t_cnt = TIMER_RELOAD - HW_TIMER;
	OS_U32 time = OS_Time;
	if ( HW_TIMER_INTERRUPT_PENDING() ) {
		t_cnt = TIMER_RELOAD - HW_TIMER;
		time++;
	}
	return(OS_FSYS/TIMER_PRESCALE0/OS_TICK_FREQ)*time  + t_cnt;
}


/*
**********************************************************************
*
*                    OS_ConvertCycles2us
*
**********************************************************************

Purpose:
	 Convert Cycles into micro seconds. (For profiling only)

	 If you have a clock frequency which is not a multiple of 1 MHz,
	 you may have to modify this routine in order to get proper
	 diagonstics.
Please note:
	 This routine is required for profiling only.
	 It does not affect operation of the OS.
*/

OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
	Cycles *= TIMER_PRESCALE0;				/* eliminate effect of prescaler */
	return(Cycles/(OS_FSYS/1000000));
}

/*********************************************************************
*
*          Communication (UART)
*
**********************************************************************
*/

#if (OS_UART!=-1)
	#if (OS_UART==1)
		#define INTOFF_UART      INTOFF_UART1
		#define UART_PENDING     BIT_UART1
		#define UART_SUBMASK     (BIT_SUB_TXD1 | BIT_SUB_RXD1)
		#define UART_SUB_RX      BIT_SUB_RXD1
		#define UART_SUB_TX      BIT_SUB_TXD1
		#define UART_STATUS      rUTRSTAT1
		#define UART_RXBUF       rURXH1
		#define UART_TXBUF       rUTXH1
		#define UART_LINECON     rULCON1
		#define UART_CONTROL     rUCON1
		#define UART_BAUD        rUBRDIV1
	#elif (OS_UART==0)
		#define INTOFF_UART      INTOFF_UART0
		#define UART_PENDING     BIT_UART0
		#define UART_SUBMASK     (BIT_SUB_TXD0 | BIT_SUB_RXD0)
		#define UART_SUB_RX      BIT_SUB_RXD0
		#define UART_SUB_TX      BIT_SUB_TXD0
		#define UART_STATUS      rUTRSTAT0
		#define UART_RXBUF       rURXH0
		#define UART_TXBUF       rUTXH0
		#define UART_LINECON     rULCON0
		#define UART_CONTROL     rUCON0
		#define UART_BAUD        rUBRDIV0
	#endif

void OS_COM_Init(void) {
	UART_CONTROL = 0x00;
	UART_LINECON = 0x03;
	UART_CONTROL = 0x85; // RxTimeout and Interrupt request or polling mode
	UART_BAUD = (OS_FSYS/4)/(16*OS_BAUDRATE)-1 ;
	rINTMSK    &= ~UART_PENDING;
	rINTSUBMSK &= ~UART_SUBMASK;




}

void OS_ISR_rx(void) {
	unsigned UartStatus = UART_STATUS;
	if ( UartStatus & 0x01 ) {
		unsigned char RxBuf = UART_RXBUF;
		OS_OnRx(RxBuf);
		//UART_TXBUF = RxBuf;
	}
}

void OS_ISR_tx(void) {
	OS_OnTx();
}

void OS_COM_Send1(OS_U8 c) {
	UART_TXBUF = c;
}

#else  /* UART handlers not defined, using dummys */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
	OS_USEPARA(c);
	OS_COM_ClearTxActive();	 /* let OS know that transmitter is not busy */
}

#endif


void swi_handler(void)
{
#ifdef S2TXU
	static OS_TASKID CurrentTask;
	CurrentTask = OS_GetTaskID();
	if ( CurrentTask ) {
		strncpy(LastOSErrorTask,CurrentTask->Name,TASK_NAME_LENGTH);
	}
	LastOSError = 0xf1;
#endif
}
void undef_handler(void)
{
#ifdef S2TXU
	static OS_TASKID CurrentTask;
	CurrentTask = OS_GetTaskID();
	if ( CurrentTask ) {
		strncpy(LastOSErrorTask,CurrentTask->Name,TASK_NAME_LENGTH);
	}
	LastOSError = 0xf2;
#endif
}
void prefetch_handler(void)
{
#ifdef S2TXU
	static OS_TASKID CurrentTask;
	CurrentTask = OS_GetTaskID();
	if ( CurrentTask ) {
		strncpy(LastOSErrorTask,CurrentTask->Name,TASK_NAME_LENGTH);
	}
	LastOSError = 0xf3;
#endif
}
void data_handler(void)
{
#ifdef S2TXU
	static OS_TASKID CurrentTask;
	CurrentTask = OS_GetTaskID();
	if ( CurrentTask ) {
		strncpy(LastOSErrorTask,CurrentTask->Name,TASK_NAME_LENGTH);
	}
	LastOSError = 0xf4;
#endif
}


volatile  time_t FastTime   =0;
volatile  time_t CurrentTime=0;
volatile  time_t RunningTime=0;

/*
**********************************************************************
*
*                    OS_irq_handler
*
**********************************************************************

Purpose:
	 Detect reason for IRQ and call correspondig service routine.

Please note:
	 If you allow nesting, bits in __INTPND must be cleared before
	 calling OS_EnterNestableInterrupt.
*/
#define rTEST     (*(volatile unsigned *)(0x30000040))
volatile int IrqCnt = 0;
volatile int DefaultIrqCnt = 0;
volatile int InTimerFlag = 0;

void OS_irq_handler(void) {
	unsigned IntSource;
	unsigned IntOffset;
	OS_EnterInterrupt();
	IntSource    = rINTPND;
	IntOffset    = rINTOFFSET;

	//OS_USER_irq_func();

	IrqCnt++;
	switch ( IntOffset ) {
#if (OS_UART != 0)
		case INTOFF_UART0:
			ClearPending(BIT_UART0);
			HandleUARTInterrupt(0);
			break;
#endif
#if (OS_UART != 1)
		case INTOFF_UART1:
			ClearPending(BIT_UART1);
			HandleUARTInterrupt(1);
			break;
#endif
		case INTOFF_UART2:
			ClearPending(BIT_UART2);
			HandleUARTInterrupt(2);
			break;
#if ((OS_UART == 0) || (OS_UART == 1))
		case INTOFF_UART:				// UART for embOSView
			ClearPending(UART_PENDING);
			{
				unsigned IntSubSource = rSUBSRCPND;
				unsigned InsSubMask   = rINTSUBMSK;
				if ( IntSubSource & UART_SUB_RX ) {
					rSUBSRCPND = UART_SUB_RX;
					OS_ISR_rx();
				}
				if ( IntSubSource & UART_SUB_TX ) {
					rSUBSRCPND = UART_SUB_TX;
					OS_ISR_tx();
				}
			}
		 // OS_LeaveInterruptNoSwitch();
		 // return;
			OS_LeaveInterrupt();
			return;
#endif
		case INTOFF_TIMER0:				// Timer for OS
			// Clear interrupt controller service pending bit.
			ClearPending(BIT_TIMER0);
			if ( FastTime++ >= 1000 ) {
				FastTime = 0;
				CurrentTime++;
				RunningTime++;
			}
			OS_TickHandler();
			OS_LeaveInterrupt();
			return;
		case INTOFF_4_7:
		case INTOFF_8_23:
			{
				U32 BitOffset;
				U32 IntRequest = rEINTPEND;
				rEINTPEND = IntRequest;

				for ( BitOffset=4; BitOffset <= 23; BitOffset++ ) {
					U32 BitMask = (1 << BitOffset) & IntRequest;
					if ( BitMask ) {
						switch ( BitOffset ) {
							case INTOFF_SILENCE:
								// For external silence
								break;
							case INTOFF_IC1_UP  :
								rTCON   &= ~TIMER2_START;	// Stop timer 2
								Inc1CntUp = 0xffff - rTCNTO2;
								rTCNTO2   = 0;
								rTCON   |= TIMER2_UPDATE;
								rTCON   &= ~TIMER2_UPDATE;
								rTCON   |= TIMER2_START;	// Start timer 2
								break;
							case INTOFF_IC1_DOWN:
								rTCON   &= ~TIMER2_START;	// Stop timer 2
								Inc1CntDown = 0xffff - rTCNTO2;
								rTCNTO2 = 0;
								rTCON   |= TIMER2_UPDATE;
								rTCON   &= ~TIMER2_UPDATE;
								rTCON   |= TIMER2_START;	// Start timer 2
								break;
							case INTOFF_IC2_UP  :
								rTCON   &= ~TIMER3_START;	// Stop timer 3
								Inc2CntUp = 0xffff - rTCNTO3;
								rTCNTO3   = 0;
								rTCON   |= TIMER3_UPDATE;
								rTCON   &= ~TIMER3_UPDATE;
								rTCON   |= TIMER3_START;	// Start timer 3
								break;
							case INTOFF_IC2_DOWN:
								rTCON   &= ~TIMER3_START;	// Stop timer 3
								Inc2CntDown = 0xffff - rTCNTO3;
								rTCNTO3 = 0;
								rTCON   |= TIMER3_UPDATE;
								rTCON   &= ~TIMER3_UPDATE;
								rTCON   |= TIMER3_START;	// Start timer 3
								break;

						}
					}
				}
				ClearPending(IntSource);
			}
			break;
		case INTOFF_ADC:			//ADC / Touchscreen //AStmark This is not completed for ADC!!!
			ClearPending(BIT_ADC);
			{
				unsigned IntSubSource = rSUBSRCPND;

				if ( IntSubSource &  BIT_SUB_TC ) {			 // TC(Touch screen Control) Interrupt
					ADIntCnt = 0;
					rSUBSRCPND = BIT_SUB_TC;
					if ( rADCTSC & 0x100 ) {
						//TouchKeyPressed = 0 ;	//key up
						//OS_RetriggerTimer(&TouchTimeOutTimer);
						rADCTSC &= 0xff;	// Set stylus down interrupt
						if ( ReadTouchKey ) {
							OS_SignalEvent(TOUCH_SCREEN_UP,ReadTouchKey);
						}
					} else {
						//rADCTSC &= 0xff;	// Set stylus down interrupt
						// <Auto X-Position and Y-Position Read>
						rADCTSC=(0<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(1<<3)|(1<<2)|(0);
						// Stylus Down,Don't care,Don't care,Don't care,Don't care,XP pullup Dis,Auto,No operation

						rADCCON |= 0x1;	// Start Auto conversion

            {
              U16 xPos,yPos;
              xPos = rADCDAT0;
              yPos = rADCDAT1;
              TXUADData[7] = (0x3ff & xPos) ;	// Catch the possition
              TXUADData[5] = (0x3ff & yPos) ;
            }
						if ( ReadTouchKey ) {
							OS_SignalEvent(TOUCH_SCREEN_DOWN,ReadTouchKey);
						}
						KbdIntCnt++;
					}
					OS_LeaveInterrupt();
					return;
				}
				if ( IntSubSource &  BIT_SUB_ADC ) {	// AD converter
					rSUBSRCPND =  BIT_SUB_ADC;
          {
            U16 xPos,yPos;
            xPos = rADCDAT0;
            yPos = rADCDAT1;
            if ( xPos & 0x4000 || yPos & 0x4000 ){
              TXUADData[7] = (0x3ff & xPos) ;	// Catch the possition
              TXUADData[5] = (0x3ff & yPos) ;
  						KbdIntCnt++;
              rADCTSC=(1<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(0<<3)|(0<<2)|(1<<1) | 1;
              // Stylus Up,Don't care,Don't care,Don't care,Don't care,XP pullup En,Normal,Waiting mode
              rADCCON |= 0x1;															// Start Auto conversion
            }else{
              int PrevCh = ADChannel;
              if ( ++ADChannel == 5 ) {											// skip touchscreen
                ADChannel++;															// go to channel 6
              } else if ( ADChannel > 6 ) {									// finished one round
                ADChannel = 0;
              }
              ADCCon->SelMux = ADChannel;
              TXUADData[PrevCh] = (0x3ff & xPos );
            }
          }
				}
			}
			//break;
			break;
		case INTOFF_UART_A:
			ClearPending(BIT_EINT0);
			HandleUARTInterrupt(3);
			break;
		case INTOFF_UART_B:
			ClearPending(BIT_EINT1);
			HandleUARTInterrupt(4);
			break;
		case INTOFF_UART_C:
			ClearPending(BIT_EINT2);
			HandleUARTInterrupt(5);
			break;
		case INTOFF_UART_D:
			ClearPending(BIT_EINT3);
			HandleUARTInterrupt(6);
			break;
		default:
			DefaultIrqCnt++;
			OS_LeaveInterrupt();
			return;

	}
	OS_LeaveInterruptNoSwitch();
}


