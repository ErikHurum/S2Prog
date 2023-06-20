/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co KG                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2008  SEGGER Microcontroller GmbH & Co KG         *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS * Real time operating system for microcontrollers      *
*                                                                    *
*                                                                    *
*       Please note:                                                 *
*                                                                    *
*       Knowledge of this file may under no circumstances            *
*       be used to write a similar product or a real-time            *
*       operating system for in-house use.                           *
*                                                                    *
*       Thank you for your fairness !                                *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS version: 3.60d                                         *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : RTOSInit_TMPA910.c
          for Toshiba TMPA910 CPU

Purpose : Initializes and handles the hardware for the OS as far
          as required by the OS.
          Feel free to modify this file acc. to your
          target system.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.H"
#include "JLINKDCC.h"

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/

#define ALLOW_NESTED_INTERRUPTS 0   // Caution: Nesting interrupts will cause higher stack load on system stack CSTACK

/*********************************************************************
*
*       Clock frequency settings
*/

#define OS_FSYS 192000000uL

#ifndef   OS_PCLK_TIMER
  #define OS_PCLK_TIMER (OS_FSYS / 2)
#endif

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ (1000)
#endif

#define OS_TIMER_PRESCALE (2)   // prescaler for system timer is fixed to 2

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 0 per default
*/
#ifndef   OS_UART
  #define OS_UART (0)
#endif

#ifndef   OS_PCLK_UART
  #define OS_PCLK_UART (OS_FSYS / 2)
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE (38400)
#endif

/********************************************************************/

#ifndef   SDRAM_TARGET
  #define SDRAM_TARGET 0
#endif

#ifndef   RAM_TARGET
  #define RAM_TARGET   0
#endif


/****** End of configuration settings *******************************/

#define OS_UART_USED (OS_UART == 0)

/*********************************************************************
*
*       Prototypes
*
**********************************************************************
*/

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** System control ***********************************************/

#define _SYSCR_BASE_ADDR   (0xF0050000)
#define _SYSCR0   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x0000)
#define _SYSCR1   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x0004)
#define _SYSCR2   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x0008)
#define _SYSCR3   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x000c)
#define _SYSCR4   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x0010)
#define _SYSCR5   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x0014)
#define _SYSCR6   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x0018)
#define _SYSCR7   *(volatile OS_U32*)(_SYSCR_BASE_ADDR + 0x001c)

/****** Timer *******************************************************/

#define _TIMER0_BASE_ADDR   (0xF0040000)
#define _TIMER1_BASE_ADDR   (0xF0040100)
#define _TIMER2_BASE_ADDR   (0xF0041000)
#define _TIMER3_BASE_ADDR   (0xF0041100)
#define _TIMER4_BASE_ADDR   (0xF0042000)
#define _TIMER5_BASE_ADDR   (0xF0042100)

#define _OS_TIMER_LOAD      *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + 0x0000)
#define _OS_TIMER_VALUE     *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + 0x0004)
#define _OS_TIMER_CTRL      *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + 0x0008)
#define _OS_TIMER_INTCLR    *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + 0x000C)
#define _OS_TIMER_RIS       *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + 0x0010)
#define _OS_TIMER_MODE      *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + 0x001C)

#define _OS_CLKCR5          *(volatile OS_U32*)(0xF0050000 + 0x0054)

/*      MATRIX + EBI interface */
#define _MATRIX_BASE_ADDR   (0xFFFFEE00)                                // MATRIX Base Address

#define _MATRIX_MCFG        (*(volatile OS_U32*) (_MATRIX_BASE_ADDR + 0x00)) // MATRIX Master configuration register
#define _MATRIX_EBICSA      (*(volatile OS_U32*) (_MATRIX_BASE_ADDR + 0x30)) // MATRIX EBI Chip Select Assignment register


/****** Vectored interrupt controller (VIC) *************************/

#define _VIC_BASE_ADDR       0xF4000000

