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
File    : RTOSInit_AT91RM9200.c     (for ATMEL AT91RM9200 CPUs)
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

#define OS_FSYS (179712000L)        /* Maximum speed                */

#ifndef   OS_PCLK_TIMER             /* Peripheral clock for timer   */
  #define OS_PCLK_TIMER (OS_FSYS/3) /* May vary from CPU clock      */
#endif                              /* depending on initialization  */

#ifndef   OS_PCLK_UART              /* Peripheral clock for UART    */
  #define OS_PCLK_UART (OS_FSYS/3)  /* May vary from CPU clock      */
#endif                              /* depending on initialization  */

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ (1000)
#endif

#define TIMER_PRESCALE (2)          /* prescaler for timer          */

#define _DELAY_PLL       (100)
#define _DELAY_MAIN_FREQ (100)

#define _PLLAR_VALUE     (0x2026BF04)  /* 179,712000 MHz for PCK */
#define _PLLBR_VALUE     (0x10483F0E)  /* 48,054857 MHz (divide by 2 for USB clock) */
#define _MCKR_VALUE      (0x00000202)  /* PCK/3 = MCK Master Clock = 59,904000MHz with PLLA selected */

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 0 per default
*       and supports UART0 and UART1
*/
#ifndef   OS_UART
  #define OS_UART (1)
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE (38400)
#endif

#ifndef   _AIC_DEBUG_MODE
  #define _AIC_DEBUG_MODE (1)
#endif

/*********************************************************************
*
*       Memory layout for SDRAM
*/
#define _SDRAM_BASE_ADDR  (0x20000000)  /* base address to access memory on CS1 */

/****** End of configuration settings *******************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1) || (OS_UART == 2) || (OS_UART == 3))

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/*********************************************************************
*
*       peripheral ID definitions for AT91RM9200
*/
#define AT91C_ID_FIQ      ( 0) // Advanced Interrupt Controller (FIQ)
#define AT91C_ID_SYS      ( 1) // System Peripheral
#define AT91C_ID_PIOA     ( 2) // Parallel IO Controller A
#define AT91C_ID_PIOB     ( 3) // Parallel IO Controller B
#define AT91C_ID_PIOC     ( 4) // Parallel IO Controller C
#define AT91C_ID_PIOD     ( 5) // Parallel IO Controller D
#define AT91C_ID_US0      ( 6) // USART 0
#define AT91C_ID_US1      ( 7) // USART 1
#define AT91C_ID_US2      ( 8) // USART 2
#define AT91C_ID_US3      ( 9) // USART 3
#define AT91C_ID_MCI      (10) // Multimedia Card Interface
#define AT91C_ID_UDP      (11) // USB Device Port
#define AT91C_ID_TWI      (12) // Two-Wire Interface
#define AT91C_ID_SPI      (13) // Serial Peripheral Interface
#define AT91C_ID_SSC0     (14) // Serial Synchronous Controller 0
#define AT91C_ID_SSC1     (15) // Serial Synchronous Controller 1
#define AT91C_ID_SSC2     (16) // Serial Synchronous Controller 2
#define AT91C_ID_TC0      (17) // Timer Counter 0
#define AT91C_ID_TC1      (18) // Timer Counter 1
#define AT91C_ID_TC2      (19) // Timer Counter 2
#define AT91C_ID_TC3      (20) // Timer Counter 3
#define AT91C_ID_TC4      (21) // Timer Counter 4
#define AT91C_ID_TC5      (22) // Timer Counter 5
#define AT91C_ID_UHP      (23) // USB Host port
#define AT91C_ID_EMAC     (24) // Ethernet MAC
#define AT91C_ID_IRQ0     (25) // Advanced Interrupt Controller (IRQ0)
#define AT91C_ID_IRQ1     (26) // Advanced Interrupt Controller (IRQ1)
#define AT91C_ID_IRQ2     (27) // Advanced Interrupt Controller (IRQ2)
#define AT91C_ID_IRQ3     (28) // Advanced Interrupt Controller (IRQ3)
#define AT91C_ID_IRQ4     (29) // Advanced Interrupt Controller (IRQ4)
#define AT91C_ID_IRQ5     (30) // Advanced Interrupt Controller (IRQ5)
#define AT91C_ID_IRQ6     (31) // Advanced Interrupt Controller (IRQ6)

/****** Timer sfr definitions ***************************************/

