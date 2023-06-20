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
File    : RTOSINIT_STR912.c   (for ST STR912 CPUs)
Purpose : Initializes and handles the hardware for embOS as far
          as required by embOS.
          Feel free to modify this file acc. to your target system.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.H"
#include "JLINKDCC.h"

/*********************************************************************
*
*       Configuration
*
*********************************************************************/


#define ALLOW_NESTED_INTERRUPTS 0   // Caution: Nesting interrupts will cause higher stack load on system stack CSTACK

/*********************************************************************
*
*       Clock frequency settings
*/
#define OS_FSYS           96000000L // CPU main clock frequnecy
                                    // may depend on PLL

#define OS_XTAL_FREQUENCY 25000000L // Frequnecy of main crystal

#ifndef OS_PCLK_TIMER               /* Peripheral clock for timer   */
  #if (OS_FSYS > 48000000)
    #define OS_PCLK_TIMER OS_FSYS/2 /* APB divider of 2 required    */
  #else
    #define OS_PCLK_TIMER OS_FSYS   /* APB divider not required     */
  #endif
#endif

#ifndef OS_PCLK_UART                /* Peripheral clock for UART    */
  #if (OS_FSYS > 48000000)
    #define OS_PCLK_UART  OS_FSYS/2 /* APB divider of 2 required    */
  #else
    #define OS_PCLK_UART OS_FSYS    /* APB divider not required     */
  #endif
#endif                              /*                              */

#ifndef   OS_INIT_PLL               /* PLL may be initialized       */
  #define OS_INIT_PLL 1             /* during startup               */
#endif

#define _OS_TIMER_PRESCALE 8
#define _OS_TIMER_INTERVAL (OS_PCLK_TIMER / _OS_TIMER_PRESCALE / 1000)

/*********************************************************************
*
*       UART settings for embOSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to embOSView, please define it to be -1
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

/****** Check configuration settings ********************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1) || (OS_UART == 2))
#if ((_OS_TIMER_PRESCALE < 1) || (_OS_TIMER_PRESCALE > 256))
  #error "_OS_TIMER_PRESCALE out of allowed range"
#endif

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** FMI registers                 *******************************/
/****** used unbuffered               *******************************/

#define _FMI_BASE_ADDR      0x54000000
#define _FMI_BBSR      *(volatile OS_U32*)(_FMI_BASE_ADDR + 0x00)
#define _FMI_NBBSR     *(volatile OS_U32*)(_FMI_BASE_ADDR + 0x04)
#define _FMI_BBADR     *(volatile OS_U32*)(_FMI_BASE_ADDR + 0x0C)
#define _FMI_NBBADR    *(volatile OS_U32*)(_FMI_BASE_ADDR + 0x10)
#define _FMI_CR        *(volatile OS_U32*)(_FMI_BASE_ADDR + 0x18)

#define _FMI_READ_WAIT_STATE_1     0x0000    /* One read wait state    */
#define _FMI_READ_WAIT_STATE_2     0x2000    /* Two read wait states   */
#define _FMI_READ_WAIT_STATE_3     0x4000    /* Three read wait states */

/* FMI write wait states */
#define _FMI_WRITE_WAIT_STATE_0    0xFFFFFEFF    /* Zero wait state */
#define _FMI_WRITE_WAIT_STATE_1    0x00000100    /* One wait state  */

/* FMI power down configuration */
#define _FMI_PWD_ENABLE            0x1000    /* FMI Power Down Enable  */
#define _FMI_PWD_DISABLE           0x0000    /* FMI Power Down Disable */

#define _FMI_LVD_ENABLE            0x0000    /* FMI Low Voltage Detector Enable  */
#define _FMI_LVD_DISABLE           0x0800    /* FMI Low Voltage Detector Disable */

/* FMI frequency range */
#define _FMI_FREQ_LOW              0x0000    /* FMI Low bus working frequency   */
#define _FMI_FREQ_HIGH             0x0040    /* FMI High bus working gfrequency */

#define _BANK1_STARTADDR           0x80000   /* FW44 device, 512KB */
//#define _BANK1_STARTADDR           0x40000   /* FW42 device, 256KB */

/****** Peripheral Bus base addresses *******************************/
/****** used unbuffered               *******************************/

#define _APB0_BASE_ADDR     0x58000000
#define _APB1_BASE_ADDR     0x5C000000

/****** UART sfdr definition ****************************************/
/****** UART0 *******************************************************/

#define _UART0_BASE_ADDR   (_APB1_BASE_ADDR + 0x4000)
#define _UART1_BASE_ADDR   (_APB1_BASE_ADDR + 0x5000)
#define _UART2_BASE_ADDR   (_APB1_BASE_ADDR + 0x6000)

/****** Assign UART sfrs used for embOSView communication ***********/