#define _VIC_IRQSTATUS       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0000)
#define _VIC_FIQSTATUS       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0004)
#define _VIC_RAWINTERRUPT    *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0008)
#define _VIC_INTSELECT       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x000C)
#define _VIC_INTENABLE       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0010)
#define _VIC_INTENABLECLEAR  *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0014)
#define _VIC_SOFTINT         *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0018)
#define _VIC_SOFTINTCLEAR    *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x001C)
#define _VIC_VECTORADDR      *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0F00)

#define _VIC_VECT_BASE_ADDR       (_VIC_BASE_ADDR + 0x0100)
#define _VIC_VECTPRIO_BASE_ADDR   (_VIC_BASE_ADDR + 0x0200)

#ifndef   _NUM_INT_VECTORS
  #define _NUM_INT_VECTORS   (32)
#endif

#define _INT_PRIORITY_MASK   (0x0F)
#define _NUM_INT_PRIORITIES  (16)

#define _INT_PRIORITY_LOWEST (0)


/****** PMC *********************************************************/

#define _PMC_BASE_ADDR       (0xF0020000)
#define _PMCDRV              *((volatile OS_U32*)(_PMC_BASE_ADDR + 0x260))

/****** SDRAM controller ********************************************/

#define _DDR_MPMC_BASE_ADDR  (0xf4300000)

#define _DMC_MEMC_CMD        *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0004)
#define _DMC_DIRECT_CMD      *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0008)
#define _DMC_MEMORY_CFG      *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x000C)
#define _DMC_REFRESH_PRD     *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0010)

#define _DMC_CAS_LATENCY     *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0014)
#define _DMC_T_DQSS          *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0018)
#define _DMC_T_MRD           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x001C)
#define _DMC_T_RAS           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0020)
#define _DMC_T_RC            *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0024)
#define _DMC_T_RCD           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0028)
#define _DMC_T_RFC           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x002C)
#define _DMC_T_RP            *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0030)
#define _DMC_T_RRD           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0034)
#define _DMC_T_WR            *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0038)
#define _DMC_T_WTR           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x003C)
#define _DMC_T_XP            *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0040)
#define _DMC_T_XSR           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0044)
#define _DMC_T_ESR           *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0048)

#define _DMC_CHIP_0_CFG      *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0200)
#define _DMC_CHIP_1_CFG      *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0204)
#define _DMC_CHIP_2_CFG      *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0208)
#define _DMC_CHIP_3_CFG      *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x020C)

#define _DMC_USER_CONFIG     *(volatile OS_U32*)(_DDR_MPMC_BASE_ADDR + 0x0304)
#define MEMC_CMD_GO          0x00000000

/*********************************************************************
*
*       Configuration for embOS
*/

/*      Assign timer used for embOS *********************************/
#define _OS_TIMER_BASE_ADDR  (_TIMER5_BASE_ADDR)
#define _OS_TIMER_INT_INDEX  (4)  // Assigned to Timer 4/5 which share the same vector

#define _OS_TIMER_INT_PRIO   (_INT_PRIORITY_LOWEST)   // Assign lowest priority
#define _OS_UART_INT_PRIO    (_INT_PRIORITY_LOWEST)   // Assign lowest priority

/*********************************************************************
*
*       local data
*
**********************************************************************
*/

/*********************************************************************
*
*       MMU and cache configuration
*/
#pragma data_alignment=16384
static __no_init unsigned int _TranslationTable [0x1000];

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _OS_ISR_Undefined
*
*       Is called when an uninstalled interrupt was detected
*       As interrupt pending condition of peripherals has to be reset,
*       program will not continue when interrupt is ignored.
*/
static void _OS_ISR_Undefined(void) {
  #if OS_DEBUG
    volatile OS_U32 Dummy;
    Dummy = 1;
    /* You may set a breakpoint here to detect undefined interrupts */
    while (Dummy > 0) {
    }
  #endif
}

/*********************************************************************
*
*       _OS_ISR_Tick() interrupt Handler
*
* Note:
*   Two hardware timer share the same interrupt vector.
*   If user application uses the second timer and interrupts are
*   enabled for the second timer, this interrupt has to be handled
*   and cleared here.
*/
static void _OS_ISR_Tick(void) {
  _OS_TIMER_INTCLR = 1;     // Writing any value Clears OS timer interrupt
  OS_HandleTick();          // Call OS tick handler
#if DEBUG
  DCC_Process();
#endif
}

