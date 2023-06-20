/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2008  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.18 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf.h
Purpose     : SEGGER internal standard configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*            Selection of Hardware
*
**********************************************************************
*/
#if defined (__TID__)
  #if (((__TID__ >>8) &0x7f) == 85)          /* IAR V850 */
    #define TARGET_AXEL_BOARD
  #endif
#elif  defined (__ghs__) && defined (__V850)
  #define TARGET_AXEL_BOARD
#endif

#if defined __WATCOMC__
  #ifndef __386__
    #define TARGET_EMBEDDED_PC
  #endif
#endif

/*********************************************************************
*
*       Softune default
*
**********************************************************************
*/
#ifdef __COMPILER_FCC911__	
  #define LCD_XSIZE      (640)   /* X-resolution of LCD, Logical coor. */
  #define LCD_YSIZE      (480)   /* Y-resolution of LCD, Logical coor. */

  #define LCD_BITSPERPIXEL (8)

  #define LCD_CONTROLLER 8720

/*********************************************************************
*
*            AVR default configuration (Slin driver)
*
**********************************************************************
*/

#elif defined (__ICCAVR__)
  #define LCD_XSIZE       240   /* X-resolution of LCD, Logical coor. */
  #define LCD_YSIZE       128   /* Y-resolution of LCD, Logical coor. */
  #define LCD_BITSPERPIXEL  1
  #define LCD_CONTROLLER 6901
  #define LCD_CACHE         0
  #define LCD_INIT_CONTROLLER()
  #define LCD_READ_A0() LCD_X_Read_A0()
  #define LCD_READ_A1() LCD_X_Read_A1()
  #define LCD_WRITE_A0(Data)
  #define LCD_WRITE_A1(Data)
  #define LCD_WAIT()
  #define LCD_EXTENDED_WAIT 0

  unsigned char LCD_X_Read_A0(void);
  unsigned char LCD_X_Read_A1(void);

/*********************************************************************
*
*            X86 - Embedded PC default configuration
*
**********************************************************************
*/
#elif defined (TARGET_EMBEDDED_PC)
  #define LCD_XSIZE            640   /* X-resolution of LCD, Logical coor. */
  #define LCD_YSIZE            480   /* Y-resolution of LCD, Logical coor. */
  #define LCD_BITSPERPIXEL      16
  #define LCD_CONTROLLER      8600
  #define LCD_SWAP_BYTE_ORDER    0
  #define LCD_SWAP_RB            1
  #define LCD_SWAP_XY            0
  #define LCD_MIRROR_X           0
  #define LCD_INIT_CONTROLLER()

/*********************************************************************
*
*            ARM default configuration (COGENT EP7312)
*
**********************************************************************
*/
#elif defined (TARGET_EP7312)
  #define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
  #define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */
  #define LCD_BITSPERPIXEL (12)
  #define LCD_CONTROLLER  444
  #define LCD_FIXEDPALETTE 44412
  #define LCD_SWAP_BYTE_ORDER (1)
  #define LCD_READ_MEM(Off)            *((U16*)         (0xc0000000+(((U32)(Off))<<1)))
  #define LCD_WRITE_MEM(Off,data)      *((U16*)         (0xc0000000+(((U32)(Off))<<1)))=data
  #define  LCD_INIT_CONTROLLER()

/*********************************************************************
*
*            ARM default configuration (WALMART AT91)
*
**********************************************************************
*/
#elif defined (TARGET_AT91)
  #define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
  #define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */
  #define LCD_BITSPERPIXEL (8)
  #define LCD_CONTROLLER 1375
  #define LCD_SWAP_BYTE_ORDER (0)

  #define LCD_READ_MEM(Off)            *((U16*)         (0x6000000+(((U32)(Off))<<1)))
  #define LCD_WRITE_MEM(Off,data)      *((U16*)         (0x6000000+(((U32)(Off))<<1)))=data
  #define LCD_READ_REG(Off)            *((volatile U16*)(0x601ffe0+(((U16)(Off))<<1)))
  #define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0x601ffe0+(((U16)(Off))<<1)))=data

/*********************************************************************
*
*                   Define contents of registers
*/

#define LCD_REG0  (0)                                          /* Product code */

#define LCD_REG1  (0x23)                                       /* Mode reg 0.    0 for 4 bit mono LCD */            \
                                                               /*                1 for 8 bit mono LCD */            \
                                                               /*             0x23 for 8 bit color LCD */           \
                 |(1<<2)                                       /*             Mask FPSHIFT during h.non-display */

#define LCD_REG2 ((3<<6)                                       /* Mode reg 1: Bits per pixel 0:1, 1:2, 2:4, 3:8 */  \
                 |(1<<5)                                       /* High performance bit for accel. of CPU access */  \
                 |(1<<4)                                       /* Input clock divide */                             \
                 |(0<<3)                                       /* Display blank */                                  \
                 |(0<<2)                                       /* Frame repeat */                                   \
                 |(0<<1)                                       /* HW video invert enable */                         \
                 |(0<<0))                                      /* SW video invert */

#define LCD_REG3                                               /* Mode reg 2. 0 for 4 bit mono LCD */               \
                  (0<<7)                                       /* LUT bypass */                                     \
                 |(0<<3)                                       /* LCDPWR override */                                \
                 |(0<<2)                                       /* hw power save enable */                           \
                 |(3<<0)                                       /* Software power save :3 = normal operation */

#define LCD_REG4 (LCD_XSIZE/8-1)                               /* horizontal panel size*/
#define LCD_REG5 ((LCD_YSIZE-1)&255)                           /* Vert. panel size, lsb */
#define LCD_REG6 ((LCD_YSIZE-1)>>8)                            /* Vert. panel size, msb */
#define LCD_REG7 (0)                                           /* FPLine start position (TFT only) */
#define LCD_REG8 (31)                                          /* H.non display period   (0 usually O.K.)*/
#define LCD_REG9 (0)                                           /* FPFrame start pos.    (TFT only) */
#define LCD_REGA (0)                                           /* v.non display period  */
#define LCD_REGB (0)                                           /* mod rate register     0: every frame */
#define LCD_REGC (0)                                           /* Screen 1 start lsb    */
#define LCD_REGD (0)                                           /* Screen 1 start msb    */

#define LCD_REG12 (LCD_BITSPERPIXEL*(LCD_VXSIZE-LCD_XSIZE)/16) /* Memory Address offset (usually 0) */
#define LCD_REG13 LCD_REG5                                     /* Vert. screen 1 size, lsb */
#define LCD_REG14 LCD_REG6                                     /* Vert. screen 1 size, msb */

#define LCD_REG18 (0x1)                                        /* GPIO0: output  */
#define LCD_REG19 (0x1)                                        /* GPIO0: 1: enable display  */
#define LCD_REG1B (0)                                          /* No swivel mode  (use 0xc0 for alt.swivel)  */
#define LCD_REG1C (0x78)                                       /* bytes per line (stride, for swivel mode only)  */

/*********************************************************************
*
*                   Init sequence for 16 bit access
*/

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0)<<8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1)<<8) | (d0))
#endif

#define LCD_INIT_CONTROLLER()                                                                    \
        LCD_WRITE_REGLH(0x00>>1,LCD_REG0, LCD_REG1);                                             \
        LCD_WRITE_REGLH(0x02>>1,LCD_REG2, LCD_REG3);                                             \
        LCD_WRITE_REGLH(0x04>>1,LCD_REG4, LCD_REG5);                                             \
        LCD_WRITE_REGLH(0x06>>1,LCD_REG6, LCD_REG7);                                             \
        LCD_WRITE_REGLH(0x08>>1,LCD_REG8, LCD_REG9);                                             \
        LCD_WRITE_REGLH(0x0a>>1,LCD_REGA, LCD_REGB);                                             \
        LCD_WRITE_REGLH(0x0c>>1,LCD_REGC, LCD_REGD);                                             \
        LCD_WRITE_REG  (0x0e>>1,0x00);                 /* 0, screen 2 start l*/                  \
        LCD_WRITE_REG  (0x10>>1,0x00);                 /* screen 2 start h */                    \
        LCD_WRITE_REGLH(0x12>>1,LCD_REG12, LCD_REG13); /* mem adr. offset, screen 1 vsize(lsb)*/ \
        LCD_WRITE_REGLH(0x14>>1,LCD_REG14, 0);                                                   \
        LCD_WRITE_REGLH(0x18>>1,LCD_REG18, LCD_REG19);                                                   \
        LCD_WRITE_REGLH(0x1a>>1,0, LCD_REG1B);                                                   \
        LCD_WRITE_REGLH(0x1c>>1,LCD_REG1C, 0)

/*********************************************************************
*
*            ARM default configuration (Phytec AT91)
*
**********************************************************************
*/
#elif defined (TARGET_AT91_PHYTEC)
  #define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
  #define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */
  #define LCD_BITSPERPIXEL (8)
  #define LCD_CONTROLLER 1375
  #define LCD_SWAP_BYTE_ORDER (1)

  #define LCD_READ_MEM(Off)            *((U16*)         (0x6040000+(((U32)(Off))<<1)))
  #define LCD_WRITE_MEM(Off,data)      *((U16*)         (0x6040000+(((U32)(Off))<<1)))=data
  #define LCD_READ_REG(Off)            *((volatile U16*)(0x605ffe0+(((U16)(Off))<<1)))
  #define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0x605ffe0+(((U16)(Off))<<1)))=data

/*********************************************************************
*
*                   Define contents of registers
*/

#define LCD_REG0  (0)                                          /* Product code */

#define LCD_REG1  (0x23)                                       /* Mode reg 0.    0 for 4 bit mono LCD */            \
                                                               /*                1 for 8 bit mono LCD */            \
                                                               /*             0x23 for 8 bit color LCD */           \
                 |(1<<2)                                       /*             Mask FPSHIFT during h.non-display */

#define LCD_REG2 ((3<<6)                                       /* Mode reg 1: Bits per pixel 0:1, 1:2, 2:4, 3:8 */  \
                 |(1<<5)                                       /* High performance bit for accel. of CPU access */  \
                 |(1<<4)                                       /* Input clock divide */                             \
                 |(0<<3)                                       /* Display blank */                                  \
                 |(0<<2)                                       /* Frame repeat */                                   \
                 |(0<<1)                                       /* HW video invert enable */                         \
                 |(0<<0))                                      /* SW video invert */

#define LCD_REG3                                               /* Mode reg 2. 0 for 4 bit mono LCD */               \
                  (0<<7)                                       /* LUT bypass */                                     \
                 |(0<<3)                                       /* LCDPWR override */                                \
                 |(0<<2)                                       /* hw power save enable */                           \
                 |(3<<0)                                       /* Software power save :3 = normal operation */

#define LCD_REG4 (LCD_XSIZE/8-1)                               /* horizontal panel size*/
#define LCD_REG5 ((LCD_YSIZE-1)&255)                           /* Vert. panel size, lsb */
#define LCD_REG6 ((LCD_YSIZE-1)>>8)                            /* Vert. panel size, msb */
#define LCD_REG7 (0)                                           /* FPLine start position (TFT only) */
#define LCD_REG8 (31)                                          /* H.non display period   (0 usually O.K.)*/
#define LCD_REG9 (0)                                           /* FPFrame start pos.    (TFT only) */
#define LCD_REGA (0)                                           /* v.non display period  */
#define LCD_REGB (0)                                           /* mod rate register     0: every frame */
#define LCD_REGC (0)                                           /* Screen 1 start lsb    */
#define LCD_REGD (0)                                           /* Screen 1 start msb    */

#define LCD_REG12 (LCD_BITSPERPIXEL*(LCD_VXSIZE-LCD_XSIZE)/16) /* Memory Address offset (usually 0) */
#define LCD_REG13 LCD_REG5                                     /* Vert. screen 1 size, lsb */
#define LCD_REG14 LCD_REG6                                     /* Vert. screen 1 size, msb */

#define LCD_REG18 (0x1)                                        /* GPIO0: output  */
#define LCD_REG19 (0x1)                                        /* GPIO0: 1: enable display  */
#define LCD_REG1B (0)                                          /* No swivel mode  (use 0xc0 for alt.swivel)  */
#define LCD_REG1C (0x78)                                       /* bytes per line (stride, for swivel mode only)  */

/*********************************************************************
*
*                   Init sequence for 16 bit access
*/

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0)<<8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1)<<8) | (d0))
#endif