#define _TC0_BASE_ADDR   (0xfffa0000UL)
#define _TC1_BASE_ADDR   (0xfffa0040UL)
#define _TC2_BASE_ADDR   (0xfffa0080UL)
#define _TC3_BASE_ADDR   (0xfffa4000UL)
#define _TC4_BASE_ADDR   (0xfffa4040UL)
#define _TC5_BASE_ADDR   (0xfffa4080UL)

/****** assign timer used for OS *********************************/

#define _OS_TC_BASE_ADDR   (_TC0_BASE_ADDR)

#define _OS_TC_CCR  (*(volatile OS_U32*)(_OS_TC_BASE_ADDR + 0x00))
#define _OS_TC_CMR  (*(volatile OS_U32*)(_OS_TC_BASE_ADDR + 0x04))
#define _OS_TC_CV   (*(volatile OS_U32*)(_OS_TC_BASE_ADDR + 0x10))
#define _OS_TC_RC   (*(volatile OS_U32*)(_OS_TC_BASE_ADDR + 0x1c))
#define _OS_TC_SR   (*(volatile OS_U32*)(_OS_TC_BASE_ADDR + 0x20))
#define _OS_TC_IER  (*(volatile OS_U32*)(_OS_TC_BASE_ADDR + 0x24))
#define _OS_TC_IDR  (*(volatile OS_U32*)(_OS_TC_BASE_ADDR + 0x28))

#if   (_OS_TC_BASE_ADDR == _TC0_BASE_ADDR)
  #define _OS_TIMER_ID (AT91C_ID_TC0)
#elif (_OS_TC_BASE_ADDR == _TC1_BASE_ADDR)
  #define _OS_TIMER_ID (AT91C_ID_TC1)
#elif (_OS_TC_BASE_ADDR == _TC2_BASE_ADDR)
  #define _OS_TIMER_ID (AT91C_ID_TC2)
#elif (_OS_TC_BASE_ADDR == _TC3_BASE_ADDR)
  #define _OS_TIMER_ID (AT91C_ID_TC3)
#elif (_OS_TC_BASE_ADDR == _TC4_BASE_ADDR)
  #define _OS_TIMER_ID (AT91C_ID_TC4)
#elif (_OS_TC_BASE_ADDR == _TC5_BASE_ADDR)
  #define _OS_TIMER_ID (AT91C_ID_TC5)
#endif

#if (_OS_TC_BASE_ADDR < _TC3_BASE_ADDR)
  #define _OS_TC_BCR    (*(volatile OS_U32*)(_TC0_BASE_ADDR + 0xc0))
  #define _OS_TC_BMR    (*(volatile OS_U32*)(_TC0_BASE_ADDR + 0xc4))
#else
  #define _OS_TC_BCR    (*(volatile OS_U32*)(_TC3_BASE_ADDR + 0xc0))
  #define _OS_TC_BMR    (*(volatile OS_U32*)(_TC3_BASE_ADDR + 0xc4))
#endif

/****** Advanced interrupt controller (AIC) *************************/
#define _AIC_BASE_ADDR      (0xfffff000UL)
#define _AIC_SMR_BASE_ADDR  (_AIC_BASE_ADDR + 0x000)
#define _AIC_SVR_BASE_ADDR  (_AIC_BASE_ADDR + 0x080)

#define _AIC_SMR0  (*(volatile OS_U32*)(_AIC_SMR_BASE_ADDR))
#define _AIC_SVR0  (*(volatile OS_U32*)(_AIC_SVR_BASE_ADDR))
#define _AIC_IVR   (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x100))
#define _AIC_ISR   (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x108))
#define _AIC_IPR   (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x10c))
#define _AIC_IDCR  (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x124))
#define _AIC_ICCR  (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x128))
#define _AIC_IECR  (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x120))
#define _AIC_EOICR (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x130))
#define _AIC_SPU   (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x134))
#define _AIC_DEBUG (*(volatile OS_U32*)(_AIC_BASE_ADDR + 0x138))

#ifndef   _NUM_INT_SOURCES
  #define _NUM_INT_SOURCES  (32)
#endif

#define _INT_PRIORITY_MASK  (0x07)
#define _NUM_INT_PRIORITIES (8)

/****** SDRAM controller interface **********************************/
#define _SDRC_BASE_ADDR     (0xFFFFFF90) // (SDRC) Base Address
#define _SDRC_MR            (*(volatile OS_U32*)(_SDRC_BASE_ADDR + 0x00))
#define _SDRC_TR            (*(volatile OS_U32*)(_SDRC_BASE_ADDR + 0x04))
#define _SDRC_CR            (*(volatile OS_U32*)(_SDRC_BASE_ADDR + 0x08))