/*********************************************************************
*
*       _Init_VIC()
*
* Function description
*   Clears and disables all interrupt vectors in VIC.
*
* Note:
*   This function may be called from __low_level_init() and therefore
*   must not use or call any function which relies on any variable,
*   because variables are not initialized before __low_level_init() is called !
*/
static void _Init_VIC(void) {
  int Index;
  OS_ISR_HANDLER** papISR;

  _VIC_INTENABLECLEAR = 0xFFFFFFFF;            // Disable all source interrupts
  _VIC_VECTORADDR     = 0;                     // Write to vector, reset VIC

  papISR = (OS_ISR_HANDLER**) _VIC_VECT_BASE_ADDR;
  for (Index = 0; Index < _NUM_INT_VECTORS; Index++) {
    *(papISR + Index) = NULL;                  // Set vector to 0;
  }
  _VIC_SOFTINTCLEAR   = 0xFFFFFFFF;            // Disable all soft interrupts
  _VIC_INTSELECT      = 0;                     // Set all channels to generate IRQ
}

/*********************************************************************
*
*       _InitFlash
*
* Function description
*   Initialize wait states and BUS interface for external Flash access
*   Needs to be called before main clock is switched to high speed
*   Depends on specific hardware and has to be implemented by user.
*
* Note:
*   This function may be called from __low_level_init() and therefore
*   must not use or call any function which relies on any variable,
*   because variables are not initialized before __low_level_init() is called !
*/
static void _InitFlash(void) {
}

/*********************************************************************
*
*       _InitClocks
*
* Function description
*   Initialize main clock and PLL
*
* NOTES: (1) Settings used here are for TMPA-910 eval board
*            and may have to be modified for other target boards or frequency
*
*        (2) This function may be called from __low_level_init() and therefore
*            must not use or call any function which relies on any variable,
*            because variables are not initialized before __low_level_init()
*            is called !
*/
static void _InitClocks(void) {
  unsigned int RegData;
  _SYSCR3 = 0x07;         // Set PLL multiplier (7 => multiply by 8)
  _SYSCR4 = (0x96 << 4)   // RS value, PLL output frequency range selection: >= 140MHz
          | (0x01 << 2)   // IS setting, Always write 1!
          | (0x01 << 0)   // FS value, PLL output frequency range selection: >= 140MHz
          ;
  _SYSCR3 = 0x87;

  do {
   RegData = _SYSCR2;
  } while ((RegData & 0x1) == 0);   // Wait until PLL is locked

  _SYSCR2 = 0x02;         // Select PLL output as system clock source
  /* Wait 5 clocks */
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");

  _SYSCR1 = 0;            /* System clock gear = 0 => Full speed */
  /* Wait 5 clocks */
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
}

/*********************************************************************
*
*       _InitSDRAM
*
* Function description
*   Initialize SDRAM controller
*
* NOTES: (1) Settings used here are for TMPA-910 eval board
*            and may have to be modified for other target boards or frequency
*
*        (2) This function may be called from __low_level_init() and therefore
*            must not use or call any function which relies on any variable,
*            because variables are not initialized before __low_level_init()
*            is called !
*/
static void _InitSDRAM(void) {
  #if (SDRAM_TARGET == 0)  // Must not be initialized, if program was downloaded to SDRAM
  /* Port drive setting */
  _PMCDRV          = 0x00000071;
  //
  // Initialize SDRAM timing paramater
  //
  _DMC_CAS_LATENCY = 0x00000006;
  _DMC_T_DQSS      = 0x00000000;
  _DMC_T_MRD       = 0x00000002;
  _DMC_T_RAS       = 0x00000007;

  _DMC_T_RC        = 0x0000000A;
  _DMC_T_RCD       = 0x00000013;

  _DMC_T_RFC       = 0x0000010A;

  _DMC_T_RP        = 0x00000013;
  _DMC_T_RRD       = 0x00000002;
  _DMC_T_WR        = 0x00000002;
  _DMC_T_WTR       = 0x00000001;
  _DMC_T_XP        = 0x0000000A;
  _DMC_T_XSR       = 0x0000000B;
  _DMC_T_ESR       = 0x00000014;

  //
  // Configure SDRAM type parameter
  _DMC_MEMORY_CFG  = 0x00008011;
  _DMC_USER_CONFIG = 0x00000011;   // 32 bit memory interface

  _DMC_REFRESH_PRD = 0x00000A60;
  _DMC_CHIP_0_CFG  = 0x000140FF;

  _DMC_DIRECT_CMD  = 0x000C0000;
  _DMC_DIRECT_CMD  = 0x00000000;

  _DMC_DIRECT_CMD  = 0x00040000;
  _DMC_DIRECT_CMD  = 0x00040000;
  _DMC_DIRECT_CMD  = 0x00080031;
  //
  // Finally start SDRAM
  //
  _DMC_MEMC_CMD    = MEMC_CMD_GO;
  #endif
}

