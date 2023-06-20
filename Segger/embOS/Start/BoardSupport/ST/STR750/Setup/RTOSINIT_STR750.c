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
File    : RTOSINIT_STR750.c                       (for ST STR750 CPUs)
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

#ifndef   OS_FSYS                   /* CPU main clock frequncy      */
  #define OS_FSYS 60000000L         /* may depend on PLL            */
#endif

#ifndef   OS_PCLK_TIMER             /* Peripheral clock for timer   */
  #define OS_PCLK_TIMER OS_FSYS/2   /* Default: CPU clock / 2       */
#endif

#ifndef   OS_PCLK_UART              /* Peripheral clock for UART    */
  #define OS_PCLK_UART OS_FSYS/2    /* Default: CPU clock / 2       */
#endif

#ifndef   OS_XTAL_FREQUENCY
  #define OS_XTAL_FREQUENCY (4000000L)
#endif

#ifndef   OS_INIT_PLL               /* PLL may be initialized       */
  #define OS_INIT_PLL 1             /* during startup               */
#endif

#define  PLL_MUL   MRCC_PLL_MUL_15

#define _OS_TIMER_INTERVAL (OS_PCLK_TIMER / 1000)
#define _OS_TIMER_PRESCALE (1)


/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 0 per default
*       and supports UART0 to UART3
*/
#ifndef   OS_UART
  #define OS_UART 0
#endif
#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400L
#endif

/****** Define behaviour of undefined interrupt handling ************/

#ifndef   OS_IGNORE_UNDEFINED_INTERRUPT
  #define OS_IGNORE_UNDEFINED_INTERRUPT 0
#endif

/****** End of configuration settings *******************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1) || (OS_UART == 2))

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** UART sfdr definition ****************************************/
/****** UART0 *******************************************************/

#define _UART0_BASE_ADDR   (0xFFFFD400)
#define _UART1_BASE_ADDR   (0xFFFFD800)
#define _UART2_BASE_ADDR   (0xFFFFDC00)

/****** Assign UART sfrs used for OSView communication ***********/

#if OS_UART_USED
  #if   (OS_UART == 0)
    #define _OS_UART_BASE_ADDR  _UART0_BASE_ADDR
    #define _OS_UART_INT_ID     _UART0_VECT_ID
    #define _OS_UART_CLK_EN_BIT (20)
    #define _OS_UART_RX_PIN     (10)
    #define _OS_UART_TX_PIN     (11)
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR  _UART1_BASE_ADDR
    #define _OS_UART_INT_ID     _UART1_VECT_ID
    #define _OS_UART_CLK_EN_BIT (21)
    #define _OS_UART_RX_PIN     (20)
    #define _OS_UART_TX_PIN     (21)
  #elif (OS_UART == 2)
    #define _OS_UART_BASE_ADDR  _UART2_BASE_ADDR
    #define _OS_UART_INT_ID     _UART2_VECT_ID
    #define _OS_UART_CLK_EN_BIT (22)
    #define _OS_UART_RX_PIN     (24)
    #define _OS_UART_TX_PIN     (25)
  #endif

  #define _OS_UART_DR      *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x00)
  #define _OS_UART_RSR     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x04)
  #define _OS_UART_FR      *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x18)
  #define _OS_UART_ILPR    *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x20)
  #define _OS_UART_IBRD    *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x24)
  #define _OS_UART_FBRD    *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x28)
  #define _OS_UART_LCR     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x2C)
  #define _OS_UART_CR      *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x30)
  #define _OS_UART_IFLS    *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x34)
  #define _OS_UART_IMSC    *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x38)
  #define _OS_UART_RIS     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x3C)
  #define _OS_UART_MIS     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x40)
  #define _OS_UART_ICR     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x44)
  #define _OS_UART_DMACR   *(volatile OS_U16*)(_OS_UART_BASE_ADDR + 0x48)

  #define _TX_EMPTY_INT_BIT (5)
  #define _RX_FULL_INT_BIT  (4)
  #define _TXRDY_FLAG       (1uL << _TX_EMPTY_INT_BIT)
  #define _RXRDY_FLAG       (1uL << _RX_FULL_INT_BIT)

  #define _OS_UART_PRIO     (0x01)  // Lowest prio