#define LCD_INIT_CONTROLLER()                                                                    \
        LCD_WRITE_REGLH(0x00>>1,LCD_REG0, LCD_REG1);                                             \
        LCD_WRITE_REGLH(0x02>>1,LCD_REG2, LCD_REG3);                                             \
        LCD_WRITE_REGLH(0x04>>1,LCD_REG4, LCD_REG5);                                             \
        LCD_WRITE_REGLH(0x06>>1,LCD_REG6, LCD_REG7);                                             \
        LCD_WRITE_REGLH(0x08>>1,LCD_REG8, LCD_REG9);                                             \
        LCD_WRITE_REGLH(0x0a>>1,LCD_REGA, LCD_REGB);                                             \
        LCD_WRITE_REGLH(0x0c>>1,LCD_REGC, LCD_REGD);                                             \
        LCD_WRITE_REG  (0x0e>>1,0x00);                 /* 0, screen 2 start l*/                  \
        LCD_WRITE_REG  (0x10>>1,0x00);                 /* screen 2 start h */                    \
        LCD_WRITE_REGLH(0x12>>1,LCD_REG12, LCD_REG13); /* mem adr. offset, screen 1 vsize(lsb)*/ \
        LCD_WRITE_REGLH(0x14>>1,LCD_REG14, 0);                                                   \
        LCD_WRITE_REGLH(0x18>>1,LCD_REG18, LCD_REG19);                                                   \
        LCD_WRITE_REGLH(0x1a>>1,0, LCD_REG1B);                                                   \
        LCD_WRITE_REGLH(0x1c>>1,LCD_REG1C, 0)

/*********************************************************************
*
*       ARM : Sharp LH79520, Logic PD board, QVGA display
*
**********************************************************************
*/

#elif defined TARGET_LH79520_QVGA

#define LCD_MEMBASE 0x21F6A000

#define LCD_BITSPERPIXEL   16
#define LCD_CONTROLLER   3200
#define LCD_XSIZE         240
#define LCD_YSIZE         320

#define LCD_SWAP_BYTE_ORDER (1)
#define LCD_SWAP_RB (0)
#define LCD_FIXEDPALETTE  555
#define LCD_ENDIAN_BIG 0
#define LCD_VRAM_ADR  LCD_MEMBASE

/* RESET, CLOCK AND POWER CONTROLLER */
#define __RCPCBASE  0xFFFE2000
#define __PERIPHCLKCTRL     *(volatile U32*)(__RCPCBASE + 0x0024)
#define __PERIPHCLKCTRL2    *(volatile U32*)(__RCPCBASE + 0x0028)
#define __PERPIHCLKSELECT	  *(volatile U32*)(__RCPCBASE + 0x0030)
#define __PERIPHCLKSELECT2	*(volatile U32*)(__RCPCBASE + 0x0034)
#define __LCDCLKPRESCALE	  *(volatile U32*)(__RCPCBASE + 0x0040)

/* COLOR LCD CONTROLLER */
#define __CLCDCBASE  0xFFFF4000
#define __LCDTIMING0    *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1    *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2    *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDUPBASE     *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	    *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL    *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	    *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT  *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE   *(volatile U32*)(__CLCDCBASE + 0x0200)
/* CLCDCBASE + 0x200 - 0x3FC LCDPALETTE 256 × 16-bit Color Palette */

/* HR-TFT LCD TIMING CONTROLLER */
#define __HRTFTCBASE  0xFFFE4000
#define __HRTFTCSETUP   *(volatile U32*)(__HRTFTCBASE + 0x0000)
#define __HRTFTCCONTROL *(volatile U32*)(__HRTFTCBASE + 0x0004)
#define __HRTFTCTIMING1 *(volatile U32*)(__HRTFTCBASE + 0x0008)
#define __HRTFTCTIMING2 *(volatile U32*)(__HRTFTCBASE + 0x000C)

/* INPUT/OUTPUT CONTROL */
#define __IOCONBASE  0xFFFE5000
#define __MEMMUX  *(volatile U32*)(__IOCONBASE + 0x0000)
#define __LCDMUX  *(volatile U32*)(__IOCONBASE + 0x0004)


#define LCD_INIT_CONTROLLER()                                             \
        __PERIPHCLKCTRL2       = (0 << 0);             /* enable clock for LCD Controller */ \
        __PERIPHCLKSELECT2     = (0 << 0);             /* select HCLK as Clock for LCD Controller */ \
        __LCDCLKPRESCALE       =  1;                   /* LCD clock prescaler /2 */ \
        __LCDMUX               = (0 << 0)              /* Configure pin 142 as LCDREV (HR-TFT panels) */ \
                               | (1 << 1)              /* Configure pin 142 as LCDREV (HR-TFT panels) */ \
                               | (1 << 2)              /* Configure pin 141 as LCDVD13 */ \
                               | (1 << 3)              /* Configure pin 140 as LCDVD14 */ \
                               | (1 << 4)              /* Configure pin 139 as LCDVD15 */ \
                               | (0 << 5)              /* Configure pin 139 as LCDVD15 */ \
                               | (0 << 6)              /* Configure pin 137 as LCDSPL (HR-TFT panels) */ \
                               | (1 << 7)              /* Configure pin 137 as LCDSPL (HR-TFT panels) */ \
                               | (0 << 8)              /* Configure pin 135 as LCDCLS (HR-TFT panels) */ \
                               | (1 << 9)              /* Configure pin 135 as LCDCLS (HR-TFT panels) */ \
                               | (0 << 10)             /* Configure pin 134 as LCDCLKIN */ \
                               | (1 << 11)             /* Configure pin 133 as LCDCLK   */ \
                               | (1 << 12)             /* Configure pin 132 as LCDVD16  */ \
                               | (0 << 13)             /* Configure pin 131 as LCDLP (HR-TFT panels) */ \
                               | (1 << 14)             /* Configure pin 131 as LCDLP (HR-TFT panels) */ \
                               | (1 << 15)             /* Configure pin 130 as LCDVD17 */ \
                               | (0 << 16)             /* Configure pin 129 as LCDSPS (HR-TFT panels) */ \
                               | (1 << 17)             /* Configure pin 129 as LCDSPS (HR-TFT panels) */ \
                               | (1 << 18)             /* Configure pin 124 as LCDVD2 */ \
                               | (1 << 19)             /* Configure pin 123 as LCDVD3 */ \
                               | (1 << 20)             /* Configure pin 122 as LCDVD4 */ \
                               | (1 << 21)             /* Configure pin 121 as LCDVD5 */ \
                               | (0 << 22)             /* Configure pin 119 as LCDPS (HR-TFT panels) */ \
                               | (1 << 23)             /* Configure pin 119 as LCDPS (HR-TFT panels) */ \
                               | (1 << 24)             /* Configure pin 118 as LCDVD7 */ \
                               | (1 << 25)             /* Configure pin 117 as LCDVD8 */ \
                               | (1 << 26)             /* Configure pin 116 as LCDVD9 */ \
                               | (1 << 27)             /* Configure pin 115 as LCDVD10 */ \
                               | (1 << 28);            /* Configure pin 114 as LCDVD11 */ \
        __LCDTIMING0           = (0x14 << 24)          /* Horizontal back  porch */ \
                               | (0x14 << 16)          /* Horizontal front porch */ \
                               | (0x3c <<  8)             /* Horizontal synchronization pulse Width */ \
                               | ((LCD_XSIZE / 16 -1) << 2); /* Pixels-Per-Line */ \
        __LCDTIMING1           = (0x07 << 24)             /* Vertical back  porch */ \
                               | (0x05 << 16)             /* Vertical front porch */ \
                               | (0    << 10)             /* Vertical synchronization Pulse Width. */ \
                               | (LCD_YSIZE - 1);         /* Lines-Per-Panel */ \
        __LCDTIMING2           = (0    << 26)             /* Bypass pixel Clock Divider */ \
                               | ((LCD_XSIZE - 1)<< 16)   /* Clocks per line */ \
                               | (0    << 14)             /* Invert Output Enable */ \
                               | (1    << 13)             /* Invert Panel Clock */ \
                               | (1    << 12)             /* Invert Horizontal Synchronization */ \
                               | (0    << 11)             /* Invert the Vertical Synchronization signal */ \
                               | (0    <<  6)             /* AC Bias signal (LCDENAB) frequency */ \
                               | (0    <<  0);            /* Panel Clock Divisor.*/ \
        __LCDUPBASE            = LCD_MEMBASE;              /* LCD Upper Panel Base address */ \
        __LCDINTRENABLE        = 0;                       /* Disable LCD interrupts */ \
        __LCDCONTROL           = (0 << 16)                /* LCD DMA FIFO Watermark level */ \
                               | (0 << 12)                /* LCD Vertical Compare */ \
                               | (1 << 11)                /* LCD Power Enable */ \
                               | (0 << 10)                /* Big-Endian Pixel Ordering within a byte */ \
                               | (0 <<  9)                /* Big-Endian Byte Ordering to the LCD */ \
                               | (0 <<  8)                /* RGB or BGR format selection:           \
                                                             1 = BGR red and blue swapped           \
                                                             0 = RGB normal output*/ \
                               | (0 <<  7)                /* RLCD is a Dual panel STN */           \
                               | (0 <<  6)                /* LCD 8bit Mono (8bit interface)*/           \
                               | (1 <<  5)                /* LCD is a TFT */           \
                               | (0 <<  4)                /* LCD is STN mono */           \
                               | (4 <<  1)                /* LCD bpp 4 = 16bpp \
                                                                     3 =  8bpp \
                                                                     2 =  4bpp \
                                                                     1 =  2bpp */ \
                               | (1 <<  0);                /* 0 =  Enable LCD Controller */  \
        __HRTFTCSETUP          = ((LCD_XSIZE - 1 ) << 4)   /* Number of pixels per line */   \
                               | (6 << 1)                  /* Conversion mode select (HF-TFT panels) */ \
                               | (1 << 0);                 /* Conversion mode select (HF-TFT panels) */ \
        __HRTFTCTIMING1        = (8    << 8)               /* Delay in LCDDCLK periods from the 1st LOW \
                                                              in the LCDLP signal, to the leading edge \
                                                              of the LCDPS and LCD-CLS signals */   \
                               | (7    << 4)               /* Polarity-Reversal delay */ \
                               | (12   << 0);              /* Delay in LCDDCLK periods from the 1st LOW \
                                                              in the LCDLP signal, to the leading edge  \
                                                              of the LCDLP signal */ \
        __HRTFTCTIMING2        = (0x53 << 9)               /* Delay in LCDDCLK periods of the LCD-SPL \
                                                              signal during vertical front and back porches. */   \
                               | (0xd0 << 0);              /* Delay in LCDDCLK periods from the first \
                                                              rising edge of the LCDSPL signal to the \
                                                              trailing edge of the LCDCLS signal */   \
        __HRTFTCCONTROL        = (1 << 1)                  /* LCDCLS enable  */   \
                               | (1 << 0);                 /* LCDSPS enable */

#define LCD_ON()
#define LCD_OFF()


/*********************************************************************
*
*       ARM : Sharp LH79520, Logic PD board, VGA display
*
**********************************************************************
*/
#elif defined TARGET_LH79520_VGA

#define LCD_MEMBASE 0x21F6A000
#define LCD_BITSPERPIXEL   16
#define LCD_CONTROLLER   3200
#define LCD_XSIZE         640
#define LCD_YSIZE         480

#define LCD_SWAP_BYTE_ORDER (1)
#define LCD_SWAP_RB (0)
#define LCD_ENDIAN_BIG 0
#define LCD_VRAM_ADR  LCD_MEMBASE

/* RESET, CLOCK AND POWER CONTROLLER */
#define __RCPCBASE  0xFFFE2000
#define __PERIPHCLKCTRL     *(volatile U32*)(__RCPCBASE + 0x0024)
#define __PERIPHCLKCTRL2    *(volatile U32*)(__RCPCBASE + 0x0028)
#define __PERPIHCLKSELECT	  *(volatile U32*)(__RCPCBASE + 0x0030)
#define __PERIPHCLKSELECT2	*(volatile U32*)(__RCPCBASE + 0x0034)
#define __LCDCLKPRESCALE	  *(volatile U32*)(__RCPCBASE + 0x0040)

/* COLOR LCD CONTROLLER */
#define __CLCDCBASE  0xFFFF4000
#define __LCDTIMING0    *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1    *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2    *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDUPBASE     *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	    *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL    *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	    *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT  *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE   *(volatile U32*)(__CLCDCBASE + 0x0200)
/* CLCDCBASE + 0x200 - 0x3FC LCDPALETTE 256 × 16-bit Color Palette */

/* HR-TFT LCD TIMING CONTROLLER */
#define __HRTFTCBASE  0xFFFE4000
#define __HRTFTCSETUP   *(volatile U32*)(__HRTFTCBASE + 0x0000)
#define __HRTFTCCONTROL *(volatile U32*)(__HRTFTCBASE + 0x0004)
#define __HRTFTCTIMING1 *(volatile U32*)(__HRTFTCBASE + 0x0008)
#define __HRTFTCTIMING2 *(volatile U32*)(__HRTFTCBASE + 0x000C)

