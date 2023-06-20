#include "TDUIncludes.h"

TDUAlarmWindow::~TDUAlarmWindow(void)
{
}

TDUAlarmWindow::TDUAlarmWindow(void)
{
	UserTouch = false;
	TimerCount =0;
	CurrentPage = 0;
	NumUnitsOnPage = 11;
	ListViewHandl = LISTVIEW_CreateAttached(WinHandl,TDU_ALARM_WIN,0);
	ListHeadHandl = LISTVIEW_GetHeader(ListViewHandl);

	WM_SetId(ListHeadHandl,GUI_ID_HEADER0);
	{
		HeaderInfo Header[]={
			{ L_WORD124 ,108 ,GUI_TA_LEFT},	 // Location
			{ L_WORD170 , 93 ,GUI_TA_LEFT},	 // Description
			{ L_WORD171 , 40 ,GUI_TA_LEFT},	 // Raised
			{ L_WORD172 , 40 ,GUI_TA_LEFT},	 // Reset
		} ;

		for ( int i=0; i< NELEMENTS(Header); i++ ) {
			AddToSKeyList(GUI_ID_HEADER0,i,Header[i].WordKey);
			LISTVIEW_AddColumn(ListViewHandl, Header[i].Width, FindDictionaryWord(Header[i].WordKey).c_str(), Header[i].Align);	// S
		}
	}

	/*
	HEADER_SetTextAlign(ListHeadHandl,0,GUI_TA_LEFT);
	HEADER_SetTextAlign(ListHeadHandl,1,GUI_TA_LEFT);
	HEADER_SetTextAlign(ListHeadHandl,2,GUI_TA_LEFT);
	HEADER_SetTextAlign(ListHeadHandl,3,GUI_TA_LEFT);
	*/
//    HEADER_SetTextAlign(ListHeadHandl,4,GUI_TA_LEFT);
	SetListViewColor();
	TableSetup();
}

void TDUAlarmWindow::SetListViewColor(void)
{
	LISTVIEW_SetBkColor(ListViewHandl  , 0, TDU_C_AL_BACK_ACKNOW);
	LISTVIEW_SetBkColor(ListViewHandl  , 1, TDU_C_AL_BACK_ACKNOW);
	LISTVIEW_SetBkColor(ListViewHandl  , 2, TDU_C_AL_BACK_ACKNOW);
	LISTVIEW_SetTextColor(ListViewHandl, 0, TDU_C_AL_TEXT_ACKNOW);
	LISTVIEW_SetTextColor(ListViewHandl, 1, TDU_C_AL_TEXT_ACKNOW);
	LISTVIEW_SetTextColor(ListViewHandl, 2, TDU_C_AL_TEXT_ACKNOW);
	LISTVIEW_SetSel(ListViewHandl,-1);
}

void TDUAlarmWindow::TableSetup(void)
{
	for ( int Count=0; Count<NumUnitsOnPage; Count++ ) {
		const char *tempString[] = {"", "", "", "", ""};
		LISTVIEW_AddRow(ListViewHandl,tempString);
	}
}

void TDUAlarmWindow::SetButton(void)
{
	//bool EnableButtons[NUMBER_OF_BUTTONS] =
	ButWindow->EnableButtons(true,true,false,true,true);
	ButWindow->ChangeButtonText(L_WORD87,L_WORD88,L_WORD237,L_WORD169,L_WORD18);
}