/****** PIO control register ****************************************/
#define _PIOA_BASE_ADDR (0xfffff400UL)
#define _PIOB_BASE_ADDR (0xfffff600UL)
#define _PIOC_BASE_ADDR (0xfffff800UL)
#define _PIOD_BASE_ADDR (0xfffffA00UL)

#define _PIO_ASR_OFFS (0x70)
#define _PIO_BSR_OFFS (0x74)
#define _PIO_PDR_OFFS (0x04)

#define _SDRAM_PIO_ASR   (*(volatile OS_U32*)(_PIOC_BASE_ADDR + _PIO_ASR_OFFS))
#define _SDRAM_PIO_BSR   (*(volatile OS_U32*)(_PIOC_BASE_ADDR + _PIO_BSR_OFFS))
#define _SDRAM_PIO_PDR   (*(volatile OS_U32*)(_PIOC_BASE_ADDR + _PIO_PDR_OFFS))


/****** USART sfr definitions  **************************************/
#define _USART0_BASE_ADDR      (0xfffc0000UL)
#define _USART1_BASE_ADDR      (0xfffc4000UL)
#define _USART2_BASE_ADDR      (0xfffc8000UL)
#define _USART3_BASE_ADDR      (0xfffcc000UL)

#define _USART_CR_OFFS    (0x00)
#define _USART_MR_OFFS    (0x04)
#define _USART_IER_OFFS   (0x08)
#define _USART_IDR_OFFS   (0x0C)
#define _USART_IMR_OFFS   (0x10)
#define _USART_CSR_OFFS   (0x14)
#define _USART_RHR_OFFS   (0x18)
#define _USART_THR_OFFS   (0x1C)
#define _USART_BRGR_OFFS  (0x20)
#define _USART_RTOR_OFFS  (0x24)
#define _USART_TTGR_OFFS  (0x28)
#define _USART_TPR_OFFS   (0x108)
#define _USART_TCR_OFFS   (0x10c)
#define _USART_PTCR_OFFS  (0x120)

/****** Power management controller (PMC) ***************************/
#define _PMC_BASE_ADDR   (0xfffffc00UL)

#define _PMC_PCER       (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x10))
#define _PMC_PCDR       (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x14))
#define _PMC_CKGR_MOR   (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x20))  /* main oscillator register */
#define _PMC_CKGR_MCFR  (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x24))  /* main clock frequency register */
#define _PMC_CKGR_PLLAR (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x28))  /* PLLA register */
#define _PMC_CKGR_PLLBR (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x2c))  /* PLLB register */
#define _PMC_SR         (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x68))  /* status register */
#define _PMC_MCKR       (*(volatile OS_U32*) (_PMC_BASE_ADDR + 0x30))  /* Master clock register */

#define _CKGR_MAINRDY_BIT        (1 << 16)
#define _PMC_LOCKA_BIT           (1 <<  1)
#define _PMC_LOCKB_BIT           (1 <<  2)
#define _PMC_MCKRDY_BIT          (1 <<  3)

#define _PMC_CSS_MAIN_CLK_SELECT (0x1)

#if _AIC_DEBUG_MODE
  #define _AIC_DEBUG_RESET()  (_AIC_IVR   = 0)
  #define _AIC_DEBUG_INIT()   (_AIC_DEBUG = 1)
#else
  #define _AIC_DEBUG_RESET()
  #define _AIC_DEBUG_INIT()
#endif

/****** External bus interface **************************************/
#define _EBI_BASE_ADDR  (0xffffff60UL)
#define _EBI_CSA   (*(volatile OS_U32*) (_EBI_BASE_ADDR + 0x00))
#define _EBI_CFGR  (*(volatile OS_U32*) (_EBI_BASE_ADDR + 0x04))

/****** Static memory controller interface **************************/
#define _SMC_BASE_ADDR      (0xffffff70UL)
#define _SMC_CSR_BASE_ADDR  (_SMC_BASE_ADDR)
#define _SMC_CSR0      (*(volatile OS_U32*) (_SMC_BASE_ADDR + 0x00))

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _DefaultFiqHandler(), a dummy FIQ handler
*       Used here to initialize AIC
*/
static void _DefaultFiqHandler(void) {
  while(1);
}

/*********************************************************************
*
*       _DefaultIrqHandler, a dummy IRQ handler
*
*       This handler is initially written into all AIC interrupt vectors
*       It is called, if no interrupt vector was installed for
*       specific interrupt source.
*       May be used during debugging to detect uninstalled interrupts
*/
static void _DefaultIrqHandler(void) {
  OS_U32 IrqSource;
  IrqSource = _AIC_ISR;  /* detect source of uninstalled interrupt */
  while(IrqSource == _AIC_ISR);
}

