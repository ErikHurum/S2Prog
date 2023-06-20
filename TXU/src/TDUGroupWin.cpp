#include "TDUIncludes.h"

const int TDUGroupWin::NumUnitsOnPage=11;

TDUGroupWin::~TDUGroupWin(void)
{
	delete ValueTable;
}


TDUGroupWin::TDUGroupWin(vector<PRogramObjectBase*> ObjVector, int WinId, TDUValueTable *DefValTable)
{
//Initiation:
	DefValueTable  = DefValTable;
	ValueTable     = new TDUValueTable[TDU_WIN_COL];
	memcpy(ValueTable,DefValTable,sizeof(TDUValueTable)*TDU_WIN_COL);
	*ValueTable    = *DefValueTable;
	UserTouch      = false;
	TimerCount     = 0;
	CurrentPage    = 0;
	// PageSize     = NumUnitsOnPage*LineHeight;
	//ObjectSet
	ObjectVector = ObjVector;
	if ( !ObjectVector.empty() ) {
		NumberOfUnits = ObjectVector.size();
		NumberOfPages = NumberOfUnits/NumUnitsOnPage;
		NumberOfUnitsLastPage = NumberOfUnits - NumberOfPages*NumUnitsOnPage;
		if ( NumberOfUnitsLastPage ) NumberOfPages++;
		ListViewHandl = LISTVIEW_CreateAttached(WinHandl,WinId,0);
		ListHeadHandl = LISTVIEW_GetHeader(ListViewHandl);
		for ( int j=0; j < TDU_WIN_COL; j++ ) {
			AnsiString vname = LibGetValue(SVT_VALUE_NAME, DefValTable[j].ValueId, ObjectVector[0],0);
			LISTVIEW_AddColumn(ListViewHandl, DefValTable[j].PixelWidth, vname.c_str(), DefValTable[j].Align);
			HEADER_SetTextAlign(ListHeadHandl,j,GUI_TA_LEFT);
		}
		SetListViewColor();
		TableSetup();
	}
}

void TDUGroupWin::SetListViewColor(void)
{
	LISTVIEW_SetBkColor(ListViewHandl, 0, BackColor);
	LISTVIEW_SetBkColor(ListViewHandl, 1, TextColor);
	LISTVIEW_SetBkColor(ListViewHandl, 2, TextColor);
	LISTVIEW_SetTextColor(ListViewHandl,0, TextColor);
	LISTVIEW_SetTextColor(ListViewHandl,1, BackColor);
	LISTVIEW_SetTextColor(ListViewHandl,2, BackColor);
}

void TDUGroupWin::TableSetup(void)
{
	AnsiString Str[TDU_WIN_COL];
	for ( unsigned Count = 0; Count<NumUnitsOnPage; Count++ ) {
		if ( Count<ObjectVector.size() ) {
			const char *tmpLstStr[TDU_WIN_COL];
			for ( int j=0; j <TDU_WIN_COL; j++ ) {
				Str[j] = LibGetValue(ValueTable[j].ValueId, ObjectVector[Count]);
				tmpLstStr[j] = Str[j].c_str();
			}
			LISTVIEW_AddRow(ListViewHandl,tmpLstStr);
		} else {
			const char *tmpLstStr[] = {"", "", "", "", ""};
			LISTVIEW_AddRow(ListViewHandl,tmpLstStr);
		}
	}
}

void TDUGroupWin::SetButton(void)
{
	bool Enable[NUMBER_OF_BUTTONS]={
		(bool)(NumberOfPages>1),
		(bool)(NumberOfPages>1),
		true,
		(bool)!PROPrinter::ObjectSet.empty(),
		true
	};
	ButWindow->EnableButtons(Enable);
	if ( !ObjectVector.empty() ) {
		if ( !PROPrinter::ObjectSet.empty() ) {
			ButWindow->ChangeButtonText(L_WORD87,L_WORD88,L_WORD89,L_WORD467,L_WORD90);
		} else {
			ButWindow->ChangeButtonText(L_WORD87,L_WORD88,L_WORD89,L_WORD237,L_WORD90);
		}
		But5LangKey = L_WORD90 ;
		UserTouch = false;
		TimedOut = false;
		TimerCount=50;
		SetListViewColor();
		SetGuiEvent(PWEventHandl,1,&aTCB[1]);
	} else {
	}
	PaintnewHeading();
}