#endif

/****** GPIO register ***********************************************/

#define _GPIO0_BASE_ADDR   0xFFFFE400
#define _GPIO1_BASE_ADDR   0xFFFFE440
#define _GPIO2_BASE_ADDR   0xFFFFE480

#define _GPIO0_PC0   *(volatile OS_U32*)(_GPIO0_BASE_ADDR + 0x00)
#define _GPIO0_PC1   *(volatile OS_U32*)(_GPIO0_BASE_ADDR + 0x04)
#define _GPIO0_PC2   *(volatile OS_U32*)(_GPIO0_BASE_ADDR + 0x08)
#define _GPIO0_PD    *(volatile OS_U32*)(_GPIO0_BASE_ADDR + 0x0C)

/****** Power, reset, config, clock control unit register ***********/

#define _CFG_GLCONF   *(volatile OS_U32*)(0x60000010)


#define _MRCC_BASE_ADDR 0x60000020

#define _MRCC_CLKCTL  *(volatile OS_U32*)(_MRCC_BASE_ADDR + 0x00)
#define _MRCC_RFSR    *(volatile OS_U32*)(_MRCC_BASE_ADDR + 0x04)
#define _MRCC_PWRCTRL *(volatile OS_U32*)(_MRCC_BASE_ADDR + 0x08)
#define _MRCC_PCLKEN  *(volatile OS_U32*)(_MRCC_BASE_ADDR + 0x10)
#define _MRCC_PSWRES  *(volatile OS_U32*)(_MRCC_BASE_ADDR + 0x14)


#define _MRCC_GPIO_EN_BIT  (24)
#define _MRCC_UART0_EN_BIT (20)
#define _MRCC_UART1_EN_BIT (21)
#define _MRCC_UART2_EN_BIT (22)
#define _MRCC_NCKDF_BIT    (18)
#define _MRCC_CKOSCSEL_BIT (21)
#define _MRCC_CKSEL_BIT    (23)
#define _MRCC_PLLEN_BIT    (24)
#define _MRCC_BCOUNT_BIT   (24)
#define _MRCC_OSC4MOFF_BIT (17)
#define _MRCC_XTDIV2_BIT   (15)
#define _MRCC_LOCK_BIT     (31)
#define _MRCC_EN33V_BIT    (16)

#define _MRCC_HPRESC_RESET_MASK      0xFFFFFFE7
#define _MRCC_PPRESC_RESET_MASK      0xFFFFFFFC
#define _MRCC_PPRESC2_RESET_MASK     0xFFFFFFFB
#define _MRCC_MX_MASK                0xE7FFFFFF

#define MRCC_PLL_MUL_16              (0 << 27)
#define MRCC_PLL_MUL_15              (1 << 27)
#define MRCC_PLL_MUL_14              (2 << 27)
#define MRCC_PLL_MUL_12              (3 << 27)

#define _OSC4M_STARTUP_TIMEOUT (254)

/****** Timer sfr definition ****************************************/

#define _TB_BASE_ADDR      (0xFFFF8800)
#define _TIM0_BASE_ADDR    (0xFFFF8C00)
#define _TIM1_BASE_ADDR    (0xFFFF9000)
#define _TIM2_BASE_ADDR    (0xFFFF9400)

#define _TIM_CR_OFFS       (0x00)
#define _TIM_SCR_OFFS      (0x04)
#define _TIM_IMCR_OFFS     (0x08)
#define _TIM_RSR_OFFS      (0x18)
#define _TIM_RER_OFFS      (0x1c)
#define _TIM_ISR_OFFS      (0x20)
#define _TIM_CNT_OFFS      (0x24)
#define _TIM_PSC_OFFS      (0x28)
#define _TIM_ARR_OFFS      (0x30)
#define _TIM_ICR1_OFFS     (0x4c)