/*********************************************************************
*
*       _SpuriousIrqHandler(), a dummy spurious IRQ handler
*/
static OS_U32 _SpuriousIrqCnt;
static void _SpuriousIrqHandler(void) {
  _SpuriousIrqCnt++;
}

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void _OS_ISR_Tick(void) {
  volatile OS_U32 Dummy;
  Dummy = _OS_TC_SR;    // Reset Timer Interrupt to reset/reenable further interrupts
  OS_HandleTick();      // Call OS tick handler
  #if DEBUG
    DCC_Process();
  #endif
}

/*********************************************************************
*
*       _InitAIC()
*
*       Initialize interupt controller by setting default vectors
*       and clearing all interrupts
*/
static void _InitAIC(void) {
  int  i;
  OS_ISR_HANDLER** papISR;

  _AIC_IDCR  = 0xFFFFFFFF;                    /* Disable all interrupts     */
  _AIC_ICCR  = 0xFFFFFFFF;                    /* Clear all interrupts       */
  _AIC_DEBUG_INIT();                          /* Force protected mode       */

  _AIC_SVR0 = (int) _DefaultFiqHandler;       /* dummy FIQ handler          */
  _AIC_SPU  = (int) _SpuriousIrqHandler ;     /* dummy spurious handler     */
  papISR = (OS_ISR_HANDLER**) _AIC_SVR_BASE_ADDR;
  for (i = 1; i < _NUM_INT_SOURCES; i++)  {   /* initially set all sources  */
    *(papISR + i) = &_DefaultIrqHandler;      /* to dummy irq handler       */
  }
  for (i = 0; i < _NUM_INT_PRIORITIES; i++) {
    _AIC_EOICR = 0;                           /* Reset interrupt controller */
  }
}

/*********************************************************************
*
*       _InitFlash
*
* Function description
*   Initialize wait states and BUS interface for external Flash access
*   Needs to be called before main clock is switched to high speed
*
* NOTE: Settings of wait states depend on CPU clock and Flash type
*       Settings used here are for AT91RM9200-EK eval board
*       and may have to be modified for other target board
*/
static void _InitFlash(void) {
/*
  _EBI_CSA = 0x00
            |(0 << 0)        // CS0    assigned to SMC
            |(0 << 1)        // CS1    assigned to SMC
            |(0 << 3)        // CS3    assigned to SMC
            |(0 << 4)        // CS4..6 assigned to SMC
            ;
*/
  _EBI_CFGR = 0x00
            |(0 << 0)        /* Data BUS pull up disabled */
            |(0 << 1)        /* Data BUS sharing disabled */
            ;
  _SMC_CSR0 = 0x00           /* Settings for CS0          */
            | 0x04           /* Number of wait states     */
            | (1 << 7)       /* Enable wait states        */
            | (2 << 8)       /* Two data float cycles     */
            | (1 << 12)      /* Flash is 16 bit type      */
            | (1 << 13)      /* 16 bit data bus width     */
            | (0 << 15)      /* standard read protocol    */
            | (0 << 16)      /* standard CS pulse         */
            | (0 << 24)      /* smallest RW setup time    */
            | (0 << 28)      /* smallest RW hold time     */
            ;
}

/*********************************************************************
*
*       _InitClocks
*
* Function description
*   Initialize main clock and PLLs
*
* NOTE: Settings used here are for AT91RM9200-EK eval board
*       and may have to be modified for other target board or frequency
*/
static void _InitClocks(OS_U32 PLLA_Val, OS_U32 PLLB_Val, OS_U32 MCKR_Val) {
  volatile int Cnt;

  // Eanble main clock OSC and wait until delay counter expired
  _PMC_CKGR_MOR = 0x0000FF01;            // PMC_MOR: MOSCEN = 1, enable main clock
  while((_PMC_CKGR_MCFR & _CKGR_MAINRDY_BIT) == 0) {
  }
  /*  Initialize PLL A for Main clock */
  _PMC_CKGR_PLLAR = PLLA_Val;
  //* Wait for PLLA stabilization LOCKA bit in PMC_SR
  Cnt = 0;
  while(((_PMC_SR & _PMC_LOCKA_BIT) == 0) && (Cnt < _DELAY_PLL) ) {
    Cnt++;
  }

  /*  Initialize PLL B for USB clock */
  _PMC_CKGR_PLLBR = PLLB_Val;
  //* Wait for PLLB stabilization LOCKB bit in PMC_SR
  Cnt = 0;
  while(((_PMC_SR & _PMC_LOCKB_BIT) == 0) && (Cnt < _DELAY_PLL) ) {
    Cnt++;
  }

  /* Select Master Clock MCK and Processor Clock PCK */
  /* Write in the MCKR dirty value concerning the clock selection CSS then overwrite it in a second sequence */
  _PMC_MCKR = _PMC_CSS_MAIN_CLK_SELECT;

  /* Wait until the master clock is stable */
  Cnt = 0;
  while(((_PMC_SR & _PMC_MCKRDY_BIT) == 0) && (Cnt < _DELAY_MAIN_FREQ) ) {
    Cnt++;
  }
  _PMC_MCKR = MCKR_Val;
  /* Wait until the master clock is stable */
  Cnt = 0;
  while(((_PMC_SR & _PMC_MCKRDY_BIT) == 0) && (Cnt < _DELAY_MAIN_FREQ) ) {
    Cnt++;
  }
}