/* INPUT/OUTPUT CONTROL */
#define __IOCONBASE  0xFFFE5000
#define __MEMMUX  *(volatile U32*)(__IOCONBASE + 0x0000)
#define __LCDMUX  *(volatile U32*)(__IOCONBASE + 0x0004)

#if   (LCD_BITSPERPIXEL == 8)

#define LCDBPP              3
#define LCD_SET_LUT_ENTRY(Pos, Color)                             \
  volatile U32 * pPalette;                                        \
  U32 Index;                                                      \
  pPalette = (volatile U32 *)(__CLCDCBASE + 0x0200) + (Pos >> 1); \
  Index    = LCD_Color2Index_555(Color);                          \
  if (Pos & 1) {                                                  \
    *pPalette &= 0x0000FFFF;                                      \
    *pPalette |= Index << 16;                                     \
  } else {                                                        \
    *pPalette &= 0xFFFF0000;                                      \
    *pPalette |= Index;                                           \
  }

#elif (LCD_BITSPERPIXEL == 16)

#define LCDBPP              4
#define LCD_FIXEDPALETTE  555

#endif

#define LCD_INIT_CONTROLLER()                    \
        __PERIPHCLKCTRL2       = (0 << 0);             /* enable clock for LCD Controller */ \
        __PERIPHCLKSELECT2     = (0 << 0);             /* select HCLK as Clock for LCD Controller */ \
        __LCDCLKPRESCALE       =  1;                   /* LCD clock prescaler /2 */ \
        __LCDMUX               = (1 << 0)              /* Configure pin 142 as LCDREV (HR-TFT panels) */ \
                               | (0 << 1)              /* Configure pin 142 as LCDREV (HR-TFT panels) */ \
                               | (1 << 2)              /* Configure pin 141 as LCDVD13 */ \
                               | (1 << 3)              /* Configure pin 140 as LCDVD14 */ \
                               | (1 << 4)              /* Configure pin 139 as LCDVD15 */ \
                               | (0 << 5)              /* Configure pin 139 as LCDVD15 */ \
                               | (1 << 6)              /* Configure pin 137 as LCDSPL (HR-TFT panels) */ \
                               | (0 << 7)              /* Configure pin 137 as LCDSPL (HR-TFT panels) */ \
                               | (1 << 8)              /* Configure pin 135 as LCDCLS (HR-TFT panels) */ \
                               | (0 << 9)              /* Configure pin 135 as LCDCLS (HR-TFT panels) */ \
                               | (0 << 10)             /* Configure pin 134 as LCDCLKIN */ \
                               | (1 << 11)             /* Configure pin 133 as LCDCLK   */ \
                               | (1 << 12)             /* Configure pin 132 as LCDVD16  */ \
                               | (1 << 13)             /* Configure pin 131 as LCDLP (HR-TFT panels) */ \
                               | (0 << 14)             /* Configure pin 131 as LCDLP (HR-TFT panels) */ \
                               | (1 << 15)             /* Configure pin 130 as LCDVD17 */ \
                               | (1 << 16)             /* Configure pin 129 as LCDSPS (HR-TFT panels) */ \
                               | (0 << 17)             /* Configure pin 129 as LCDSPS (HR-TFT panels) */ \
                               | (1 << 18)             /* Configure pin 124 as LCDVD2 */ \
                               | (1 << 19)             /* Configure pin 123 as LCDVD3 */ \
                               | (1 << 20)             /* Configure pin 122 as LCDVD4 */ \
                               | (1 << 21)             /* Configure pin 121 as LCDVD5 */ \
                               | (1 << 22)             /* Configure pin 119 as LCDPS (HR-TFT panels) */ \
                               | (0 << 23)             /* Configure pin 119 as LCDPS (HR-TFT panels) */ \
                               | (1 << 24)             /* Configure pin 118 as LCDVD7 */ \
                               | (1 << 25)             /* Configure pin 117 as LCDVD8 */ \
                               | (1 << 26)             /* Configure pin 116 as LCDVD9 */ \
                               | (1 << 27)             /* Configure pin 115 as LCDVD10 */ \
                               | (1 << 28);            /* Configure pin 114 as LCDVD11 */ \
        __LCDTIMING0           = (0x60 << 24)          /* Horizontal back  porch */ \
                               | (0x32 << 16)          /* Horizontal front porch */ \
                               | (0x0F <<  8)             /* Horizontal synchronization pulse Width */ \
                               | ((LCD_XSIZE / 16 -1) << 2); /* Pixels-Per-Line */ \
        __LCDTIMING1           = (0x1d << 24)             /* Vertical back  porch */ \
                               | (0x04 << 16)             /* Vertical front porch */ \
                               | (7    << 10)             /* Vertical synchronization Pulse Width. */ \
                               | (LCD_YSIZE - 1);         /* Lines-Per-Panel */ \
        __LCDTIMING2           = (1    << 26)             /* Bypass pixel Clock Divider */ \
                               | ((LCD_XSIZE - 1)<< 16)   /* Clocks per line */ \
                               | (0    << 14)             /* Invert Output Enable */ \
                               | (0    << 13)             /* Invert Panel Clock */ \
                               | (1    << 12)             /* Invert Horizontal Synchronization */ \
                               | (1    << 11)             /* Invert the Vertical Synchronization signal */ \
                               | (0    <<  6)             /* AC Bias signal (LCDENAB) frequency */ \
                               | (0    <<  0);            /* Panel Clock Divisor.*/ \
        __LCDUPBASE            = LCD_MEMBASE;              /* LCD Upper Panel Base address */ \
        __LCDINTRENABLE        = 0;                       /* Disable LCD interrupts */ \
        __LCDCONTROL           = (1 << 16)                /* LCD DMA FIFO Watermark level */ \
                               | (0 << 12)                /* LCD Vertical Compare */ \
                               | (1 << 11)                /* LCD Power Enable */ \
                               | (0 << 10)                /* Big-Endian Pixel Ordering within a byte */ \
                               | (0 <<  9)                /* Big-Endian Byte Ordering to the LCD */ \
                               | (0 <<  8)                /* RGB or BGR format selection:           \
                                                             1 = BGR red and blue swapped           \
                                                             0 = RGB normal output*/ \
                               | (0 <<  7)                /* RLCD is a Dual panel STN */           \
                               | (0 <<  6)                /* LCD 8bit Mono (8bit interface)*/           \
                               | (1 <<  5)                /* LCD is a TFT */           \
                               | (0 <<  4)                /* LCD is STN mono */           \
                               | (LCDBPP <<  1)           /* LCD bpp 4 = 16bpp \
                                                                     3 =  8bpp \
                                                                     2 =  4bpp \
                                                                     1 =  2bpp */ \
                               | (1 <<  0);                /* 0 =  Enable LCD Controller */ \
        __HRTFTCSETUP          = 0x7f0

#define LCD_ON()
#define LCD_OFF()

/*********************************************************************
*
*       ARM : Sharp LH79524, Logic PD board, QVGA display
*
**********************************************************************
*/
#elif defined TARGET_LH79524_QVGA

/*********************************************************************
*
*       General configuration
*
**********************************************************************
*/
#define LCD_VRAM_ADR         0x2006A000
#define LCD_BITSPERPIXEL   16
#define LCD_CONTROLLER   3200
#define LCD_XSIZE         240
#define LCD_YSIZE         320
#define LCD_ENDIAN_BIG      0
#define LCD_FIXEDPALETTE  555

/*********************************************************************
*
*       SFR register definitions
*
**********************************************************************
*/
/* RESET, CLOCK AND POWER CONTROLLER */
#define __RCPCBASE  0xFFFE2000
#define __PERIPHCLKCTRL1    *(volatile U32*)(__RCPCBASE + 0x0028)
#define __AHBCLKCTRL        *(volatile U32*)(__RCPCBASE + 0x002C)
#define __LCDCLKPRESCALE	  *(volatile U32*)(__RCPCBASE + 0x0040)

/* COLOR LCD CONTROLLER */
#define __CLCDCBASE  0xFFFF4000
#define __LCDTIMING0        *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1        *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2        *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDUPBASE         *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	        *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE     *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL        *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	        *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT      *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE       *(volatile U32*)(__CLCDCBASE + 0x0200)

/* HR-TFT LCD TIMING CONTROLLER */
#define __HRTFTCBASE  0xFFFE4000
#define __HRTFTCSETUP       *(volatile U32*)(__HRTFTCBASE + 0x0000)
#define __HRTFTCCONTROL     *(volatile U32*)(__HRTFTCBASE + 0x0004)
#define __HRTFTCTIMING1     *(volatile U32*)(__HRTFTCBASE + 0x0008)
#define __HRTFTCTIMING2     *(volatile U32*)(__HRTFTCBASE + 0x000C)

/* INPUT/OUTPUT CONTROL */
#define __IOCONBASE  0xFFFE5000
#define __MUXCTL1             *(volatile U32*)(__IOCONBASE + 0x0000)
#define __MUXCTL19            *(volatile U32*)(__IOCONBASE + 0x0090)
#define __MUXCTL20            *(volatile U32*)(__IOCONBASE + 0x0098)
#define __MUXCTL21            *(volatile U32*)(__IOCONBASE + 0x00A0)
#define __MUXCTL22            *(volatile U32*)(__IOCONBASE + 0x00A8)

/*********************************************************************
*
*       Initialization macro
*
**********************************************************************
*/
#define LCD_INIT_CONTROLLER()                                                                         \
  __AHBCLKCTRL       = 0; \
  __PERIPHCLKCTRL1   &= ~(1   << 0);                /* Enable clock for LCD Controller */             \
  __LCDCLKPRESCALE   =   1;                         /* LCD clock prescaler /2 */                      \
  __MUXCTL1          |= (1    <<  2)                /* PL1 = LCDVDD15 */                            \
                     |  (1    <<  0);               /* PL0 = LCDVDD14 */                            \
  __MUXCTL19         |= (2    << 12)                /* PE6 = LCDMOD */                            \
                     |  (1    <<  8)                /* PE5 = LCDVDDEN */                            \
                     |  (2    <<  4)                /* PE4 = LCDREV */                            \
                     |  (1    <<  2);               /* PE3 = LCDCLS */                            \
  __MUXCTL20         |= (1    << 10)                /* PE1 = LCDDCLK */                            \
                     |  (2    <<  6)                /* PE0 = LCDHRLP */                            \
                     |  (2    <<  2)                /* PF7 = LCDSPS */                            \
                     |  (2    <<  0);               /* PF6 = LCDSPL */                            \
  __MUXCTL21         |= (1    << 10)                /* PF5 = LCDVDD11 */                            \
                     |  (1    <<  8)                /* PL3 = LCDVDD13 */                            \
                     |  (1    <<  6)                /* PF4 = LCDVDD10 */                            \
                     |  (1    <<  4)                /* PL2 = LCDVDD12 */                            \
                     |  (1    <<  2)                /* PF3 = LCDVDD9 */                            \
                     |  (1    <<  0);               /* PF2 = LCDVDD8 */                            \
  __MUXCTL22         |= (1    << 14)                /* PF1 = LCDVDD7 */                            \
                     |  (1    << 12)                /* PF0 = LCDVDD6 */                            \
                     |  (1    << 10)                /* PG7 = LCDVDD5 */                            \
                     |  (1    <<  8)                /* PG6 = LCDVDD4 */                            \
                     |  (1    <<  6)                /* PG5 = LCDVDD3 */                            \
                     |  (1    <<  4)                /* PG4 = LCDVDD2 */                            \
                     |  (1    <<  2)                /* PG3 = LCDVDD1 */                            \
                     |  (1    <<  0);               /* PG2 = LCDVDD0 */                            \
  __LCDTIMING0       = (0x14 << 24)                 /* Horizontal back  porch */                      \
                     | (0x14 << 16)                 /* Horizontal front porch */                      \
                     | (0x3c <<  8)                 /* Horizontal synchronization pulse Width */      \
                     | ((LCD_XSIZE / 16 -1) << 2);  /* Pixels-Per-Line */                             \
  __LCDTIMING1       = (0x07 << 24)                 /* Vertical back  porch */                        \
                     | (0x05 << 16)                 /* Vertical front porch */                        \
                     | (0    << 10)                 /* Vertical synchronization Pulse Width. */       \
                     | (LCD_YSIZE - 1);             /* Lines-Per-Panel */                             \
  __LCDTIMING2       = (0    << 26)                 /* Bypass pixel Clock Divider */                  \
                     | ((LCD_XSIZE - 1)<< 16)       /* Clocks per line */                             \
                     | (0    << 14)                 /* Invert Output Enable */                        \
                     | (1    << 13)                 /* Invert Panel Clock */                          \
                     | (1    << 12)                 /* Invert Horizontal Synchronization */           \
                     | (0    << 11)                 /* Invert the Vertical Synchronization signal */  \
                     | (0    <<  6)                 /* AC Bias signal (LCDENAB) frequency */          \
                     | (0    <<  0);                /* Panel Clock Divisor.*/                         \
  __LCDUPBASE        = LCD_VRAM_ADR;                /* LCD Upper Panel Base address */                \
  __LCDINTRENABLE    = 0;                           /* Disable LCD interrupts */                      \
  __LCDCONTROL       = (0    << 16)                 /* LCD DMA FIFO Watermark level */                \
                     | (0    << 12)                 /* LCD Vertical Compare */                        \
                     | (1    << 11)                 /* LCD Power Enable */                            \
                     | (0    << 10)                 /* Big-Endian Pixel Ordering within a byte */     \
                     | (0    <<  9)                 /* Big-Endian Byte Ordering to the LCD */         \
                     | (0    <<  8)                 /* RGB or BGR format selection:                   \
                                                       1 = BGR red and blue swapped                   \
                                                       0 = RGB normal output*/                        \
                     | (0    <<  7)                 /* RLCD is a Dual panel STN */                    \
                     | (0    <<  6)                 /* LCD 8bit Mono (8bit interface)*/               \
                     | (1    <<  5)                 /* LCD is a TFT */                                \
                     | (0    <<  4)                 /* LCD is STN mono */                             \
                     | (4    <<  1)                 /* LCD bpp 4 = 16bpp                              \
                                                               3 =  8bpp                              \
                                                               2 =  4bpp                              \
                                                               1 =  2bpp */                           \
                     | (1    <<  0);                /* 0 =  Enable LCD Controller */                  \
  __HRTFTCSETUP      = ((LCD_XSIZE - 1 ) << 4)      /* Number of pixels per line */                   \
                     | (6    << 1)                  /* Conversion mode select (HF-TFT panels) */      \
                     | (1    << 0);                 /* Conversion mode select (HF-TFT panels) */      \
  __HRTFTCTIMING1    = (8    << 8)                  /* Delay in LCDDCLK periods from the 1st LOW      \
                                                       in the LCDLP signal, to the leading edge       \
                                                       of the LCDPS and LCD-CLS signals */            \
                     | (7    << 4)                  /* Polarity-Reversal delay */                     \
                     | (12   << 0);                 /* Delay in LCDDCLK periods from the 1st LOW      \
                                                       in the LCDLP signal, to the leading edge       \
                                                       of the LCDLP signal */                         \
  __HRTFTCTIMING2    = (0x53 << 9)                  /* Delay in LCDDCLK periods of the LCD-SPL signal \
                                                       during vertical front and back porches. */     \
                     | (0xd0 << 0);                 /* Delay in LCDDCLK periods from the first        \
                                                       rising edge of the LCDSPL signal to the        \
                                                       trailing edge of the LCDCLS signal */          \
  __HRTFTCCONTROL    = (1    << 1)                  /* LCDCLS enable  */                              \
                     | (1    << 0);                 /* LCDSPS enable */

