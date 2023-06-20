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
Purpose     : sAMPLE configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

#define LCD_ALLOW_NON_OPTIMIZED_MODE 1

/*********************************************************************
*
*       Equal for all layers
*/
#define _CONTROLLER          66706
#define _BITSPERPIXEL           16
#define _SWAP_RB                 1
#define _XSIZE                 240
#define _YSIZE                 400

/*********************************************************************
*
*       Layer 0
*/
#define LCD_CONTROLLER_0          _CONTROLLER
#define LCD_BITSPERPIXEL_0        _BITSPERPIXEL
#define LCD_SWAP_RB_0             _SWAP_RB
#define LCD_XSIZE_0               _XSIZE
#define LCD_YSIZE_0               _YSIZE
#define LCD_MIRROR_X_0           1
#define LCD_MIRROR_Y_0           0
#define LCD_SWAP_XY_0            0

/*********************************************************************
*
*       Layer 1
*/
#define LCD_CONTROLLER_1          _CONTROLLER
#define LCD_BITSPERPIXEL_1        _BITSPERPIXEL
#define LCD_SWAP_RB_1             _SWAP_RB
#define LCD_XSIZE_1               _YSIZE
#define LCD_YSIZE_1               _XSIZE
#define LCD_MIRROR_X_1           0
#define LCD_MIRROR_Y_1           0
#define LCD_SWAP_XY_1            1

/*********************************************************************
*
*       Layer 2
*/
#define LCD_CONTROLLER_2          _CONTROLLER
#define LCD_BITSPERPIXEL_2        _BITSPERPIXEL
#define LCD_SWAP_RB_2             _SWAP_RB
#define LCD_XSIZE_2               _XSIZE
#define LCD_YSIZE_2               _YSIZE
#define LCD_MIRROR_X_2           0
#define LCD_MIRROR_Y_2           1
#define LCD_SWAP_XY_2            0

/*********************************************************************
*
*       Layer 3
*/
#define LCD_CONTROLLER_3          _CONTROLLER
#define LCD_BITSPERPIXEL_3        _BITSPERPIXEL
#define LCD_SWAP_RB_3             _SWAP_RB
#define LCD_XSIZE_3               _YSIZE
#define LCD_YSIZE_3               _XSIZE
#define LCD_MIRROR_X_3           1
#define LCD_MIRROR_Y_3           1
#define LCD_SWAP_XY_3            1

/*********************************************************************
*
*       Prototypes of interface routines
*/
void LCD_X_Write01(char c);
void LCD_X_Write00(char c);
void LCD_X_WriteM01(char * pData, int NumBytes);
void LCD_X_WriteM00(char * pData, int NumBytes);
char LCD_X_Read00(void);
char LCD_X_Read01(void);
void LCD_X_ReadM01 (char * pData, int NumBytes);

/*********************************************************************
*
*       Use the same interface routines for all layers
*/
#define LCD_WRITE_A0_0(Byte)            LCD_X_Write00(Byte)
#define LCD_WRITE_A1_0(Byte)            LCD_X_Write01(Byte)
#define LCD_WRITEM_A0_0(Byte, NumBytes) LCD_X_WriteM00(Byte, NumBytes)
#define LCD_WRITEM_A1_0(Byte, NumBytes) LCD_X_WriteM01(Byte, NumBytes)
#define LCD_READ_A0_0(Byte)             Byte = LCD_X_Read00()
#define LCD_READ_A1_0(Byte)             Byte = LCD_X_Read01()
#define LCD_READM_A1_0(Byte, NumBytes)  LCD_X_ReadM01(Byte, NumBytes)