/*********************************************************************
*
*       _InitSDRAM
*
* Function description
*   Initialize SDRAM controller
*
* NOTE: Settings used here are for AT91RM9200-EK eval board
*       and may have to be modified for other target board
*/
static void _InitSDRAM(void) {
  int   i;
  volatile int *pSDRAM;

  pSDRAM = (int *)_SDRAM_BASE_ADDR;

  /* Configure PIO for peripheral function used for SDRAM access */
  if ((_EBI_CSA  & (1 << 1)) == 0) {   // Make sure we do not init SDRAM if program is already running in SDRAM
    _SDRAM_PIO_ASR = 0xffff0000;   /* Select peripheral A function: D16..D31 used as data signals for SDRAM */
    _SDRAM_PIO_BSR = 0x0;          /* Disable peripheral B function */
    _SDRAM_PIO_PDR = 0xffff0000;   /* disable PIO for D16..D31 */

    /* Setup MEMC to support CS1 = SDRAM */
    _EBI_CSA  |= (1 << 1);         /* assign CS1 */

    /* Init SDRAM controller */
    _SDRC_CR = 0x01                    /* 9 bit        */
             | (0x1 << 2)              /* 12 bit       */
             | (0x1 << 4)              /* 4 Banks      */
             | (0x2 << 5)              /* 2 CAS cycles */
             | 0x100
             | 0x4000
             | 0x8000
             | 0x880000
             | 0x21000000
             ;

    /* 2. Send Precharge All command to SDRAM */
    _SDRC_MR = 0x02;
    *pSDRAM  = 0;

    /* 3. Eight Auto-refresh are provided */
    _SDRC_MR = 0x04;
    for(i = 0; i < 8; i++) {
      *pSDRAM = 0;
    }

    /* 4. Send mode register command to program the SDRAM parameters  */
    _SDRC_MR       = 0x03;
    *(pSDRAM+0x80) = 0;

    /* 5. Write refresh rate into SDRAMC refresh timer COUNT register */
    _SDRC_TR = 0x2E0;
    *pSDRAM  = 0;

    /* 6. Normal Mode Command is provided, 3 clocks after tMRD is set */
    _SDRC_MR = 0x00;
    *pSDRAM  = 0;
  }
}

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
#define _OS_TIMER_RELOAD (OS_PCLK_TIMER/TIMER_PRESCALE/OS_TICK_FREQ)
#define _OS_TIMER_PRIO   (0x00)       // lowest priority