void TDUGroupWin::PWTimer(void)
{
	if ( !ObjectVector.empty() ) {
		TimerCount++;
		Paintnew();
	}
}

void TDUGroupWin::Paintnew(void)
{
	if ( !ObjectVector.empty() ) {
		if ( UserTouch ) {
			TimedOut = false;
			TimerCount = 0;
			UserTouch = false;
		} else if ( TimerCount>=4 && !TimedOut ) {
			TimedOut = true;
			TimerCount = 0;
			LISTVIEW_SetSel(ListViewHandl,-1);
		}
		unsigned Index;
		if ( (CurrentPage+1)==NumberOfPages && NumberOfPages>1) {
			Index = ObjectVector.size()- NumUnitsOnPage;
		} else {
			Index = CurrentPage*NumUnitsOnPage;
		}

		for ( unsigned Count=0;!( PhysKeyPressed & TOUCH_PRESWIN_FLAG) && Count < 11 ;Count++,Index++ ) {
			if ( Index < ObjectVector.size() ) {
				for ( int j=0; j<TDU_WIN_COL; j++ ) {
					int ValueId = ValueTable[j].ValueId;
					AnsiString str = LibGetValue(ValueId, ObjectVector[Index]);
					switch (ValueId) {
					case SVT_PRO_STATUS:
						{
							int color = TDU_C_AL_BACK_ACTIVE;
							if ( (!str.compare("A")) || (!str.compare("E")) )	color = TDU_C_AL_BACK_ACTIVE;
							if ( !str.compare("W") ) color = TDU_C_AL_BACK_WARNING;
							LISTVIEW_SetItemTextWithColor(ListViewHandl, j, Count, str.c_str(),color, BackColor);
						}
						break;
					case SVT_INTERFACE:
						{
							PROTank *TnkPtr = (PROTank*)ObjectVector[Index];
							int color;
							switch (TnkPtr->HasWater) {
							default: color = TextColor;
								break;
							case WSENSOR_NO_SENSOR:color = GUI_YELLOW;break;
							case WSENSOR_CARGO    :color = GUI_BROWN; break;
							case WSENSOR_WATER    :color = GUI_BLUE;  break;
							case WSENSOR_EMPTY    :color = GUI_GREEN; break;
							case WSENSOR_LOW_LEVEL:color = GUI_YELLOW;break;
							case WSENSOR_DISABLE  :color = GUI_YELLOW;break;
							case WSENSOR_FAILURE  :color = GUI_RED;   break;
							}
							LISTVIEW_SetItemTextWithColor(ListViewHandl, j, Count, str.c_str(),color, BackColor);
						}
						break;
					default:
						LISTVIEW_SetItemTextWithColor(ListViewHandl, j, Count, str.c_str(),TextColor, BackColor);
						//LISTVIEW_SetItemText(ListViewHandl, j, Count, str.c_str());
						break;
					}
				}
			} else {
				for ( int j=0; j<TDU_WIN_COL; j++ ) {
					LISTVIEW_SetItemText(ListViewHandl, j, Count, "");
				}
			}
		}
	}
}

void TDUGroupWin::PaintnewHeading(void)
{
	if ( !ObjectVector.empty() ) {
		for ( int i=0; i<TDU_WIN_COL; i++ ) {
			AnsiString vname;
			int ErrorStatus;
			vname = LibGetValue(SVT_VALUE_NAME, ValueTable[i].ValueId, ObjectVector[0], 0,&ErrorStatus);
			if ( ErrorStatus == GETVAL_ERROR ) {
				ValueTable[i].ValueId = DefValueTable[i].ValueId;
				vname = LibGetValue(SVT_VALUE_NAME, ValueTable[i].ValueId, ObjectVector[0], 0,&ErrorStatus);
			}
			HEADER_SetItemText(ListHeadHandl,i,vname.c_str());
		}
		WM_InvalidateWindow(ListHeadHandl);
	}
}