#define LCD_WRITE_A0_1(Byte)            LCD_X_Write00(Byte)
#define LCD_WRITE_A1_1(Byte)            LCD_X_Write01(Byte)
#define LCD_WRITEM_A0_1(Byte, NumBytes) LCD_X_WriteM00(Byte, NumBytes)
#define LCD_WRITEM_A1_1(Byte, NumBytes) LCD_X_WriteM01(Byte, NumBytes)
#define LCD_READ_A0_1(Byte)             Byte = LCD_X_Read00()
#define LCD_READ_A1_1(Byte)             Byte = LCD_X_Read01()
#define LCD_READM_A1_1(Byte, NumBytes)  LCD_X_ReadM01(Byte, NumBytes)

#define LCD_WRITE_A0_2(Byte)            LCD_X_Write00(Byte)
#define LCD_WRITE_A1_2(Byte)            LCD_X_Write01(Byte)
#define LCD_WRITEM_A0_2(Byte, NumBytes) LCD_X_WriteM00(Byte, NumBytes)
#define LCD_WRITEM_A1_2(Byte, NumBytes) LCD_X_WriteM01(Byte, NumBytes)
#define LCD_READ_A0_2(Byte)             Byte = LCD_X_Read00()
#define LCD_READ_A1_2(Byte)             Byte = LCD_X_Read01()
#define LCD_READM_A1_2(Byte, NumBytes)  LCD_X_ReadM01(Byte, NumBytes)

#define LCD_WRITE_A0_3(Byte)            LCD_X_Write00(Byte)
#define LCD_WRITE_A1_3(Byte)            LCD_X_Write01(Byte)
#define LCD_WRITEM_A0_3(Byte, NumBytes) LCD_X_WriteM00(Byte, NumBytes)
#define LCD_WRITEM_A1_3(Byte, NumBytes) LCD_X_WriteM01(Byte, NumBytes)
#define LCD_READ_A0_3(Byte)             Byte = LCD_X_Read00()
#define LCD_READ_A1_3(Byte)             Byte = LCD_X_Read01()
#define LCD_READM_A1_3(Byte, NumBytes)  LCD_X_ReadM01(Byte, NumBytes)

/*********************************************************************
*
*       Initialization
*/
#define DELAY(Cnt) { volatile U32 i, j; j = Cnt << 8; for (i = 0; i < j; i++); }

