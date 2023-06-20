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
File        : LCDConf_13A03_C8_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE      320      /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      240      /* Y-resolution of LCD, Logical coor. */

#define LCD_CONTROLLER 1304

#define LCD_SWAP_BYTE_ORDER 1
#define LCD_BITSPERPIXEL    8
#define LCD_SWAP_RB         1
#define LCD_USE_BITBLT      1

#define REG_ADDR 0x00000 /* TBD */
#define MEM_ADDR 0x00000 /* TBD */

/*********************************************************************
*
*       Full bus configuration
*
**********************************************************************
*/

#define LCD_READ_MEM(Off)            *((U16 *)         (MEM_ADDR + (((U32)(Off)) << 1)))
#define LCD_WRITE_MEM(Off,Data)      *((U16 *)         (MEM_ADDR + (((U32)(Off)) << 1))) = Data
#define LCD_READ_REG(Off)            *((volatile U16 *)(REG_ADDR + (((U32)(Off)) << 1)))
#define LCD_WRITE_REG(Off,Data)      *((volatile U16 *)(REG_ADDR + (((U32)(Off)) << 1))) = Data

/*********************************************************************
*
*       Init sequence for 16 bit access (LCD)
*
**********************************************************************
*/

#define LCD_INIT_CONTROLLER() \
  _WriteReg32(0x14, 0x00000000); /* Power Save Configuration Register                  */  \
  _WriteReg32(0x64, 0x28D70000); /* GPIO Status and Control Register                   */  \
  _WriteReg32(0x04, 0x00000000); /* Memory Clock Configuration Register                */  \
  _WriteReg32(0x08, 0x00000043); /* Pixel Clock Configuration Register                 */  \
  _WriteReg32(0x0C, 0x000000D0); /* Panel Type and MOD Rate Register                   */  \
  _WriteReg32(0x10, 0x00000008); /* Display Settings Register                          */  \
  _WriteReg32(0x20, 0x0000002B); /* Horizontal Total Register                          */  \
  _WriteReg32(0x24, 0x00000027); /* Horizontal Display Period Register                 */  \
  _WriteReg32(0x28, 0x00000000); /* Horizontal Display Period Start Position Register  */  \
  _WriteReg32(0x2C, 0x00870156); /* FPLINE Register                                    */  \
  _WriteReg32(0x30, 0x000000FA); /* Vertical Total Register                            */  \
  _WriteReg32(0x34, 0x000000EF); /* Vertical Display Period Register                   */  \
  _WriteReg32(0x38, 0x00000000); /* Vertical Display Period Start Position Register    */  \
  _WriteReg32(0x3C, 0x00800000); /* FPFRAME Register                                   */  \
  _WriteReg32(0x40, 0x00000000); /* Main Window Display Start Address Register         */  \
  _WriteReg32(0x44, 0x00000050); /* Main Window Line Address Offset Register           */  \
  _WriteReg32(0x50, 0x00000000); /* PIP+ Window Display Start Address Register         */  \
  _WriteReg32(0x54, 0x00000050); /* PIP+ Window Line Address Offset Register           */  \
  _WriteReg32(0x58, 0x00000000); /* PIP+ Window X Positions Register                   */  \
  _WriteReg32(0x5C, 0x00000000); /* PIP+ Window Y Positions Register                   */  \
  _WriteReg32(0x60, 0x00000000); /* Special Purpose Register                           */  \
  _WriteReg32(0x70, 0x00000000); /* PWM Clock Configuration Register                   */  \
  _WriteReg32(0x74, 0x00000000); /* PWMOUT Duty Cycle Register                         */  \
  _WriteReg32(0x80, 0x00000000); /* Scratch Pad A Register                             */  \
  _WriteReg32(0x84, 0x00000000); /* Scratch Pad B Register                             */  \
  _WriteReg32(0x88, 0x00000000); /* Scratch Pad C Register                             */  \
  _WriteReg32(0xFE, 0x00000032); /* LCD Panel Power On Delay (in ms)                   */  \
  _WriteReg32(0x64, 0x28D70001); /* GPIO Status and Control Register                   */  \
  _WriteReg32(0x14, 0x00000000)  /* Power Save Configuration Register                  */

#endif /* LCDCONF_H */
