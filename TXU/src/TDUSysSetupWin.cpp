#include "TDUIncludes.h"


TDUSysSetupWin::~TDUSysSetupWin(void)
{
}

TDUSysSetupWin::TDUSysSetupWin(void)
{
    Closed = true;
    PinCodeOK = false;
}

ValueList PWBackColorList[] =  {
    {L_WORD462          ,L_WORD237,GUI_BLACK},                              // {"Black"          ,"",GUI_BLACK},
    {L_WORD463          ,L_WORD237,GUI_DARKGRAY},                           // {"Dark Gray"      ,"",GUI_DARKGRAY},
    {L_WORD464          ,L_WORD237,GUI_LIGHTGRAY},                          // {"Light Gray"     ,"",GUI_LIGHTGRAY},
    {L_WORD465          ,L_WORD237,GUI_WHITE},                              // {"White"          ,"",GUI_WHITE},
    {L_WORD466          ,L_WORD237,GUI_BLUE},                               // {"Blue"           ,"",GUI_BLUE},
};

ValueList PWTextColorList[] =  {
    {L_WORD462          ,L_WORD237,GUI_BLACK},                              //   {"Black"          ,"",GUI_BLACK},
    {L_WORD463          ,L_WORD237,GUI_DARKGRAY},                           //   {"Dark Gray"      ,"",GUI_DARKGRAY},
    {L_WORD464          ,L_WORD237,GUI_LIGHTGRAY},                          //   {"Light Gray"     ,"",GUI_LIGHTGRAY},
    {L_WORD465          ,L_WORD237,GUI_WHITE},                              //   {"White"          ,"",GUI_WHITE},
    {L_WORD565          ,L_WORD237,GUI_GREEN},                              //   {"Green"          ,"",GUI_GREEN},
};

int SizeofPWBackColorList = NELEMENTS(PWBackColorList);
int SizeofPWTextColorList = NELEMENTS(PWTextColorList);


const GUI_WIDGET_CREATE_INFO TDUSysSetupWin::aDialogCreate[] =
{
    { FRAMEWIN_CreateIndirect,"System setup page"   ,TDU_SYSSETUP_WIN, 0, 0, 0, 0, FRAMEWIN_CF_MAXIMIZED, 0},
    { BUTTON_CreateIndirect, "Close"                ,   GUI_ID_CLOSE, 195, 155,  80, 20},
    { TEXT_CreateIndirect,   "Screen saver:"        ,   GUI_ID_TEXT0,   6,   6,  80, 20, TEXT_CF_LEFT},
    { EDIT_CreateIndirect,   ""                     ,   GUI_ID_EDIT1,   6,  26,  41, 15, GUI_TA_HCENTER | GUI_TA_VCENTER, 20},
    { TEXT_CreateIndirect,   "minutes"              ,   GUI_ID_TEXT1,  50,  26,  40, 20, TEXT_CF_LEFT},
    { TEXT_CreateIndirect,   "Alarm off delay:"     ,   GUI_ID_TEXT2,   6,  60,  80, 20, TEXT_CF_LEFT},
    { EDIT_CreateIndirect,   ""                     ,   GUI_ID_EDIT2,   6,  80,  41, 15, GUI_TA_HCENTER | GUI_TA_VCENTER, 20},
    { TEXT_CreateIndirect,   "seconds"              ,   GUI_ID_TEXT3,  50,  80,  40, 20, TEXT_CF_LEFT},
    //   { TEXT_CreateIndirect,   "Change Pin code:"     ,		       0,   6, 122,  80, 20, TEXT_CF_LEFT },
//	{ EDIT_CreateIndirect,	 "****"                 ,	GUI_ID_EDIT3,   6, 142,	 40, 15, GUI_TA_HCENTER | GUI_TA_VCENTER, 20 },

    { TEXT_CreateIndirect,   "Set color:"           ,   GUI_ID_TEXT4, 110,   6,  90,  18, TEXT_CF_LEFT},
    { TEXT_CreateIndirect,   "Background"           ,   GUI_ID_TEXT5, 110,  24,  90,  18, TEXT_CF_LEFT},
    { DROPDOWN_CreateIndirect, NULL                ,GUI_ID_DROPDOWN0, 110,  42,  74,  70, 0, 3},
    { TEXT_CreateIndirect,   "Foreground"           ,   GUI_ID_TEXT6, 190,  24,  90,  18, TEXT_CF_LEFT},
    { DROPDOWN_CreateIndirect, NULL                ,GUI_ID_DROPDOWN4, 190,  42,  74,  70, 0, 3},

    { TEXT_CreateIndirect,   "Brightness:"          , GUI_ID_TEXT7, 110,  80,  80, 20, TEXT_CF_LEFT},
    { BUTTON_CreateIndirect, "/\\"                  , GUI_ID_BUTTON2, 112, 100,  25, 25},
    { BUTTON_CreateIndirect, "\\/"                  , GUI_ID_BUTTON3, 148, 100,  25, 25},

    { BUTTON_CreateIndirect, "Buzzer /\nLight test" , GUI_ID_BUTTON0, 195,  75,  80, 35},
    { BUTTON_CreateIndirect, "Change Pin code"      , GUI_ID_BUTTON4,   4, 105,  90, 20},
    { BUTTON_CreateIndirect, "Calibrate screen"     , GUI_ID_BUTTON5,   4, 130,  90, 20},
    { BUTTON_CreateIndirect, "Factory defaults"     , GUI_ID_BUTTON6,   4, 155,  90, 20},
//    { BUTTON_CreateIndirect, "Write\nconfig file"   , GUI_ID_BUTTON7, 195, 115,  80, 35},// EHSMark Disable writing config file
};