#if OS_UART_USED
  #if   (OS_UART == 0)
    #define _OS_UART_BASE_ADDR     _UART0_BASE_ADDR
    #define _OS_UART_INT_ID   _VIC_IRQ_UART0_ID
    #define _OS_UART_RX_PORT  5
    #define _OS_UART_TX_PORT  3
    #define _OS_UART_RX_PIN   1
    #define _OS_UART_TX_PIN   4
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR     _UART1_BASE_ADDR
    #define _OS_UART_INT_ID   _VIC_IRQ_UART1_ID
    #define _OS_UART_RX_PORT  3
    #define _OS_UART_TX_PORT  3
    #define _OS_UART_RX_PIN   2
    #define _OS_UART_TX_PIN   3
  #elif (OS_UART == 2)
    #define _OS_UART_BASE_ADDR     _UART2_BASE_ADDR
    #define _OS_UART_INT_ID   _VIC_IRQ_UART2_ID
    #define _OS_UART_RX_PORT  3
    #define _OS_UART_TX_PORT  3
    #define _OS_UART_RX_PIN   1
    #define _OS_UART_TX_PIN   5
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

  #define _TX_EMPTY_INT_BIT 5
  #define _RX_FULL_INT_BIT  4
  #define _TXRDY_FLAG       (1 << _TX_EMPTY_INT_BIT)
  #define _RXRDY_FLAG       (1 << _RX_FULL_INT_BIT)
#endif

/****** GPIO register ***********************************************/

#define _GPIO_BASE_ADDR     (_APB0_BASE_ADDR + 0x6000)
#define _GPIO0_BASE_ADDR    (_APB0_BASE_ADDR + 0x6000)
#define _GPIO1_BASE_ADDR    (_APB0_BASE_ADDR + 0x7000)
#define _GPIO2_BASE_ADDR    (_APB0_BASE_ADDR + 0x8000)
#define _GPIO3_BASE_ADDR    (_APB0_BASE_ADDR + 0x9000)
#define _GPIO4_BASE_ADDR    (_APB0_BASE_ADDR + 0xA000)
#define _GPIO5_BASE_ADDR    (_APB0_BASE_ADDR + 0xB000)
#define _GPIO6_BASE_ADDR    (_APB0_BASE_ADDR + 0xC000)
#define _GPIO7_BASE_ADDR    (_APB0_BASE_ADDR + 0xD000)
#define _GPIO8_BASE_ADDR    (_APB0_BASE_ADDR + 0xE000)
#define _GPIO9_BASE_ADDR    (_APB0_BASE_ADDR + 0xF000)

#define _GPIO_DIR_OFFS 0x400
#define _GPIO_SEL_OFFS 0x41C

/****** system, reset clock control unit register *******************/

#define _SCU_BASE_ADDR            (_APB1_BASE_ADDR + 0x2000)

#define _SCU_CLKCNTR         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x00)
#define _SCU_PLLCONF         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x04)
#define _SCU_SYSSTATUS       *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x08)
#define _SCU_PCGR0           *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x14)
#define _SCU_PCGR1           *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x18)
#define _SCU_PRR0            *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x1C)
#define _SCU_PRR1            *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x20)
#define _SCU_SCR0            *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x34)
#define _SCU_SCR1            *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x38)
#define _SCU_SCR2            *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x3C)

#define _SCU_GPIOOUT_BASE_ADDR    (_SCU_BASE_ADDR + 0x44)
#define _SCU_GPIOOUT0        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x44)
#define _SCU_GPIOOUT1        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x48)
#define _SCU_GPIOOUT2        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x4C)
#define _SCU_GPIOOUT3        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x50)
#define _SCU_GPIOOUT4        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x54)
#define _SCU_GPIOOUT5        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x58)
#define _SCU_GPIOOUT6        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x5C)
#define _SCU_GPIOOUT7        *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x60)
#define _SCU_GPIOIN_BASE_ADDR     (_SCU_BASE_ADDR + 0x64)
#define _SCU_GPIOIN0         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x64)
#define _SCU_GPIOIN1         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x68)
#define _SCU_GPIOIN2         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x6C)
#define _SCU_GPIOIN3         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x70)
#define _SCU_GPIOIN4         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x74)
#define _SCU_GPIOIN5         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x78)
#define _SCU_GPIOIN6         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x7C)
#define _SCU_GPIOIN7         *(volatile OS_U32*)(_SCU_BASE_ADDR + 0x80)

#define _SCU_CLKSEL_PLL      (0x00)
#define _SCU_CLKSEL_RTC      (0x01)
#define _SCU_CLKSEL_MAIN     (0x02)

#define _SCU_PLLEN           0x80000
#define _SCU_PCLK_Div1       0xFFFFFE7F
#define _SCU_PCLK_Div2       0x80
#define _SCU_FLAG_LOCK       0x1