void TDUAlarmWindow::PWTimer(void)
{
    if ( (AlarmBasic::PROActiveAlarmList.Changed & 1) || ( AlarmBasic::PROAcknowAlarmList.Changed & 1 ) ) {
        //int Align = GUI_TA_HCENTER;
        AnsiString AlMsg;
        AlarmBasic::PROActiveAlarmList.Protect();
        AlarmBasic::PROAcknowAlarmList.Protect();
        if ( !AlarmBasic::PROActiveAlarmList.isEmpty() ) {
            PRONode *TNode = AlarmBasic::PROActiveAlarmList.getHead();
            TNode = TNode->getNext();
            AlarmBasic *TempElement = (AlarmBasic*)TNode->getElement();
            AlMsg = TempElement->Get_CompleteMessage();
        } else if ( !AlarmBasic::PROAcknowAlarmList.isEmpty() ) {
            PRONode *TNode = AlarmBasic::PROAcknowAlarmList.getHead();
            TNode = TNode->getNext();
            AlarmBasic *TempElement = (AlarmBasic*)TNode->getElement();
            AlMsg = TempElement->Get_CompleteMessage();
        } else {
            AlMsg =  FindDictionaryWord(L_WORD173).c_str();	// No Alarm
        }
        AlarmBasic::PROActiveAlarmList.UnProtect();
        AlarmBasic::PROAcknowAlarmList.UnProtect();
        if ( AlMsg.Length()>20 ) {
            BUTTON_SetTextAlign(MainWindow->ButtonAlarm,GUI_TA_LEFT | GUI_TA_VCENTER);
        } else {
            BUTTON_SetTextAlign(MainWindow->ButtonAlarm,GUI_TA_HCENTER | GUI_TA_VCENTER);
        }
        BUTTON_SetText(MainWindow->ButtonAlarm, AlMsg.c_str());
        if ( CurrentWinID == TDU_ALARM_WIN ) {
            AlarmBasic::PROActiveAlarmList.Changed &= ~1;
            AlarmBasic::PROAcknowAlarmList.Changed &= ~1;
            Paintnew();
        }
    }
}
void TDUAlarmWindow::SetColours(int Line, AlarmBasic *AlElement)
{
	GUI_COLOR FgColor = TDU_C_AL_TEXT_ACKNOW;
	GUI_COLOR BkColor = TDU_C_AL_BACK_ACKNOW;
	switch ( AlElement->State ) {
	case AlarmBasic::AlActive: // We have the right state OK
		FgColor = TDU_C_AL_TEXT_ACTIVE;
		BkColor = TDU_C_AL_BACK_ACTIVE;
		break;
	case AlarmBasic::AlAknowledged:
		//FgColor = TDU_C_AL_TEXT_ACTIVE;
		//BkColor = TDU_C_AL_BACK_ACTIVE;
		FgColor = TDU_C_AL_TEXT_ACKNOW;
		BkColor = TDU_C_AL_BACK_ACKNOW;
		break;
	case AlarmBasic::AlIdle:
		FgColor = TDU_C_AL_TEXT_ACKNOW;
		BkColor = TDU_C_AL_BACK_ACKNOW;
		break;
	}
	AnsiString Location  = AlElement->Get_Location();
	AnsiString Type          = AlElement->Get_Message();
	AnsiString Raised        = AlElement->GetRisedTime();
	AnsiString Reset         = AlElement->GetResetTime();
	LISTVIEW_SetItemTextWithColor(ListViewHandl, 0, Line, Location.c_str(),FgColor, BkColor);
	LISTVIEW_SetItemTextWithColor(ListViewHandl, 1, Line, Type.c_str(),FgColor, BkColor);
	LISTVIEW_SetItemTextWithColor(ListViewHandl, 2, Line, Raised.c_str(),FgColor, BkColor);
	LISTVIEW_SetItemTextWithColor(ListViewHandl, 3, Line, Reset.c_str(),FgColor, BkColor);

}

void TDUAlarmWindow::Paintnew(void)
{
	NumberOfUnits = AlarmBasic::PROActiveAlarmList.Size()+AlarmBasic::PROAcknowAlarmList.Size();
	AlarmBasic::PROActiveAlarmList.Protect();
	int Cnt = 0;
	int LVCount = 0;
	bool ChangedFlag = false;
	bool CorrectSide = false;
	PageCount = NumberOfUnits/NumUnitsOnPage;
	NumberOfUnitsLastPage = NumberOfUnits - PageCount*NumUnitsOnPage;
	if ( NumberOfUnitsLastPage ) PageCount++;

	if ( !AlarmBasic::PROActiveAlarmList.isEmpty() ) {
		int ActiveAlarmListSize = AlarmBasic::PROActiveAlarmList.Size();
		PRONode *TNode = AlarmBasic::PROActiveAlarmList.getHead();
		TNode = TNode->getNext();
		AlarmBasic *TempElement = (AlarmBasic*)TNode->getElement();

		for ( ; Cnt < NumUnitsOnPage*CurrentPage && Cnt < ActiveAlarmListSize; Cnt++ ) {
			TNode = TNode->getNext();
		}
		if ( Cnt < ActiveAlarmListSize )CorrectSide = true;

		for ( ;!ChangedFlag && Cnt<ActiveAlarmListSize;Cnt++ ) {
			TempElement = (AlarmBasic*)TNode->getElement();
			AlarmBasic::PROActiveAlarmList.UnProtect();
			SetColours(LVCount++,TempElement);
			AlarmBasic::PROActiveAlarmList.Protect();
			ChangedFlag = (bool)(AlarmBasic::PROActiveAlarmList.Changed & 1 );
			TNode = TNode->getNext();
		}
	}
	AlarmBasic::PROActiveAlarmList.UnProtect();
	if ( !ChangedFlag ) {
		AlarmBasic::PROAcknowAlarmList.Protect();
		int TotalListSize = AlarmBasic::PROActiveAlarmList.Size()+AlarmBasic::PROAcknowAlarmList.Size();
		if ( !AlarmBasic::PROAcknowAlarmList.isEmpty() ) {
			int AcknowAlarmListSize = AlarmBasic::PROAcknowAlarmList.Size();
			PRONode *TNode = AlarmBasic::PROAcknowAlarmList.getHead();
			TNode = TNode->getNext();
			AlarmBasic *TempElement = (AlarmBasic*)TNode->getElement();

			if ( !CorrectSide ) {
				for ( ; Cnt < NumUnitsOnPage*CurrentPage && Cnt < TotalListSize; Cnt++ ) {
					TNode = TNode->getNext();
				}
			}

			for ( ;!ChangedFlag && Cnt < TotalListSize; Cnt++ ) {
				TempElement = (AlarmBasic*)TNode->getElement();
				AlarmBasic::PROAcknowAlarmList.UnProtect();
				SetColours(LVCount++,TempElement);
				AlarmBasic::PROAcknowAlarmList.Protect();
				ChangedFlag = (bool)(AlarmBasic::PROAcknowAlarmList.Changed & 1 );
				TNode = TNode->getNext();
			}
		}
		AlarmBasic::PROAcknowAlarmList.UnProtect();
		for ( ;LVCount<NumUnitsOnPage;LVCount++ ) {
			LISTVIEW_SetItemTextWithColor(ListViewHandl, 0, LVCount, "",TDU_C_AL_TEXT_ACKNOW, TDU_C_AL_BACK_ACKNOW);
			LISTVIEW_SetItemTextWithColor(ListViewHandl, 1, LVCount, "",TDU_C_AL_TEXT_ACKNOW, TDU_C_AL_BACK_ACKNOW);
			LISTVIEW_SetItemTextWithColor(ListViewHandl, 2, LVCount, "",TDU_C_AL_TEXT_ACKNOW, TDU_C_AL_BACK_ACKNOW);
			LISTVIEW_SetItemTextWithColor(ListViewHandl, 3, LVCount, "",TDU_C_AL_TEXT_ACKNOW, TDU_C_AL_BACK_ACKNOW);
		}
	}
}