/*********************************************************************
*
*       _InitSMC
*
* Function description
*   Initialize static memory controller
*
* NOTES: (1) Settings used here are for TMPA-910 eval board
*            and may have to be modified for other target boards or frequency
*
*        (2) This function may be called from __low_level_init() and therefore
*            must not use or call any function which relies on any variable,
*            because variables are not initialized before __low_level_init()
*            is called !
*/
static void _InitSMC(void) {
}

/*********************************************************************
*
*       _CopyToSDRAM
*
* Function description
*   Copy whole application from Flash to SDRAM, which has to be initialized before
*
* NOTES: (1) Settings used here are for TMPA-910 eval board
*            and may have to be modified for other target boards
*
*        (2) This function may be called from __low_level_init() and therefore
*            must not use or call any function which relies on any variable,
*            because variables are not initialized before __low_level_init()
*            is called !
*
*        (3) The function has to be called, before MMU is initialized and
*            SDRAM is remapped to 0x0.
*/
#ifndef   _SDRAM_BASE_ADDR
  #define _SDRAM_BASE_ADDR (0x40000000)
#endif

#if (RAM_TARGET == 0) // Not used for target application which runs in internal RAM, avoid warning
#if __ICCARM__
#if (__VER__ >= 500)
static void _CopyToSDRAM(void) {
  unsigned long Size;
  #pragma segment="PROGRAM_DATA"
  #pragma section=".intvec"
  Size = (unsigned long) __segment_end("PROGRAM_DATA") - (unsigned long) __segment_begin(".intvec");
  memcpy((void*)_SDRAM_BASE_ADDR, (void*) __segment_begin(".intvec"), Size);
};
#else

static void _CopyToSDRAM(void) {
  unsigned long Size;
  #pragma segment="PROGRAM_END"
  #pragma segment="INTVEC"
  Size = (unsigned long) __segment_begin("PROGRAM_END") - (unsigned long) __segment_begin("INTVEC");
  memcpy((void*)_SDRAM_BASE_ADDR, (void*) __segment_begin("INTVEC"), Size);
};
#endif  // __VER__ >= 500

#endif  // __ICCARM__

#endif  // RAM_TARGET == 0

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       OS_InitHW()
*
*       Initialize the hardware (timer) required for the OS to run.
*       May be modified, if an other timer should be used
*/
#define OS_TIMER_RELOAD ((OS_PCLK_TIMER/OS_TIMER_PRESCALE/OS_TICK_FREQ) - 1)
#if (OS_TIMER_RELOAD >= 0x00010000)  // Timer values are limited to 16 bit values
  #error "OS timer can not be used, please check configuration"
#endif

void OS_InitHW(void) {
  OS_IncDI();
  OS_ARM_CACHE_Sync();               // Ensure, caches are synchronized
  _OS_TIMER_CTRL = 0;                // Stop timer
  _OS_CLKCR5    |= 0x0F;             // Default value after Reset = fHCLK / 2
  _OS_TIMER_LOAD = OS_TIMER_RELOAD;  // Set timer interval
  _OS_TIMER_CTRL = (1 << 7)
                 | (1 << 6)
                 | (1 << 5)
                 | (0 << 4)
                 | (0 << 3)
                 | (0 << 2)
                 | (1 << 1)
                 | (0 << 0)
                 ;

  OS_ARM_InstallISRHandler(_OS_TIMER_INT_INDEX, _OS_ISR_Tick);
  OS_ARM_ISRSetPrio(_OS_TIMER_INT_INDEX, _INT_PRIORITY_LOWEST);
  OS_ARM_EnableISR(_OS_TIMER_INT_INDEX);

  OS_COM_Init();
  OS_DecRI();
}