#define _SCU_VIC_ENABLE_BIT  5
#define _SCU_TIM0_ENABLE_BIT 0
#define _SCU_TIM1_ENABLE_BIT 0
#define _SCU_TIM2_ENABLE_BIT 1
#define _SCU_TIM3_ENABLE_BIT 1

/****** Timer sfr definition ****************************************/

#define _TIM0_BASE_ADDR     (_APB0_BASE_ADDR + 0x2000)
#define _TIM1_BASE_ADDR     (_APB0_BASE_ADDR + 0x3000)
#define _TIM2_BASE_ADDR     (_APB0_BASE_ADDR + 0x4000)
#define _TIM3_BASE_ADDR     (_APB0_BASE_ADDR + 0x5000)

#define _TIM_ICAR_OFFS 0x00
#define _TIM_ICBR_OFFS 0x04
#define _TIM_OCAR_OFFS 0x08
#define _TIM_OCBR_OFFS 0x0C
#define _TIM_CNTR_OFFS 0x10
#define _TIM_CR1_OFFS  0x14
#define _TIM_CR2_OFFS  0x18
#define _TIM_SR_OFFS   0x1C

#define _TIMER_INT_BIT_NO  14        /* Output compare match flag 1 */

/****** Assign timer sfrs used for embOS timer **********************/
/****** We use timer 1                   ****************************/

#define _OS_TIM_BASE_ADDR   _TIM1_BASE_ADDR
#define _OS_TIM_OCR         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_OCAR_OFFS)
#define _OS_TIM_CR1         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_CR1_OFFS)
#define _OS_TIM_CR2         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_CR2_OFFS)
#define _OS_TIM_CNTR        *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_CNTR_OFFS)
#define _OS_TIM_SR          *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + _TIM_SR_OFFS)

#if   (_OS_TIM_BASE_ADDR == _TIM0_BASE_ADDR)
  #define  _OS_TIMER_INT_ID    _VIC_IRQ_TIM0_ID
  #define  _SCU_TIM_ENABLE_BIT _SCU_TIM0_ENABLE_BIT
  #define  _SCU_TIM_PRESCALE   _SCU_SCR1
#elif (_OS_TIM_BASE_ADDR == _TIM1_BASE_ADDR)
  #define  _OS_TIMER_INT_ID    _VIC_IRQ_TIM1_ID
  #define  _SCU_TIM_ENABLE_BIT _SCU_TIM1_ENABLE_BIT
  #define  _SCU_TIM_PRESCALE   _SCU_SCR1
#elif (_OS_TIM_BASE_ADDR == _TIM2_BASE_ADDR)
  #define  _OS_TIMER_INT_ID    _VIC_IRQ_TIM2_ID
  #define  _SCU_TIM_ENABLE_BIT _SCU_TIM2_ENABLE_BIT
  #define  _SCU_TIM_PRESCALE   _SCU_SCR2
#elif (_OS_TIM_BASE_ADDR == _TIM3_BASE_ADDR)
  #define  _OS_TIMER_INT_ID    _VIC_IRQ_TIM3_ID
  #define  _SCU_TIM_ENABLE_BIT _SCU_TIM3_ENABLE_BIT
  #define  _SCU_TIM_PRESCALE   _SCU_SCR2
#else
  #error "Unsupported assignment of embOS timer"
#endif

/****** Vectored interrupt controller (VIC) *************************/

#define _VIC0_BASE_ADDR  0xFFFFF000
#define _VIC1_BASE_ADDR  0xFC000000

#define _VIC0_IRQ_STATUS           *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0000)
#define _VIC0_FIQ_STATUS           *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0004)
#define _VIC0_RAW_INTR             *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0008)
#define _VIC0_INT_SELECT           *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x000C)
#define _VIC0_INT_ENABLE           *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0010)
#define _VIC0_INT_ENCLEAR          *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0014)
#define _VIC0_SOFT_INT             *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0018)
#define _VIC0_SOFT_INT_CLEAR       *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x001C)
#define _VIC0_PROTECTION           *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0020)
#define _VIC0_CURR_VECTADDR        *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0030)
#define _VIC0_DEF_VECTADDR         *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0034)
#define _VIC0_VECT_BASE_ADDR       *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0100)
#define _VIC0_VECT_CNTL_BASE_ADDR  *(volatile OS_U32*)(_VIC0_BASE_ADDR + 0x0200)

#define _VIC1_IRQ_STATUS           *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0000)
#define _VIC1_FIQ_STATUS           *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0004)
#define _VIC1_RAW_INTR             *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0008)
#define _VIC1_INT_SELECT           *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x000C)
#define _VIC1_INT_ENABLE           *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0010)
#define _VIC1_INT_ENCLEAR          *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0014)
#define _VIC1_SOFT_INT             *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0018)
#define _VIC1_SOFT_INT_CLEAR       *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x001C)
#define _VIC1_PROTECTION           *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0020)
#define _VIC1_CURR_VECTADDR        *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0030)
#define _VIC1_DEF_VECTADDR         *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0034)
#define _VIC1_VECT_BASE_ADDR       *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0100)
#define _VIC1_VECT_CNTL_BASE_ADDR  *(volatile OS_U32*)(_VIC1_BASE_ADDR + 0x0200)

