#include "TDUIncludes.h"

void DisplayMessage(AnsiString Heading, AnsiString Message)
{
	switch ( CurrentDeviceId ) {
		case DEVICE_TCU:	// TCU
			break;
		case DEVICE_TDU:	// TDU
		case DEVICE_TDU_SIMULATOR:
			ListMessageBox->Exec(0, Heading, Message);
			break;
	}
}

/*********************************************************************
*				Added by EHS 5/11/03
*       LISTVIEW_SetItemTextWithColor
*/
extern "C"{
	void LISTVIEW_SetItemTextWithColor(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, const char *MyStr, GUI_COLOR FgColor, GUI_COLOR BkColor)
	{
		if ( hObj ) {
			LISTVIEW_SetItemText(hObj, Column, Row, MyStr);
			LISTVIEW_SetItemTextColor(hObj,Column, Row, 0, FgColor);
			LISTVIEW_SetItemBkColor(hObj,Column,Row, 0, BkColor);
			LISTVIEW_SetItemTextColor(hObj,Column, Row, 2, BkColor);
			LISTVIEW_SetItemBkColor(hObj,Column,Row, 2, FgColor);
		}
	}
}


