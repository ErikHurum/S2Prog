#include "TDUIncludes.h"

static void cbWin1(WM_MESSAGE *pMsg) {
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) {
    case WM_NOTIFY_PARENT:
        {
            int NCode, Id;
            Id = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
            NCode = pMsg->Data.v;                               /* Notification code */
            switch (NCode) {
            case WM_NOTIFICATION_RELEASED:
                {
                    LevelSwitchWindow->UnitClicked(hWin, Id);
                }
                break;
            }
        }
        break;
    case WM_PAINT:
        GUI_SetBkColor(TDU_C_BACK_DEFAULT);
        GUI_Clear();
        GUI_SetColor(TDU_C_TEXT_DEFAULT);
        break;
    case WM_CREATE:
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

static void cbWin0(WM_MESSAGE *pMsg) {
    //WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) {
    case WM_PAINT:
//			GUI_SetBkColor(GUI_RED);
        GUI_SetBkColor(TDU_C_PW_BACK);
        GUI_Clear();
        break;
    case WM_CREATE:
        break;
    case MESSAGE_YES_RETURN:
        {
            AnsiString TmpString;
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case SVT_TANK_STATE_STR_LSW:    /* Disable all level switches */
                LibPutValue(SVT_TANK_STATE_STR_LSW, PROTanksystemUnit::MySelf->IDNumber, PROSystemData::TXUSystemData, tSeaGoing);
                break;
            case GUI_ID_BUTTON1:    /* Level Button */
                break;
            }
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

TDULevelSwitchWin::~TDULevelSwitchWin(void) {
}

TDULevelSwitchWin::TDULevelSwitchWin(void) {
    MainWinHandl = 0;
    ScrollHandl = 0;
    LevelSwicthSystem = LSW_NOT_DEFINED;
    for (int i = 0; i < LSW_MAX_ENTRIES; i++) {
        TankButton[i] = 0;
    }
    StartX = 0;
    StartY = (LineHeight - 2);
    CurrentPage = 0;
    PageCount = 0;
    LastPage = -1;
    FirstPage = 1000; // Just start with a stupid hig number
    if (!PROLevelSwitch::ObjVector.empty()) {
        //	ScrollHandl   = SCROLLBAR_Create(PWinXSize-19, 0, 18, PWinYSize,WinHandl, 999, WM_CF_SHOW, SCROLLBAR_CF_VERTICAL);
        //	SCROLLBAR_SetNumItems(ScrollHandl,(NumberOfUnits+1));
        //	SCROLLBAR_SetPageSize(ScrollHandl,NumUnitsOnPage);
        unsigned MaxStrLen = 0;
        for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
            PROLevelSwitch *TempElement = (PROLevelSwitch *)PROLevelSwitch::ObjVector[i];
            FirstPage = min(FirstPage, TempElement->Page);
        }
        for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
            PROLevelSwitch *TempElement = (PROLevelSwitch *)PROLevelSwitch::ObjVector[i];
            Page.insert(TempElement->Page - FirstPage+1);
            XPos.insert(TempElement->XPos);
            YPos.insert(TempElement->YPos);
            MaxStrLen = MAX(MaxStrLen, TempElement->Name.length());
        }
        PageCount = Page.size();
        if (!PageCount) {
            PageCount = 1;
        }
        int XPosCnt      = XPos.size();
        int YPosCnt      = YPos.size();
        int XStep        = PWinXSize / (XPosCnt + 1);
        int YStep        = (PWinYSize - 8) / (YPosCnt + 1);
        int BWidth       = 45;
        int BHeight      = 20;
        int BXCorrection = BWidth / 2;
        int BYCorrection = BHeight / 2;
        MainWinHandl     = WM_CreateWindowAsChild(0, 0, PWinXSize, PageCount * PWinXSize, WinHandl, WM_CF_SHOW, cbWin0, 0);
        VisibleWinHandl  = WM_CreateWindowAsChild(0, 0, PWinXSize, PageCount * PWinXSize, MainWinHandl, WM_CF_SHOW, cbWin1, 0);
        WM_EnableMemdev(MainWinHandl);
        WM_EnableMemdev(VisibleWinHandl);
        if (MaxStrLen > 5 && XPosCnt < 4) {
            BWidth = 65;
        }
        for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
            PROLevelSwitch *TempElement = (PROLevelSwitch *)PROLevelSwitch::ObjVector[i];
            int XPosition = XStep * TempElement->XPos - BXCorrection;
            int YPosition = PWinYSize * (TempElement->Page - FirstPage) + YStep * TempElement->YPos - BYCorrection;
            TankButton[i] = BUTTON_CreateEx(XPosition, YPosition, BWidth, BHeight, VisibleWinHandl, WM_CF_SHOW, 0, LSW_BUTTON0 + i);
            BUTTON_SetText(TankButton[i], TempElement->Name.c_str());
        }
    }
}