/****** Vectored interrupt controller sources ************************/

#define _VIC_IRQ_WD_ID      0  // IRQ0  Watchdog
#define _VIC_IRQ_SWI_ID     1  // IRQ1  Software interrupt
#define _VIC_IRQ_CPU_RX_ID  2  // IRQ2  Debug receive command
#define _VIC_IRQ_CPU_TX_ID  3  // IRQ3  Debug transmit command
#define _VIC_IRQ_TIM0_ID    4  // IRQ4  Timer 0
#define _VIC_IRQ_TIM1_ID    5  // IRQ4  Timer 0
#define _VIC_IRQ_TIM2_ID    6  // IRQ4  Timer 0
#define _VIC_IRQ_TIM3_ID    7  // IRQ4  Timer 0
#define _VIC_IRQ_USBH_ID    8  // IRQ8  USB high priority
#define _VIC_IRQ_USBL_ID    9  // IRQ9  USB low priority
#define _VIC_IRQ_SCU_ID    10  // IRQ10 SCU
#define _VIC_IRQ_MAC_ID    11  // IRQ11 MAC
#define _VIC_IRQ_DMA_ID    12  // IRQ12 DMA
#define _VIC_IRQ_CAN_ID    13  // IRQ13 CAN
#define _VIC_IRQ_IMC_ID    14  // IRQ14 Induction motor control
#define _VIC_IRQ_ADC_ID    15  // IRQ15 A/D converter
#define _VIC_IRQ_UART0_ID  16  // IRQ16 UART0
#define _VIC_IRQ_UART1_ID  17  // IRQ17 UART1
#define _VIC_IRQ_UART2_ID  18  // IRQ18 UART2
#define _VIC_IRQ_I2C0_ID   19  // IRQ19 I2C channel 0
#define _VIC_IRQ_I2C1_ID   20  // IRQ20 I2C channel 1
#define _VIC_IRQ_SSP0_ID   21  // IRQ21 SSP channel 0
#define _VIC_IRQ_SSP1_ID   22  // IRQ22 SSP channel 1
#define _VIC_IRQ_SCUB_ID   23  // IRQ23 SCU brown out
#define _VIC_IRQ_RTC_ID    24  // IRQ24 SCU brown out
#define _VIC_IRQ_WIUA_ID   25  // IRQ25 WIU all
#define _VIC_IRQ_WIU0_ID   26  // IRQ26 WIU group 0
#define _VIC_IRQ_WIU1_ID   27  // IRQ27 WIU group 1
#define _VIC_IRQ_WIU2_ID   28  // IRQ28 WIU group 2
#define _VIC_IRQ_WIU3_ID   29  // IRQ29 WIU group 3
#define _VIC_IRQ_USBW_ID   30  // IRQ30 USB wake up
#define _VIC_IRQ_PFQ_ID    31  // IRQ31 Prefetch queue and branch

#ifndef   NUM_INT_SOURCES
  #define NUM_INT_SOURCES  32
#endif

#ifndef   NUM_INT_VECTORS
  #define NUM_INT_VECTORS  32
#endif

#ifndef   NUM_VECTORS_PER_VIC
  #define NUM_VECTORS_PER_VIC  16
#endif

#ifndef   NUM_INTS_PER_VIC
  #define NUM_INTS_PER_VIC  16
#endif

#define _INT_SOURCE_MASK  0x0F

#define _INT_PRIORITY_MASK 0x0F