/*********************************************************************
*
*       Idle loop  (OS_Idle)
*
*       Please note:
*       This is basically the "core" of the idle loop.
*       This core loop can be changed, but:
*       The idle loop does not have a stack of its own, therefore no
*       functionality should be implemented that relies on the stack
*       to be preserved. However, a simple program loop can be programmed
*       (like toggeling an output or incrementing a counter)
*/
void OS_Idle(void) {         /* Idle loop: No task is ready to exec */
  while (1) {
  }
}

/*********************************************************************
*
*       OS_GetTime_Cycles()
*
*       This routine is required for task-info via OSView or high
*       resolution time maesurement functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  unsigned int Count;
  OS_U32       Time;

  Count = _OS_TIMER_VALUE;
  Time  = OS_GetTime32() + 1;

  if (_OS_TIMER_RIS & (1 << 0)) {    /* if timer interrupt pending */
    Count = _OS_TIMER_VALUE;         /* Adjust result              */
    Time++;
  }
  return (OS_TIMER_RELOAD) * Time - Count;
}

/*********************************************************************
*
*       OS_ConvertCycles2us()
*
**********************************************************************

Purpose:
   Convert Cycles into micro seconds.

   If your clock frequency is not a multiple of 1 MHz, you may have to
   modify this routine in order to get proper diagonstics.
Please note:
   This routine is required for profiling or high resolution time
   measurement. It does not affect operation of embOS.
*/

OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
  return Cycles/(OS_PCLK_TIMER/OS_TIMER_PRESCALE/1000000);
}

/*********************************************************************
*
*       Communication for OSView via UART (optional)
*
**********************************************************************
*/
#if OS_UART_USED
#if   (OS_UART == 0)
  #define OS_UART_BASE_ADDR  (0xF2000000)
  #define _OS_UART_INT_INDEX 10
#elif (OS_UART == 1)
  #define OS_UART_BASE_ADDR   (0xF2001000)
  #define _OS_UART_INT_INDEX 11
#endif

#define _USART_DR_OFFS       (0x00)
#define _USART_RSR_OFFS      (0x04)
#define _USART_ECR_OFFS      (0x04)
#define _USART_FR_OFFS       (0x18)
#define _USART_ILPR_OFFS     (0x20)
#define _USART_IBRD_OFFS     (0x24)
#define _USART_FBRD_OFFS     (0x28)
#define _USART_LCR_H_OFFS    (0x2C)
#define _USART_CR_OFFS       (0x30)
#define _USART_IFLS_OFFS     (0x34)
#define _USART_IMSC_OFFS     (0x38)
#define _USART_RIS_OFFS      (0x3C)
#define _USART_MIS_OFFS      (0x40)
#define _USART_ICR_OFFS      (0x44)
#define _USART_DMACR_OFFS    (0x48)

#define _USART_DR            (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_DR_OFFS))       // Data read/write register
#define _USART_RSR           (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_RSR_OFFS))      // Receive status register (read)/error clear register (write)
#define _USART_ECR           (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_ECR_OFFS))      // Receive status register (read)/error clear register (write)
#define _USART_FR            (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_FR_OFFS))       // Flag register (read only)
#define _USART_ILPR          (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_ILPR_OFFS))     // IrDA low-power counter register
#define _USART_IBRD          (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_IBRD_OFFS))     // Integer baud rate divisor register
#define _USART_FBRD          (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_FBRD_OFFS))     // Fractional baud rate divisor register
#define _USART_LCR_H         (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_LCR_H_OFFS))    // Line control register, high-order bytes
#define _USART_CR            (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_CR_OFFS))       // Control register
#define _USART_IFLS          (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_IFLS_OFFS))     // Interrupt FIFO level select register
#define _USART_IMSC          (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_IMSC_OFFS))     // Interrupt mask set/clear
#define _USART_RIS           (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_RIS_OFFS))      // Raw interrupt status
#define _USART_MIS           (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_MIS_OFFS))      // Masked interrupt status
#define _USART_ICR           (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_ICR_OFFS))      // Interrupt clear register
#define _USART_DMACR         (*(volatile OS_U32*) (OS_UART_BASE_ADDR + _USART_DMACR_OFFS))    // DMA control register

