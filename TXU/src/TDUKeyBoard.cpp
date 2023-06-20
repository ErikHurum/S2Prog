#include "TDUIncludes.h"
#include "TDUKeyBoard.h"

//#if (GUI_WINSUPPORT && GUI_SUPPORT_TOUCH)

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/* Static variables */
static char   _CmdNext;

int TDU_WaitKey(void) {
	int r = 0;
	int tMax = GUI_GetTime() + 2*4000;
	int tDiff;
	int c = GUI_GetKey();
	while ( tDiff = tMax-GUI_GetTime(), (tDiff > 0) ) {
		TSN_Delay(10);
		WM_ExecIdle();
		if ( (r = GUI_GetKey()) != 0 )
			break;
	}
	WM_ExecIdle();
	return r;
}



int TDU_CheckCancel(void) {
	int c = GUI_GetKey();
#if GUI_WINSUPPORT
	WM_ExecIdle();
#endif
	return _CmdNext;
}

/*********************************************************************
*       _ExecKeyboard
* This creates a keyboard.
* The routine returns after ENTER or ESC has been pressed.
**********************************************************************/

static char _acTextAll[] ={ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', '.', '-', 0
};

static char _acTextNum[] = {
	'7','8','9',
	'4','5','6',
	'1','2','3',
	'0','.','-',0
};

static char _acTextNumPinCode[] = {
	'7','8','9',
	'4','5','6',
	'1','2','3',
	'0',0
};

TDUKeyBoard::~TDUKeyBoard(void)
{
}

TDUKeyBoard::TDUKeyBoard(void)
{
	Closed = true;
}


int TDUKeyBoard::ExecKeyBoardAll(WM_HWIN hCurrentWin,char *buf)
{
	int ReturnValue = -1;
	if ( Closed ) {
		UseCallBack = false;
		int i;
		int Key;
		BUTTON_Handle ahButton[39];
		BUTTON_Handle hButtonESC;
		BUTTON_Handle hButtonEnter;
		EDIT_Handle   hEdit;
		U8 TBuf[2];
		Closed = false;

		WinHandl  = WM_CreateWindow( 2,40,286,180,WM_CF_SHOW,cbKeyBoard,0);
		WM_BringToTop(WinHandl);

		/* Create Keyboard Buttons */
		for ( i=0; i<(countof(ahButton)-1); i++ ) {
			int Pos = (i <(countof(ahButton)-1)) ? i : i+4;
			int x0 = (i<29) ?  5+28*(Pos%10) :  5+28*((Pos+1)%10) ;
			int y0 = (i<29) ? 76+28*(Pos/10) : 76+28*((Pos+1)/10) ;
			char c = _acTextAll[i];
			int Id = c ? c : 1;
			char ac[2] = {0};
			char *s= ac;
			ac[0] = c;
			ahButton[i] = BUTTON_Create( x0, y0, 25, 25, Id,BUTTON_CF_SHOW );
			BUTTON_SetText(ahButton[i], s);
#if GUI_SUPPORT_MEMDEV
			BUTTON_EnableMemdev(ahButton[i]);
#endif
		}
		ahButton[i]  = BUTTON_Create(  89, 188, 109, 25, ' ',BUTTON_CF_SHOW );
		hButtonESC   = BUTTON_Create( 220,  46,  60, 25, GUI_ID_CANCEL,BUTTON_CF_SHOW );
		hButtonEnter = BUTTON_Create( 257, 132,  25, 53, GUI_ID_CLOSE,BUTTON_CF_SHOW );
		BUTTON_SetText(hButtonESC, "ESC");
		BUTTON_SetFont(hButtonEnter,&GUI_Font8x16);
		TBuf[0] = 148;
		TBuf[1] = 0;
		BUTTON_SetText(hButtonEnter, (char*)TBuf);
		hEdit = EDIT_Create( 5, 46, 210, 25, ' ', 80, 0 );
		EDIT_SetFont(hEdit, &GUI_Font8x16);
		/* Handle Keyboard until ESC or ENTER is pressed */
		do {
			Key = TDU_WaitKey();
			switch ( Key ) {
			case 0:
			case GUI_ID_CANCEL:
				buf[0]=0;
				ReturnValue = -1;
				break;
			case GUI_ID_CLOSE:
				EDIT_GetText(hEdit, buf, 180);
				ReturnValue = 0;
				break;
			default:
				EDIT_AddKey(hEdit, Key);
				ReturnValue = 1;
			}
		} while ( (Key!=GUI_ID_CLOSE) && (Key!=GUI_ID_CANCEL) && (Key!=0) );
		/* Cleanup */
		for ( i=0; i< countof(ahButton); i++ ) {
			BUTTON_Delete(ahButton[i]);
		}
		BUTTON_Delete(hButtonESC);
		BUTTON_Delete(hButtonEnter);
		EDIT_Delete(hEdit);
		WM_DeleteWindow(WinHandl);
		Closed = true;
//		WM_ExecIdle();
	}
	return ReturnValue;
}