#define LCD_ON()
#define LCD_OFF()

/*********************************************************************
*
*       ARM : Sharp LH79524, Logic PD board, VGA display
*
**********************************************************************
*/
#elif defined TARGET_LH79524_VGA

/*********************************************************************
*
*       General configuration
*
**********************************************************************
*/
#define LCD_VRAM_ADR         0x2006A000
#define LCD_BITSPERPIXEL   16
#define LCD_CONTROLLER   3200
#define LCD_XSIZE         640
#define LCD_YSIZE         480
#define LCD_ENDIAN_BIG      0
#define LCD_FIXEDPALETTE  555

/*********************************************************************
*
*       SFR register definitions
*
**********************************************************************
*/
/* RESET, CLOCK AND POWER CONTROLLER */
#define __RCPCBASE  0xFFFE2000
#define __PERIPHCLKCTRL1    *(volatile U32*)(__RCPCBASE + 0x0028)
#define __AHBCLKCTRL        *(volatile U32*)(__RCPCBASE + 0x002C)
#define __LCDCLKPRESCALE	  *(volatile U32*)(__RCPCBASE + 0x0040)

/* COLOR LCD CONTROLLER */
#define __CLCDCBASE  0xFFFF4000
#define __LCDTIMING0        *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1        *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2        *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDUPBASE         *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	        *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE     *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL        *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	        *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT      *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE       *(volatile U32*)(__CLCDCBASE + 0x0200)

/* HR-TFT LCD TIMING CONTROLLER */
#define __HRTFTCBASE  0xFFFE4000
#define __HRTFTCSETUP       *(volatile U32*)(__HRTFTCBASE + 0x0000)
#define __HRTFTCCONTROL     *(volatile U32*)(__HRTFTCBASE + 0x0004)
#define __HRTFTCTIMING1     *(volatile U32*)(__HRTFTCBASE + 0x0008)
#define __HRTFTCTIMING2     *(volatile U32*)(__HRTFTCBASE + 0x000C)

/* INPUT/OUTPUT CONTROL */
#define __IOCONBASE  0xFFFE5000
#define __MUXCTL1             *(volatile U32*)(__IOCONBASE + 0x0000)
#define __MUXCTL19            *(volatile U32*)(__IOCONBASE + 0x0090)
#define __MUXCTL20            *(volatile U32*)(__IOCONBASE + 0x0098)
#define __MUXCTL21            *(volatile U32*)(__IOCONBASE + 0x00A0)
#define __MUXCTL22            *(volatile U32*)(__IOCONBASE + 0x00A8)

/*********************************************************************
*
*       Initialization macro
*
**********************************************************************
*/
#define LCD_INIT_CONTROLLER()                                                                              \
  __AHBCLKCTRL       = 0x00000000;                                                                         \
  __PERIPHCLKCTRL1   &= ~(  1 <<  0);                 /* Enable clock for LCD Controller */                \
  __LCDCLKPRESCALE   = 0x00000000;                    /* LCD clock prescaler */                            \
  __MUXCTL1          |=  (  1 <<  0)                  /* PL1 = LCDVDD15 */                                 \
                     |   (  1 <<  2);                 /* PL0 = LCDVDD14 */                                 \
  __MUXCTL19         |=  (  1 << 12)                  /* PE6 = LCDVEEN */                                  \
                     |   (  1 <<  8)                  /* PE5 = LCDVDDEN */                                 \
                     |   (  2 <<  4)                  /* PE4 = LCDREV */                                   \
                     |   (  1 <<  2);                 /* PE3 = LCDCLS */                                   \
  __MUXCTL20         |=  (  1 << 10)                  /* PE1 = LCDDCLK */                                  \
                     |   (  1 <<  6)                  /* PE0 = LCDLP */                                    \
                     |   (  1 <<  2)                  /* PF7 = LCDFP */                                    \
                     |   (  1 <<  0);                 /* PF6 = LCDEN */                                    \
  __MUXCTL21         |=  (  1 << 10)                  /* PF5 = LCDVDD11 */                                 \
                     |   (  1 <<  8)                  /* PL3 = LCDVDD13 */                                 \
                     |   (  1 <<  6)                  /* PF4 = LCDVDD10 */                                 \
                     |   (  1 <<  4)                  /* PL2 = LCDVDD12 */                                 \
                     |   (  1 <<  2)                  /* PF3 = LCDVDD9 */                                  \
                     |   (  1 <<  0);                 /* PF2 = LCDVDD8 */                                  \
  __MUXCTL22         |=  (  1 << 14)                  /* PF1 = LCDVDD7 */                                  \
                     |   (  1 << 12)                  /* PF0 = LCDVDD6 */                                  \
                     |   (  1 << 10)                  /* PG7 = LCDVDD5 */                                  \
                     |   (  1 <<  8)                  /* PG6 = LCDVDD4 */                                  \
                     |   (  1 <<  6)                  /* PG5 = LCDVDD3 */                                  \
                     |   (  1 <<  4)                  /* PG4 = LCDVDD2 */                                  \
                     |   (  1 <<  2)                  /* PG3 = LCDVDD1 */                                  \
                     |   (  1 <<  0);                 /* PG2 = LCDVDD0 */                                  \
  __LCDTIMING0       =   ( 96 << 24)                  /* Horizontal Back Porch */                          \
                     |   ( 50 << 16)                  /* Horizontal Front Porch */                         \
                     |   ( 16 <<  8)                  /* Horizontal Synchronization Pulse Width */         \
                     |   ((LCD_XSIZE / 16 - 1) << 2); /* Pixels-Per-Line */                                \
  __LCDTIMING1       =   ( 26 << 24)                  /* Vertical Back Porch */                            \
                     |   (  4 << 16)                  /* Vertical Front Porch */                           \
                     |   (  7 << 10)                  /* Vertical Synchronization (Pulse) Width */         \
                     |   (LCD_YSIZE - 1);             /* Lines Per Panel */                                \
  __LCDTIMING2       =   (  0 << 27)                  /* Panel Clock Divisor (upper five bits) */          \
                     |   (  0 << 26)                  /* Bypass Pixel Clock Divider */                     \
                     |   ((LCD_XSIZE - 1) << 16)      /* Clocks Per Line */                                \
                     |   (  0 << 14)                  /* Invert Output Enable */                           \
                     |   (  0 << 13)                  /* Invert Panel Clock */                             \
                     |   (  1 << 12)                  /* Invert Horizontal Synchronization */              \
                     |   (  1 << 11)                  /* Invert the Vertical Synchronization Signal */     \
                     |   (  0 <<  6)                  /* AC Bias Signal Frequency */                       \
                     |   (  0 <<  0);                 /* Panel Clock Divisor */                            \
  __LCDUPBASE        = LCD_VRAM_ADR;                  /* Upper Panel Frame Buffer Base Address Register */ \
  __LCDINTRENABLE    = 0x00000000;                    /* Interrupt Enable Register */                      \
  __LCDCONTROL       =   (  1 << 16)                  /* LCD DMA FIFO Watermark Level */                   \
                     |   (  0 << 12)                  /* LCD Vertical Compare */                           \
                     |   (  1 << 11)                  /* LCD Power Enable */                               \
                     |   (  0 << 10)                  /* Big-Endian Pixel Ordering */                      \
                     |   (  0 <<  9)                  /* Big-Endian Byte Ordering to the LCD */            \
                     |   (  0 <<  8)                  /* RGB or BGR Format Selection */                    \
                     |   (  0 <<  7)                  /* Dual Panel STN LCD */                             \
                     |   (  0 <<  6)                  /* Monochrome LCD */                                 \
                     |   (  1 <<  5)                  /* TFT LCD */                                        \
                     |   (  0 <<  4)                  /* Monochrome STN LCD */                             \
                     |   (  4 <<  1)                  /* LCD Bits-Per-Pixel */                             \
                     |   (  1 <<  0);                 /* Color LCD Controller Enable */                    \
  __HRTFTCSETUP      =   (  0 <<  4)                  /* Pixels Per Line */                                \
                     |   (  0 <<  0);                 /* Conversion Mode Select */                         \
  __HRTFTCCONTROL    =   (  0 <<  9)                  /* MOD Signal Override Enable */                     \
                     |   (  0 <<  8)                  /* Mod Signal Value */                               \
                     |   (  1 <<  4)                  /* LCDVEEEN Output Enable */                         \
                     |   (  0 <<  3)                  /* Display Control Signal Output */                  \
                     |   (  0 <<  1)                  /* CLS Enable */                                     \
                     |   (  0 <<  0)                  /* SPS Enable */

#define LCD_ON()
#define LCD_OFF()

/*********************************************************************
*
*       ARM : Sharp LH75401, Logic PD board, QVGA display
*
**********************************************************************
*/

#elif defined TARGET_LH75401_QVGA

#define LCD_MEMBASE 0x4805A800

#define LCD_BITSPERPIXEL    8
#define LCD_CONTROLLER   3200
#define LCD_XSIZE         320
#define LCD_YSIZE         240
#define LCD_SWAP_XY         1
#define LCD_MIRROR_X        1

#define LCD_SWAP_RB         0
#define LCD_ENDIAN_BIG      0
#define LCD_VRAM_ADR LCD_MEMBASE

#if   (LCD_BITSPERPIXEL == 8)

#define LCDBPP              3
#define LCD_SET_LUT_ENTRY(Pos, Color)                             \
  volatile U32 * pPalette;                                        \
  U32 Index;                                                      \
  pPalette = (volatile U32 *)(__CLCDCBASE + 0x0200) + (Pos >> 1); \
  Index    = LCD_Color2Index_444_16(Color) >> 1;                  \
  if (Pos & 1) {                                                  \
    *pPalette &= 0x0000FFFF;                                      \
    *pPalette |= Index << 16;                                     \
  } else {                                                        \
    *pPalette &= 0xFFFF0000;                                      \
    *pPalette |= Index;                                           \
  }

#elif (LCD_BITSPERPIXEL == 16)

#define LCDBPP              4
#define LCD_FIXEDPALETTE  555

#endif