bool TDUGroupWin::SetupWin(void)
{
	bool Found = false;
	if ( TimedOut ) {
		AnsiString Text1(FindDictionaryWord(L_WORD165).c_str());	// Detail view warning:
		AnsiString Text2(FindDictionaryWord(L_WORD166).c_str());	// Select a tank by pressing on the row and push Detail button.
		OKMessageBox->Exec(WinHandl, Text1, Text2);
	} else {
		int SelectIndex = LISTVIEW_GetSel(ListViewHandl);
		if ( !ObjectVector.empty() ) {
			int StartIndex;
			if ( (CurrentPage+1)==NumberOfPages && NumberOfPages>1) {
				StartIndex = ObjectVector.size()- NumUnitsOnPage;
			} else {
				StartIndex = CurrentPage*NumUnitsOnPage;
			}
			unsigned Index = StartIndex+SelectIndex;
			if ( Index < ObjectVector.size()) {
				TankDetails->CreateMultiPage(WinHandl,(PRogramObject*)ObjectVector[Index]);
				Found = true;
			}
		}
		TimedOut = false;
		TimerCount=50;
		SetGuiEvent(PWEventHandl,1,&aTCB[1]);
	}
	return(Found);
}

void TDUGroupWin::ButtonClicked(int ButtID)
{
	if ( !ObjectVector.empty() ) {
		switch ( ButtID ) {
		case TDU_BUTTON_ID_PW1:
			if ( CurrentPage<=0 ) {
				//	CurrentPage = NumberOfPages-1;
				CurrentPage = 0;
			} else {
				CurrentPage--;
			}
			TimedOut = false;
			TimerCount=50;
			SetGuiEvent(PWEventHandl,1,&aTCB[1]);
			break;
		case TDU_BUTTON_ID_PW2:
			if ( CurrentPage >= (NumberOfPages-1) ) {
//					CurrentPage = 0;
				CurrentPage = (NumberOfPages-1);
			} else {
				CurrentPage++;
			}
			TimedOut = false;
			TimerCount=50;
			SetGuiEvent(PWEventHandl,1,&aTCB[1]);
			break;
		case TDU_BUTTON_ID_PW3:
			AppSetup();
			break;
		case TDU_BUTTON_ID_PW4:			// REPORT_BALLAST REPORT_CARGO
			PrintReport(PROPrinter::CurPrinterId);
			break;
		case TDU_BUTTON_ID_PW5:
			{
				if ( But5LangKey == L_WORD90 ) {

					if ( SetupWin() ) {
						ButWindow->ChangeSWord(TDU_BUTTON_ID_PW5,0,L_WORD18);
						But5LangKey = L_WORD18;
					}
				} else {
					ButWindow->ChangeSWord(TDU_BUTTON_ID_PW5,0,L_WORD90);
					But5LangKey = L_WORD90 ;
					if ( !TankDetails->Closed ) {
						TankDetails->Closed = true;
						if ( !KeyBoard->Closed ) {					 //1
							KeyBoard->CloseTimer.Stop();
						}
						GUI_EndDialog(TankDetails->WinHandl, 0);
					}
				}
			}
			break;
		}
	}
}

void TDUGroupWin::cbEventHandler(WM_MESSAGE * pMsg)
{
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_PAINT:
		UpdateFields(true);
		break;
	case WM_NOTIFY_PARENT:
		{
			int NCode;//, Id;
			//Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
			NCode = pMsg->Data.v;								/* Notification code */
			switch ( NCode ) {
			case WM_NOTIFICATION_RELEASED:		/* React only if released */
				{
					UserTouch = true;
					SetGuiEvent(PWEventHandl,1,&aTCB[1]);
				}
				break;
			}
		}
		break;
	case WM_CREATE:
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void TDUGroupWin::AppSetup(void)
{
}
void TDUGroupWin::PrintReport(int PrinterId)
{
}

