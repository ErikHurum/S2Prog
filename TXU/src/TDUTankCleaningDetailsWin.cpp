#include "TDUIncludes.h"


const TDUValueTable TDUTankCleaningDetailsWin::TableValues[TDU_WIN_COL]={
	{SVT_PRO_NAME, 120, GUI_TA_LEFT},
	{SVT_TWM_SERIAL_ID, 50, GUI_TA_LEFT},
	{SVT_TWM_ON_OFF_STATUS, 90, GUI_TA_CENTER},
	{SVT_NOT_DEFINED, 20, GUI_TA_RIGHT},
	{SVT_NOT_DEFINED, 20, GUI_TA_RIGHT}
	/*{SVT_PRO_STATUS ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME   ,71,GUI_TA_LEFT},
	{SVT_ULLAGE_UTI ,66,GUI_TA_RIGHT},
	{SVT_VOLPERCENT ,66,GUI_TA_RIGHT},
	{SVT_WEIGHT     ,66,GUI_TA_RIGHT},*/
};


TDUTankCleaningDetailsWin::TDUTankCleaningDetailsWin(vector<PRogramObjectBase*> *pItemVec)
	: TDUGroupWin(*pItemVec, TDU_TANK_CLEANING_DETAILS_WIN, (TDUValueTable*)&TableValues)
{
    ResetWinRefreshTimer(UI_Refresh_Timer_First_Wait_Secs);
}


TDUTankCleaningDetailsWin::~TDUTankCleaningDetailsWin(void)
{
}


void TDUTankCleaningDetailsWin::SetButton(void)
{
	bool Enable[NUMBER_OF_BUTTONS]={
		false,
		false,
		false,
		(bool)!PROPrinter::ObjectSet.empty(),
		false
	};
	ButWindow->EnableButtons(Enable);

	if (!PROTank::TankVector.empty())
	{
		ButWindow->ChangeButtonText(L_WORD87,L_WORD88,L_WORD89,L_WORD237,L_WORD90);
	} 
}



void TDUTankCleaningDetailsWin::ButtonClicked(int btnID)
{
}



void TDUTankCleaningDetailsWin::SetTankToDisplay(PROTank *pTank)
{
	this->pTank = pTank;

	// ObjectVector contains objects which will be displayed:
	ObjectVector.clear();
	ObjectVector.assign(pTank->TankWashingMachineVector.begin(), pTank->TankWashingMachineVector.end());
}


PROTank* TDUTankCleaningDetailsWin::GetTank(void)
{
	return pTank;
}



void TDUTankCleaningDetailsWin::cbEventHandler(WM_MESSAGE * pMsg)
{
	switch ( pMsg->MsgId ) {
	case WM_TIMER:
		if (pMsg->Data.v == hTimer)
		{
            TableUpdate();
			WM_InvalidateWindow(WinHandl);					    // schedule redrawing of this window
			ResetWinRefreshTimer(UI_Refresh_Timer_Interval_Secs);
		}
	default:
		TDUGroupWin::cbEventHandler(pMsg);
		break;
	}
}


/// Should be called at a point in time after TableSetup(void) has been called.
/// Refreshes the contents of the table.
///
void TDUTankCleaningDetailsWin::TableUpdate(void)
{
	AnsiString rowStrings[TDU_WIN_COL];
	unsigned numTwms = ObjectVector.size();

	unsigned numExistingRows = LISTVIEW_GetNumRows(ListViewHandl);
	if (numExistingRows > 0)
	{
		LISTVIEW_DeleteAllRows(ListViewHandl);
	}


	for ( unsigned rowCount = 0; rowCount < numTwms; rowCount++ ) 
	{
		if ( rowCount < numTwms) 
		{
			const char *tmpLstStr[TDU_WIN_COL];
			for ( int j=0; j <TDU_WIN_COL; j++ ) {
				rowStrings[j] = LibGetValue(ValueTable[j].ValueId, ObjectVector[rowCount]);
				tmpLstStr[j] = rowStrings[j].c_str();
			}
			LISTVIEW_AddRow(ListViewHandl,tmpLstStr);
		} else {
			const char *tmpLstStr[] = {"", "", "", "", ""};
			LISTVIEW_AddRow(ListViewHandl,tmpLstStr);
		}
	}
}



void TDUTankCleaningDetailsWin::ResetWinRefreshTimer(int seconds)
{
	int updateTimeMillis = seconds * 1000;

	if (hTimer == 0)
	{
		hTimer = WM_CreateTimer(WinHandl, UI_Refresh_Timer_UserId, updateTimeMillis, 0);
	}
	else
	{
		WM_RestartTimer(hTimer, updateTimeMillis);
	}
}