/* RESET, CLOCK AND POWER CONTROLLER */
#define __RCPCBASE          0xFFFE2000
#define __PERIPHCLKCTRL     *(volatile U32*)(__RCPCBASE + 0x0024)
#define __PERIPHCLKCTRL2    *(volatile U32*)(__RCPCBASE + 0x0028)
#define __PERPIHCLKSELECT   *(volatile U32*)(__RCPCBASE + 0x0030)
#define __PERIPHCLKSELECT2  *(volatile U32*)(__RCPCBASE + 0x0034)
#define __LCDCLKPRESCALE    *(volatile U32*)(__RCPCBASE + 0x0040)

/* COLOR LCD CONTROLLER */
#define __CLCDCBASE         0xFFFF4000
#define __LCDTIMING0        *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1        *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2        *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDUPBASE         *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE         *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE     *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL        *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS         *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT      *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE       *(volatile U32*)(__CLCDCBASE + 0x0200)
/* CLCDCBASE + 0x200 - 0x3FC LCDPALETTE 256 × 16-bit Color Palette */

/* HR-TFT LCD TIMING CONTROLLER */
#define __HRTFTCBASE        0xFFFE4000
#define __HRTFTCSETUP       *(volatile U32*)(__HRTFTCBASE + 0x0000)
#define __HRTFTCCONTROL     *(volatile U32*)(__HRTFTCBASE + 0x0004)
#define __HRTFTCTIMING1     *(volatile U32*)(__HRTFTCBASE + 0x0008)
#define __HRTFTCTIMING2     *(volatile U32*)(__HRTFTCBASE + 0x000C)

/* INPUT/OUTPUT CONTROL */
#define __IOCONBASE         0xFFFE5000
#define __LCDMUX            *(volatile U32*)(__IOCONBASE + 0x0010)

#define LCD_INIT_CONTROLLER()                                             \
        __PERIPHCLKCTRL2       = (0 << 0);                   /* enable clock for LCD Controller */ \
        __PERIPHCLKSELECT2     = (0 << 0);                   /* select HCLK as Clock for LCD Controller */ \
        __LCDCLKPRESCALE       =  1;                         /* LCD clock prescaler /2 */ \
        __LCDMUX               = (4 << 0);                   /* TFT Mode */ \
        __LCDTIMING0           = (0x14 << 24)                /* Horizontal back  porch */ \
                               | (0x14 << 16)                /* Horizontal front porch */ \
                               | (0x3c <<  8)                /* Horizontal synchronization pulse Width */ \
                               | ((LCD_YSIZE / 16 -1) << 2); /* Pixels-Per-Line */ \
        __LCDTIMING1           = (0x07 << 24)                /* Vertical back  porch */ \
                               | (0x05 << 16)                /* Vertical front porch */ \
                               | (0    << 10)                /* Vertical synchronization Pulse Width. */ \
                               | (LCD_XSIZE - 1);            /* Lines-Per-Panel */ \
        __LCDTIMING2           = (0    << 26)                /* Bypass pixel Clock Divider */ \
                               | ((LCD_YSIZE - 1)<< 16)      /* Clocks per line */ \
                               | (0    << 14)                /* Invert Output Enable */ \
                               | (1    << 13)                /* Invert Panel Clock */ \
                               | (1    << 12)                /* Invert Horizontal Synchronization */ \
                               | (0    << 11)                /* Invert the Vertical Synchronization signal */ \
                               | (0    <<  6)                /* AC Bias signal (LCDENAB) frequency */ \
                               | (0    <<  0);               /* Panel Clock Divisor.*/ \
        __LCDUPBASE            = LCD_MEMBASE;                /* LCD Upper Panel Base address */ \
        __LCDINTRENABLE        = 0;                          /* Disable LCD interrupts */ \
        __LCDCONTROL           = (0 << 16)                   /* LCD DMA FIFO Watermark level */ \
                               | (0 << 12)                   /* LCD Vertical Compare */ \
                               | (1 << 11)                   /* LCD Power Enable */ \
                               | (0 << 10)                   /* Big-Endian Pixel Ordering within a byte */ \
                               | (0 <<  9)                   /* Big-Endian Byte Ordering to the LCD */ \
                               | (0 <<  8)                   /* RGB or BGR format selection:           \
                                                                1 = BGR red and blue swapped           \
                                                                0 = RGB normal output*/ \
                               | (0 <<  7)                   /* RLCD is a Dual panel STN */           \
                               | (0 <<  6)                   /* LCD 8bit Mono (8bit interface)*/           \
                               | (1 <<  5)                   /* LCD is a TFT */           \
                               | (0 <<  4)                   /* LCD is STN mono */           \
                               | (LCDBPP <<  1)              /* LCD bpp 4 = 16bpp \
                                                                        3 =  8bpp \
                                                                        2 =  4bpp \
                                                                        1 =  2bpp */ \
                               | (1 <<  0);                  /* 0 =  Enable LCD Controller */  \
        __HRTFTCSETUP          = ((LCD_YSIZE - 1 ) << 4)     /* Number of pixels per line */   \
                               | (6 << 1)                    /* Conversion mode select (HF-TFT panels) */ \
                               | (1 << 0);                   /* Conversion mode select (HF-TFT panels) */ \
        __HRTFTCTIMING1        = (8    << 8)                 /* Delay in LCDDCLK periods from the 1st LOW \
                                                                in the LCDLP signal, to the leading edge \
                                                                of the LCDPS and LCD-CLS signals */   \
                               | (7    << 4)                 /* Polarity-Reversal delay */ \
                               | (12   << 0);                /* Delay in LCDDCLK periods from the 1st LOW \
                                                                in the LCDLP signal, to the leading edge  \
                                                                of the LCDLP signal */ \
        __HRTFTCTIMING2        = (0x53 << 9)                 /* Delay in LCDDCLK periods of the LCD-SPL \
                                                                signal during vertical front and back porches. */   \
                               | (0xd0 << 0);                /* Delay in LCDDCLK periods from the first \
                                                                rising edge of the LCDSPL signal to the \
                                                                trailing edge of the LCDCLS signal */   \
        __HRTFTCCONTROL        = (1 << 1)                    /* LCDCLS enable  */   \
                               | (1 << 0);                   /* LCDSPS enable */

#define LCD_ON()
#define LCD_OFF()

/*********************************************************************
*
*       ARM : Sharp LH7A400, Logic PD board, VGA display
*
**********************************************************************
*/
#elif defined TARGET_LH7A400_VGA

#define LCD_MEMBASE      0xC1000000
#define LCD_BITSPERPIXEL   16
#define LCD_XSIZE         640
#define LCD_YSIZE         480

#define LCD_CONTROLLER   3200

#define LCD_FIXEDPALETTE    555
#define LCD_SWAP_RB         (0)
#define LCD_SWAP_BYTE_ORDER (1)
#define LCD_ENDIAN_BIG       0
#define LCD_VRAM_ADR  LCD_MEMBASE

#define __CLCDCBASE     0x80003000
#define __LCDTIMING0    *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1    *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2    *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDTIMING3    *(volatile U32*)(__CLCDCBASE + 0x000C)
#define __LCDUPBASE     *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	    *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL    *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	    *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT  *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE   *(volatile U32*)(__CLCDCBASE + 0x0200)

#define __ALILCDCBASE    0x80001000
#define __ALISETUP      *(volatile U32*)(__ALILCDCBASE + 0x0000)
#define __ALICONTROL    *(volatile U32*)(__ALILCDCBASE + 0x0004)
#define __ALITIMING1    *(volatile U32*)(__ALILCDCBASE + 0x0008)
#define __ALITIMING2    *(volatile U32*)(__ALILCDCBASE + 0x000C)

#define __GPIOBASE  0x80000E00
#define __GPIO_PAD           *(volatile U32*)(__GPIOBASE + 0x0000)
#define __GPIO_PBD           *(volatile U32*)(__GPIOBASE + 0x0004)
#define __GPIO_PCD           *(volatile U32*)(__GPIOBASE + 0x0008)
#define __GPIO_PDD           *(volatile U32*)(__GPIOBASE + 0x000C)
#define __GPIO_PADD          *(volatile U32*)(__GPIOBASE + 0x0010)
#define __GPIO_PBDD          *(volatile U32*)(__GPIOBASE + 0x0014)
#define __GPIO_PCDD          *(volatile U32*)(__GPIOBASE + 0x0018)
#define __GPIO_PDDD          *(volatile U32*)(__GPIOBASE + 0x001C)
#define __GPIO_PED           *(volatile U32*)(__GPIOBASE + 0x0020)
#define __GPIO_PEDD          *(volatile U32*)(__GPIOBASE + 0x0024)
#define __GPIO_KBDCTL        *(volatile U32*)(__GPIOBASE + 0x0028)
#define __GPIO_PINMUX        *(volatile U32*)(__GPIOBASE + 0x002C)
#define __GPIO_PFD           *(volatile U32*)(__GPIOBASE + 0x0030)
#define __GPIO_PFDD          *(volatile U32*)(__GPIOBASE + 0x0034)
#define __GPIO_PGD           *(volatile U32*)(__GPIOBASE + 0x0038)
#define __GPIO_PGDD          *(volatile U32*)(__GPIOBASE + 0x003C)
#define __GPIO_PHD           *(volatile U32*)(__GPIOBASE + 0x0040)
#define __GPIO_PHDD          *(volatile U32*)(__GPIOBASE + 0x0044)

#define __GPIO_INTTYPE1      *(volatile U32*)(__GPIOBASE + 0x004C)
#define __GPIO_INTTYPE2      *(volatile U32*)(__GPIOBASE + 0x0050)
#define __GPIO_GPIOFEOI      *(volatile U32*)(__GPIOBASE + 0x0054)
#define __GPIO_GPIOINTEN     *(volatile U32*)(__GPIOBASE + 0x0058)
#define __GPIO_INTSTATUS     *(volatile U32*)(__GPIOBASE + 0x005C)
#define __GPIO_RAWINTSTATUS  *(volatile U32*)(__GPIOBASE + 0x0060)
#define __GPIO_DEBOUNCE      *(volatile U32*)(__GPIOBASE + 0x0064)
#define __GPIO_PAPD          *(volatile U32*)(__GPIOBASE + 0x0068)
#define __GPIO_PBPD          *(volatile U32*)(__GPIOBASE + 0x006C)
#define __GPIO_PCPD          *(volatile U32*)(__GPIOBASE + 0x0070)
#define __GPIO_PDPD          *(volatile U32*)(__GPIOBASE + 0x0074)
#define __GPIO_PEPD          *(volatile U32*)(__GPIOBASE + 0x0078)
#define __GPIO_PFPD          *(volatile U32*)(__GPIOBASE + 0x007C)
#define __GPIO_PGPD          *(volatile U32*)(__GPIOBASE + 0x0080)
#define __GPIO_PHPD          *(volatile U32*)(__GPIOBASE + 0x0084)

#define __CARD_ENGINE_CTRL   *(volatile U32*)(0x70200000)