//New keypad for PinCode.
void TDUKeyBoard::ExecKeyBoardPinCode(WM_HWIN hCurrentWin,int WordKey, int ID)
{
	if ( Closed ) {
		Closed = false;
		UseCallBack = true;
		int i;
//		int Key;
		U8 TBuf[2];
		ReturnBuf[0] = 0;
		ReturnValue = -1;
		ValueID = ID;
		DialogWinHandl = hCurrentWin;

		//	WinHandl  = WM_CreateWindowAsChild( 2,40,118,150,hCurrentWin,WM_CF_SHOW,cbKeyBoard,0);
		//	WinHandl  = WM_CreateWindow( 2,40,118,170,WM_CF_SHOW,cbKeyBoardPinCode,0);
		WinHandl  = WM_CreateWindow( 100,40,118,170,WM_CF_SHOW,cbKeyBoardPinCode,0);
		WM_SetStayOnTop(WinHandl, 1);

		for ( i=0; i<countof(ahButtonPinCode); i++ ) {
			int x0 =  3+28*(i%3);//5+28*(i%3);
			int y0 = 56+28*(i/3);//76+28*(i/3);
			char c = _acTextNumPinCode[i];
			int Id = c ? c : 1;
			char ac[2] = {0,0};
			char *s= ac;
			ac[0] = c;
			ahButtonPinCode[i] = BUTTON_CreateAsChild( x0, y0, 25, 25, WinHandl, Id, BUTTON_CF_SHOW );
			BUTTON_SetText(ahButtonPinCode[i], s);
		}
		hButtonBackSpace  = BUTTON_CreateAsChild( 86,  56, 25, 25, WinHandl, GUI_KEY_BACKSPACE,BUTTON_CF_SHOW );
		hButtonESC              = BUTTON_CreateAsChild( 86,  84, 25, 25, WinHandl, GUI_KEY_ESCAPE,BUTTON_CF_SHOW );
		hButtonEnter            = BUTTON_CreateAsChild( 86, 112, 25, 53, WinHandl, GUI_KEY_ENTER, BUTTON_CF_SHOW );

		BUTTON_SetFont(hButtonBackSpace,&GUI_Font8x16);
		TBuf[0] = 144;
		TBuf[1] = 0;
		BUTTON_SetText(hButtonBackSpace,(char*)TBuf);

		BUTTON_SetText(hButtonESC,           "Esc");

		BUTTON_SetFont(hButtonEnter,&GUI_Font8x16);
		TBuf[0] = 148;
		TBuf[1] = 0;
		BUTTON_SetText(hButtonEnter, (char*)TBuf);

		hText   = TEXT_CreateAsChild( 3,  3, 108, 22, WinHandl, 0, WM_CF_SHOW, FindDictionaryWord(WordKey).c_str(), TEXT_CF_LEFT | TEXT_CF_VCENTER );
		TEXT_SetTextColor(hText,GUI_WHITE);
		hTextEdit = EDIT_CreateAsChild( 3, 27, 108, 25, WinHandl, ' ', 80, 0 );
		EDIT_SetFont(hTextEdit, &GUI_Font8x16);
		hTextEditPinCode = EDIT_CreateAsChild( 3, 27, 108, 25, WinHandl, ' ', 80, 0 );
		EDIT_SetFont(hTextEditPinCode, &GUI_Font8x16);
		WM_HideWindow(hTextEditPinCode);
		CloseTimer.Init(WinHandl,false,&Closed,TimeOut);
		WM_EnableMemdev(WinHandl);
	}
}
//New keypad for num.
void TDUKeyBoard::ExecKeyBoardNum(WM_HWIN hCurrentWin,int WordKey, int ID)
{
	if ( Closed ) {
		Closed = false;
		UseCallBack = true;
		int i;
//		int Key;
		U8 TBuf[2];
		ReturnBuf[0] = 0;
		ReturnValue = -1;
		ValueID = ID;
		DialogWinHandl = hCurrentWin;

		//	WinHandl  = WM_CreateWindowAsChild( 2,40,118,150,hCurrentWin,WM_CF_SHOW,cbKeyBoard,0);
		WinHandl  = WM_CreateWindow( 2,40,118,170,WM_CF_SHOW,cbKeyBoard,0);
		WM_SetStayOnTop(WinHandl, 1);

		for ( i=0; i<countof(ahButton); i++ ) {
			int x0 =  3+28*(i%3);//5+28*(i%3);
			int y0 = 56+28*(i/3);//76+28*(i/3);
			char c = _acTextNum[i];
			int Id = c ? c : 1;
			char ac[2] = {0,0};
			char *s= ac;
			ac[0] = c;
			ahButton[i] = BUTTON_CreateAsChild( x0, y0, 25, 25, WinHandl, Id, BUTTON_CF_SHOW );
			BUTTON_SetText(ahButton[i], s);
		}
		hButtonBackSpace  = BUTTON_CreateAsChild( 86,  56, 25, 25, WinHandl, GUI_KEY_BACKSPACE,BUTTON_CF_SHOW );
		hButtonESC              = BUTTON_CreateAsChild( 86,  84, 25, 25, WinHandl, GUI_KEY_ESCAPE,BUTTON_CF_SHOW );
		hButtonEnter            = BUTTON_CreateAsChild( 86, 112, 25, 53, WinHandl, GUI_KEY_ENTER, BUTTON_CF_SHOW );

		BUTTON_SetFont(hButtonBackSpace,&GUI_Font8x16);
		TBuf[0] = 144;
		TBuf[1] = 0;
		BUTTON_SetText(hButtonBackSpace,(char*)TBuf);

		BUTTON_SetText(hButtonESC,           "Esc");

		BUTTON_SetFont(hButtonEnter,&GUI_Font8x16);
		TBuf[0] = 148;
		TBuf[1] = 0;
		BUTTON_SetText(hButtonEnter,(char*)TBuf);

		hText   = TEXT_CreateAsChild( 3,  3, 108, 22, WinHandl, 0, WM_CF_SHOW, FindDictionaryWord(WordKey).c_str(), TEXT_CF_LEFT | TEXT_CF_VCENTER );
		TEXT_SetTextColor(hText,GUI_WHITE);
		hTextEdit = EDIT_CreateAsChild( 3, 27, 108, 25, WinHandl, ' ', 80, 0 );
		EDIT_SetFont(hTextEdit, &GUI_Font8x16);
		CloseTimer.Init(WinHandl,false,&Closed,TimeOut);
		WM_EnableMemdev(WinHandl);
	}
}