#define INIT_CONTROLLER() \
  DELAY(10);                                                                             \
  LCD_X_Init();                                                                          \
  DELAY(10);                                                                             \
  LCD_WRITE_A0(0xC0); LCD_WRITE_A1(0x00); /* Internal EEPROM */                          \
  LCD_WRITE_A0(0xC0); LCD_WRITE_A1(0x02); /* Internal EEPROM */                          \
  DELAY(10);                                                                             \
  LCD_WRITE_A0(0xC0); LCD_WRITE_A1(0x00); /* Internal EEPROM */                          \
  LCD_WRITE_A0(0x68); LCD_WRITE_A1(0x41); /* COM-pp */                                   \
  LCD_WRITE_A0(0x69); LCD_WRITE_A1(0x7D); /* COM-center */                               \
  LCD_WRITE_A0(0x01); LCD_WRITE_A1(0x02); /* 8bit 8/8 transfer */                        \
  LCD_WRITE_A0(0x08); LCD_WRITE_A1(0x00); /* Normally black */                           \
  LCD_WRITE_A0(0x10); LCD_WRITE_A1(0xF0); /* Panel X-size=240 */                         \
  LCD_WRITE_A0(0x11); LCD_WRITE_A1(0x90); /* Panel Y-size=400 */                         \
  LCD_WRITE_A0(0x12); LCD_WRITE_A1(0x01); /* Panel Y-size=400 */                         \
  LCD_WRITE_A0(0x1E); LCD_WRITE_A1(0x50); /* Number of vertical line=400 */              \
  LCD_WRITE_A0(0x1D); LCD_WRITE_A1(0x07); /* RAM write direction :landscape */           \
  LCD_WRITE_A0(0x1A); LCD_WRITE_A1(0xEF); /* RAM pointer X */                            \
  LCD_WRITE_A0(0x1B); LCD_WRITE_A1(0x8F); /* RAM pointer Y */                            \
  LCD_WRITE_A0(0x1C); LCD_WRITE_A1(0x01); /* RAM pointer Y */                            \
  LCD_WRITE_A0(0x30); LCD_WRITE_A1(0x81); /* Select the display-RAM data */              \
  LCD_WRITE_A0(0x33); LCD_WRITE_A1(0x02); /* Non-display data color */                   \
  LCD_WRITE_A0(0x42); LCD_WRITE_A1(0x70); /* Vertical front poach=112h */                \
  LCD_WRITE_A0(0x43); LCD_WRITE_A1(0x01); /* Vertical back poach=1h */                   \
  LCD_WRITE_A0(0x44); LCD_WRITE_A1(0x3F); /* H scan interval=96clock */                  \
  LCD_WRITE_A0(0x45); LCD_WRITE_A1(0x14); /* GSP start position=10clock */               \
  LCD_WRITE_A0(0x46); LCD_WRITE_A1(0x0F); /* GCK start position=15clock */               \
  LCD_WRITE_A0(0x48); LCD_WRITE_A1(0x03); /* COM inversion position=3clock */            \
  LCD_WRITE_A0(0x4A); LCD_WRITE_A1(0x01); /* Signal setting */                           \
  LCD_WRITE_A0(0x4B); LCD_WRITE_A1(0xA8); /* SSD setting */                              \
  LCD_WRITE_A0(0x4C); LCD_WRITE_A1(0x12); /* ASW start position=18clock */               \
  LCD_WRITE_A0(0x5A); LCD_WRITE_A1(0x00); /* Battery pull-out detection off */           \
  LCD_WRITE_A0(0x62); LCD_WRITE_A1(0x52); /* ASW width10, interval2clock */              \
  LCD_WRITE_A0(0x65); LCD_WRITE_A1(0x02); /* AMP bias current setting */                 \
  LCD_WRITE_A0(0x66); LCD_WRITE_A1(0x06); /* VGM5.2V */                                  \
  LCD_WRITE_A0(0x6A); LCD_WRITE_A1(0x02); /* VCOM output */                              \
  LCD_WRITE_A0(0x81); LCD_WRITE_A1(0x44); /* VR,VS boost clock setting */                \
  LCD_WRITE_A0(0x82); LCD_WRITE_A1(0x2D); /* DCK,DCKB timing setting */                  \
  LCD_WRITE_A0(0x83); LCD_WRITE_A1(0x25); /* DCDC Dual, AVR,5.2V,DCDC drivability=min */ \
  LCD_WRITE_A0(0x84); LCD_WRITE_A1(0x17); /* VR setting */                               \
  LCD_WRITE_A0(0x85); LCD_WRITE_A1(0x27); /* DCDC Dual, AVS5.4V,DCDC drivability=min */  \
  LCD_WRITE_A0(0x86); LCD_WRITE_A1(0x17); /* VS setting */                               \
  LCD_WRITE_A0(0x90); LCD_WRITE_A1(0x25); /* Auto ON timing setting */                   \
  LCD_WRITE_A0(0x91); LCD_WRITE_A1(0x05); /* Auto ON/OFF setting(1V) */                  \
  LCD_WRITE_A0(0x92); LCD_WRITE_A1(0x15); /* Auto OFF timing setting */                  \
  LCD_WRITE_A0(0x31); LCD_WRITE_A1(0x01); /* VAL */                                      \
  LCD_WRITE_A0(0x19); LCD_WRITE_A1(0x01); /* Window access mode */                       \
  LCD_WRITE_A0(0x3E); LCD_WRITE_A1(0x01); /* Auto ON sequence */                         \
  DELAY(120)

#define LCD_INIT_CONTROLLER_0()   INIT_CONTROLLER()
#define LCD_INIT_CONTROLLER_1()   INIT_CONTROLLER()
#define LCD_INIT_CONTROLLER_2()   INIT_CONTROLLER()
#define LCD_INIT_CONTROLLER_3()   INIT_CONTROLLER()

#endif /* LCDCONF_H */