void OS_InitHW(void) {
  volatile OS_U32 Dummy;
  OS_DI();
  _InitAIC();                         // Initialize and reset AIC
  // Initialize OS timer (selected timer, capture mode channel C)
  _PMC_PCER    = (1 << _OS_TIMER_ID); // Enable peripheral clock for timer 0
  _OS_TC_IDR   = 0xff;                // Disable all timer/counter 0 interrupts.
  _OS_TC_BMR   = 0x02;                // Runs on internal clock
  _OS_TC_CMR   = 0x00004000;          // Capture mode, CPCTRG=1, TCCLKS=0 (=> MCLK/2)
  _OS_TC_RC    = _OS_TIMER_RELOAD;    // Set compare register
  _OS_TC_CCR   = 1;                   // Enable the clock.
  _OS_TC_CCR   = 5;                   // Software trigger.
  Dummy        = _OS_TC_SR;           // Read timer/counter 0 status register to clear flags.
  _OS_TC_IER   = (1 << 4);            // Interrupt on RC compare.
  // Setup interrupt controller for OS timer interrupt using selected timer
  OS_ARM_InstallISRHandler(_OS_TIMER_ID, &_OS_ISR_Tick); // Timer/counter 0 interrupt vector.
  OS_ARM_ISRSetPrio(_OS_TIMER_ID, 0x00);                 // Timer/counter 0 interrupt level sensitive at lowest priority (0).
  _AIC_ICCR = (1 << _OS_TIMER_ID);                       // Clears timer/counter 0 interrupt.
  OS_ARM_EnableISR(_OS_TIMER_ID);                        // Enable timer/counter 0 interrupt.
  // optionally initialize UART for OSView
  OS_COM_Init();
  OS_RestoreI();
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
void OS_Idle(void) {     // Idle loop: No task is ready to exec
  while (1) {
  }
}

/*********************************************************************
*
*       Get time [cycles]
*
*       This routine is required for task-info via OSView or high
*       resolution time maesurement functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  unsigned int t_cnt = _OS_TC_CV;       // Read current timer value
  OS_U32 time = OS_GetTime32();         // Read current OS time
  if (_AIC_IPR & (1 << _OS_TIMER_ID)) { // Timer Interrupt pending ?
    t_cnt = _OS_TC_CV;                  // Adjust result
    time++;
  }
  return _OS_TIMER_RELOAD*time + t_cnt;
}

/*********************************************************************
*
*       OS_ConvertCycles2us
*
*       Convert Cycles into micro seconds.
*
*       If your clock frequency is not a multiple of 1 MHz,
*       you may have to modify this routine in order to get proper
*       diagonstics.
*
*       This routine is required for profiling or high resolution time
*       measurement only. It does not affect operation of the OS.
*/
OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
  Cycles *= TIMER_PRESCALE;           // eliminate effect of prescaler
  return Cycles/(OS_PCLK_TIMER/1000000);
}

/*********************************************************************
*
*       Communication for OSView via UART (optional)
*
**********************************************************************
*/
#if OS_UART_USED
  /* Assign selected USART used for OSView to hardware ***********/
  #if (OS_UART == 0)
    #define _OS_UART_BASE_ADDR    (_USART0_BASE_ADDR)
    #define _OS_UART_ID           (AT91C_ID_US0)
    #define _USART_PIO_BASE_ADDR  (_PIOA_BASE_ADDR)
    #define _USART_PIO_PDR_VAL    ((1 << 17) | (1 << 18))
    #define _USART_PIO_ABSEL_OFFS (_PIO_ASR_OFFS )
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR    (_USART1_BASE_ADDR)
    #define _OS_UART_ID           (AT91C_ID_US1)
    #define _USART_PIO_BASE_ADDR  (_PIOB_BASE_ADDR)
    #define _USART_PIO_PDR_VAL    ((1 << 20) | (1 << 21))
    #define _USART_PIO_ABSEL_OFFS (_PIO_ASR_OFFS )
  #elif (OS_UART == 2)
    #define _OS_UART_BASE_ADDR    (_USART2_BASE_ADDR)
    #define _OS_UART_ID           (AT91C_ID_US2)
    #define _USART_PIO_BASE_ADDR  (_PIOA_BASE_ADDR)
    #define _USART_PIO_PDR_VAL    ((1 << 22) | (1 << 23))
    #define _USART_PIO_ABSEL_OFFS (_PIO_ASR_OFFS )
  #elif (OS_UART == 3)
    #define _OS_UART_BASE_ADDR    (_USART3_BASE_ADDR)
    #define _OS_UART_ID           (AT91C_ID_US3)
    #define _USART_PIO_BASE_ADDR  (_PIOA_BASE_ADDR)
    #define _USART_PIO_PDR_VAL    ((1 << 5) | (1 << 6))
    #define _USART_PIO_ABSEL_OFFS (_PIO_BSR_OFFS )
  #endif

  #define _USART_PIO_PDR   (*(volatile OS_U32*)(_USART_PIO_BASE_ADDR + _PIO_PDR_OFFS))
  #define _USART_PIO_ABSEL (*(volatile OS_U32*)(_USART_PIO_BASE_ADDR + _USART_PIO_ABSEL_OFFS ))

  #define _OS_USART_CR     (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_CR_OFFS))
  #define _OS_USART_MR     (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_MR_OFFS))
  #define _OS_USART_IER    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_IER_OFFS))
  #define _OS_USART_IDR    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_IDR_OFFS))
  #define _OS_USART_IMR    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_IMR_OFFS))
  #define _OS_USART_CSR    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_CSR_OFFS))
  #define _OS_USART_RHR    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_RHR_OFFS))
  #define _OS_USART_THR    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_THR_OFFS))
  #define _OS_USART_BRGR   (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_BRGR_OFFS))
  #define _OS_USART_RTOR   (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_RTOR_OFFS))
  #define _OS_USART_TTGR   (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_TTGR_OFFS))
  #define _OS_USART_TPR    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_TPR_OFFS))
  #define _OS_USART_TCR    (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_TCR_OFFS))
  #define _OS_USART_PTCR   (*(volatile OS_U32*)(_OS_UART_BASE_ADDR + _USART_PTCR_OFFS))

  #define _USART_RXRDY          (1 << 0)   /* Rx status flag       */
  #define _USART_TXRDY          (1 << 1)   /* Tx RDY Status flag   */
  #define _USART_TXEMPTY        (1 << 9)   /* Tx EMPTY Status flag */
  #define _USART_ENDTX          (1 << 4)   /* Tx end flag          */

  #define _USART_RX_ERROR_FLAGS (0xE0)     /* Parity, framing, overrun error */

  #define _OS_UART_PRIO         (0x00)     /* Lowest priority for UART interrupts */
  #define _USART_TXINT_FLAG     (_USART_ENDTX)