void TDUKeyBoard::EndKeyBoardNum(void)
{
	if ( !Closed ) {
		if ( ReturnValue == 0 ) {
			WM_MESSAGE MyMsgPtr;
			MyMsgPtr.hWin = DialogWinHandl;
			MyMsgPtr.hWinSrc = ValueID;
//		MyMsgPtr.hWinSrc = WinHandl;
			MyMsgPtr.MsgId = MESSAGE_KEYPAD_RETURN;
			//	MyMsgPtr.Data.v = ValueID;
			MyMsgPtr.Data.p = ReturnBuf;
			WM_SendMessage(DialogWinHandl,&MyMsgPtr);
			//	WM_SendToParent(WinHandl,MyMsgPtr);
			//			MyMsgPtr.hWinSrc = ValueID;
//		WM_SendMessage(ParentWinHandl,&MyMsgPtr);
			//		WM_SendMessageNoPara(ParentWinHandl,MESSAGE_KEYPAD_RETURN);
		}
/* Cleanup */
/* No need 	WM_DeleteWindow delets all child
	for (int i=0; i< countof(ahButton); i++) {
			BUTTON_Delete(ahButton[i]);
		}
		BUTTON_Delete(hButtonBackSpace);
		BUTTON_Delete(hButtonESC);
		BUTTON_Delete(hButtonEnter);
		EDIT_Delete(hTextEdit);*/

		CloseTimer.Stop();
	}
}