void TDUAlarmWindow::ButtonClicked(int ButtID)
{
	switch ( ButtID ) {
	case TDU_BUTTON_ID_PW1:
		if ( CurrentPage<=0 ) {
			//	CurrentPage = PageCount-1;
			CurrentPage = 0;
		} else {
			CurrentPage--;
		}
		TimedOut = false;
		TimerCount=50;
		Paintnew();
		SetGuiEvent(PWEventHandl,1,&aTCB[1]);
		break;
	case TDU_BUTTON_ID_PW2:
		if ( CurrentPage >= (PageCount-1) ) {
//					CurrentPage = 0;
			CurrentPage = (PageCount-1);
		} else {
			CurrentPage++;
		}
		TimedOut = false;
		TimerCount=50;
		Paintnew();
		SetGuiEvent(PWEventHandl,1,&aTCB[1]);
		break;
	case TDU_BUTTON_ID_PW3:
		AckAllButtonClicked();
		AlarmBasic::AlarmSilence = true;
		break;
	case TDU_BUTTON_ID_PW4:
		AckButtonClicked(AlarmBasic::LocalResetCnt++);
		AlarmBasic::AlarmSilence = true;
		break;
	case TDU_BUTTON_ID_PW5:
		MainWindow->SetPreviousWindow();
		break;
	}
}

void TDUAlarmWindow::AckAllButtonClicked(void)
{
	AlarmBasic::AckAll();
}

void TDUAlarmWindow::AckButtonClicked(int ButtID)
{
   // AnsiString Text2;
	AlarmBasic::PROActiveAlarmList.Protect();
	if ( !AlarmBasic::PROActiveAlarmList.isEmpty() ) {
		AlarmBasic *TempElement;
		PRONode *TNode = AlarmBasic::PROActiveAlarmList.getHead();
		TNode = TNode->getNext();
		int ListSize = AlarmBasic::PROActiveAlarmList.Size();
		int index = 0;
		while ( index<ButtID && index<ListSize ) {
			index++;
			TNode = TNode->getNext();
		}
		if ( index<ListSize ) {
            //  We located the alarm
            TempElement = (AlarmBasic*)TNode->getElement();

			if ( Master || AlarmCriticalComFailure::ComFailure )
				TempElement->MoveAlarmToAknowledge();
			else
				TempElement->SendData(CMD_PRO_ALARM_ACK);
		}
	}
	AlarmBasic::PROActiveAlarmList.UnProtect();
}

void TDUAlarmWindow::cbEventHandler(WM_MESSAGE * pMsg)
{
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	int NCode, Id;
	case WM_TOUCH:
		{
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch ( Id ) {
			case 1:
				UserTouch = true;
				break;
			}
		}
		break;
	case WM_TOUCH_CHILD:
		{
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch ( Id ) {
			case 1:
				UserTouch = true;
				break;
			}
		}
		break;
	case WM_NOTIFY_PARENT:
		{
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch ( NCode ) {
			case WM_NOTIFICATION_CLICKED:
//					case WM_NOTIFICATION_RELEASED:		/* React only if released */
				{
					LISTVIEW_SetSel(ListViewHandl,-1);
					UserTouch = true;
				}
				break;
			case WM_NOTIFICATION_VALUE_CHANGED:
				{
/*							if ( XScrollPos != SCROLLBAR_GetValue(ScrollHandl) ) {
								XScrollPos = SCROLLBAR_GetValue(ScrollHandl);
								WM_MoveTo(MainWinHandl,0,0-XScrollPos*LineHeight+2*LineHeight);
							}
*/}
				break;
			}
		}
		break;
	case WM_PAINT:
		CurrentPage = 0;
		Paintnew();
		break;
	case MESSAGE_LANGUAGE_CHANGE:
		UpdateLanguage();
		break;
	case WM_CREATE:
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}