/****** Assign timer sfrs used for OS timer *************************/
/****** Per default, we use the time base timer *********************/

#define _OS_TIM_BASE_ADDR   _TB_BASE_ADDR
#define _OS_TIM_CR          *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_CR_OFFS)
#define _OS_TIM_SCR         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_SCR_OFFS)
#define _OS_TIM_IMCR        *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_IMCR_OFFS)
#define _OS_TIM_RSR         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_RSR_OFFS)
#define _OS_TIM_RER         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_RER_OFFS)
#define _OS_TIM_ISR         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_ISR_OFFS)
#define _OS_TIM_CNT         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_CNT_OFFS)
#define _OS_TIM_PSC         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_PSC_OFFS)
#define _OS_TIM_ARR         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_ARR_OFFS)
#define _OS_TIM_ICR1        *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_ICR1_OFFS)

#if   _OS_TIM_BASE_ADDR == _TB_BASE_ADDR
  #define _MRCC_TIM_BIT     (1)
  #define _OS_TIMER_ID      (31)
#elif _OS_TIM_BASE_ADDR == _TIM0_BASE_ADDR
  #define _MRCC_TIM_BIT     (2)
  #define _OS_TIMER_ID      (12)
#elif _OS_TIM_BASE_ADDR == _TIM1_BASE_ADDR
  #define _MRCC_TIM_BIT     (3)
  #define _OS_TIMER_ID      (8)
#elif _OS_TIM_BASE_ADDR == _TIM2_BASE_ADDR
  #define _MRCC_TIM_BIT     (4)
  #define _OS_TIMER_ID      (4)
#endif

/****** Enhanced interrupt controller (EIC) *************************/

#define _EIC_ICR   *(volatile OS_U32*)0xfffff800
#define _EIC_CICR  *(volatile OS_U32*)0xfffff804
#define _EIC_CPIR  *(volatile OS_U32*)0xfffff808
#define _EIC_IVR   *(volatile OS_U32*)0xfffff818
#define _EIC_FIR   *(volatile OS_U32*)0xfffff81C
#define _EIC_IER   *(volatile OS_U32*)0xfffff820
#define _EIC_IPR   *(volatile OS_U32*)0xfffff840
#define _EIC_SIR0  *(volatile OS_U32*)0xfffff860

/****** Enhanced interrupt controller interrupt sources *************/

#define _UART0_VECT_ID     21  // IRQ21 UART0.IRQ UART 0 global interrupt
#define _UART1_VECT_ID     20  // IRQ20 UART1.IRQ UART 1 global interrupt
#define _UART2_VECT_ID     19  // IRQ19 UART2.IRQ UART 2 global interrupt

#ifndef NUM_INT_SOURCES
  #define NUM_INT_SOURCES  32
#endif
#define _INT_CHANNEL_MASK  0x1F

#define _INT_PRIORITY_MASK 0x0F

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static OS_ISR_HANDLER* _apOS_ISRHandler[NUM_INT_SOURCES];

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*******************************************************************************
* Function Name  : WriteCKOSCSELBit
* Description    : Executes the CKOSCSEL bit writing sequence.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void _WriteCKOSCSELBit(void) {
  volatile OS_U32 Tmp;
  OS_U32 Tmp1;
  OS_U32 Tmp2;

  Tmp  = _MRCC_CLKCTL;
  Tmp1 = Tmp |  (1uL << _MRCC_CKOSCSEL_BIT);
  Tmp2 = Tmp & ~(1uL << _MRCC_CKOSCSEL_BIT);
  _MRCC_CLKCTL = Tmp1;  /* Set CKOSCSEL bit */
  _MRCC_CLKCTL = Tmp1;  /* Set CKOSCSEL bit */
  _MRCC_CLKCTL = Tmp2;  /* Reset CKOSCSEL bit */
  _MRCC_CLKCTL = Tmp1;  /* Set CKOSCSEL bit */
  Tmp = _MRCC_CLKCTL;   /* Read CKOSCSEL bit */
}

