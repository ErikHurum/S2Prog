#include <stdio.h>
#include "RTOS.h"               /* embOS include */
#include "GUI.h"
#include "GUI_X.h"
#include "WM.h"
#include "ANPro10Inc.h"
#include "2410addr.h"
#include "TSNVersion.h"

OS_TASK GUITaskHandle;													 /* Task control blocks */
char GUITaskStack[4*4096];
extern short GlobalDeviceHWId;

char RevisionName[4][10]={
	"TCU_R1",
	"TCU_R2",
	"TDU_R1",
	"TDU_R2",
};

#ifdef ANBOOTLOADER
extern "C" {
		// Bitmap Files
	extern const GUI_BITMAP bmScanjetlogo;
}
#endif
/*******************************************************************
*       _GUI_Task
*  This task does the background processing.
*  The MainTask job is to update invalid windows, but other things such as
*  evaluating mouse or touch input may also be done.
*/
void GUI_Task(void)
{
	while ( 1 ) {
		GUI_Exec();											/* Do the background work ... Update windows etc.) */
//		GUI_TOUCH_Exec();
		GUI_X_ExecIdle();						/* Nothing left to do for the moment ... Idle processing */
	}

}


int LCDXSize;
int LCDYSize;

void InitTDUGUI(void)
{
	GUI_Init();
	WM_SetCreateFlags(WM_CF_MEMDEV);   /* Use memory devices on all windows to avoid flicker */

	LCDXSize = LCD_GET_XSIZE();
	LCDYSize = LCD_GET_YSIZE();
//Set Welcome picture:
	GUI_SetBkColor(GUI_LIGHTGRAY);
	GUI_Clear();
	GUI_SetColor(GUI_BLACK);
	GUI_DrawBitmap(&bmScanjetlogo,20,1);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(&GUI_Font24B_ASCII);
	GUI_DispStringHCenterAt("Boot loader",LCDXSize/2,120);
	GUI_SetFont(&GUI_Font16B_ASCII);
	char Buf[80];
	sprintf(Buf,"Revision:  %s.",RevisionName[GlobalDeviceHWId]);
	GUI_DispStringAt(Buf,1,200);
	sprintf(Buf,"Version:%i.%i.%i.%i",VERSION_PROD_NO,VERSION_PACKET,VERSION_BOOT_NEW_FUNC,VERSION_BOOT_BUG_FIX);
	GUI_DispStringAt(Buf,1,220);
  //OS_Delay(1000);
	OS_CREATETASK(&GUITaskHandle, "GUI_TASK", GUI_Task,          10, GUITaskStack);		//Background window update
}