void TDUSysSetupWin::ExecDialogBox(WM_HWIN hCurrentWin)
{
    //if ( !Closed ) {
    //	if ( WinHandl ) {
    //		CloseTimer.Stop();
    //	}
    //}
    //Closed = false;
    //WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbSysWin,
    //											hCurrentWin, 0, 0);
    //CloseTimer.Init(WinHandl,true,&Closed,TimeOut);
    // WM_EnableMemdev(WinHandl);

    if ( Closed ) {
        Closed = false;
        WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbSysWin,
                                       hCurrentWin, 0, 0);
        DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN0), 1 );
        DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN4), 1 );
        WM_EnableMemdev(WinHandl);
        PinCodeOK = false;
        GetDialogHandles();
    } else {
        WM_BringToTop(WinHandl);
    }
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSysSetupWin::GetDialogHandles(void)
{
    hButBuzzer      = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON0);
    hButUpp         = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON2);
    hButDown        = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON3);
    hButFactDef     = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON6);
    hButWriteConfig = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON7);

    hEditScreen     = WM_GetDialogItem(WinHandl, GUI_ID_EDIT1);
    hEditAlOffTime  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT2);
    hDropdBackColor = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN0);
    hDropdForeColor = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN4);
    InitSysWin();
}

void TDUSysSetupWin::InitSysWin(void)
{

    while ( DROPDOWN_GetNumItems(hDropdBackColor)>0 ) {
        DROPDOWN_DeleteItem(hDropdBackColor, 0);
    }
    while ( DROPDOWN_GetNumItems(hDropdForeColor)>0 ) {
        DROPDOWN_DeleteItem(hDropdForeColor, 0);
    }
    {
        int WordKey[]={L_WORD462, L_WORD463, L_WORD464, L_WORD465, L_WORD466};
        AddToDropDownsList(GUI_ID_DROPDOWN0,WordKey,NELEMENTS(WordKey));
    }
    {
        int WordKey[]={L_WORD462, L_WORD463, L_WORD464, L_WORD465, L_WORD565};
        AddToDropDownsList(GUI_ID_DROPDOWN4,WordKey,NELEMENTS(WordKey));
    }

    BUTTON_SetBkColor(hButBuzzer, BUTTON_CI_PRESSED, TDU_C_AL_BACK_ACTIVE);
    U8 Arrow[2];
    Arrow[0]  = 146;
    Arrow[1]  = 0;
    BUTTON_SetFont(hButUpp,&GUI_Font8x16);
    BUTTON_SetText(hButUpp,(char*)Arrow);
    Arrow[0]  = 147;
    Arrow[1]  = 0;
    BUTTON_SetFont(hButDown,&GUI_Font8x16);
    BUTTON_SetText(hButDown,(char*)Arrow);
    HoldSound = true;
    UpdateSysWin();
    {
        const GUIKey Words[] ={
            {TDU_SYSSETUP_WIN   ,0,L_WORD54},
            {GUI_ID_CLOSE       ,0,L_WORD18},
            {GUI_ID_TEXT0       ,0,L_WORD55},
            {GUI_ID_TEXT1       ,0,L_WORD56},
            {GUI_ID_TEXT2       ,0,L_WORD57},
            {GUI_ID_TEXT3       ,0,L_WORD58},
            {GUI_ID_TEXT4       ,0,L_WORD61},
            {GUI_ID_TEXT5       ,0,L_WORD62},
            {GUI_ID_TEXT6       ,0,L_WORD63},
            {GUI_ID_TEXT7       ,0,L_WORD64},
            {GUI_ID_BUTTON0     ,0,L_WORD65},
            {GUI_ID_BUTTON4     ,0,L_WORD66},
            {GUI_ID_BUTTON5     ,0,L_WORD67},
            {GUI_ID_BUTTON6     ,0,L_WORD770},
            {GUI_ID_BUTTON7     ,0,L_WORD920},
        };
        AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
    }
}

