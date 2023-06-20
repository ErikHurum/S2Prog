/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************

File        : LH79531.h
Purpose     : Sfrs for Sharp LH79531
              Note: This file does not define all sfrs; only those
              required by embOS or emLoad.
              Feel free to add missing sfrs.
              We only wrote it because SHARP did not supply anything
              like it ... :-(
---------------------------END-OF-HEADER------------------------------
*/

#ifndef LH79531_H    // Avoid multiple inclusion
#define LH79531_H
 
  #ifndef OS_U8
    #define OS_U8 unsigned char
  #endif
  #ifndef OS_U16
    #define OS_U16 unsigned short
  #endif
  #ifndef OS_U32
    #define OS_U32 unsigned int
  #endif

  //  Interrupt masks for interrupt controller
  #define OS_TICK_IRQ_MASK  (1<<6)        // interrupt mask bit for timer
  #define UART_CH0_IRQ_MASK (1<<9)        // interrupt mask for UART channel 0
  #define UART_CH1_IRQ_MASK (1<<10)       // interrupt mask for UART channel 1
  #define UART_CH2_IRQ_MASK (1<<11)       // interrupt mask for UART channel 2


  #define CACHE_CONTROL_REG  *(volatile OS_U32*)0xFFFFAC80
  #define CT0_LOAD           *(volatile OS_U16*)0xFFFF5800
  #define CT0_VALUE          *(volatile OS_U16*)0xFFFF5804
  #define CT0_CONTROL        *(volatile OS_U8*) 0xFFFF5808
  #define CT0_CLEAR          *(volatile OS_U32*)0xFFFF580c
  #define OS_TIMER_IRQ_CLEAR CT0_CLEAR  // Used to clear timer interrupt 
  #define IRQ_STATUS         *(volatile OS_U32*)0xFFFF7400
  #define IRQ_RAW_STATUS     *(volatile OS_U32*)0xFFFF7404
  #define IRQ_ENABLE_SET     *(volatile OS_U32*)0xFFFF7408
  #define IRQ_ENABLE_CLEAR   *(volatile OS_U32*)0xFFFF740c
  #define IRQ_CLEAR          *(volatile OS_U32*)0xFFFF7608
  
  #define UART0DR            *(volatile OS_U8*) 0xFFFF4000
  #define UART0RXSTAT        *(volatile OS_U8*) 0xFFFF4004
  #define UART0MSEQI         *(volatile OS_U8*) 0xFFFF4004
  #define H_UART0BRLCR       *(volatile OS_U8*) 0xFFFF4008
  #define M_UART0BRLCR       *(volatile OS_U8*) 0xFFFF400C
  #define L_UART0BRLCR       *(volatile OS_U8*) 0xFFFF4010
  #define UART0CON           *(volatile OS_U8*) 0xFFFF4014
  #define UART0FLG           *(volatile OS_U8*) 0xFFFF4018
  #define UART0MCR           *(volatile OS_U8*) 0xFFFF401C
  #define UART0INTMSK        *(volatile OS_U8*) 0xFFFF4020
  #define UART0STAT          *(volatile OS_U8*) 0xFFFF4024
  #define UART0INTR          *(volatile OS_U8*) 0xFFFF4028

  #define UART1DR            *(volatile OS_U8*) 0xFFFF4400
  #define UART1RXSTAT        *(volatile OS_U8*) 0xFFFF4404
  #define UART1MSEQI         *(volatile OS_U8*) 0xFFFF4404
  #define H_UART1BRLCR       *(volatile OS_U8*) 0xFFFF4408
  #define M_UART1BRLCR       *(volatile OS_U8*) 0xFFFF440C
  #define L_UART1BRLCR       *(volatile OS_U8*) 0xFFFF4410
  #define UART1CON           *(volatile OS_U8*) 0xFFFF4414
  #define UART1FLG           *(volatile OS_U8*) 0xFFFF4418
  #define UART1MCR           *(volatile OS_U8*) 0xFFFF441C
  #define UART1INTMSK        *(volatile OS_U8*) 0xFFFF4420
  #define UART1STAT          *(volatile OS_U8*) 0xFFFF4424
  #define UART1INTR          *(volatile OS_U8*) 0xFFFF4428
  
  #define UART2DR            *(volatile OS_U8*) 0xFFFF4800
  #define UART2RXSTAT        *(volatile OS_U8*) 0xFFFF4804
  #define UART2MSEQI         *(volatile OS_U8*) 0xFFFF4804
  #define H_UART2BRLCR       *(volatile OS_U8*) 0xFFFF4808
  #define M_UART2BRLCR       *(volatile OS_U8*) 0xFFFF480C
  #define L_UART2BRLCR       *(volatile OS_U8*) 0xFFFF4810
  #define UART2CON           *(volatile OS_U8*) 0xFFFF4814
  #define UART2FLG           *(volatile OS_U8*) 0xFFFF4818
  #define UART2MCR           *(volatile OS_U8*) 0xFFFF481C
  #define UART2INTMSK        *(volatile OS_U8*) 0xFFFF4820
  #define UART2STAT          *(volatile OS_U8*) 0xFFFF4824
  #define UART2INTR          *(volatile OS_U8*) 0xFFFF4828
  
  //  Clock control and PLL settings
  #define PLL_CTL            *(volatile OS_U32*)0xFFFF7C08
  #define PLL_FREQ           *(volatile OS_U32*)0xFFFF7C0C
  #define PLL_PSR            *(volatile OS_U32*)0xFFFF7C10
  #define PLL_WUC            *(volatile OS_U32*)0xFFFF7C20
  
  //  MPU register, Start address
  #define SEG0START          *(volatile OS_U32*)0xFFFFAC00
  #define SEG1START          *(volatile OS_U32*)0xFFFFAC04
  #define SEG2START          *(volatile OS_U32*)0xFFFFAC08
  #define SEG3START          *(volatile OS_U32*)0xFFFFAC0C
  #define SEG4START          *(volatile OS_U32*)0xFFFFAC10
  #define SEG5START          *(volatile OS_U32*)0xFFFFAC14
  #define SEG6START          *(volatile OS_U32*)0xFFFFAC18
  #define SEG7START          *(volatile OS_U32*)0xFFFFAC1C
  //  MPU register, Segment size
  #define SEG0SIZE           *(volatile OS_U32*)0xFFFFAC20
  #define SEG1SIZE           *(volatile OS_U32*)0xFFFFAC24
  #define SEG2SIZE           *(volatile OS_U32*)0xFFFFAC28
  #define SEG3SIZE           *(volatile OS_U32*)0xFFFFAC2C
  #define SEG4SIZE           *(volatile OS_U32*)0xFFFFAC30
  #define SEG5SIZE           *(volatile OS_U32*)0xFFFFAC34
  #define SEG6SIZE           *(volatile OS_U32*)0xFFFFAC38
  #define SEG7SIZE           *(volatile OS_U32*)0xFFFFAC3C
  //  MPU register, Segment configuration
  #define SEG0CFG            *(volatile OS_U32*)0xFFFFAC40
  #define SEG1CFG            *(volatile OS_U32*)0xFFFFAC44
  #define SEG2CFG            *(volatile OS_U32*)0xFFFFAC48
  #define SEG3CFG            *(volatile OS_U32*)0xFFFFAC4C
  #define SEG4CFG            *(volatile OS_U32*)0xFFFFAC50
  #define SEG5CFG            *(volatile OS_U32*)0xFFFFAC54
  #define SEG6CFG            *(volatile OS_U32*)0xFFFFAC58
  #define SEG7CFG            *(volatile OS_U32*)0xFFFFAC5C
  #define SEGDEFCFG          *(volatile OS_U32*)0xFFFFAC60

  //  External BUS Interface (EBI) configuration registers
	//  RAM_SEG_REGx enables CE outputs and defines block size
  #define RAM_SEG_REG0       *(volatile OS_U32*)0xFFFFA400
  #define RAM_SEG_REG1       *(volatile OS_U32*)0xFFFFA404
  #define RAM_SEG_REG2       *(volatile OS_U32*)0xFFFFA408
  #define RAM_SEG_REG3       *(volatile OS_U32*)0xFFFFA40C
  #define RAM_SEG_REG4       *(volatile OS_U32*)0xFFFFA410
  #define RAM_SEG_REG5       *(volatile OS_U32*)0xFFFFA414
  #define RAM_SEG_REG6       *(volatile OS_U32*)0xFFFFA418
  #define RAM_SEG_REG7       *(volatile OS_U32*)0xFFFFA41C
  //  RAM_CTL_REGx defines BUS timing 
  #define RAM_CTL_REG0       *(volatile OS_U32*)0xFFFFA420
  #define RAM_CTL_REG1       *(volatile OS_U32*)0xFFFFA424
  #define RAM_CTL_REG2       *(volatile OS_U32*)0xFFFFA428
  #define RAM_CTL_REG3       *(volatile OS_U32*)0xFFFFA42C
  #define RAM_CTL_REG4       *(volatile OS_U32*)0xFFFFA430
  #define RAM_CTL_REG5       *(volatile OS_U32*)0xFFFFA434
  #define RAM_CTL_REG6       *(volatile OS_U32*)0xFFFFA438
  #define RAM_CTL_REG7       *(volatile OS_U32*)0xFFFFA43C

  // SDRAM interface configuration registers
  #define SDRAM_SEG0_REG     *(volatile OS_U32*)0xFFFFC000
  #define SDRAM_SDR0_REG     *(volatile OS_U32*)0xFFFFC004
  #define SDRAM_SEG1_REG     *(volatile OS_U32*)0xFFFFC008
  #define SDRAM_SDR1_REG     *(volatile OS_U32*)0xFFFFC00C
  #define SDRAM_CNTROL       *(volatile OS_U32*)0xFFFFC010
  #define SDRAM_STATUS       *(volatile OS_U32*)0xFFFFC014
  #define SDRAM_TIMING0      *(volatile OS_U32*)0xFFFFC018
  #define SDRAM_TIMING1      *(volatile OS_U32*)0xFFFFC01C
  #define SDRAM_TIMING2      *(volatile OS_U32*)0xFFFFC020

  // RCP programming registers
  #define ASBBridgeCtrl      *(volatile OS_U32*)0xFFFF782C
#endif