#define _OS_TIMER_VECT_INDEX      15  // lowest priority, allowed range 0..15, Timer ints are connected to VIC0
#define _OS_UART_VECT_INDEX       31  // lowest priority, allowed range 16..31, UART ints are connected to VIC1

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
*       _InitVICs()
*
* Function description
*   Clears and disables all interrut vectors in VIC.
*   CPU interrupt has to be disabled before calling this function.
*/
static void _InitVICs(void) {
  int Index;

  _SCU_PRR0          &= ~(1 << _SCU_VIC_ENABLE_BIT); // reset VIC
  _SCU_PCGR0         |= (1 << _SCU_VIC_ENABLE_BIT);  // Enable clock to VIC
  _SCU_PRR0          |= (1 << _SCU_VIC_ENABLE_BIT);  // Cancel reset state of VIC

  _VIC0_INT_ENCLEAR   = 0xFFFFFFFF;        // Disable all source interrupts
  _VIC1_INT_ENCLEAR   = 0xFFFFFFFF;        // Disable all source interrupts
  for (Index = 0; Index < NUM_INT_VECTORS; Index++) {
    OS_ARM_DisableISR(Index);              // Disable channel
    OS_ARM_AssignISRSource(Index, 0);      // Assign to hardware channel 0
    OS_ARM_InstallISRHandler(Index, NULL); // Set vector to 0;
  }
  _VIC0_SOFT_INT_CLEAR  = 0xFFFFFFFF;      // Disable all soft interrupts
  _VIC0_INT_SELECT      = 0;               // Set all channels to generate IRQ
  _VIC0_DEF_VECTADDR    = 0;               // Set default vector to 0
  _VIC1_SOFT_INT_CLEAR  = 0xFFFFFFFF;      // Disable all soft interrupts
  _VIC1_INT_SELECT      = 0;               // Set all channels to generate IRQ
  _VIC1_DEF_VECTADDR    = 0;               // Set default vector to 0
}

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void _OS_ISR_Tick(void) {
  _OS_TIM_SR  &= ~(1 << _TIMER_INT_BIT_NO);  // Clear embOS timer interrupt flag
  _OS_TIM_OCR += _OS_TIMER_INTERVAL;         // advance to next count;
  OS_HandleTick();                           // Call embOS tick handler
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
*       Initialize the hardware (timer) required for embOS to run.
*       May be modified, if an other timer should be used
*/
void OS_InitHW(void) {
  OS_DI();
  _InitVICs();                              // Initialize VICs, clear and disable all interrupts
  // Initialize timer for embOS
  _SCU_PCGR1 |= (1 << _SCU_TIM_ENABLE_BIT); // Enable clock to timer module
  _SCU_PRR1  |= (1 << _SCU_TIM_ENABLE_BIT); // Cancel reset state of timer module

  _OS_TIM_CR1 = 0;                          // Stop timer, reset mode
  _OS_TIM_CR2 = 0;                          // Disable all interrupts, clear prescaler
  _OS_TIM_OCR = _OS_TIMER_INTERVAL;         // Setup compare register, initially use 1000 ticks per second
  _OS_TIM_CR2 = (1 << 14) | (_OS_TIMER_PRESCALE - 1);   // Enable output capture interrupt A, set selected prescaler
  _OS_TIM_CNTR = 0;
  _OS_TIM_CR1 = (1 << 15);                  // Start timer
  // Setup interrupt controller
  OS_ARM_InstallISRHandler(_OS_TIMER_VECT_INDEX, &_OS_ISR_Tick); // Timer/counter interrupt vector.
  OS_ARM_AssignISRSource(_OS_TIMER_VECT_INDEX, _OS_TIMER_INT_ID);
  OS_ARM_EnableISR(_OS_TIMER_VECT_INDEX);                        // Enable timer/counter interrupt.
  OS_ARM_EnableISRSource(_OS_TIMER_INT_ID);                      // Enable timer/counter interrupt.
  // Initialize UART for embOSView
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
*       This routine is required for task-info via embOSView or high
*       resolution time maesurement functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  OS_U32 time;
  OS_I16 count;

  time  = _OS_TIM_CNTR;
  count = _OS_TIM_OCR - time;    // Read current timer value
  time  = OS_GetTime32();        // Read current embOS time
  if (count < 0) {               // Timer Interrupt pending ?
    time++;                      // Adjust result, read timer again
    count = 0 - count;
  } else {
    count = _OS_TIMER_INTERVAL - count;
  }
  return (_OS_TIMER_INTERVAL) * time + count;
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
  return Cycles/(OS_PCLK_TIMER/_OS_TIMER_PRESCALE/1000000);
}

/*********************************************************************
*
*       Communication for embOSView via UART (optional)
*
**********************************************************************
*/

#if OS_UART_USED

/*********************************************************************
*
*       OS_COM_Isr() embOS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void _OS_COM_Isr(void) {
  int UartStatus;

  do {
    UartStatus = _OS_UART_MIS;                      // Examine current interrupt status
    if (UartStatus & _RXRDY_FLAG) {                 // Data received?
      OS_U16 Data;
      _OS_UART_ICR &= ~_RXRDY_FLAG;                 // Clear Interrupt pending condition
      Data = _OS_UART_DR;                           // Get current Data
      if ((Data & 0xFF00) == 0) {                   // check error flags
        OS_OnRx(Data);                              // Process actual byte
      } else {
      }
    }
    if (UartStatus & _TXRDY_FLAG) {                 // Check Tx status => Send next character
      _OS_UART_ICR = _TXRDY_FLAG;                   // Clear Tx Int
      if (OS_OnTx()) {                              // No more characters to send ?
        _OS_UART_IMSC &= ~(1 << _TX_EMPTY_INT_BIT); // Disable further tx interrupts
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
  _OS_UART_DR    = c;                         // Send character
  _OS_UART_IMSC |= (1 << _TX_EMPTY_INT_BIT);  // enable Tx Empty interrupt
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for embOSView
*/
#define _BAUDDIVIDE ((OS_PCLK_UART+OS_BAUDRATE*8L)/(OS_BAUDRATE*16L))

void OS_COM_Init(void) {
  volatile int Dummy;
  OS_U32* pSfr;

  OS_DI();

  // Setup GPIOIN to alternate function for Rx
  pSfr   = (OS_U32*)(_SCU_GPIOIN_BASE_ADDR + (_OS_UART_RX_PORT * 4));
  *pSfr |= (1 << _OS_UART_RX_PIN);
  // Setup GPIOOUT to alternate function for Tx
  pSfr   = (OS_U32*)(_SCU_GPIOOUT_BASE_ADDR + (_OS_UART_TX_PORT * 4));
  *pSfr  = (*pSfr & ~(3 << (_OS_UART_TX_PIN * 2))) | (3 << (_OS_UART_TX_PIN * 2));
  // Setup GPIO port for Tx to output mode
  pSfr   = (OS_U32*)(_GPIO_BASE_ADDR + (0x1000 * _OS_UART_TX_PORT) + _GPIO_DIR_OFFS);
  *pSfr |= (1 << _OS_UART_TX_PIN);
  // Enable peripheral clock and clear reset condition for selected UART
  if (OS_UART == 0) {
    _SCU_PCGR1 |= (1 << 3);  // Enable Clock
    _SCU_PRR1  |= (1 << 3);  // Clear reset condition
  } else if (OS_UART == 1) {
    _SCU_PCGR1 |= (1 << 4);
    _SCU_PRR1  |= (1 << 4);
  } else if (OS_UART == 2) {
    _SCU_PCGR1 |= (1 << 5);
    _SCU_PRR1  |= (1 << 5);
  } else {
    return;  // error, unsupported UART
  }
  //
  // Initially disable UART
  //
  _OS_UART_CR =  (0 << 0)       // Disable UART
               | (0 << 2)       // IrDa low power, don't care
               | (0 << 7)       // Loopback disabled
               | (0 << 8)       // Transmit disabled
               | (0 << 9)       // Receive disabled
               | (0 << 10)      // DTR, not used
               | (0 << 11)      // RTS, not used
               | (0 << 14)      // RTS handshake disabled
               | (0 << 15)      // CTS handshake disabled
               ;

  _OS_UART_IMSC = 0;            // Disable all UART interrupts
  _OS_UART_ICR  = 0xFFFF;       // Clear all UART interrupts

  _OS_UART_IBRD = _BAUDDIVIDE;  // Setup baudrate generator, integer part
  // fractions should not be necessary on low baudrates
  _OS_UART_FBRD = 0;  // Setup baudrate generator, fractional part

  _OS_UART_LCR = (0 << 0)       // Normal mode, don't send break
               | (0 << 1)       // No parity
               | (0 << 2)       // ODD Parity select (don't care)
               | (0 << 3)       // One stop bit
               | (0 << 4)       // FIFO disabled
               | (3 << 5)       // 8 data bits (0=>5; 1=>5; 2=>7; 3=>8)
               | (0 << 7)       // Stick parity (MARK/SPACE), don't care
               ;
  /*  Install embOS UART interrupt handler */
  OS_ARM_InstallISRHandler(_OS_UART_VECT_INDEX, &_OS_COM_Isr);  // Set UART interrupt vector.
  OS_ARM_AssignISRSource(_OS_UART_VECT_INDEX, _OS_UART_INT_ID);
  OS_ARM_EnableISR(_OS_UART_VECT_INDEX);                        // Enable UART interrupt vector.
  OS_ARM_EnableISRSource(_OS_UART_INT_ID);                      // Enable UART interrupt.

  Dummy = _OS_UART_DR;          // Clear Rx data register
  _OS_UART_RSR = 0;             // Reset all errors
  //
  // Finally enable UART and UART Rx interrupt
  //
  _OS_UART_CR =  (1 << 0)       // Enable UART
               | (0 << 2)       // IrDa low power, don't care
               | (0 << 7)       // Loopback disabled
               | (1 << 8)       // Transmit enabled
               | (1 << 9)       // Receive disabled
               | (0 << 10)      // DTR, not used
               | (0 << 11)      // RTS, not used
               | (0 << 14)      // RTS handshake disabled
               | (0 << 15)      // CTS handshake disabled
               ;

  _OS_UART_IMSC = (1 << _RX_FULL_INT_BIT);  // Enable UART Rx interrupt
  OS_RestoreI();
}

#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let embOS know that Tx is not busy
}
#endif /*  OS_UART_USED  */