void TDUSysSetupWin::UpdateSysWin(void)
{
    AnsiString TimeStr = LibGetValue(SVT_TOUCH_SCREEN_TIMEOUT,PROSystemData::TXUSystemData);
    EDIT_SetText(hEditScreen,TimeStr.c_str());
//	Time =(AnsiString)PROProjectInfo::WaterIngrAlOffDelay;
    TimeStr = LibGetValue(SVT_ALARM_OFF_DELAY,PROSystemData::TXUSystemData);
    EDIT_SetText(hEditAlOffTime,TimeStr.c_str());
}

void TDUSysSetupWin::SetAppColor(WM_HWIN hWin,int Key)
{
    WM_HWIN hDropd0;
    hDropd0 = WM_GetDialogItem(hWin, Key);
    switch ( Key ) {
    case GUI_ID_DROPDOWN0:
        {
            int color = DROPDOWN_GetSel(hDropd0);
            if ( color>-1 ) {
                if ( PWBackColorList[color].Value != TextColor ) {
                    BackColor = PWBackColorList[color].Value;
                    //	SetListViewColor();
                } else {
                    SystemWindow->SysWin1->SysSetupWin->InitSysWin();
                }
            }
        }
        break;
    case GUI_ID_DROPDOWN4:
        {
            int color = DROPDOWN_GetSel(hDropd0);
            if ( color>-1 ) {
                if ( PWTextColorList[color].Value != BackColor ) {
                    TextColor = PWTextColorList[color].Value;
                    //	SetListViewColor();
                } else {
                    SystemWindow->SysWin1->SysSetupWin->InitSysWin();
                }
            }
        }
        break;
    }
    SystemWindow->IsModified = true;
    SignalSaveSettings(FLASH_SAVE_SETTINGS);
}

void TDUSysSetupWin::SetScreenOffTime(AnsiString StringBuf)
{
    int Time = atoi(StringBuf.c_str());
    if ( (Time>=TOUCH_MIN_TIMEOUT) && (Time<=TOUCH_MAX_TIMEOUT) ) {
        LibPutValue( SVT_TOUCH_SCREEN_TIMEOUT, PROSystemData::TXUSystemData, StringBuf);
    } else {
        AnsiString Text1("Fault in insert of time!");
        AnsiString Text2("Time must be between "+(AnsiString)TOUCH_MIN_TIMEOUT+" and "+(AnsiString)TOUCH_MAX_TIMEOUT+" minutes");
        OKMessageBox->Exec(WinHandl,Text1 , Text2);
    }
}

void TDUSysSetupWin::SetAlarmOffTime(AnsiString StringBuf)
{
    int Time = atoi(StringBuf.c_str());
    int Min = MIN_ALARM_OFF_DELAY/1000;
    int Max = MAX_ALARM_OFF_DELAY/1000;
    if ( (Time>=Min) && (Time<=Max) ) {
        LibPutValue( SVT_ALARM_OFF_DELAY, PROSystemData::TXUSystemData, StringBuf);
    } else {
        AnsiString Text1("Fault in insert of time!");
        AnsiString Text2("Time must be between "+(AnsiString)Min+" and "+(AnsiString)Max);
        OKMessageBox->Exec(WinHandl,Text1 , Text2);
    }
}

void TDUSysSetupWin::ChangePinCode(AnsiString PinCodeStr)
{
//    int pin = atoi(PinCodeStr);
    int length = PinCodeStr.length();
    int pin = atoi(PinCodeStr.c_str());
    if ( pin>0 ) {
        if ( PinCodeStr.compare(PROSystemData::TXUSystemData->UserPinCode)==0 ) {
            PinCodeOK = true;
            KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(WinHandl),L_WORD665,GUI_ID_BUTTON8);//"Enter new pin code:"
        } else if ( (length>4) && (pin == UNLOCK_PIN_CODE) ) {
            PinCodeOK = true;
            KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(WinHandl),L_WORD665,GUI_ID_BUTTON8);//"Enter new pin code:"
        } else {
            PinCodeOK = false;
        }
    } else {
        PinCodeOK = false;
    }
    if ( !PinCodeOK ) {
        AnsiString Text1("Message!");
        AnsiString Text2("Invalid pin code.");
        OKMessageBox->Exec(WinHandl,Text1 , Text2);
    }
}