/*********************************************************************
*
*       _InitPLL
*
* Function description
*   Initialize main clock and PLL
*   Should be called as early as possible in order to keep boot time short
*   WARNING: Improper settings may lock CPU
*   Please examine whether init sequence fits your harware configuration
*   We assume a CPU running with external 4 or 8 MHz oscillator and switch to 60 MHz
*/
static void _InitPLL(void) {
  #if OS_INIT_PLL
  OS_U32 Cnt;
  OS_U32 Temp;
  //
  // Set Flash Burst mode
  //
  _CFG_GLCONF |= (1uL << 8);
  //
  // Reset MRCC system (for debug purpose)
  //
  _MRCC_CLKCTL &= ~(1uL << _MRCC_NCKDF_BIT);             // Try to clear NCKDF bit
  if ((_MRCC_CLKCTL & (1uL << _MRCC_NCKDF_BIT)) != 0) {  // No clock detected on OSC4M
    // Reset LOCKIE, LOCKIF, CKUSBSEL, NCKDIE, OSC4MOFF, OSC4MBYP, MCOS[1:0],
    // MCOP, HPRESC[1:0], PPRES[2:0] bits
    _MRCC_CLKCTL &= 0x9FB40000;
    if ((_MRCC_CLKCTL & (1uL << _MRCC_CKOSCSEL_BIT)) != 0)  {  // Clear CKOSCSEL bit
      _WriteCKOSCSELBit();                                     // Execute CKOSCSEL bit writing sequence
    }
  } else {                                                     // Clock is present on OSC4M
    if ((_MRCC_CLKCTL & (1uL << _MRCC_CKOSCSEL_BIT)) != 0)  {
      _MRCC_CLKCTL &= ~(1uL << _MRCC_CKSEL_BIT);               // Reset CKSEL bit
      _WriteCKOSCSELBit();                                     // Clear CKOSCSEL bit by special sequence */
    }
    if ((_MRCC_CLKCTL & (1uL << _MRCC_CKSEL_BIT)) == 0) {
      _MRCC_CLKCTL |= (1uL << _MRCC_CKSEL_BIT);                // Set CKSEL bit to select Oscillator as clock source
    }
    _MRCC_CLKCTL &= ~(1uL << _MRCC_PLLEN_BIT);                 // Disable PLL
    _MRCC_CLKCTL &= 0x87B70000;                                // Reset LOCKIE, LOCKIF, MX[1:0], CKUSBSEL, NCKDIE, MCOS[1:0], MCOP, HPRESC[1:0], PPRES[2:0]
    _MRCC_CLKCTL &= ~(1uL << _MRCC_CKSEL_BIT);                 // Reset CKSEL bit
    _MRCC_CLKCTL &= 0xFFFCFFFF;                                // Reset OSC4MOFF and OSC4MBYP bits
  }
  /* Reset RTCM, EN33V, LP_PARAM[15:13], WFI_FLASH_EN, LPMC_DBG and LPMC[1:0] bits */
  _MRCC_PWRCTRL &= 0xFBFE1FE1;
  _MRCC_PCLKEN   = 0x00;                                       // Reset PCLKEN, => disable all peripheral clocks
  _MRCC_PSWRES   = 0x00;                                       // Reset PSWRES register bits
  _MRCC_CLKCTL  &= ~(1uL << _MRCC_NCKDF_BIT);                  // Clear NCKDF bit

  //
  // Wait for OSC4M start-up
  //
  Cnt = 0;
  do {   // Clear No Clock Detected flag
    if(_MRCC_CLKCTL & (1uL << _MRCC_NCKDF_BIT) != 0) {
      _MRCC_CLKCTL &= ~(1uL << _MRCC_NCKDF_BIT);
    }
    Cnt++;
  } while ((_MRCC_RFSR & (1uL << _MRCC_BCOUNT_BIT) == 0) && (Cnt <= _OSC4M_STARTUP_TIMEOUT));
  //
  // Set HCLK prescaler
  //
  Temp  = _MRCC_CLKCTL & _MRCC_HPRESC_RESET_MASK;
  Temp |= (0uL << 3);    // Set HCLK divider to 1 (b4..3 = 0)
  _MRCC_CLKCTL = Temp;
  //
  // Set CKTIM prescaler
  //
  Temp = _MRCC_CLKCTL & _MRCC_PPRESC_RESET_MASK;
  Temp |= (1uL << 0);    // Set CK_TIM divider to 2 (b1..0 = 1)
  _MRCC_CLKCTL = Temp;
  //
  // Set PCLK divider
  //
  Temp  = _MRCC_CLKCTL & _MRCC_PPRESC2_RESET_MASK;
  Temp |= (0uL << 2);    // Set PCLK divider to 1   (b2 = 0)
  _MRCC_CLKCTL = Temp;
  //
  // Set CKSYS and enable PLL
  //
  if ((_MRCC_CLKCTL & ((1uL << _MRCC_NCKDF_BIT) | (1uL << _MRCC_OSC4MOFF_BIT))) == 0)  {  // Check whether Main osc clock is present
    if( ((_MRCC_CLKCTL & (1uL << _MRCC_PLLEN_BIT)) != 0)
        && ((_MRCC_CLKCTL & ~_MRCC_MX_MASK) == PLL_MUL))  {  // If PLL is already setup, select CK_PLL1 as CK_SYS clock source
      _MRCC_CLKCTL &= ~(1uL << _MRCC_CKSEL_BIT);
    } else {
      //
      // If CK_RTC is selected as CK_OSC clock source, switch to Oscillator
      //
      if ((_MRCC_CLKCTL & (1uL << _MRCC_CKOSCSEL_BIT)) != 0) {
        if ((_MRCC_CLKCTL & (1uL << _MRCC_CKSEL_BIT)) != 0)  {
          _MRCC_CLKCTL &= ~(1uL << _MRCC_CKSEL_BIT);
        }
        _WriteCKOSCSELBit(); // Clear CKOSCSEL bit by special CKOSCSEL bit writing sequence
        if ((_MRCC_CLKCTL & (1uL << _MRCC_CKOSCSEL_BIT)) != 0) {  // Check if CKOSCSEL is set to 0
          goto ExitPLLInit;                                       // Error, do not initialize PLL
        }
      }
      _MRCC_CLKCTL |= (1uL << _MRCC_CKSEL_BIT);      // Select CK_OSC as CK_SYS clock source
      _MRCC_CLKCTL &= ~(1uL << _MRCC_PLLEN_BIT);     // Disable PLL
      _MRCC_CLKCTL &= _MRCC_MX_MASK;                 // Configure PLL multiplier, clear MX-bits
      if(PLL_MUL != MRCC_PLL_MUL_16) {               // Set MX[1:0] bits according to PLL_Mul value
        _MRCC_CLKCTL |= PLL_MUL;
      }
      if(OS_XTAL_FREQUENCY == 4000000) {             // 4 MHz external Quartz oscillator used as main oscillator
        _MRCC_CLKCTL &= ~(1uL << _MRCC_XTDIV2_BIT);  // Disable Oscillator Divider by 2
      } else if (OS_XTAL_FREQUENCY == 8000000) {     // 8 MHz external Quartz oscillator used as main oscillator
        _MRCC_CLKCTL |= (1uL << _MRCC_XTDIV2_BIT);   // Enable Oscillator Divider by 2
      }
      //
      // Now Enable PLL and wait until PLL is locked
      //
      _MRCC_CLKCTL |= (1uL << _MRCC_PLLEN_BIT);
      while ((_MRCC_CLKCTL & (1uL << _MRCC_LOCK_BIT)) == 0) {
        /* If OSC4M clock disapear or the PLL is disabled, exit */
        if (((_MRCC_CLKCTL & (1uL << _MRCC_NCKDF_BIT)) != 0) ||
            ((_MRCC_CLKCTL & (1uL << _MRCC_PLLEN_BIT)) == 0)) {
          goto ExitPLLInit;
        }
      }
      _MRCC_CLKCTL &= ~(1uL << _MRCC_CKSEL_BIT);     // Finally Select CK_PLL1 as CK_SYS clock source
    }
  }
  ExitPLLInit:
  //
  // GPIO pins configuration, optimized for 3V3 operation
  //
  _MRCC_PWRCTRL |= (1uL << _MRCC_EN33V_BIT);
  #endif
}

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void _OS_ISR_Tick(void) {
  _OS_TIM_ISR &= ~(1uL << 0);     // Clear OS timer interrupt flag
  OS_HandleTick();                // Call OS tick handler
#if DEBUG
  DCC_Process();
#endif
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
#define _OS_TIMER_PRIO   0x01                  // lowest priority

void OS_InitHW(void) {
  OS_DI();
  //
  // Initialize timer for OS
  //
  _OS_TIM_CR    = 0;                           // Disable timer
  _MRCC_PCLKEN |=  (1uL << _MRCC_TIM_BIT);     // Enable timer clock
  _MRCC_PSWRES &= ~(1uL << _MRCC_TIM_BIT);     // Clear software reset
  _OS_TIM_PSC   = (_OS_TIMER_PRESCALE - 1);    // Init prescaler for timer
  _OS_TIM_SCR   = 0                            // b15..10, b7..b5, b1..b0 always 0
                | (0 << 2)                     // 0: Slave mode disabled
                | (0 << 3)                     // b4..3: Slave mod selection, don't care
                | (0 << 5)                     // b7..b5: Always 0
                | (0 << 8)                     // b9..8: Trigger selection, 0 => internal
                ;
  _OS_TIM_CR    = 0;                           // Disable timer
  _OS_TIM_CR    = 0                            // Setup counting mode
                | (1 << 4)                     // Select Up/Down counting mode. 1 => Down count
                ;

  _OS_TIM_ARR   = _OS_TIMER_INTERVAL;
  _OS_TIM_ISR   = 0;                           // Clear all timer interrupt flags
  _OS_TIM_CR   |= (1uL << 0);                  // Enable timer update interrupt
  _OS_TIM_RSR   = (1uL << 0);                  // Request update interrupt only
  _OS_TIM_RER   = (1uL << 0);                  // Enable update interrupt request
  _OS_TIM_CR   |= (1uL << 2);                  // Enable and start timer

  OS_ARM_InstallISRHandler(_OS_TIMER_ID, &_OS_ISR_Tick); // Timer/counter interrupt vector.
  OS_ARM_ISRSetPrio(_OS_TIMER_ID, _OS_TIMER_PRIO);       // Timer/counter interrupt priority.
  OS_ARM_EnableISR(_OS_TIMER_ID);                        // Enable timer/counter 0 interrupt.
  // optionally initialize UART for OSView
  OS_COM_Init();
  _EIC_ICR |= 0x01; // Enable interrupt controller
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
*       resolution time measurement functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  OS_U32 Time;
  OS_I32 Count;

  Time  = OS_GetTime32() + 1;            // Read current OS time
  Count = _OS_TIM_CNT;                   // Read current timer value
  //
  // If timer Interrupt pending, adjust result
  //
  if ((_OS_TIM_ISR & (1uL << 0)) != 0) {
    Time++;
    Count = _OS_TIM_CNT;                  // Read current timer value
  }
  return (_OS_TIMER_INTERVAL) * Time - Count;
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
  return Cycles/(OS_PCLK_TIMER/1000000);
}

/*********************************************************************
*
*       Communication for OSView via UART (optional)
*
**********************************************************************
*/

#if OS_UART_USED

/*********************************************************************
*
*       OS_COM_ISR_Usart() OS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void _OS_COM_Isr(void) {
  int UartStatus;

  do {
    UartStatus = _OS_UART_MIS;                        // Examine current interrupt status
    if (UartStatus & _RXRDY_FLAG) {                   // Data received?
      OS_U16 Data;
      _OS_UART_ICR &= ~_RXRDY_FLAG;                   // Clear Interrupt pending condition
      Data = _OS_UART_DR;                             // Get current Data
      if ((Data & 0xFF00) == 0) {                     // check error flags
        OS_OnRx(Data);                                // Process actual byte
      } else {
        _OS_UART_RSR = 0;                             // Reset all errors
      }
    }
    if (UartStatus & _TXRDY_FLAG) {                   // Check Tx status => Send next character
      _OS_UART_ICR = _TXRDY_FLAG;                     // Clear Tx Int
      if (OS_OnTx()) {                                // No more characters to send ?
        _OS_UART_IMSC &= ~(1uL << _TX_EMPTY_INT_BIT); // Disable further tx interrupts
      }
    }
  } while (UartStatus & _OS_UART_MIS & (_TXRDY_FLAG | _RXRDY_FLAG));
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  _OS_UART_DR    = c;                           // Send character
  _OS_UART_IMSC |= (1uL << _TX_EMPTY_INT_BIT);  // enable Tx Empty interrupt
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
#define _BAUDDIVIDE ((OS_PCLK_UART+OS_BAUDRATE*8L)/(OS_BAUDRATE*16L))

void OS_COM_Init(void) {
  volatile OS_U32 Dummy;

  OS_DI();
  //
  // Enable peripheral clock for GPIO
  //
  _MRCC_PCLKEN |=  (1uL << _MRCC_GPIO_EN_BIT);
  _MRCC_PSWRES &= ~(1uL << _MRCC_GPIO_EN_BIT);             // Clear software reset

  _MRCC_PSWRES |=  (1uL << _OS_UART_CLK_EN_BIT);           // Reset UART
  _MRCC_PSWRES &= ~(1uL << _OS_UART_CLK_EN_BIT);

  _MRCC_PCLKEN |=  (1uL << _OS_UART_CLK_EN_BIT);           // Enable UART clock

  // Setup Port-Mode for TX pin to alternate function push-pull
  _GPIO0_PC0   |=  (1uL << _OS_UART_TX_PIN);
  _GPIO0_PC1   |=  (1uL << _OS_UART_TX_PIN);
  _GPIO0_PC2   |=  (1uL << _OS_UART_TX_PIN);               // Select output
  // Setup Port-Mode for RX pin to input mode, floating
  _GPIO0_PC0   |=  (1uL << _OS_UART_RX_PIN);
  _GPIO0_PC1   &= ~(1uL << _OS_UART_RX_PIN);
  _GPIO0_PC2   &= ~(1uL << _OS_UART_RX_PIN);

  _OS_UART_CR = 0;              // Initially disable the UART

  // Setup UART mode
  _OS_UART_LCR = (0 << 0)       // Reserved, always 0
               | (0 << 1)       // No parity
               | (0 << 2)       // ODD Parity select (don't care)
               | (0 << 3)       // One stop bit
               | (1 << 4)       // 0: FIFO disabled, initially enable FIFO (!)
               | (3 << 5)       // 8 data bits (0=>5; 1=>5; 2=>7; 3=>8)
               | (0 << 7)       // Stick parity (MARK/SPACE), don't care
               | (0 << 8)       // LIN master mode disabled
               | (0 << 9)       // b12..9: LIN break len, don't care
               ;

  _OS_UART_IBRD = _BAUDDIVIDE;  // Setup baudrate generator, integer part
  // fractions should not be necessary on low baudrates
  _OS_UART_FBRD = 0;  // Setup baudrate generator, fractional part

  _OS_UART_CR  |= (1uL << 8)    // Enable Tx
               |  (1uL << 9)    // Enable Rx
               ;

  _OS_UART_IMSC = 0;            // Disable all UART interrupts
  _OS_UART_ICR  = 0xFFFF;       // Clear all UART interrupts

  _OS_UART_IFLS &= ~(0x3);      // Clear TX FIFO level

  /*  Install embOS UART interrupt handler */
  OS_ARM_InstallISRHandler(_OS_UART_INT_ID, &_OS_COM_Isr); // Install UART interrupt vector.
  OS_ARM_ISRSetPrio(_OS_UART_INT_ID, _OS_UART_PRIO);       // Set UART interrupt priority.
  OS_ARM_EnableISR(_OS_UART_INT_ID);                       // Enable UART interrupt.

  Dummy = _OS_UART_DR;          // Clear Rx data register
  _OS_UART_RSR = 0;             // Reset all errors
  //
  // Enable UART interrupt
  //
  _OS_UART_IMSC = (1uL << _RX_FULL_INT_BIT);  // Enable UART Rx interrupt
  //
  // Flush the FIFO to enable Tx
  //
  _OS_UART_LCR &= ~(1 << 4);    // Disable FIFO
  //
  // Finally enable UART
  //
  _OS_UART_CR |= (1uL << 0);    // Enable UART
  OS_RestoreI();
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
*       _OS_ISR_Undefined
*
*       Is called when an uninstalled interrupt was detected
*       As interrupt pending condition of peripherals has to be reset,
*       program will not continue when interrupt is ignored.
*/
static void _OS_ISR_Undefined(int Index) {
  #if (OS_IGNORE_UNDEFINED_INTERRUPT == 0)
    volatile OS_U32 Dummy;
    Dummy = Index;
    /* You may set a breakpoint here to detect undefined interrupts */
    while (Dummy < (_INT_CHANNEL_MASK + 1)) {
    }
  #endif
}

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
  int ISRIndex;
  ISRIndex = _EIC_IVR;                       // Perform a dummy vector read to update CICR
  ISRIndex = _EIC_CICR & _INT_CHANNEL_MASK;  // Examine current interrupt source (channel number)
  pISR     = _apOS_ISRHandler[ISRIndex];     // Read interrupt vector
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();               // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                       // Inform OS that interrupt handler is running
#endif
  if (pISR != NULL) {
    pISR();                                  // Call installed interrupt service routine
  } else {
    _OS_ISR_Undefined(ISRIndex);
  }
  OS_DI();                                   // Disable interrupts and unlock
  _EIC_IPR |= (1uL << ISRIndex);             // Clear current interrupt pending bit, reset EIC
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();               // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                       // Leave interrupt, perform task switch if required
#endif
}

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*/
OS_ISR_HANDLER* OS_ARM_InstallISRHandler (int ISRIndex, OS_ISR_HANDLER* pISRHandler) {
  OS_ISR_HANDLER*  pOldHandler;

#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return NULL;
  }
#endif
  OS_DI();
  pOldHandler                = _apOS_ISRHandler[ISRIndex];
  _apOS_ISRHandler[ISRIndex] = pISRHandler;
  OS_RestoreI();
  return pOldHandler;
}

/*********************************************************************
*
*       OS_ARM_EnableISR
*/
void OS_ARM_EnableISR(int ISRIndex) {
#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  _EIC_IER |= (1uL << ISRIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*/
void OS_ARM_DisableISR(int ISRIndex) {
#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  _EIC_IER &= ~(1uL << ISRIndex);
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
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return 0;
  }
#endif
  OS_DI();
  pPrio = (OS_U32*)&_EIC_SIR0;
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
*       This function is called during startup and
*       has to return 1 to perform segment initialization
*/
OS_INTERWORK int __low_level_init(void);  /* Avoid "no ptototype" warning */
OS_INTERWORK int __low_level_init(void) {
  _InitPLL();
  return 1;
}

/*****  EOF  ********************************************************/
