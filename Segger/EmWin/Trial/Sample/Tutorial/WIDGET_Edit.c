/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : WIDGET_Edit.c
Purpose     : Example demonstrating the use of a EDIT widget
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "EDIT.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GUI_NUMBYTES   1500 /* Available memory in bytes for emWin */
#define GUI_BLOCKSIZE    32 /* Average memory block size */

/*******************************************************************
*
*       static code
*
********************************************************************
*/

/*******************************************************************
*
*       _DemoEdit
*
  Edit a string until ESC or ENTER is pressed
*/
static void _DemoEdit(void) {
  EDIT_Handle hEdit;
  char aBuffer[28];
  int Key;
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WIDGET_Edit - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringHCenterAt("Use keyboard to modify string...", 160, 90);
  /* Create edit widget */
  hEdit = EDIT_Create( 50, 110, 220, 25, ' ', sizeof(aBuffer), 0 );
  /* Modify edit widget */
  EDIT_SetText(hEdit, "Press <ENTER> when done...");
  EDIT_SetFont(hEdit, &GUI_Font8x16);
  EDIT_SetTextColor(hEdit, 0, GUI_RED);
  /* Set keyboard focus to edit widget */
  WM_SetFocus(hEdit);
  /* Handle keyboard until ESC or ENTER is pressed */
  do {
    WM_Exec();
    Key = GUI_GetKey();
  } while ((Key != GUI_KEY_ENTER) && (Key != GUI_KEY_ESCAPE));
  /* Fetch result from edit widget */
  if (Key == GUI_KEY_ENTER) {
    EDIT_GetText(hEdit, aBuffer, sizeof(aBuffer));
  }
  /* Delete the edit widget */
  EDIT_Delete(hEdit);
  GUI_ClearRect(0, 50, 319, 239);
  /* Display the changed string */
  if (Key == GUI_KEY_ENTER) {
    GUI_Delay(250);
    GUI_DispStringHCenterAt("The string you have modified is:", 160, 90);
    GUI_DispStringHCenterAt(aBuffer, 160, 110);
    GUI_Delay(3000);
    GUI_ClearRect(0, 50, 319, 239);
  }
  GUI_Delay(500);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_Init();
  while (1) {
    _DemoEdit();
  }
}

/*********************************************************************
*
*       GUI_X_Config
*/
void GUI_X_Config(void) {
  static U32 aMemory[GUI_NUMBYTES >> 2];                      /* Memory block for emWin, 32bit aligned */
  GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES & 0xFFFFFFFC); /* Assign it to emWin */
  GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);                    /* Set average memory block size */
}

/*************************** End of file ****************************/