bool TDUSysSetupWin::CheckPinCode(AnsiString PinCodeStr)
{
    bool PCodeOK = false;
    int length = PinCodeStr.length();
    int pin = atoi(PinCodeStr.c_str());
    if ( pin>0 ) {
        if ( PinCodeStr.compare(PROSystemData::TXUSystemData->UserPinCode)==0 ) {
            PCodeOK = true;
        } else if ( (length>4) && (pin == UNLOCK_PIN_CODE) ) {
            PinCodeOK = true;
        } else {
            PCodeOK = false;
        }
    } else {
        PCodeOK = false;
    }
    if ( !PCodeOK ) {
        AnsiString Text1("Message!");
        AnsiString Text2("Invalid pin code.");
        OKMessageBox->Exec(WinHandl,Text1 , Text2);
    }
	return PCodeOK;

}
void TDUSysSetupWin::FirstNewPinCode(AnsiString PinCodeStr)
{
    int length = PinCodeStr.length();
    int pin = atoi(PinCodeStr.c_str());
//new keyboard for pin    int foundPtr = PinCodeStr.find(".-");
    if ( pin<0 ) {
        PinCodeOK = false;
    } else {
        if ( (length<5)&&(length>3) ) {
            PinCodeOK = true;
            TempPinCode = PinCodeStr;
            TSN_Delay(50);
            KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(WinHandl),L_WORD669,GUI_ID_BUTTON9); //"Re-enter new pin code:"
        } else {
            PinCodeOK = false;
        }
    }
    if ( !PinCodeOK ) {
        AnsiString Text1("Message!");
        AnsiString Text2("Invalid pin code, must be 4 digit");
        OKMessageBox->Exec(WinHandl,Text1 , Text2);
//        KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(WinHandl),"Enter new pin code:",GUI_ID_BUTTON8);
    }
}

void TDUSysSetupWin::SecondNewPinCode(AnsiString PinCodeStr)
{
    if ( TempPinCode.compare(PinCodeStr)==0 ) {
        LibPutValue(SVT_USER_PIN_CODE, PROSystemData::TXUSystemData, PinCodeStr, true);
    } else {
        PinCodeOK = false;
        AnsiString Text1("Message!");
        AnsiString Text2("Not equal to first new pin code");
        OKMessageBox->Exec(WinHandl,Text1 , Text2);
    }
}

void TDUSysSetupWin::MakeSound(void)
{
#ifdef WIN32
    int Max = 200;
    int count = 0;
    while ( HoldSound && (count++<Max) ) {
        Beep(500,10);
        TSN_Delay(10);
        WM_ExecIdle();
    }
#endif
}