/****** Final check of configuration ********************************/
#ifndef OS_UART_USED
  #error "OS_UART_USED has to be defined"
#endif

/*********************************************************************
*
*       embOS interrupt handler and ISR specific functions
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
  #if (OS_IGNORE_UNDEFINED_INTERRUPT == 0)
    volatile int Dummy;

    Dummy = 1;
    /* You may set a breakpoint here to detect undefined interrupts */
    while (Dummy > 0) {
    }
  #endif
}

/*********************************************************************
*
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq_handler is called from embOS OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
OS_INTERWORK void OS_irq_handler(void) {
  OS_ISR_HANDLER* pISR;
  OS_ISR_HANDLER* pISR1;

  pISR  = (OS_ISR_HANDLER*) _VIC0_CURR_VECTADDR; // Get current interrupt handler
  pISR1 = (OS_ISR_HANDLER*) _VIC1_CURR_VECTADDR; // Get current interrupt handler of VIC1
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();                   // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                           // Inform OS that interrupt handler is running
#endif
  if (pISR != NULL) {
    pISR();
  } else {
    if (pISR1 != NULL) {
      pISR1();
    } else {
      _OS_ISR_Undefined();
    }
  }
  OS_DI();                                       // Disable interrupts and unlock
  _VIC0_CURR_VECTADDR = (OS_U32) pISR;           // Clear current interrupt pending condition, reset VIC
  _VIC1_CURR_VECTADDR = (OS_U32) pISR1;          // Clear current interrupt pending condition, reset VIC
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();                   // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                           // Leave interrupt, perform task switch if required
#endif
}

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*/
OS_ISR_HANDLER* OS_ARM_InstallISRHandler (int ISRIndex, OS_ISR_HANDLER* pISRHandler) {
  OS_ISR_HANDLER*  pOldHandler;
  OS_ISR_HANDLER** papISR;

#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return NULL;
  }