/*********************************************************************
*
*       OS_COM_ISR_Usart() OS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void OS_COM_ISR_Usart(void) {
  int UsartStatus;
  volatile OS_U32 Dummy;

  UsartStatus = _OS_USART_CSR;                    // Examine status register
  do {
    if (UsartStatus & _USART_RXRDY)    {          // Data received?
      if (UsartStatus & _USART_RX_ERROR_FLAGS) {  // Any error ?
        Dummy = _OS_USART_RHR;                    // => Discard data
        _OS_USART_CR = (1 << 8);                  // RSTSTA: Reset Status Bits PARE, FRAME, OVRE and RXBRK
      } else {
        OS_OnRx(_OS_USART_RHR);                   // Process actual byte
      }
    }
    if (UsartStatus & _OS_USART_IMR & _USART_TXINT_FLAG) { // Check Tx status => Send next character
      if (OS_OnTx()) {                                     // No more characters to send ?
        _OS_USART_IDR = _USART_TXINT_FLAG;                 // Disable further tx interrupts
      }
    }
    UsartStatus = _OS_USART_CSR;                           // Examine current status
  } while (UsartStatus & _OS_USART_IMR & (_USART_TXINT_FLAG | _USART_RXRDY));
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
static OS_U8 buffer1;

void OS_COM_Send1(OS_U8 c) {
  buffer1 = c;
  _OS_USART_TPR  = (OS_U32) &buffer1;
  _OS_USART_TCR  = 1;
  _OS_USART_PTCR = (1 << 8);         /* Enable transmission */
  _OS_USART_IER = _USART_TXINT_FLAG; /* enable Tx interrupt */
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {                  // Initialize UART, enable UART interrupts
  _PMC_PCER        = (1 << _OS_UART_ID);  // Enable peripheral clock for selected USART
  _USART_PIO_PDR   = _USART_PIO_PDR_VAL;  // Enable peripheral output signals (disable PIO Port)
  _USART_PIO_ABSEL = _USART_PIO_PDR_VAL;  // Select peripheral function A ob according to selected USART
  _OS_USART_IDR    = 0xffffffffUL;        // Initially disable all USART interrupts
  _OS_USART_CR     =  (1 <<  2)           // RSTRX: Reset Receiver: 1 = The receiver logic is reset.
                   |  (1 <<  3)           // RSTTX: Reset Transmitter: 1 = The transmitter logic is reset.
                   ;
  _OS_USART_CR     =  (0 <<  2)           // RSTRX: Reset Receiver: 1 = The receiver logic is reset.
                   |  (0 <<  3)           // RSTTX: Reset Transmitter: 1 = The transmitter logic is reset.
                   |  (1 <<  4)           // RXEN: Receiver Enable: 1 = The receiver is enabled if RXDIS is 0.
                   |  (0 <<  5)           // RXDIS: Receiver Disable: 0 = Noeffect.
                   |  (1 <<  6)           // TXEN: Transmitter Enable: 1 = The transmitter is enabled if TXDIS is 0.
                   |  (0 <<  7)           // TXDIS: Transmitter Disable: 0 = Noeffect.
                   |  (1 <<  8)           // RSTSTA: Reset Status Bits: 1 = Resets the status bits PARE, FRAME, OVRE and RXBRK in the US_CSR.
                   |  (0 <<  9)           // STTBRK: Start Break: 0 = Noeffect.
                   |  (0 << 10)           // STPBRK: Stop Break: 0 = Noeffect.
                   |  (0 << 11)           // STTTO: Start Time-out: 0 = Noeffect.
                   |  (0 << 12)           // SENDA: Send Address: 0 = Noeffect.
                   ;
  _OS_USART_MR     =  (0 <<  4)           // USCLKS: Clock Selection: 0 = MCK
                   |  (3 <<  6)           // CHRL: Character Length: 3 = Eight bits
                   |  (0 <<  8)           // SYNC: Synchronous Mode Select: 0 = USART operates in Asynchronous Mode.
                   |(0x4 <<  9)           // PAR: Parity Type: 0x4 = No parity
                   |  (0 << 12)           // NBSTOP: Number of Stop Bits: 0 = 1 stop bit
                   |  (0 << 14)           // CHMODE: Channel Mode: 0 = Normal mode
                   |  (0 << 17)           // MODE9: 9-bit Character Length: 0 = CHRL defines character length.
                   |  (0 << 18)           // CKLO: Clock Output Select: 0 = The USART does not drive the SCK pin.
                   ;
  _OS_USART_BRGR   = (OS_PCLK_UART / (OS_BAUDRATE * 16));
  _OS_USART_IER    = (1 << 0)            // Enable Rx Interrupt
                   ;
  // Setup interrupt controller for OS USART
  OS_ARM_InstallISRHandler(_OS_UART_ID, &OS_COM_ISR_Usart);  // OS UART interrupt handler vector
  OS_ARM_ISRSetPrio(_OS_UART_ID, _OS_UART_PRIO);             // Level sensitive, selected priority.
  _AIC_ICCR = (1 << _OS_UART_ID);                            // Clear OS usart interrupt.
  OS_ARM_EnableISR(_OS_UART_ID);                             // Enable OS usart interrupts
}