void TDUKeyBoard::cbKeyBoard(WM_MESSAGE * pMsg) {
	int NCode, Id;
//	WM_HWIN hEdit0;
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_TOUCH_CHILD:
		break;
	case WM_PAINT:
		GUI_SetBkColor(TDU_C_KB_BACK);
		GUI_Clear();
		GUI_SetColor(TDU_C_KB_TEXT);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(&TDU_FONT_BIG);
		break;
	case WM_CREATE:
		break;
	case WM_NOTIFY_PARENT:
		{
			if ( KeyBoard->UseCallBack ) {
				Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
				NCode = pMsg->Data.v;
				switch ( NCode ) {
				case WM_NOTIFICATION_RELEASED:		/* React only if released */
					switch ( Id ) {
					case 0:
					case GUI_KEY_ESCAPE:
						KeyBoard->ReturnBuf[0]=0;
						KeyBoard->CloseTimer.Stop();
						break;
					case GUI_KEY_ENTER:
						{
							EDIT_GetText(KeyBoard->hTextEdit, KeyBoard->ReturnBuf, BUF_SIZE);
							if ( KeyBoard->ReturnBuf[0] ) {
								WM_MESSAGE MyMsgPtr;
								MyMsgPtr.hWin = KeyBoard->DialogWinHandl;
								MyMsgPtr.hWinSrc = KeyBoard->ValueID;
								MyMsgPtr.MsgId = MESSAGE_KEYPAD_RETURN;
								//  	MyMsgPtr.Data.v = ValueID;
								MyMsgPtr.Data.p = KeyBoard->ReturnBuf;
								KeyBoard->CloseTimer.Stop();
								if ( KeyBoard->DialogWinHandl > 0 )
									WM_SendMessage(KeyBoard->DialogWinHandl,&MyMsgPtr);
							} else {
								KeyBoard->ReturnBuf[0]=0;
								KeyBoard->CloseTimer.Stop();
							}
						}
						break;
					default:
						{
							EDIT_AddKey(KeyBoard->hTextEdit, Id);
							KeyBoard->ReturnValue = 1;
							KeyBoard->CloseTimer.ReStart(KeyBoard->TimeOut);
						}
						break;
					}
				}
			}
		}
		break;
	case WM_KEY:
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

void TDUKeyBoard::cbKeyBoardPinCode(WM_MESSAGE * pMsg) {
	int NCode, Id;
//	WM_HWIN hEdit0;
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_TOUCH_CHILD:
		break;
	case WM_PAINT:
		GUI_SetBkColor(TDU_C_KB_BACK);
		GUI_Clear();
		GUI_SetColor(TDU_C_KB_TEXT);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(&TDU_FONT_BIG);
		break;
	case WM_CREATE:
		break;
	case WM_NOTIFY_PARENT:
		{
			if ( KeyBoard->UseCallBack ) {
				Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
				NCode = pMsg->Data.v;
				switch ( NCode ) {
				case WM_NOTIFICATION_RELEASED:		/* React only if released */
					switch ( Id ) {
					case 0:
					case GUI_KEY_ESCAPE:
						KeyBoard->ReturnBuf[0]=0;
						KeyBoard->CloseTimer.Stop();
						break;
					case GUI_KEY_ENTER:
						{
							EDIT_GetText(KeyBoard->hTextEditPinCode, KeyBoard->ReturnBuf, BUF_SIZE);
							if ( KeyBoard->ReturnBuf[0] ) {
								WM_MESSAGE MyMsgPtr;
								MyMsgPtr.hWin = KeyBoard->DialogWinHandl;
								MyMsgPtr.hWinSrc = KeyBoard->ValueID;
								//		MyMsgPtr.hWinSrc = WinHandl;
								MyMsgPtr.MsgId = MESSAGE_PINCODE_RETURN;
								//	MyMsgPtr.Data.v = ValueID;
								MyMsgPtr.Data.p = KeyBoard->ReturnBuf;
								KeyBoard->CloseTimer.Stop();
								if ( KeyBoard->DialogWinHandl > 0 )
									WM_SendMessage(KeyBoard->DialogWinHandl,&MyMsgPtr);
							} else {
								KeyBoard->ReturnBuf[0]=0;
								KeyBoard->CloseTimer.Stop();
							}
						}
						break;
					case GUI_KEY_BACKSPACE:
						EDIT_AddKey(KeyBoard->hTextEditPinCode, Id);
						EDIT_AddKey(KeyBoard->hTextEdit, Id);
						break;
					default:
						{
							EDIT_AddKey(KeyBoard->hTextEditPinCode, Id);
							int test = '*' ? '*' : 1;
							EDIT_AddKey(KeyBoard->hTextEdit, test);
							KeyBoard->ReturnValue = 1;
							KeyBoard->CloseTimer.ReStart(KeyBoard->TimeOut);
						}
						break;
					}
				}
			}
		}
		break;
	case WM_KEY:
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