#define _USART_RX_BIT 4
#define _USART_TX_BIT 5

#define _GPION_BASE_ADDR     0xF080C000
#define _GPION_FR1_OFFSET    0x424
#define _GPION_FR2_OFFSET    0x428
#define _GPION_FR1           (*(volatile OS_U32*) (_GPION_BASE_ADDR + _GPION_FR1_OFFSET))
#define _GPION_FR2           (*(volatile OS_U32*) (_GPION_BASE_ADDR + _GPION_FR2_OFFSET))

/*********************************************************************
*
*       OS_COM_ISR_Usart() OS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void _OS_COM_ISR_Usart(void) {
  OS_U32 c;
  if (_USART_RIS & (1 << _USART_TX_BIT)) {  // Tx interrupt?
    _USART_ICR |= (1 << _USART_TX_BIT);     // Clear Tx interrupt bit
    if (OS_OnTx()) {                        // No more characters to send?
      _USART_IMSC &= ~(1 << _USART_TX_BIT); // Disable further tx interrupts
      _USART_ICR  |=  (1 << _USART_TX_BIT); // Clear Tx interrupt
    }
  } else {
    c = _USART_DR & 0xFF;                   // Read Uart Rx register
    if (_USART_RIS & (0x0F << 7)) {         // Error interrupt?
      _USART_ECR = 0xFFFFFFFF;              // Clear any Rx error
      _USART_ICR = (0x0F << 7);             // Clear interrupt flag
    } else {
      OS_OnRx((OS_U8)c);                    // Real Rx interrupt
      _USART_ICR = (1 << _USART_RX_BIT);    // Clear interrupt flag
    }
  }
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  _USART_IMSC |= (1 << 5);    // Enable Transmit interrupt
  _USART_DR    = c;
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {
  //
  // Set Port N to Uart functionality
  //
  _GPION_FR1 = 0x01;
  _GPION_FR2 = 0x02;
  //
  // Set Baud Rate
  //
  _USART_IBRD  = 0x9C;       // Programmed divisor (integer)
  _USART_FBRD  = 0x10;       // Programmed divisor (fractional)
  _USART_LCR_H = 0x60;       // 8N1

  OS_ARM_InstallISRHandler(_OS_UART_INT_INDEX, _OS_COM_ISR_Usart);
  OS_ARM_ISRSetPrio(_OS_UART_INT_INDEX, _OS_UART_INT_PRIO);
  OS_ARM_EnableISR(_OS_UART_INT_INDEX);

  _USART_IMSC = (1 << _USART_RX_BIT) | (0x0F << 7);   // Enable Receive and Error interrupts
  _USART_CR   = 0x301;                                // Enable Transmit and Receive, enable UART
}


#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           /* avoid compiler warning */
  OS_COM_ClearTxActive();  /* let the OS know that Tx is not busy */
}

#endif /*  OS_UART_USED  */

/****** Final check of configuration ********************************/

#ifndef OS_UART_USED
  #error "OS_UART_USED has to be defined"
#endif

/*********************************************************************
*
*       OS interrupt handler and ISR specific functions
*
**********************************************************************
*/

