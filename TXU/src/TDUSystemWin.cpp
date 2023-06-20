#include "TDUIncludes.h"

TDUSystemWin::~TDUSystemWin(void) {
#if defined(S2TXU) || defined(ANBOOLOADER)
    OS_DeleteRSema(&SysWinSema);
#else
    delete SysWinSema;
#endif
}

TDUSystemWin::TDUSystemWin(void) {
#if defined(S2TXU) || defined(ANBOOLOADER)
    OS_CREATERSEMA(&SysWinSema);
    //WithProtection = false;
#else
    //ListSema = CreateMutex( NULL, FALSE, NULL );
    SysWinSema = new ANCriticalSection;
    AcquireCnt = 0;
#endif

    SysWin1    = new TDUSysWin1;
    SysWin2    = new TDUSysWin2;
    SysWin3    = new TDUSysWin3;
    SysWin4    = new TDUSysWin4;
    SysWin5    = new TDUSysWin5;

    SysWin1IsClosed    = true;
    SysWin2IsClosed    = true;
    SysWin3IsClosed    = true;
    SysWin4IsClosed    = true;
    SysWin5IsClosed    = true;
    CurrentSysWin      = TDU_NO_WIN;
    IsModified         = false;

}

void TDUSystemWin::CloseSystemWin(void) {
    Protect();
    if (!SysWin1IsClosed) {
        SysWin1->CloseSysWin();
        GUI_EndDialog(SysWin1->WinHandl, 0);
        while (!SysWin1IsClosed) {
            TSN_Delay(1);
        }
    } else if (!SysWin2IsClosed) {
        GUI_EndDialog(SysWin2->WinHandl, 0);
        while (!SysWin2IsClosed) {
            TSN_Delay(1);
        }
    } else if (!SysWin3IsClosed) {
        GUI_EndDialog(SysWin3->WinHandl, 0);
        while (!SysWin3IsClosed) {
            TSN_Delay(1);
        }
    } else if (!SysWin4IsClosed) {
        GUI_EndDialog(SysWin4->WinHandl, 0);
        while (!SysWin4IsClosed) {
            TSN_Delay(1);
        }
    } else if (!SysWin5IsClosed) {
        GUI_EndDialog(SysWin5->WinHandl, 0);
        while (!SysWin5IsClosed) {
            TSN_Delay(1);
        }
    } else if (!SensorDetails->IsClosed) {
        SensorDetails->IsClosed = true;
        GUI_EndDialog(SensorDetails->WinHandl, 0);
        while (!SensorDetails->IsClosed) {
            TSN_Delay(1);
        }
    }
    UnProtect();
    // Give the windows system a little time to close down the page
    //TSN_Delay(50);
}

void TDUSystemWin::SetButton(void) {
    SystemWindow->Protect();
    ButWindow->EnableButtons(true, true, false, false, true);
    ButWindow->ChangeButtonText(L_WORD167, L_WORD168, L_WORD237, L_WORD237, L_WORD18);
    switch (CurrentSysWin) {
    case TDU_SYSWIN1:
        SysWin1->ExecDialogBox(WinHandl);
        break;
    case TDU_SYSWIN2:
        SysWin2->ExecDialogBox(WinHandl);
        break;
    case TDU_SYSWIN3:
        SysWin3->ExecDialogBox(WinHandl);
        break;
    case TDU_SYSWIN4:
        SysWin4->ExecDialogBox(WinHandl);
        break;
    case TDU_SYSWIN5:
        SysWin5->ExecDialogBox(WinHandl);
        break;
    default:
        SysWin1->ExecDialogBox(WinHandl);
        break;
    }
    SystemWindow->UnProtect();
}

void TDUSystemWin::ButtonClicked(int ButtID) {
    Protect();
    switch (ButtID) {
    case TDU_BUTTON_ID_PW1: // < Prev
        {
            CloseSystemWin();
            switch (CurrentSysWin) {
            case TDU_SYSWIN1:
                SysWin5->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN2:
                SysWin1->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN3:
                SysWin2->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN4:
                SysWin3->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN5:
                SysWin4->ExecDialogBox(WinHandl);
                break;
            }

        }
        break;
    case TDU_BUTTON_ID_PW2: // > Next
        {
            CloseSystemWin();
            switch (CurrentSysWin) {
            case TDU_SYSWIN1:
                SysWin2->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN2:
                SysWin3->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN3:
                SysWin4->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN4:
                SysWin5->ExecDialogBox(WinHandl);
                break;
            case TDU_SYSWIN5:
                SysWin1->ExecDialogBox(WinHandl);
                break;
            }
        }
        break;
    case TDU_BUTTON_ID_PW3:
        switch (CurrentSysWin) {
        case TDU_SYSWIN1:
        case TDU_SYSWIN2:
        case TDU_SYSWIN4:
        case TDU_SYSWIN5:
            break;
        case TDU_SYSWIN3:
            for (int i = 0; i < 3; i++) {
                ButWindow->EnableButton(i, false);
            }
            SysWin3->SetupWin();
            break;
        }
        break;
    case TDU_BUTTON_ID_PW4:
        break;
    case TDU_BUTTON_ID_PW5:
        if (!SensorDetails->IsClosed) {
            SensorDetails->IsClosed = true;
            GUI_EndDialog(SensorDetails->WinHandl, 0);
            CurrentSysWin = SensorDetails->PreviousSysWin;
            ButWindow->EnableButton(0, true);
            ButWindow->EnableButton(1, true);
        } else {
            CloseSystemWin();
            MainWindow->SetPreviousWindow();
        }
        break;
    }
    UnProtect();
}