#endif
  OS_DI();
  if (ISRIndex < NUM_VECTORS_PER_VIC) {
    papISR = (OS_ISR_HANDLER**) &_VIC0_VECT_BASE_ADDR;
  } else {
    ISRIndex -= NUM_VECTORS_PER_VIC;
    papISR = (OS_ISR_HANDLER**) &_VIC1_VECT_BASE_ADDR;
  }
  pOldHandler          = *(papISR + ISRIndex);
  *(papISR + ISRIndex) = pISRHandler;
  OS_RestoreI();
  return pOldHandler;
}

/*********************************************************************
*
*       OS_ARM_AssignISRSource
*/
void OS_ARM_AssignISRSource(int ISRIndex, int Source) {
  OS_U32* pCntlRegister;
  OS_U32 ControlReg;

#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  if (ISRIndex < NUM_VECTORS_PER_VIC) {
    pCntlRegister = (OS_U32*) &_VIC0_VECT_CNTL_BASE_ADDR;
  } else {
    ISRIndex -= NUM_VECTORS_PER_VIC;
    pCntlRegister = (OS_U32*) &_VIC1_VECT_CNTL_BASE_ADDR;
  }
  OS_DI();
  ControlReg  = *(pCntlRegister + ISRIndex) & ~_INT_SOURCE_MASK;
  *(pCntlRegister + ISRIndex) = (ControlReg | (Source & _INT_SOURCE_MASK));
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_EnableISR
*/
void OS_ARM_EnableISR(int ISRIndex) {
  OS_U32* pCntlRegister;

#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return ;
  }
#endif
  if (ISRIndex < NUM_VECTORS_PER_VIC) {
    pCntlRegister = (OS_U32*) &_VIC0_VECT_CNTL_BASE_ADDR;
  } else {
    ISRIndex -= NUM_VECTORS_PER_VIC;
    pCntlRegister = (OS_U32*) &_VIC1_VECT_CNTL_BASE_ADDR;
  }
  OS_DI();
  *(pCntlRegister + ISRIndex) |= (1 << 5);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*/
void OS_ARM_DisableISR(int ISRIndex) {
  OS_U32* pCntlRegister;

#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  if (ISRIndex < NUM_VECTORS_PER_VIC) {
    pCntlRegister = (OS_U32*) &_VIC0_VECT_CNTL_BASE_ADDR;
  } else {
    ISRIndex -= NUM_VECTORS_PER_VIC;
    pCntlRegister = (OS_U32*) &_VIC1_VECT_CNTL_BASE_ADDR;
  }
  OS_DI();
  *(pCntlRegister + ISRIndex) &= ~(1 << 5);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_EnableISRSource