#define LCD_INIT_CONTROLLER()                                                         \
        __GPIO_PINMUX         |= (1 << 1) \
                               | (1 << 0); \
        __LCDCONTROL           = 0x00000000;               /* Disable the LCD Controller first */ \
        __ALICONTROL           = 0x00000000;               /* Disable LCDCLS and LCDSPS signals */ \
        __ALISETUP             = (0x00 << 13)              /* Enable Advanced LCD Interface (ALI) */     \
                               | ((LCD_XSIZE - 1) <<  4);  /* Setup Pixels per lines for ALI  */         \
        __LCDTIMING0           = (((LCD_XSIZE / 16) - 1) << 2)    /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 16 - 1) <<  8)         /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 51 - 1) << 16)         /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 90 - 1) << 24);        /* Setup Pixels per lines for LCD Timings register1 */  \
        __LCDTIMING1           = (LCD_YSIZE - 1)           /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 8 - 1) << 10)          /* Use 4 Vertical Sychronization Pulse width */  \
                               | ((95 - 1) << 16)          /* Set Vertical Front Porch */ \
                               | ((27 - 1) << 24);         /* Set Vertical backporch */ \
        __LCDTIMING2           = (2 <<  0)                        /* Set Vertical backporch */ \
                               | (1 << 11)                        /* LCDFFP is active low */   \
                               | (1 << 12)                        /* LCDLP is active low  */ \
                               | ((LCD_XSIZE - 1) << 16); \
        __LCDTIMING3           = 0;                        /* Not available */ \
        __LCDUPBASE            = LCD_MEMBASE;  \
        *(volatile U32*)(0x71a00000)            = 3;  \
        *(volatile U32*)(0x71800000)            = 3;  \
        *(volatile U32*)(0x71800000)            = 0x80;  \
        __LCDCONTROL           = (1 << 16)                /* LCD DMA FIFO Watermark level */ \
                               | (0 << 12)                /* LCD Vertical Compare */ \
                               | (1 << 11)                /* LCD Power Enable */ \
                               | (0 << 10)                /* Big-Endian Pixel Ordering within a byte */ \
                               | (0 <<  9)                /* Big-Endian Byte Ordering to the LCD */ \
                               | (0 <<  8)                /* RGB or BGR format selection:           \
                                                             1 = BGR red and blue swapped           \
                                                             0 = RGB normal output*/ \
                               | (0 <<  7)                /* RLCD is a Dual panel STN */           \
                               | (0 <<  6)                /* LCD 4bit Mono (4bit interface)*/           \
                               | (1 <<  5)                /* LCD is a TFT */           \
                               | (0 <<  4)                /* LCD is STN mono */           \
                               | (4 <<  1)                /* LCD bpp 4 = 16bpp \
                                                                     3 =  8bpp \
                                                                     2 =  4bpp \
                                                                     1 =  2bpp */ \
                               | (1 <<  0);                /* 0 =  Enable LCD Controller */ \
        /* Setup Port pins */ \
        __GPIO_PADD           |= 0xb5;                     \
        __GPIO_PBDD           |= 0xc0;                     \
        __GPIO_PCDD           |= 0xb5;                     \
        __GPIO_PDDD           |= 0x00;                     \
        __GPIO_PEDD           |= 0xff;                     \
        __GPIO_PFDD           |= 0x00;                     \
        __GPIO_PGDD           |= 0x00;                     \
        __GPIO_PHDD           |= 0xcf;                     \
        __GPIO_PAD            |= 0x0f;                     \
        __GPIO_PBD            |= 0x3f;                     \
        __GPIO_PCD            |= 0xb9;                     \
        __GPIO_PDD            |= 0x00;                     \
        __GPIO_PED            |= 0xf0;                     \
        __GPIO_PFD            |= 0xff;                     \
        __GPIO_PGD            |= 0xff;                     \
        __GPIO_PHD            |= 0xfc;                     \
        __GPIO_INTTYPE1        = 0x10; \
        /* Enable VEE */ \
        __CARD_ENGINE_CTRL    = 0xffffffff;

/*
        __GPIO_PAD             = 0x7c; \
        __GPIO_PBD             = 0x07; \
        __GPIO_PCD             = 0x04; \
        __GPIO_PDD             = 0x00; \
        __GPIO_PADD            = 0x04; \
        __GPIO_PBDD            = 0x00; \
        __GPIO_PCDD            = 0x00; \
        __GPIO_PDDD            = 0x00; \
        __GPIO_PED             = 0x00; \
        __GPIO_PEDD            = 0x00; \
        __GPIO_KBDCTL          = 0x00; \
        __GPIO_PINMUX          = 0x0b; \
        __GPIO_PFD             = 0xcf; \
        __GPIO_PFDD            = 0x00; \
        __GPIO_PGD             = 0xff; \
        __GPIO_PGDD            = 0x00; \
        __GPIO_PHD             = 0xfc; \
        __GPIO_PHDD            = 0x00; \
        __GPIO_INTTYPE1        = 0x00; \
        __GPIO_INTTYPE2        = 0x00; \
        __GPIO_GPIOFEOI        = 0x00; \
        __GPIO_GPIOINTEN       = 0x08; \
        __GPIO_INTSTATUS       = 0x00; \
        __GPIO_RAWINTSTATUS    = 0x30; \
        __GPIO_DEBOUNCE        = 0x00; \
        __GPIO_PAPD            = 0x7c; \
        __GPIO_PBPD            = 0x07; \
        __GPIO_PCPD            = 0x04; \
        __GPIO_PDPD            = 0x00; \
        __GPIO_PEPD            = 0x00; \
        __GPIO_PFPD            = 0xcf; \
        __GPIO_PGPD            = 0xff; \
        __GPIO_PHPD            = 0xfc
*/

/*
        __GPIO_PAD             |= 0x7c; \
        __GPIO_PBD             |= 0x07; \
        __GPIO_PCD             |= 0x04; \
        __GPIO_PADD            |= 0x04; \
        __GPIO_PINMUX          |= 0x0b; \
        __GPIO_PFD             |= 0xcf; \
        __GPIO_PGD             |= 0xff; \
        __GPIO_PHD             |= 0xfc; \
        __GPIO_GPIOINTEN       |= 0x08; \
        __GPIO_RAWINTSTATUS    |= 0x30; \
        __GPIO_PAPD            |= 0x7c; \
        __GPIO_PBPD            |= 0x07; \
        __GPIO_PCPD            |= 0x04; \
        __GPIO_PFPD            |= 0xcf; \
        __GPIO_PGPD            |= 0xff; \
        __GPIO_PHPD            |= 0xfc
*/

#define LCD_ON()
#define LCD_OFF()

/*********************************************************************
*
*       ARM : Sharp LH7A404, Logic PD board, VGA display
*
**********************************************************************
*/
#elif defined TARGET_LH7A404_VGA

#define LCD_MEMBASE      0xC1000000
#define LCD_BITSPERPIXEL   16
#define LCD_XSIZE         640
#define LCD_YSIZE         480

#define LCD_CONTROLLER   3200

#define LCD_FIXEDPALETTE    555
#define LCD_SWAP_RB         (0)
#define LCD_SWAP_BYTE_ORDER (1)
#define LCD_ENDIAN_BIG       0
#define LCD_VRAM_ADR  LCD_MEMBASE

#define __CLCDCBASE     0x80003000
#define __LCDTIMING0    *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1    *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2    *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDTIMING3    *(volatile U32*)(__CLCDCBASE + 0x000C)
#define __LCDUPBASE     *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	    *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL    *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	    *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT  *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE   *(volatile U32*)(__CLCDCBASE + 0x0200)

#define __ALILCDCBASE    0x80001000
#define __ALISETUP      *(volatile U32*)(__ALILCDCBASE + 0x0000)
#define __ALICONTROL    *(volatile U32*)(__ALILCDCBASE + 0x0004)
#define __ALITIMING1    *(volatile U32*)(__ALILCDCBASE + 0x0008)
#define __ALITIMING2    *(volatile U32*)(__ALILCDCBASE + 0x000C)
#define __PINMUX        *(volatile U32*)(0x80000E2C)

#define __GPIOBASE  0x80000E00
#define __GPIO_PAD           *(volatile U32*)(__GPIOBASE + 0x0000)
#define __GPIO_PBD           *(volatile U32*)(__GPIOBASE + 0x0004)
#define __GPIO_PCD           *(volatile U32*)(__GPIOBASE + 0x0008)
#define __GPIO_PDD           *(volatile U32*)(__GPIOBASE + 0x000C)
#define __GPIO_PADD          *(volatile U32*)(__GPIOBASE + 0x0010)
#define __GPIO_PBDD          *(volatile U32*)(__GPIOBASE + 0x0014)
#define __GPIO_PCDD          *(volatile U32*)(__GPIOBASE + 0x0018)
#define __GPIO_PDDD          *(volatile U32*)(__GPIOBASE + 0x001C)
#define __GPIO_PED           *(volatile U32*)(__GPIOBASE + 0x0020)
#define __GPIO_PEDD          *(volatile U32*)(__GPIOBASE + 0x0024)
#define __GPIO_KBDCTL        *(volatile U32*)(__GPIOBASE + 0x0028)
#define __GPIO_PINMUX        *(volatile U32*)(__GPIOBASE + 0x002C)
#define __GPIO_PFD           *(volatile U32*)(__GPIOBASE + 0x0030)
#define __GPIO_PFDD          *(volatile U32*)(__GPIOBASE + 0x0034)
#define __GPIO_PGD           *(volatile U32*)(__GPIOBASE + 0x0038)
#define __GPIO_PGDD          *(volatile U32*)(__GPIOBASE + 0x003C)
#define __GPIO_PHD           *(volatile U32*)(__GPIOBASE + 0x0040)
#define __GPIO_PHDD          *(volatile U32*)(__GPIOBASE + 0x0044)
#define __GPIO_INTTYPE1      *(volatile U32*)(__GPIOBASE + 0x004C)
#define __GPIO_INTTYPE2      *(volatile U32*)(__GPIOBASE + 0x0050)
#define __GPIO_GPIOFEOI      *(volatile U32*)(__GPIOBASE + 0x0054)
#define __GPIO_GPIOINTEN     *(volatile U32*)(__GPIOBASE + 0x0058)
#define __GPIO_INTSTATUS     *(volatile U32*)(__GPIOBASE + 0x005C)
#define __GPIO_RAWINTSTATUS  *(volatile U32*)(__GPIOBASE + 0x0060)
#define __GPIO_DEBOUNCE      *(volatile U32*)(__GPIOBASE + 0x0064)
#define __GPIO_PAPD          *(volatile U32*)(__GPIOBASE + 0x0068)
#define __GPIO_PBPD          *(volatile U32*)(__GPIOBASE + 0x006C)
#define __GPIO_PCPD          *(volatile U32*)(__GPIOBASE + 0x0070)
#define __GPIO_PDPD          *(volatile U32*)(__GPIOBASE + 0x0074)
#define __GPIO_PEPD          *(volatile U32*)(__GPIOBASE + 0x0078)
#define __GPIO_PFPD          *(volatile U32*)(__GPIOBASE + 0x007C)
#define __GPIO_PGPD          *(volatile U32*)(__GPIOBASE + 0x0080)
#define __GPIO_PHPD          *(volatile U32*)(__GPIOBASE + 0x0084)

#define LCD_INIT_CONTROLLER()                                                         \
        __PINMUX              |= (1 << 1) \
                               | (1 << 0); \
        __LCDCONTROL           = 0x00000000;               /* Disable the LCD Controller first */ \
        __ALICONTROL           = 0x00000000;               /* Disable LCDCLS and LCDSPS signals */ \
        __ALISETUP             = (0x00 << 13)              /* Enable Advanced LCD Interface (ALI) */     \
                               | ((LCD_XSIZE - 1) <<  4);  /* Setup Pixels per lines for ALI  */         \
        __LCDTIMING0           = (((LCD_XSIZE / 16) - 1) << 2)    /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 16 - 1) <<  8)         /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 51 - 1) << 16)         /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 90 - 1) << 24);        /* Setup Pixels per lines for LCD Timings register1 */  \
        __LCDTIMING1           = (LCD_YSIZE - 1)           /* Setup Pixels per lines for LCD Timings register1 */  \
                               | (( 8 - 1) << 10)          /* Use 4 Vertical Sychronization Pulse width */  \
                               | ((95 - 1) << 16)          /* Set Vertical Front Porch */ \
                               | ((27 - 1) << 24);         /* Set Vertical backporch */ \
        __LCDTIMING2           = (2 <<  0)                        /* Set Vertical backporch */ \
                               | (1 << 11)                        /* LCDFFP is active low */   \
                               | (1 << 12)                        /* LCDLP is active low  */ \
                               | ((LCD_XSIZE - 1) << 16); \
        __LCDTIMING3           = 0;                        /* Not available */ \
        __LCDUPBASE            = LCD_MEMBASE;  \
        *(volatile U32*)(0x71a00000)            = 3;  \
        *(volatile U32*)(0x71800000)            = 3;  \
        *(volatile U32*)(0x71800000)            = 0x80;  \
        __LCDCONTROL           = (1 << 16)                /* LCD DMA FIFO Watermark level */ \
                               | (0 << 12)                /* LCD Vertical Compare */ \
                               | (1 << 11)                /* LCD Power Enable */ \
                               | (0 << 10)                /* Big-Endian Pixel Ordering within a byte */ \
                               | (0 <<  9)                /* Big-Endian Byte Ordering to the LCD */ \
                               | (0 <<  8)                /* RGB or BGR format selection:           \
                                                             1 = BGR red and blue swapped           \
                                                             0 = RGB normal output*/ \
                               | (0 <<  7)                /* RLCD is a Dual panel STN */           \
                               | (0 <<  6)                /* LCD 4bit Mono (4bit interface)*/           \
                               | (1 <<  5)                /* LCD is a TFT */           \
                               | (0 <<  4)                /* LCD is STN mono */           \
                               | (4 <<  1)                /* LCD bpp 4 = 16bpp \
                                                                     3 =  8bpp \
                                                                     2 =  4bpp \
                                                                     1 =  2bpp */ \
                               | (1 <<  0);                /* 0 =  Enable LCD Controller */ \
        /* Setup Port pins */ \
        __GPIO_PADD           |= 0xb5;                     \
        __GPIO_PBDD           |= 0xc0;                     \
        __GPIO_PCDD           |= 0xb5;                     \
        __GPIO_PDDD           |= 0x00;                     \
        __GPIO_PEDD           |= 0xff;                     \
        __GPIO_PFDD           |= 0x00;                     \
        __GPIO_PGDD           |= 0x00;                     \
        __GPIO_PHDD           |= 0xcf;                     \
        __GPIO_PAD            |= 0x0f;                     \
        __GPIO_PBD            |= 0x3f;                     \
        __GPIO_PCD            |= 0xb9;                     \
        __GPIO_PDD            |= 0x00;                     \
        __GPIO_PED            |= 0xf0;                     \
        __GPIO_PFD            |= 0xff;                     \
        __GPIO_PGD            |= 0xff;                     \
        __GPIO_PHD            |= 0xfc;                     \
        __GPIO_INTTYPE1        = 0x10;