void TDUSystemWin::cbEventHandler(WM_MESSAGE *pMsg) {
    //WM_HWIN hWin =(pMsg->hWin);
    switch (pMsg->MsgId) {
    case WM_PAINT:
        {
            GUI_SetBkColor(TDU_C_BACK_DEFAULT);
            GUI_Clear();
            GUI_SetColor(TDU_C_TEXT_DEFAULT);
        }
        UpdateFields(true);
        break;
    case WM_CREATE:
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

void TDUSystemWin::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || PRogramObjectBase::WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        LocalString += KeyWord(C_TDU_SYSTEM_WIN) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_TDU_BACK_COLOR) + (AnsiString)BackColor + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_TDU_TEXT_COLOR) + (AnsiString)TextColor + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_TDU_CURRENT_SYSWIN) + (AnsiString)CurrentSysWin + CrLfStr;
        if (CurrentWinID != TDU_WARNING_WIN  ) {
            LocalString += TabStr1 + KeyWord(C_TDU_CURRENT_WIN) + (AnsiString)CurrentWinID + CrLfStr;
        }
        if (CargoWindow) {
            LocalString += TabStr1 + KeyWord(C_TDU_CARGO_WIN) + TabStr1;
            //	  LocalString +=TabStr2+KeyWord(C_TDU_VALUE_TAB);
            for (int i = 0; i < 3; i++) {
                LocalString += (AnsiString)CargoWindow->ValueTable[i + 2].ValueId + TabStr1;
            }
            LocalString += CrLfStr;
            //     LocalString +=KeyWord(C_TDU_WIN_END)+CrLfStr;
        }
        if (BallastWindow) {
            LocalString += TabStr1 + KeyWord(C_TDU_BALLAST_WIN) + TabStr1;
            for (int i = 0; i < 3; i++) {
                LocalString += (AnsiString)BallastWindow->ValueTable[i + 2].ValueId + TabStr1;
            }
            LocalString += CrLfStr;
            //     LocalString +=KeyWord(C_TDU_WIN_END)+CrLfStr;
        }
        if (ServiceWindow) {
            LocalString += TabStr1 + KeyWord(C_TDU_SERVICE_WIN) + TabStr1;
            for (int i = 0; i < 3; i++) {
                LocalString += (AnsiString)ServiceWindow->ValueTable[i + 2].ValueId + TabStr1;
            }
            LocalString += CrLfStr;
            //     LocalString +=KeyWord(C_TDU_WIN_END)+CrLfStr;
        }
        if (TankPressWindow) {
            LocalString += TabStr1 + KeyWord(C_TDU_TANKPRESS_WIN) + TabStr1;
            for (int i = 0; i < 3; i++) {
                LocalString += (AnsiString)TankPressWindow->ValueTable[i + 2].ValueId + TabStr1;
            }
            LocalString += CrLfStr;
            //     LocalString +=KeyWord(C_TDU_WIN_END)+CrLfStr;
        }
        if (LinePressWindow) {
            LocalString += TabStr1 + KeyWord(C_TDU_LINEPRESS_WIN) + TabStr1;
            for (int i = 0; i < 3; i++) {
                LocalString += (AnsiString)LinePressWindow->ValueTable[i + 2].ValueId + TabStr1;
            }
            LocalString += CrLfStr;
            //     LocalString +=KeyWord(C_TDU_WIN_END)+CrLfStr;
        }
        if (TempWindow) {
            LocalString += TabStr1 + KeyWord(C_TDU_TEMP_WIN) + TabStr1;
            for (int i = 0; i < 3; i++) {
                LocalString += (AnsiString)TempWindow->ValueTable[i + 2].ValueId + TabStr1;
            }
            LocalString += CrLfStr;
            //     LocalString +=KeyWord(C_TDU_WIN_END)+CrLfStr;
        }
        if (VoidSpaceWindow) {
            LocalString += TabStr1 + KeyWord(C_TDU_VOIDSPACE_WIN) + TabStr1;
            for (int i = 0; i < 3; i++) {
                LocalString += (AnsiString)VoidSpaceWindow->ValueTable[i + 2].ValueId + TabStr1;
            }
            LocalString += CrLfStr;
            //     LocalString +=KeyWord(C_TDU_WIN_END)+CrLfStr;
        }

        LocalString += KeyWord(C_PRO_END) + CrLfStr; //C_TDU_WIN_END
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool TDUSystemWin::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning((AnsiString)"TDU setting:\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                RestoreSettingsWarning((AnsiString)"TDU setting:\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_TDU_CURRENT_WIN:
                {
                    int tmpCurrentWinID = SettingsString->ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                    if (tmpCurrentWinID != TDU_WARNING_WIN  ) {
                        CurrentWinID = tmpCurrentWinID;
                    }
                }
                break;
            case C_TDU_CURRENT_SYSWIN:
                CurrentSysWin = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_TDU_BACK_COLOR:
                BackColor = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_TDU_TEXT_COLOR:
                TextColor = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_TDU_CARGO_WIN:
                if (CargoWindow) {
                    for (int i = 0; i < 3 && NoError; i++) {
                        int value = SettingsString->ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            CargoWindow->ValueTable[i + 2].ValueId = value;
                        }
                    }
                    CargoWindow->PaintnewHeading();
                }
                break;
            case C_TDU_BALLAST_WIN:
                if (BallastWindow) {
                    for (int i = 0; i < 3 && NoError; i++) {
                        int value = SettingsString->ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            BallastWindow->ValueTable[i + 2].ValueId = value;
                        }
                    }
                    BallastWindow->PaintnewHeading();
                }
                break;
            case C_TDU_SERVICE_WIN:
                if (ServiceWindow) {
                    for (int i = 0; i < 3 && NoError; i++) {
                        int value = SettingsString->ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            ServiceWindow->ValueTable[i + 2].ValueId = value;
                        }
                    }
                    ServiceWindow->PaintnewHeading();
                }
                break;
            case C_TDU_TANKPRESS_WIN:
                if (TankPressWindow) {
                    for (int i = 0; i < 3 && NoError; i++) {
                        int value = SettingsString->ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            TankPressWindow->ValueTable[i + 2].ValueId = value;
                        }
                    }
                    TankPressWindow->PaintnewHeading();
                }
                break;
            case C_TDU_LINEPRESS_WIN:
                if (LinePressWindow) {
                    for (int i = 0; i < 3 && NoError; i++) {
                        int value = SettingsString->ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            LinePressWindow->ValueTable[i + 2].ValueId = value;
                        }
                    }
                    LinePressWindow->PaintnewHeading();
                }
                break;
            case C_TDU_TEMP_WIN:
                if (TempWindow) {
                    for (int i = 0; i < 3 && NoError; i++) {
                        int value = SettingsString->ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            TempWindow->ValueTable[i + 2].ValueId = value;
                        }
                    }
                    TempWindow->PaintnewHeading();
                }
                break;
            case C_TDU_VOIDSPACE_WIN:
                if (VoidSpaceWindow) {
                    for (int i = 0; i < 3 && NoError; i++) {
                        int value = SettingsString->ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            VoidSpaceWindow->ValueTable[i + 2].ValueId = value;
                        }
                    }
                    VoidSpaceWindow->PaintnewHeading();
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
// Refresh window:
    //MainWindow->SetWindow(CurrentWinID);
    TSN_Delay(500);
    return (NoError);
}
void TDUSystemWin::SetModifiedFlag(void) {
    IsModified = true;
    SignalSaveSettings(FLASH_SAVE_SETTINGS);
}

void TDUSystemWin::Protect(void) {
    if (this) {
#ifdef S2TXU
        OS_Use(&SysWinSema);
#else
        //if ( !AcquireCnt ) {
        AcquireCnt++;
        SysWinSema->Acquire();
        //}
#endif
    }
}

void TDUSystemWin::UnProtect(void) {
    if (this) {
#ifdef S2TXU
        OS_Unuse(&SysWinSema);
#else
        //if ( AcquireCnt ) {
        AcquireCnt--;
        //}else{
        SysWinSema->Release();
        //}
#endif
    }
}


void TDUSystemWin::ChangeSystemWindow(int NewWindow) {
    Protect();
    CurrentSysWin = NewWindow;
    UnProtect();
}