void TDULevelSwitchWin::SetButton(void) {
    if (PROLevelSwitch::Adjustable) {
        bool ButtonEnable[NUMBER_OF_BUTTONS] = {
            (bool)(PageCount > 1),
            (bool)(PageCount > 1),
            true,
            true,
            true
        };
        ButWindow->EnableButtons(ButtonEnable);
        ButWindow->ChangeButtonText(L_WORD87, L_WORD88, L_WORD3, L_WORD4, L_WORD868);
    } else {
        bool ButtonEnable[NUMBER_OF_BUTTONS] = {
            (bool)(PageCount > 1),
            (bool)(PageCount > 1),
            true,
            true,
            false
        };
        ButWindow->EnableButtons(ButtonEnable);
        ButWindow->ChangeButtonText(L_WORD87, L_WORD88, L_WORD3, L_WORD4, L_WORD237);
    }
    Paintnew();
}

void TDULevelSwitchWin::PWTimer(void) {
    if (!PROLevelSwitch::ObjVector.empty()) {
        RefreshWindow();
    }
}

void TDULevelSwitchWin::SetButtonColours(BUTTON_Handle TButton, PROLevelSwitch *LSwitchPtr) {

    if (LSwitchPtr) {
        int BackColor;
        if (LSwitchPtr->IsWarning) {
            BackColor = TDU_C_AL_BACK_ACTIVE_95;
        } else {
            BackColor = TDU_C_AL_BACK_ACTIVE;
        }
        switch (LSwitchPtr->LevelSwitchAlPtr->State) {
        case AlarmBasic::AlActive:
            // Let us blink
            if (BUTTON_GetBkColor(TButton, 0) != BackColor) {
                BUTTON_SetBkColor(TButton, 0, BackColor);
                BUTTON_SetTextColor(TButton, 0, TDU_C_AL_TEXT_ACTIVE);
            } else {
                BUTTON_SetBkColor(TButton, 0, TDU_C_AL_TEXT_ACTIVE);
                BUTTON_SetTextColor(TButton, 0, BackColor);
            }
            break;
        case AlarmBasic::AlAknowledged:
            if (BUTTON_GetBkColor(TButton, 0) != BackColor) {
                BUTTON_SetBkColor(TButton, 0, BackColor);
                BUTTON_SetTextColor(TButton, 0, TDU_C_AL_TEXT_ACTIVE);
            }
            break;
        case AlarmBasic::AlIdle:
        default:
            if (LSwitchPtr->HWFailure
                || LSwitchPtr->LevelSwitchSensor->ActiveAlarms
                || !LSwitchPtr->LevelSwitchSensor->Enable
                || !LSwitchPtr->LevelSwitchAlPtr->Enable) {
                //if ( BUTTON_GetBkColor(  TButton, 0)!=TDU_C_AL_BACK_WARNING ) {
                BUTTON_SetBkColor(TButton, 0, TDU_C_AL_BACK_WARNING);
                BUTTON_SetTextColor(TButton, 0, TDU_C_AL_TEXT_WARNING);
                //}
            } else if (BUTTON_GetBkColor(TButton, 0) != TDU_C_AL_BACK_NOAL) {
                BUTTON_SetBkColor(TButton, 0, TDU_C_AL_BACK_NOAL);
                BUTTON_SetTextColor(TButton, 0, TDU_C_AL_TEXT_NOAL);
            }
            break;
        }
    } else {
        if (BUTTON_GetBkColor(TButton, 0) != TDU_C_BU_BACK) {
            WM_HideWindow(TButton);
            BUTTON_SetBkColor(TButton, 0, TDU_C_BU_BACK);
            BUTTON_SetTextColor(TButton, 0, TDU_C_BU_TEXT);
        }
    }

}
void TDULevelSwitchWin::RefreshWindow(void) {
    for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
        PROLevelSwitch *TempElement = (PROLevelSwitch *)PROLevelSwitch::ObjVector[i];
        SetButtonColours(TankButton[i], TempElement);
    }
}