#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let the OS know that Tx is not busy
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
  pISR = (OS_ISR_HANDLER*) _AIC_IVR;  // Read interrupt vector to release NIRQ to CPU core
  _AIC_DEBUG_RESET();                 // Reset AIC if in debug mode
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();        // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                // Inform OS that interrupt handler is running
#endif
  pISR();                             // Call interrupt service routine
  OS_DI();                            // Disable interrupts and unlock
  _AIC_EOICR = 0;                     // interrupt controller =>  Restore previous priority
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();        // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                // Leave interrupt, perform task switch if required
#endif
}

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*
*/
OS_ISR_HANDLER* OS_ARM_InstallISRHandler (int ISRIndex, OS_ISR_HANDLER* pISRHandler) {
  OS_ISR_HANDLER*  pOldHandler;
  OS_ISR_HANDLER** papISR;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return NULL;
  }
#endif

  OS_DI();
  papISR = (OS_ISR_HANDLER**)&_AIC_SVR0;
  pOldHandler          = *(papISR + ISRIndex);
  *(papISR + ISRIndex) = pISRHandler;
  OS_RestoreI();
  return pOldHandler;
}

/*********************************************************************
*
*       OS_ARM_EnableISR
*
*/
void OS_ARM_EnableISR(int ISRIndex) {
#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif

  OS_DI();
  _AIC_IECR = (1 << ISRIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*
*/
void OS_ARM_DisableISR(int ISRIndex) {
#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif

  OS_DI();
  _AIC_IECR &= ~(1 << ISRIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  OS_U32* pPrio;
  int     OldPrio;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return 0;
  }
#endif

  OS_DI();
  pPrio = (OS_U32*)&_AIC_SMR0;
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
#ifdef __cplusplus
extern "C" {
#endif

#pragma diag_suppress=Pe940 // IAR specific: No warning for missing return
OS_U32 GetPC(void);
OS_U32 GetPC(void) {
  __asm("mov r0, pc");
}

OS_INTERWORK int __low_level_init(void); /* declare function to avoid compiler warning */
OS_INTERWORK int __low_level_init(void) {
  /*
  *   Setup waitstates for Flash and external BUS interface before switching to high speed
  */
  _InitFlash();
  /*
  *   Initialize main clock oscillator and PLLs
  */
  _InitClocks(_PLLAR_VALUE, _PLLBR_VALUE, _MCKR_VALUE);
  /*
  *   Initialize SDRAM
  */
  _InitSDRAM();
  /*
  *   Make sure vector area is o.k.
  */
  if (GetPC() & 0x20000000) {   // Running in SDRAM ?
    memcpy((void*)0, (void*)0x20000000, 0x40);
  }
  return 1;  /* Always return 1 to force initialization of segments */
}

#ifdef __cplusplus
  }
#endif

/*****  EOF  ********************************************************/