void TDUSysSetupWin::cbSysWin(WM_MESSAGE *pMsg)
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch ( pMsg->MsgId ) {
    case WM_PAINT:
        GUI_DrawRect(   2,   2,  94,  50);
        GUI_DrawRect(   2,  56,  94, 100);
        GUI_DrawRect( 104,   2, 270,  66);
        GUI_DrawRect( 104,  76, 180, 132);
        SystemWindow->SysWin1->SysSetupWin->UpdateLanguage();
        {
            int ind0 = -1;
            int ind4 = -1;
            for ( int j=0; j<SizeofPWBackColorList; j++ ) {
                if ( PWBackColorList[j].Value==BackColor )ind0=j;
            }
            for ( int j=0; j<SizeofPWTextColorList; j++ ) {
                if ( PWTextColorList[j].Value==TextColor )ind4=j;
            }

            DROPDOWN_SetSel(SystemWindow->SysWin1->SysSetupWin->hDropdBackColor,ind0);
            DROPDOWN_SetSel(SystemWindow->SysWin1->SysSetupWin->hDropdForeColor,ind4);
        }
        break;
    case WM_INIT_DIALOG:
        SystemWindow->SysWin1->SysSetupWin->FirstTime = true;
        break;
    case MESSAGE_PINCODE_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            AnsiString StringBuf =(char*)pMsg->Data.p;
            switch ( ValueId ) {
            case GUI_ID_BUTTON4:
                SystemWindow->SysWin1->SysSetupWin->ChangePinCode(StringBuf);
                break;
            case GUI_ID_BUTTON7:
                if ( SystemWindow->SysWin1->SysSetupWin->CheckPinCode(StringBuf) ) {
                    int State;

                    if ( PROSystemData::HasConfigWritePermission ) {
                        State = C_DISABLE;
                    } else {
                        State = C_ENABLE;
                    }
                    LibPutValue(SVT_FORCE_WRITE_CONFIG, PROSystemData::TXUSystemData, FindKeyWord(State), true);
                }
                break;
            case GUI_ID_BUTTON8:
                SystemWindow->SysWin1->SysSetupWin->FirstNewPinCode(StringBuf);
                break;
            case GUI_ID_BUTTON9:
                SystemWindow->SysWin1->SysSetupWin->SecondNewPinCode(StringBuf);
                break;
            }
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            AnsiString StringBuf =(char*)pMsg->Data.p;
            if ( ValueId == GUI_ID_EDIT1 ) {
                SystemWindow->SysWin1->SysSetupWin->SetScreenOffTime(StringBuf);
            }
            if ( ValueId == GUI_ID_EDIT2 ) {
                SystemWindow->SysWin1->SysSetupWin->SetAlarmOffTime(StringBuf);
            }
        }
        if ( !SystemWindow->SysWin1->SysSetupWin->Closed ) {
            SystemWindow->SysWin1->SysSetupWin->UpdateSysWin();
        }
        break;
    case WM_TOUCH_CHILD:
        {
            Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
            switch ( Id ) {
            case GUI_ID_EDIT1:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD666,Id);//"Screen saver time, min."
                break;
            case GUI_ID_EDIT2:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD667,Id);//Alarm delay time, sec.
                break;
            }
        }
        break;
    case WM_NOTIFY_PARENT:
        {
            Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
            NCode = pMsg->Data.v;               /* Notification code */
            switch ( NCode ) {
            case WM_NOTIFICATION_SEL_CHANGED:
                {
                    switch ( Id ) {
                    case GUI_ID_DROPDOWN0:
                    case GUI_ID_DROPDOWN4:
                        SystemWindow->SysWin1->SysSetupWin->SetAppColor(hWin,Id);
                        break;
                    }
                }
                break;
            case WM_NOTIFICATION_CLICKED:    /* React only if released */
                switch ( Id ) {
                case GUI_ID_BUTTON0: /* TestBuzzer Button */
#ifdef WIN32
                    SystemWindow->SysWin1->SysSetupWin->HoldSound = true;
                    SystemWindow->SysWin1->SysSetupWin->MakeSound();
#else
                    ANPRO10_SendBuzzerTest(BUZZER_TEST_PRESSED);
#endif
                    break;
                case GUI_ID_BUTTON2:
                    LCD_BACKLIGHT_ADJUST(-10);  // Up
                    break;
                case GUI_ID_BUTTON3:
                    LCD_BACKLIGHT_ADJUST(10); // Down
                    break;
                case GUI_ID_BUTTON6:
#ifdef S2TXU
                    SetFactoryDefaults();
#endif
                    break;

                case GUI_ID_BUTTON7:
                    KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hWin),L_WORD150,Id);//"Enter old pin code:"
                    break;
                case GUI_ID_BUTTON4: /* Change pin code */
                    KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hWin),L_WORD668,Id);//"Enter old pin code:"
                    break;
                case GUI_ID_BUTTON5: /* Calibrate screen */
                    PreviousWinID = CurrentWinID;
                    CurrentWinID = TDU_CALIBRATE_WIN;
                    MainWindow->SetWindow(CurrentWinID);
                    CalibrateScreen->Exec();
                    break;
                }
                break;
            case WM_NOTIFICATION_RELEASED:      /* React only if released */
                switch ( Id ) {
                case GUI_ID_BUTTON0:    /* TestBuzzer Button */
                    {
#ifdef WIN32
                        SystemWindow->SysWin1->SysSetupWin->HoldSound = false;
#else
                        ANPRO10_SendBuzzerTest(BUZZER_TEST_RELEASED);
#endif
                    }
                    break;
                case GUI_ID_CLOSE:   /* Close Button */
                    SystemWindow->SysWin1->CloseSysWin();
                    break;
                }
                break;
            }
        }
        break;
    default:
        WM_DefaultProc(pMsg);
        break;
    }
}
