#include "TDUIncludes.h"

TDUConfigWarning *TDUConfigWarning::WinPtr = NULL;
TDUConfigWarning::~TDUConfigWarning(void)
{
    WinPtr = NULL;
}

TDUConfigWarning::TDUConfigWarning(void)
{
    WinPtr = this;
    {
        const GUIKey Words[] ={
            {TDU_CONFWARNING_WIN    ,0,L_WORD84},
            {GUI_ID_CLOSE           ,0,L_WORD86},
            {GUI_ID_TEXT0           ,0,L_WORD85},
        };
        AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
    }
    ExecDialogBox(NULL);

}

const GUI_WIDGET_CREATE_INFO TDUConfigWarning::aDialogCreate[] =
{
    { FRAMEWIN_CreateIndirect,"Config or Settings file Error", TDU_CONFWARNING_WIN, 0, 0, 320, 240, FRAMEWIN_CF_MOVEABLE, 0},
    { TEXT_CreateIndirect,      "Text",     GUI_ID_TEXT0,   2, 2, 230, 42, TEXT_CF_LEFT},
    { BUTTON_CreateIndirect,    "Continue", GUI_ID_CLOSE, 250, 4,  60, 22},
};


void TDUConfigWarning::ExecDialogBox(WM_HWIN hCurrentWin)
{
    if ( !Closed ) {
        if ( WinHandl ) {
            CloseTimer.Stop();
        }
    }
    Closed = false;
    WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbConfigWarning,
                                   hCurrentWin, 0, 0);
    hText = WM_GetDialogItem(WinHandl, GUI_ID_TEXT0);
    TEXT_SetFont(hText,&TDU_FONT_PW);
    AnsiString str = "There are fault in the configuration; \nthe program may not work properly.";
    TEXT_SetText(hText, str.c_str());
    TEXT_SetTextColor(hText, TDU_C_AL_BACK_ACTIVE);
    hConfigWarning = MULTIEDIT_Create(2, 50, 316, 186, WinHandl, 0, WM_CF_SHOW, MULTIEDIT_CF_AUTOSCROLLBAR_V, "test", 100);
    MULTIEDIT_SetReadOnly(hConfigWarning, 1);
    MULTIEDIT_SetWrapWord(hConfigWarning);
    MULTIEDIT_SetBkColor(hConfigWarning, MULTIEDIT_CI_READONLY, TDU_C_AL_BACK_WARNING);
    CloseTimer.Init(WinHandl,true,&Closed,1*60*60*1000);
    //WM_EnableMemdev(WinHandl);
}

void TDUConfigWarning::cbConfigWarning(WM_MESSAGE *pMsg)
{
    int NCode, Id;
    //WM_HWIN hWin = pMsg->hWin;
    switch ( pMsg->MsgId ) {
    case WM_INIT_DIALOG:
		if ( ConfigWarnings){
			ConfigWarnings->FirstTime = true;
		}
        break;
    case WM_PAINT:
        {
            AnsiString WarningString = ConfigWarningsString + HWOverviewWarningsString+RestoreSettingsWarningsString;
            int length1 = WarningString.length();
            if (length1 > 4000) WarningString.resize(4000);
            MULTIEDIT_SetText(WinPtr->hConfigWarning, WarningString.c_str());
        }
        ConfigWarnings->UpdateLanguage();
        break;
    case WM_TOUCH_CHILD:
        break;
    case WM_KEY:
        //switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key)
        //{
        //	case GUI_KEY_ESCAPE:
        //			GUI_EndDialog(hWin, 1);
        //		break;
        //	case GUI_KEY_ENTER:
        //			GUI_EndDialog(hWin, 0);
        //		break;
        //}
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
        NCode = pMsg->Data.v;               /* Notification code */
        switch ( NCode ) {
        case WM_NOTIFICATION_RELEASED:    /* React only if released */
            switch ( Id ) {
            case GUI_ID_CLOSE:   /* Close Button */
                CurrentWinID = TDU_SYSTEM_WIN;
                ConfigWarnings->CloseTimer.Stop();
               // WM_BringToBottom(ConfigWarnings->WinHandl);
                break;
            }
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}