#define LCD_ON()
#define LCD_OFF()

/*********************************************************************
*
*       ARM configuration Philips LPC2294
*
**********************************************************************
*/
#elif defined TARGET_LPC2294

#define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */

#define LCD_BITSPERPIXEL (8)

#define LCD_CONTROLLER 1375

#define LCD_SWAP_BYTE_ORDER 1

/*********************************************************************
*
*       Full bus configuration
*/
#define LCD_READ_MEM(Off)            *((U16*)         (0x83040000+(((U32)(Off))<<1)))
#define LCD_WRITE_MEM(Off,data)      *((U16*)         (0x83040000+(((U32)(Off))<<1)))=data
#define LCD_READ_REG(Off)            *((volatile U16*)(0x8305ffe0+(((U16)(Off))<<1)))
#define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0x8305ffe0+(((U16)(Off))<<1)))=data

/*********************************************************************
*
*       Define contents of registers
*/
#define LCD_REG0  (0)                                          /* Product code */

#define LCD_REG1  (0x23)                                       /* Mode reg 0.    0 for 4 bit mono LCD */            \
                                                               /*                1 for 8 bit mono LCD */            \
                                                               /*             0x23 for 8 bit color LCD */           \
                 |(1<<2)                                       /*             Mask FPSHIFT during h.non-display */

#define LCD_REG2 ((3<<6)                                       /* Mode reg 1: Bits per pixel 0:1, 1:2, 2:4, 3:8 */  \
                 |(1<<5)                                       /* High performance bit for accel. of CPU access */  \
                 |(1<<4)                                       /* Input clock divide */                             \
                 |(0<<3)                                       /* Display blank */                                  \
                 |(0<<2)                                       /* Frame repeat */                                   \
                 |(0<<1)                                       /* HW video invert enable */                         \
                 |(0<<0))                                      /* SW video invert */

#define LCD_REG3                                               /* Mode reg 2. 0 for 4 bit mono LCD */               \
                  (0<<7)                                       /* LUT bypass */                                     \
                 |(0<<3)                                       /* LCDPWR override */                                \
                 |(0<<2)                                       /* hw power save enable */                           \
                 |(3<<0)                                       /* Software power save :3 = normal operation */

#define LCD_REG4 (LCD_XSIZE/8-1)                               /* horizontal panel size*/
#define LCD_REG5 ((LCD_YSIZE-1)&255)                           /* Vert. panel size, lsb */
#define LCD_REG6 ((LCD_YSIZE-1)>>8)                            /* Vert. panel size, msb */
#define LCD_REG7 (0)                                           /* FPLine start position (TFT only) */
#define LCD_REG8 (31)                                          /* H.non display period   (0 usually O.K.)*/
#define LCD_REG9 (0)                                           /* FPFrame start pos.    (TFT only) */
#define LCD_REGA (0)                                           /* v.non display period  */
#define LCD_REGB (0)                                           /* mod rate register     0: every frame */
#define LCD_REGC (0)                                           /* Screen 1 start lsb    */
#define LCD_REGD (0)                                           /* Screen 1 start msb    */

#define LCD_REG11 (LCD_BITSPERPIXEL*(LCD_VXSIZE-LCD_XSIZE)/16) /* Memory Address offset (usually 0) */
#define LCD_REG12 LCD_REG5                                     /* Vert. screen 1 size, lsb */
#define LCD_REG13 LCD_REG6                                     /* Vert. screen 1 size, msb */

#define LCD_REG1B (0)                                          /* No swivel mode  (use 0xc0 for alt.swivel)  */
#define LCD_REG1C (0x78)                                       /* bytes per line (stride, for swivel mode only)  */

/*********************************************************************
*
*       Init sequence for 16 bit access
*/

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0)<<8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1)<<8) | (d0))
#endif

#define LCD_INIT_CONTROLLER()                                                                    \
        LCD_WRITE_REGLH(0x00>>1,LCD_REG0, LCD_REG1);                                             \
        LCD_WRITE_REGLH(0x02>>1,LCD_REG2, LCD_REG3);                                             \
        LCD_WRITE_REGLH(0x04>>1,LCD_REG4, LCD_REG5);                                             \
        LCD_WRITE_REGLH(0x06>>1,LCD_REG6, LCD_REG7);                                             \
        LCD_WRITE_REGLH(0x08>>1,LCD_REG8, LCD_REG9);                                             \
        LCD_WRITE_REGLH(0x0a>>1,LCD_REGA, LCD_REGB);                                             \
        LCD_WRITE_REGLH(0x0c>>1,LCD_REGC, LCD_REGD);                                             \
        LCD_WRITE_REG  (0x0e>>1,0x00);                 /* 0, screen 2 start l*/                  \
        LCD_WRITE_REGLH(0x10>>1,0x00,      LCD_REG11); /* mem adr. offset */                     \
        LCD_WRITE_REGLH(0x12>>1,LCD_REG12, LCD_REG13); /* screen 1 vsize */                      \
        LCD_WRITE_REGLH(0x1a>>1,0, LCD_REG1B);                                                   \
        LCD_WRITE_REGLH(0x1c>>1,LCD_REG1C, 0)


/*********************************************************************
*
*           Axel board (V850)
*
**********************************************************************
*/
#elif defined TARGET_AXEL_BOARD
#define LCD_CONTROLLER 1386
#define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */

#define LCD_SWAP_BYTE_ORDER 0
#define LCD_BITSPERPIXEL    16
#define LCD_SWAP_RB         1
#define LCD_USE_BITBLT      1
#ifdef CPU_V850_SA2
  #define LCD_FIXEDPALETTE    -1
#endif
/*********************************************************************
*
*                   Full bus configuration
*/

#define LCD_READ_MEM(Off)            *((U16 *)        (0x600000+(((U32)(Off))<<1)))
#define LCD_WRITE_MEM(Off,Data)      *((U16 *)        (0x600000+(((U32)(Off))<<1)))=Data
#define LCD_READ_REG(Off)            *((volatile U16*)(0x400000+(((U32)(Off))<<1)))
#define LCD_WRITE_REG(Off,Data)      *((volatile U16*)(0x400000+(((U32)(Off))<<1)))=Data

/*********************************************************************
*
*                   Define contents of registers
*/

#define LCD_REG001 (0x00) /* Miscellaneous Register                                */
#define LCD_REGXXX (0x00) /* Display Mode Register                                 */
#define LCD_REG004 (0x04) /* General IO Pins Configuration Register 0              */
#define LCD_REG005 (0x00) /* General IO Pins Configuration Register 1              */
#define LCD_REG008 (0x04) /* General IO Pins Control Register 0                    */
#define LCD_REG009 (0x00) /* General IO Pins Control Register 1                    */
#define LCD_REG010 (0x01) /* Memory Clock Configuration Register                   */
#define LCD_REG014 (0x11) /* LCD Pixel Clock Configuration Register                */
#define LCD_REG018 (0x00) /* CRT/TV Pixel Clock Configuration Register             */
#define LCD_REG01C (0x01) /* MediaPlug Clock Configuration Register                */
#define LCD_REG01E (0x00) /* CPU To Memory Wait State Select Register              */
#define LCD_REG020 (0x80) /* Memory Configuration Register                         */
#define LCD_REG021 (0x01) /* DRAM Refresh Rate Register                            */
#define LCD_REG02A (0x11) /* DRAM Timings Control Register 0                       */
#define LCD_REG02B (0x13) /* DRAM Timings Control Register 1                       */
#define LCD_REG030 (0x1d) /* Panel Type Register                                   */
#define LCD_REG031 (0x00) /* MOD Rate Register                                     */
#define LCD_REG032 (LCD_XSIZE/8-1) /* LCD Horizontal Display Width Register        */
#define LCD_REG034 (0x03) /* LCD Horizontal Non-Display Period Register            */
#define LCD_REG035 (0x01) /* TFT FPLINE Start Position Register                    */
#define LCD_REG036 (0x09) /* TFT FPLINE Pulse Width Register                       */
#define LCD_REG038 ((LCD_YSIZE-1)%256) /* LCD Vertical Display Height Register 0   */
#define LCD_REG039 ((LCD_YSIZE-1)/256) /* LCD Vertical Display Height Register 1   */
#define LCD_REG03A (60) /* LCD Vertical Non-Display Period Register                */
#define LCD_REG03B (52) /* TFT FPFRAME Start Position Register                     */
#define LCD_REG03C (0x00) /* TFT FPFRAME Pulse Width Register                      */
#define LCD_REG040 (0x05) /* LCD Display Mode Register                             */
#define LCD_REG041 (0x00) /* LCD Miscellaneous Register                            */
#define LCD_REG042 (0x00) /* LCD Display Start Address Register 0                  */
#define LCD_REG043 (0x00) /* LCD Display Start Address Register 1                  */
#define LCD_REG044 (0x00) /* LCD Display Start Address Register 2                  */
#define LCD_REG046 (0x40) /* LCD Memory Address Offset Register 0                  */
#define LCD_REG047 (0x01) /* LCD Memory Address Offset Register 1                  */
#define LCD_REG048 (0x00) /* LCD Pixel Panning Register                            */
#define LCD_REG04A (0x00) /* LCD Display FIFO High Threshold Control Register      */
#define LCD_REG04B (0x00) /* LCD Display FIFO Low Threshold Control Register       */
#define LCD_REG050 (0x4F) /* CRT/TV Horizontal Display Width Register              */
#define LCD_REG052 (0x13) /* CRT/TV Horizontal Non-Display Period Register         */
#define LCD_REG053 (0x01) /* CRT/TV HRTC Start Position Register                   */
#define LCD_REG054 (0x0B) /* CRT/TV HRTC Pulse Width Register                      */
#define LCD_REG056 (0xDF) /* CRT/TV Vertical Display Height Register 0             */
#define LCD_REG057 (0x01) /* CRT/TV Vertical Display Height Register 1             */
#define LCD_REG058 (0x2B) /* CRT/TV Vertical Non-Display Period Register           */
#define LCD_REG059 (0x09) /* CRT/TV VRTC Start Position Register                   */
#define LCD_REG05A (0x01) /* CRT/TV VRTC Pulse Width Register                      */
#define LCD_REG05B (0x10) /* TV Output Control Register                            */
#define LCD_REG060 (0x03) /* CRT/TV Display Mode Register                          */
#define LCD_REG062 (0x00) /* CRT/TV Display Start Address Register 0               */
#define LCD_REG063 (0x00) /* CRT/TV Display Start Address Register 1               */
#define LCD_REG064 (0x00) /* CRT/TV Display Start Address Register 2               */
#define LCD_REG066 (0x40) /* CRT/TV Memory Address Offset Register 0               */
#define LCD_REG067 (0x01) /* CRT/TV Memory Address Offset Register 1               */
#define LCD_REG068 (0x00) /* CRT/TV Pixel Panning Register                         */
#define LCD_REG06A (0x00) /* CRT/TV Display FIFO High Threshold Control Register   */
#define LCD_REG06B (0x00) /* CRT/TV Display FIFO Low Threshold Control Register    */
#define LCD_REG070 (0x00) /* LCD Ink/Cursor Control Register                       */
#define LCD_REG071 (0x01) /* LCD Ink/Cursor Start Address Register                 */
#define LCD_REG072 (0x00) /* LCD Cursor X Position Register 0                      */
#define LCD_REG073 (0x00) /* LCD Cursor X Position Register 1                      */
#define LCD_REG074 (0x00) /* LCD Cursor Y Position Register 0                      */
#define LCD_REG075 (0x00) /* LCD Cursor Y Position Register 1                      */
#define LCD_REG076 (0x00) /* LCD Ink/Cursor Blue Color 0 Register                  */
#define LCD_REG077 (0x00) /* LCD Ink/Cursor Green Color 0 Register                 */
#define LCD_REG078 (0x00) /* LCD Ink/Cursor Red Color 0 Register                   */
#define LCD_REG07A (0x1F) /* LCD Ink/Cursor Blue Color 1 Register                  */
#define LCD_REG07B (0x3F) /* LCD Ink/Cursor Green Color 1 Register                 */
#define LCD_REG07C (0x1F) /* LCD Ink/Cursor Red Color 1 Register                   */
#define LCD_REG07E (0x00) /* LCD Ink/Cursor FIFO Threshold Register                */
#define LCD_REG080 (0x00) /* CRT/TV Ink/Cursor Control Register                    */
#define LCD_REG081 (0x01) /* CRT/TV Ink/Cursor Start Address Register              */
#define LCD_REG082 (0x00) /* CRT/TV Cursor X Position Register 0                   */
#define LCD_REG083 (0x00) /* CRT/TV Cursor X Position Register 1                   */
#define LCD_REG084 (0x00) /* CRT/TV Cursor Y Position Register 0                   */
#define LCD_REG085 (0x00) /* CRT/TV Cursor Y Position Register 1                   */
#define LCD_REG086 (0x00) /* CRT/TV Ink/Cursor Blue Color 0 Register               */
#define LCD_REG087 (0x00) /* CRT/TV Ink/Cursor Green Color 0 Register              */
#define LCD_REG088 (0x00) /* CRT/TV Ink/Cursor Red Color 0 Register                */
#define LCD_REG08A (0x1F) /* CRT/TV Ink/Cursor Blue Color 1 Register               */
#define LCD_REG08B (0x3F) /* CRT/TV Ink/Cursor Green Color 1 Register              */
#define LCD_REG08C (0x1F) /* CRT/TV Ink/Cursor Red Color 1 Register                */
#define LCD_REG08E (0x00) /* CRT/TV Ink/Cursor FIFO Threshold Register             */
#define LCD_REG1F0 (0x10) /* Power Save Configuration Register                     */
#define LCD_REG1F1 (0x00) /* Power Save Status Register                            */
#define LCD_REG1F4 (0x00) /* CPU-to-Memory Access Watchdog Timer Register          */
#define LCD_REG1FC (0x01) /* Display Mode Register                                 */