void TDULevelSwitchWin::MoveWin(void) {
    int Y = -CurrentPage * PWinYSize;
    //int Y =  -CurrentPage*10;
    // if(Y==0) Y=StartY;
//  WM_MoveWindow(MainWinHandl, StartX, Y);
    WM_MoveChildTo(VisibleWinHandl, StartX, Y);
    //SetGuiEvent(PWEventHandl,1,&PresentWindowsTCB);
}

void TDULevelSwitchWin::ButtonClicked(int ButtID) {
    if (!PROLevelSwitch::ObjVector.empty()) {
        switch (ButtID) {
        case TDU_BUTTON_ID_PW1:
            if (CurrentPage  <= 0) {
                //	CurrentPage = PageCount-1;
                CurrentPage = 0;
            } else {
                CurrentPage--;
            }
            MoveWin();
            break;
        case TDU_BUTTON_ID_PW2:
            if (CurrentPage >= (PageCount - 1 )) {
//					CurrentPage = 0;
                CurrentPage = PageCount - 1 ;
            } else {
                CurrentPage++;
            }
            MoveWin();
            break;
        case TDU_BUTTON_ID_PW3:
            LibPutValue(SVT_TANK_STATE_STR_LSW, PROTanksystemUnit::MySelf->IDNumber, PROSystemData::TXUSystemData, tLoad);
            break;
        case TDU_BUTTON_ID_PW4:
            ConfirmMessageBox->Exec(MainWinHandl, L_WORD854, L_WORD862, SVT_TANK_STATE_STR_LSW);
            //
            break;
        case TDU_BUTTON_ID_PW5:
            break;
        }
    }
}

void TDULevelSwitchWin::UnitClicked(WM_HWIN hWin, int ButtID) {
    switch (ButtID) {
    case TDU_BUTTON_ID_PW4:
        LibPutValue(SVT_TANK_STATE_STR_LSW, PROTanksystemUnit::MySelf->IDNumber, PROSystemData::TXUSystemData, tSeaGoing);
        break;
    default:
        {
            bool Found = false;
            for (unsigned i = 0; !Found && i < PROLevelSwitch::ObjVector.size(); i++) {
                PROLevelSwitch *TempElement = (PROLevelSwitch *)PROLevelSwitch::ObjVector[i];
                if (TempElement && (ButtID == WM_GetId(TankButton[i]))) {
                    Found = true;
                    AlarmLevelSwitch *AlPtr = TempElement->LevelSwitchAlPtr;
                    switch (AlPtr->State) {
                    case AlarmBasic::AlActive :
                        AlPtr->SendData(CMD_PRO_ALARM_ACK);
                        break;
                    case AlarmBasic::AlIdle :
                    case AlarmBasic::AlAknowledged:
                    case AlarmBasic::AlBlocked :
                        break;
                    }
                }
            }
        }
        break;
    }
}

void TDULevelSwitchWin::cbEventHandler(WM_MESSAGE *pMsg) {
    //WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) {
    case MESSAGE_YES_RETURN:
        {
            //int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            //LibPutValue( SVT_WI_PROTECTION,CurrentWIPtr,ProtPlate);
            LevelSwitchWindow->Paintnew();
        }
        break;
    case WM_NOTIFY_CHILD_HAS_FOCUS:

        break;
    case WM_NOTIFY_PARENT:
        {
            int NCode; //, Id;
//			Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
            NCode = pMsg->Data.v;                               /* Notification code */
            switch (NCode) {
            case WM_NOTIFICATION_RELEASED:      /* React only if released */
                break;
            case WM_NOTIFICATION_VALUE_CHANGED:
/*						{
                            if ( XScrollPos != SCROLLBAR_LibGetValue(ScrollHandl) ) {
                                XScrollPos = SCROLLBAR_GetValue(ScrollHandl);
                                WM_MoveTo(MainWinHandl,0,0-XScrollPos*LineHeight*(LineHeight-2));
                            }
                        }*/
                break;
            }
        }
        break;
    case WM_PAINT:
        GUI_SetBkColor(TDU_C_PW_BACK);
        GUI_Clear();
        GUI_SetColor(TDU_C_PW_TEXT);
        GUI_SetTextMode(GUI_TM_TRANS);
        GUI_SetFont(&TDU_FONT_BIG);
        UpdateFields(true);
        //GUI_DispStringAt(FindDictionaryWord(TSN_LEVELSWITCH_APP).c_str(),70,80);
        break;
    case WM_CREATE:
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}