/*********************************************************************
*
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq_handler is called from OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
OS_INTERWORK void OS_irq_handler(void) {
  OS_ISR_HANDLER* pISR;
  pISR = (OS_ISR_HANDLER*) _VIC_VECTORADDR;   // Get current interrupt handler
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();                // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                        // Inform OS that interrupt handler is running
#endif
  if (pISR != NULL) {
    pISR();                                   // Call installed interrupt service routine
  } else {
    _OS_ISR_Undefined();
  }
  OS_DI();                                    // Disable interrupts and unlock
  _VIC_VECTORADDR = 0;                        // Clear current interrupt pending condition, reset VIC
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();                // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                        // Leave interrupt, perform task switch if required
#endif
}

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*/
OS_ISR_HANDLER* OS_ARM_InstallISRHandler (int ISRIndex, OS_ISR_HANDLER* pISRHandler) {
  OS_ISR_HANDLER*  pOldHandler;
  OS_ISR_HANDLER** papISR;

#if OS_DEBUG
  if (ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return NULL;
  }
#endif
  OS_DI();
  papISR = (OS_ISR_HANDLER**) _VIC_VECT_BASE_ADDR;
  pOldHandler          = *(papISR + ISRIndex);
  *(papISR + ISRIndex) = pISRHandler;
  OS_RestoreI();
  return pOldHandler;
}

/*********************************************************************
*
*       OS_ARM_EnableISR
*/
void OS_ARM_EnableISR(int ISRIndex) {
#if OS_DEBUG
  if (ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  _VIC_INTENABLE |= (1 << ISRIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*/
void OS_ARM_DisableISR(int ISRIndex) {
#if OS_DEBUG
  if (ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  _VIC_INTENABLECLEAR = (1 << ISRIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  OS_U32* pPrio;
  int     OldPrio;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return 0;
  }
#endif
  OS_DI();
  pPrio = (OS_U32*)_VIC_VECTPRIO_BASE_ADDR;
  OldPrio = pPrio[ISRIndex];
  pPrio[ISRIndex] = (OldPrio & ~_INT_PRIORITY_MASK) | (Prio & _INT_PRIORITY_MASK);
  OS_RestoreI();
  return OldPrio & _INT_PRIORITY_MASK;
}

/*********************************************************************
*
*       __low_level_init()
*
*       Initialize memory controller, clock generation and pll
*
*       Has to be modified, if another CPU clock frequency should be
*       used. This function is called during startup and
*       has to return 1 to perform segment initialization
*/
OS_INTERWORK int __low_level_init(void);    // Avoid "no ptototype" warning
OS_INTERWORK int __low_level_init(void) {
  //
  //  Setup waitstates for external BUS interface before switching to high speed
  //
  _InitFlash();
  //
  //  Initialize main clock oscillator and PLLs
  //
  _InitClocks();
  //
  //  Initialize SDRAM
  //
  _InitSDRAM();
  //
  //  Initialize static memory controller
  //
  _InitSMC();
  //
  // Copy program from Flash to SDRAM
  //
#if (RAM_TARGET == 0)  // If application is not built to run in internal RAM
  _CopyToSDRAM();
#endif
  //
  // Init MMU and caches
  //
  OS_ARM_MMU_InitTT      (&_TranslationTable[0]);
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B,     0x000, 0x400, 0x020);    // SDRAM, the first 32 MB (program area) are remapped to 0 to map vectors to correct address, cacheable, bufferable
#if (IMAGE_TARGET==1)                                                                               // Special version for eval kit software
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B,     0x202, 0x400, 0x01E);    // Flash remapped to SDRAM-addr area, 32MB, cacheable, bufferable
#else
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B,     0x200, 0x400, 0x020);    // Flash remapped to SDRAM-addr area, 32MB, cacheable, bufferable
#endif
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B,     0x400, 0x400, 0x040);    // SDRAM, 64MB , original address, cacheable, bufferable
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB,   0x440, 0x400, 0x040);    // SDRAM, 64MB data area, remapped, cacheable, NON bufferable
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB,   0x600, 0x600, 0x001);    // CS1 area, 1MB, NON cacheable, NON bufferable
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB,   0xf00, 0xf00, 0x080);    // Internal SFRs, original address range, NON cacheable, NON bufferable
  OS_ARM_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB,   0xf80, 0xf80, 0x080);    // Internal SRAM, original address range, NON cacheable, NON bufferable
  OS_ARM_MMU_Enable      (&_TranslationTable[0]);
  OS_ARM_ICACHE_Enable();
  OS_ARM_DCACHE_Enable();
  //
  // Initialize interrupt controller
  //
  _Init_VIC();
  //
  //  Perform other initialization here, if required
  //
  return 1;
}

/*****  EOF  ********************************************************/