*/
void OS_ARM_EnableISRSource(int SourceIndex) {
#if DEBUG
  if ((unsigned)SourceIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  if (SourceIndex < NUM_INTS_PER_VIC) {
    _VIC0_INT_ENABLE |= (1 << SourceIndex);
  } else {
    SourceIndex -= NUM_INTS_PER_VIC;
    _VIC1_INT_ENABLE |= (1 << SourceIndex);
  }
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISRSource
*/
void OS_ARM_DisableISRSource(int SourceIndex) {
#if DEBUG
  if ((unsigned)SourceIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  if (SourceIndex < NUM_INTS_PER_VIC) {
    _VIC0_INT_ENCLEAR = (1 << SourceIndex);
  } else {
    SourceIndex -= NUM_INTS_PER_VIC;
    _VIC1_INT_ENCLEAR = (1 << SourceIndex);
  }
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  // Not supported for CPU with VIC
  return 0;
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
#pragma diag_suppress=Pe940 // IAR specific: No warning for missing return
OS_U32 GetPC(void);
OS_U32 GetPC(void) {
  __asm("mov r0, pc");
}

OS_INTERWORK int __low_level_init(void);  /* Avoid "no ptototype" warning */
OS_INTERWORK int __low_level_init(void) {
  OS_U32 CLKCNTR_Value;
  int i;
  //
  // Check if vector jump table is programmed at 0x0 for RAM targets
  //
  if ((GetPC() & 0x04000000) && ((*(OS_U32*) 0x18 != 0xE59FF010) || (*(OS_U32*) 0x30 != 0x04000018))) {
    while(1) {  // Fatal error! Vector jump table not programmed at 0x0. See ReadMe.txt for more info.
    }
  }
  //
  // Initialize Clock source and PLL
  //
  CLKCNTR_Value  = _SCU_CLKCNTR;      // Get the current Clock control value
  CLKCNTR_Value &= ~0x3;              // Clear field MCLKSEL
  CLKCNTR_Value |= _SCU_CLKSEL_MAIN;  // Select Main oscillator as source
  _SCU_CLKCNTR   = CLKCNTR_Value;     // Update CLKCNTR register value
  //
  // Write a write flash configuration register command and configure Flash configuration
  //
  *(volatile unsigned short *)(_FMI_NBBADR << 2)  = 0x60;
  *(volatile unsigned short *)((_FMI_NBBADR << 2) | _FMI_READ_WAIT_STATE_2 | _FMI_PWD_ENABLE | _FMI_LVD_ENABLE | _FMI_FREQ_HIGH) = 0x03;
  //
  // Set the PCLK Clock to MCLK/2, because peripheral clock is limited to 48 MHz
  //
  _SCU_CLKCNTR &= _SCU_PCLK_Div1;    // Clear APBDIV[1:0] field
  _SCU_CLKCNTR |= _SCU_PCLK_Div2;    // Update field with PCLK Divisor
  //
  // Setup PLL config registers
  //
  #if   (OS_FSYS == 48000000)
    #define _PLL_P 3
  #elif (OS_FSYS == 96000000)
    #define _PLL_P 2
  #else
    #error "Unsupported PLL frequency, please modify PLL init function"
  #endif
  #define _PLL_N (0x18 * 8)
  #define _PLL_M (OS_XTAL_FREQUENCY / 1000000)

  if(_SCU_CLKCNTR & 0x3) {              // Check if PLL not already selected as clock
    for(i = 10 ;i > 0; i--);            // Add a short delay before disabling PLL
    _SCU_PLLCONF &= ~_SCU_PLLEN;        // Disable PLL
    _SCU_PLLCONF =0;                    // Clear PLLCONF register
    _SCU_PLLCONF |= (_PLL_N << 8);      // Update PLLN field
    _SCU_PLLCONF |= _PLL_M;             // Update PLLM field
    _SCU_PLLCONF |= (_PLL_P << 16);     // Update PLLP field
  }
  //
  // Enable PLL if not already enabled
  //
  if (((_SCU_PLLCONF & _SCU_PLLEN) && (_SCU_SYSSTATUS & _SCU_FLAG_LOCK)) == 0) {
    _SCU_SYSSTATUS |= _SCU_FLAG_LOCK;              // Clear LOCK bit
    _SCU_PLLCONF   |= _SCU_PLLEN;                  // Enable PLL
    while((_SCU_SYSSTATUS & _SCU_FLAG_LOCK) == 0); // Wait until PLL locks
  }
  //
  // Select PLL as clock source
  //
  CLKCNTR_Value  = _SCU_CLKCNTR;         // Get current CLKCNTR register value
  CLKCNTR_Value &= ~0x3;                 // Clear MCLKSEL
  //
  // Check if PLL is enabled & locked
  //
  if (((_SCU_PLLCONF & _SCU_PLLEN) && (_SCU_SYSSTATUS & _SCU_FLAG_LOCK))) {
    CLKCNTR_Value |= _SCU_CLKSEL_PLL; // Switch to PLL as clock source
    _SCU_CLKCNTR   = CLKCNTR_Value;   // Update CLKCNTR register
  }
  //
  // Finally return 1 to force initialization of segments
  //
  return 1;
}

/*****  EOF  ********************************************************/