/*********************************************************************
*
*                   Init sequence for 16 bit access (LCD)
*/

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0) << 8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1) << 8) | (d0))
#endif


#define LCD_INIT_CONTROLLER()                          \
  LCD_WRITE_REGLH(0x000 >> 1,          0, LCD_REG001); \
  LCD_WRITE_REGLH(0x1FC >> 1,          0,          0); \
  LCD_WRITE_REGLH(0x004 >> 1, LCD_REG004, LCD_REG005); \
  LCD_WRITE_REGLH(0x008 >> 1, LCD_REG008, LCD_REG009); \
  LCD_WRITE_REGLH(0x010 >> 1, LCD_REG010,          0); \
  LCD_WRITE_REGLH(0x014 >> 1, LCD_REG014,          0); \
  LCD_WRITE_REGLH(0x01E >> 1, LCD_REG01E,          0); \
  LCD_WRITE_REGLH(0x020 >> 1, LCD_REG020, LCD_REG021); \
  LCD_WRITE_REGLH(0x02A >> 1, LCD_REG02A, LCD_REG02B); \
  LCD_WRITE_REGLH(0x030 >> 1, LCD_REG030, LCD_REG031); \
  LCD_WRITE_REGLH(0x032 >> 1, LCD_REG032,          0); \
  LCD_WRITE_REGLH(0x034 >> 1, LCD_REG034, LCD_REG035); \
  LCD_WRITE_REGLH(0x036 >> 1, LCD_REG036,          0); \
  LCD_WRITE_REGLH(0x038 >> 1, LCD_REG038, LCD_REG039); \
  LCD_WRITE_REGLH(0x03A >> 1, LCD_REG03A, LCD_REG03B); \
  LCD_WRITE_REGLH(0x03C >> 1, LCD_REG03C,          0); \
  LCD_WRITE_REGLH(0x040 >> 1, LCD_REG040, LCD_REG041); \
  LCD_WRITE_REGLH(0x042 >> 1, LCD_REG042, LCD_REG043); \
  LCD_WRITE_REGLH(0x044 >> 1, LCD_REG044,          0); \
  LCD_WRITE_REGLH(0x046 >> 1, LCD_REG046, LCD_REG047); \
  LCD_WRITE_REGLH(0x048 >> 1, LCD_REG048,          0); \
  LCD_WRITE_REGLH(0x04A >> 1, LCD_REG04A, LCD_REG04B); \
  LCD_WRITE_REGLH(0x1F0 >> 1, LCD_REG1F0, LCD_REG1F1); \
  LCD_WRITE_REGLH(0x1FC >> 1, LCD_REG1FC,          0)


/*********************************************************************
*
*           Standard config for simulation
*
**********************************************************************
*/
#elif defined WIN32

#define LCD_XSIZE            640   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE            480   /* Y-resolution of LCD, Logical coor. */
#define LCD_VXSIZE           (LCD_XSIZE)
#define LCD_VYSIZE           (LCD_YSIZE * 1)
#define LCD_BITSPERPIXEL      16
#define LCD_CONTROLLER      1300

#define LCD_INIT_CONTROLLER()

/*********************************************************************
*
*           Standard config (Armin board, 13705)
*
**********************************************************************
*/

#else
#define LCD_XSIZE            320   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE            240   /* Y-resolution of LCD, Logical coor. */
#define LCD_BITSPERPIXEL       8
#define LCD_CONTROLLER      1375
#define LCD_SWAP_BYTE_ORDER    0
#define LCD_SWAP_XY            0
#define LCD_MIRROR_X           0

#ifdef NC308          /* Mitsubishi NC308 */
    #define LCD_READ_MEM(Off)            *((U16*)         (0xc00000+(((U32)(Off))<<1)))
    #define LCD_WRITE_MEM(Off,data)      *((U16*)         (0xc00000+(((U32)(Off))<<1)))=data
    #define LCD_READ_REG(Off)            *((volatile U16*)(0xc1ffe0+(((U16)(Off))<<1)))
    #define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0xc1ffe0+(((U16)(Off))<<1)))=data
#elif defined (NC30)  /* Mitsubishi NC30 */
  #define LCD_READ_MEM(Off)              *((U16*)         (0x80000+(((U32)(Off))<<1)))
  #define LCD_WRITE_MEM(Off,data)        *((U16*)         (0x80000+(((U32)(Off))<<1)))=data
  #define LCD_READ_REG(Off)              *((volatile U16*)(0x9ffe0+(((U16)(Off))<<1)))
  #define LCD_WRITE_REG(Off,data)        *((volatile U16*)(0x9ffe0+(((U16)(Off))<<1)))=data
#elif defined (__TID__)   /* IAR target identifier */
  #if (((__TID__ >>8) &0x7f) == 48)  /* IAR MC80 */
    #define LCD_READ_MEM(Off)            *((U16*)         (0xc00000+(((U32)(Off))<<1)))
    #define LCD_WRITE_MEM(Off,data)      *((U16*)         (0xc00000+(((U32)(Off))<<1)))=data
    #define LCD_READ_REG(Off)            *((volatile U16*)(0xc1ffe0+(((U16)(Off))<<1)))
    #define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0xc1ffe0+(((U16)(Off))<<1)))=data
  #else    /* IAR M16C/60 */
    #define LCD_READ_MEM(Off)            *((U16*)         (0x80000+(((U32)(Off))<<1)))
    #define LCD_WRITE_MEM(Off,data)      *((U16*)         (0x80000+(((U32)(Off))<<1)))=data
    #define LCD_READ_REG(Off)            *((volatile U16*)(0x9ffe0+(((U16)(Off))<<1)))
    #define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0x9ffe0+(((U16)(Off))<<1)))=data
  #endif
#elif defined(_CM16C) /* TASKING M16C */
  #define LCD_READ_MEM(Off)              *((U16*)         (0x80000+(((U32)(Off))<<1)))
  #define LCD_WRITE_MEM(Off,data)        *((U16*)         (0x80000+(((U32)(Off))<<1)))=data
  #define LCD_READ_REG(Off)              *((volatile U16*)(0x9ffe0+(((U16)(Off))<<1)))
  #define LCD_WRITE_REG(Off,data)        *((volatile U16*)(0x9ffe0+(((U16)(Off))<<1)))=data
#else
    #define LCD_READ_MEM(Off)        0
    #define LCD_WRITE_MEM(Off,data)
    #define LCD_READ_REG(Off)        0
    #define LCD_WRITE_REG(Off,data)
#endif

/*********************************************************************
*
*                   Define contents of registers
*/

#define LCD_REG0  (0)                                          /* Product code */

#define LCD_REG1  (0x23)                                       /* Mode reg 0.    0 for 4 bit mono LCD */            \
                                                               /*                1 for 8 bit mono LCD */            \
                                                               /*             0x23 for 8 bit color LCD */           \
                 |(1<<2)                                       /*             Mask FPSHIFT during h.non-display */

#define LCD_REG2 ((3<<6)                                       /* Mode reg 1: Bits per pixel 0:1, 1:2, 2:4, 3:8 */  \
                 |(1<<5)                                       /* High performance bit for accel. of CPU access */  \
                 |(1<<4)                                       /* Input clock divide */                             \
                 |(0<<3)                                       /* Display blank */                                  \
                 |(0<<2)                                       /* Frame repeat */                                   \
                 |(0<<1)                                       /* HW video invert enable */                         \
                 |(0<<0))                                      /* SW video invert */

#define LCD_REG3                                               /* Mode reg 2. 0 for 4 bit mono LCD */               \
                  (0<<7)                                       /* LUT bypass */                                     \
                 |(0<<3)                                       /* LCDPWR override */                                \
                 |(0<<2)                                       /* hw power save enable */                           \
                 |(3<<0)                                       /* Software power save :3 = normal operation */

#define LCD_REG4 (LCD_XSIZE/8-1)                               /* horizontal panel size*/
#define LCD_REG5 ((LCD_YSIZE-1)&255)                           /* Vert. panel size, lsb */
#define LCD_REG6 ((LCD_YSIZE-1)>>8)                            /* Vert. panel size, msb */
#define LCD_REG7 (0)                                           /* FPLine start position (TFT only) */
#define LCD_REG8 (31)                                          /* H.non display period   (0 usually O.K.)*/
#define LCD_REG9 (0)                                           /* FPFrame start pos.    (TFT only) */
#define LCD_REGA (0)                                           /* v.non display period  */
#define LCD_REGB (0)                                           /* mod rate register     0: every frame */
#define LCD_REGC (0)                                           /* Screen 1 start lsb    */
#define LCD_REGD (0)                                           /* Screen 1 start msb    */

#define LCD_REG12 (LCD_BITSPERPIXEL*(LCD_VXSIZE-LCD_XSIZE)/16) /* Memory Address offset (usually 0) */
#define LCD_REG13 LCD_REG5                                     /* Vert. screen 1 size, lsb */
#define LCD_REG14 LCD_REG6                                     /* Vert. screen 1 size, msb */

#define LCD_REG1B (0)                                          /* No swivel mode  (use 0xc0 for alt.swivel)  */
#define LCD_REG1C (0x78)                                       /* bytes per line (stride, for swivel mode only)  */

/*********************************************************************
*
*                   Init sequence for 16 bit access
*/

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0)<<8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1)<<8) | (d0))
#endif

#define LCD_INIT_CONTROLLER()                                                                    \
        LCD_WRITE_REGLH(0x00>>1,LCD_REG0, LCD_REG1);                                             \
        LCD_WRITE_REGLH(0x02>>1,LCD_REG2, LCD_REG3);                                             \
        LCD_WRITE_REGLH(0x04>>1,LCD_REG4, LCD_REG5);                                             \
        LCD_WRITE_REGLH(0x06>>1,LCD_REG6, LCD_REG7);                                             \
        LCD_WRITE_REGLH(0x08>>1,LCD_REG8, LCD_REG9);                                             \
        LCD_WRITE_REGLH(0x0a>>1,LCD_REGA, LCD_REGB);                                             \
        LCD_WRITE_REGLH(0x0c>>1,LCD_REGC, LCD_REGD);                                             \
        LCD_WRITE_REG  (0x0e>>1,0x00);                 /* 0, screen 2 start l*/                  \
        LCD_WRITE_REG  (0x10>>1,0x00);                 /* screen 2 start h */                    \
        LCD_WRITE_REGLH(0x12>>1,LCD_REG12, LCD_REG13); /* mem adr. offset, screen 1 vsize(lsb)*/ \
        LCD_WRITE_REGLH(0x14>>1,LCD_REG14, 0);                                                   \
        LCD_WRITE_REGLH(0x1a>>1,0, LCD_REG1B);                                                   \
        LCD_WRITE_REGLH(0x1c>>1,LCD_REG1C, 0)

/*********************************************************************
*
*                   Hardware selection (Segger internal only)
*/

#define TARGET_HARDWARE_137X
#endif

/*********************************************************************
*
*                   Second display (This is for simulation only)
*/
#define LCD_CONTROLLER_1 1300
#define LCD_XSIZE_1      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE_1      (240)   /* Y-resolution of LCD, Logical coor. */

#define LCD_BITSPERPIXEL_1    16


#endif /* LCDCONF_H */

