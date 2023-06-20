#include "TDUIncludes.h"
TDUCalDataWin::TDUCalDataWin(void) {
    CurrentHWUnit       = NULL;
    UserTouch           = false;
    TimerCount          = 0;
    PreviousSysWin      = TDU_NO_WIN;
    IsClosed            = true;
    LevOffsetWinEnable = true;
}

TDUCalDataWin::~TDUCalDataWin(void) {
}

const GUI_WIDGET_CREATE_INFO TDUCalDataWin::aDialogCreate[] =
{
    { FRAMEWIN_CreateIndirect,  "Calibration Data", TDU_CALDATA_WIN,  0,   0, 286, 198, FRAMEWIN_CF_MAXIMIZED, 0 },
    { TEXT_CreateIndirect,      "SnsInfo", GUI_ID_TEXT0,  2,   0, 281,  15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect,      "SerNum", GUI_ID_TEXT1,  2,  15,  38,  15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect,      NULL, GUI_ID_EDIT0,  45,  15,  50,  15, TEXT_CF_LEFT },
    { CHECKBOX_CreateIndirect,  NULL, GUI_ID_CHECK0, 138,  15,  80,  15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect,      NULL, GUI_ID_TEXT6, 210,  15,  50,  15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect,      "Gain", GUI_ID_TEXT2,  2,  30,  38,  15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect,      NULL, GUI_ID_EDIT1, 45,  30,  50,  15, TEXT_CF_RIGHT },
    { TEXT_CreateIndirect,      "", GUI_ID_TEXT3, 138,  30, 130,  15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect,      "Offset", GUI_ID_TEXT4,  2,  45,  38,  15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect,      NULL, GUI_ID_EDIT2, 45,  45,  50,  15, TEXT_CF_RIGHT },
    { TEXT_CreateIndirect,      "", GUI_ID_TEXT5, 95,  45,  40,  15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect,      "Table offset", GUI_ID_TEXT9, 138,  45,  70,  15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect,      NULL, GUI_ID_EDIT4, 210,  45,  50,  15, TEXT_CF_RIGHT },

    { TEXT_CreateIndirect,      "Value", GUI_ID_TEXT7,  2,  60,  38,  15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect,      NULL, GUI_ID_EDIT3, 45,  60,  50,  15, TEXT_CF_RIGHT },
    { TEXT_CreateIndirect,      "", GUI_ID_TEXT8, 95,  60,  40,  15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect,      "Level offset", GUI_ID_TEXT10, 138,  60,  70,  15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect,      NULL, GUI_ID_EDIT5, 210,  60,  50,  15, TEXT_CF_RIGHT },

    { LISTVIEW_CreateIndirect,  NULL, GUI_ID_LISTVIEW0,  0,  75, 281, 105, 0 },

};


void TDUCalDataWin::ExecDialogBox(WM_HWIN hCurrentWin) {
    SystemWindow->Protect();
    if ( IsClosed ) {
        IsClosed = false;
        WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), &cbSysWin,
                                       hCurrentWin, 0, 0);
        PreviousSysWin = SystemWindow->CurrentSysWin;
        SystemWindow->CurrentSysWin = TDU_CALWIN;
        ButWindow->EnableButton(0, false);
        ButWindow->EnableButton(1, false);

        WM_EnableMemdev(WinHandl);
        GetDialogHandles();
    } else {
        WM_BringToTop(WinHandl);
    }
    SystemWindow->UnProtect();
}

/*********************************************************************
*
*       CreateMultiPage
*
*/
void TDUCalDataWin::CreatePage(WM_HWIN hCurrentWin, PRogramObjectBase *OwnerPtr, PROIOComponent *PROPtr, AnsiString SnsInf) {
    LevOffsetWinEnable = true;
    /* Create the frame window */
    Owner       = OwnerPtr;
    SnsPtr  = PROPtr;
    SnsInfo = SnsInf;

    if ( IsClosed ) {
        IsClosed = false;
        WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), &cbSysWin,
                                       hCurrentWin, 0, 0);
        PreviousSysWin = SystemWindow->CurrentSysWin;
        SystemWindow->CurrentSysWin = TDU_CALWIN;
        ButWindow->EnableButton(0, false);
        ButWindow->EnableButton(1, false);
        WM_EnableMemdev(WinHandl);
        GetDialogHandles();
        {
            const GUIKey Words[] = {
                { TDU_CALDATA_WIN, 0, L_WORD546 },
                { GUI_ID_TEXT1, 0, L_WORD547 }, // Serial number text
                { GUI_ID_CHECK0, 0, L_WORD1 },  // Enable
                { GUI_ID_TEXT2, 0, L_WORD126 }, // Gain text
                { GUI_ID_TEXT4, 0, L_WORD127 },   // Offset text
                { GUI_ID_TEXT7, 0, L_WORD128 },    // Value text
                                                   // { GUI_ID_TEXT9, 0, L_WORD983 },   // Table offset text
                { GUI_ID_TEXT9, 0, 1000 },   // Table offset text
                { GUI_ID_TEXT10, 0, L_WORD550 },   // Level offset text
            };
            AddToSKeyList((GUIKey *)Words, NELEMENTS(Words));
        }
        {
            GUIUpdateKey UpdateValues[] = {
                { GUI_ID_EDIT0, 0, SnsPtr, SVT_AI_SERIAL_NUMBER, 0,           0, L_WORD547, NULL },
                { GUI_ID_EDIT1, 0, SnsPtr, SVT_AI_GAIN, 0,           0, L_WORD126, NULL },
                { GUI_ID_EDIT2, 0, SnsPtr, SVT_AI_OFFSET, 0, GUI_ID_TEXT5, L_WORD127, NULL },
                { GUI_ID_EDIT3, 0, SnsPtr, SVT_AI_CALC_VAL, 0, GUI_ID_TEXT8, L_WORD128, NULL },
                { GUI_ID_EDIT4, 0, Owner, SVT_TABLE_OFFSET, 0,           0, L_WORD983, NULL },
                { GUI_ID_EDIT5, 0, Owner, SVT_LEVEL_OFFSET, 0,           0, L_WORD550, NULL },
                { GUI_ID_CHECK0, 0, SnsPtr, SVT_AI_ENABLE, 0,           0, L_WORD1, NULL },
                { GUI_ID_TEXT3, 0, SnsPtr, SVT_AI_RANGE, 0,           0,         0, NULL },
                { GUI_ID_TEXT6, 0, SnsPtr, SVT_IO_CH_EEP_SNS_STAT, 0,           0,         0, NULL },
            };
            SetUpWidgetInfoTable((GUIUpdateKey *)UpdateValues, GUI_COUNTOF(UpdateValues));
        }
    } else {
        WM_BringToTop(WinHandl);
    }
    AnsiString InfoStr     = SnsInfo + "(" + LibGetValue(SVT_AI_LOCATION, SnsPtr) + ")";
    SetText(GUI_ID_TEXT0, 0, InfoStr);
}


void TDUCalDataWin::Update(void) {
    UpdateFields(false);
    switch ( SnsPtr->Type ) {
    case C_AI_LeSw_ADCard   :
    case C_AI_LeSw_Valcom   :
    case C_AI_LeSw_API      :
    case C_AI_LeSw_HS       :
    case C_AI_LeSw_mA       :
        break;
    case C_AI_LeSw_Vega     :
    case C_AI_LeSw_Vega62   :
    case C_AI_LeSw_Vega64   :
        ChangeText(1);
        break;
    case C_AI_1728          :
    case C_AI_P906_0110     :
    case C_AI_P906_0111     :
        {
            ChangeText(0);
            const int ValKey1[] = { SVT_AI_CAL_DATA_FRO, SVT_AI_CAL_DATA_G1, SVT_AI_CAL_DATA_G2, SVT_AI_CAL_DATA_G3 };
            const int ValKey2[] = { SVT_AI_CAL_DATA_NL1, SVT_AI_CAL_DATA_NL2 };
            int RCnt = 0;
            AIPressSensor_mV *mVSns = (AIPressSensor_mV *)SnsPtr;
            for ( int Row = 0; Row < NELEMENTS(ValKey1); Row++ ) {
                for ( int Col = 0; Col < MAX_MV_CALDATA; Col++ ) {
                    AnsiString ValStr = LibGetValue(ValKey1[Row], Col, mVSns);
                    LISTVIEW_SetItemText(SnsListView, Col + 1, RCnt, ValStr.c_str());
                }
                RCnt++;
            }
            for ( int Row = 0; Row < NELEMENTS(ValKey2); Row++ ) {
                AnsiString ValStr = LibGetValue(ValKey2[Row], mVSns);
                LISTVIEW_SetItemText(SnsListView, 1, RCnt++, ValStr.c_str());
            }
        }
        break;
    case C_AI_Radar_Hart        :
    case C_AI_AirPurge          :
    case C_AI_MB_Press_mA       :
    case C_AI_MB_DiffPre_mA     :
        ChangeText(0);
        break;
    case C_AI_ATM_N_Ex          :
    case C_AI_ATM_Ex            :
    case C_AI_ATM_Ex_H          :
    case C_AI_ATM_N_Ex_0_1      :
    case C_AI_Gen_4_20mA        :
    case C_AI_DIFF_PRESSURE_mA  :
    case C_AI_Radar_4_20mA      :
    case C_AI_Float_4_20mA      :
    case C_AI_INC1_MACRON       :
    case C_AI_INC2_MACRON       :
        ChangeText(0);
        {
            const char *ValTxt[2] = { "4", "20" };
            for ( int Col = 0; Col < 2; Col++ ) {
                LISTVIEW_SetItemText(SnsListView, Col + 1, 0, ValTxt[Col]);
            }
        }
        break;
    case C_AI_INC1_N2       :
    case C_AI_INC2_N2       :
        break;
    case C_AI_Pt100         :
    case C_AI_Pt1000        :
    case C_AI_TEMP_AD590    :
    case C_AI_TEMP_mA       :
    case C_AI_WATERINGRESS  :
    case C_AI_WATERINGR_MAIN:
    case C_AI_WATERINGR_PRE :
    case C_AI_WATERINGR_TEMP:
    case C_AI_WashTrackSensor  :
        break;
    }
}


/*********************************************************************
*
* Dialog procedure
*/
void TDUCalDataWin::GetDialogHandles(void) {
    SnsListView         = WM_GetDialogItem(WinHandl, GUI_ID_LISTVIEW0);

    LISTVIEW_SetFont(SnsListView, &TDU_FONT_ST);
    InitSysWin();
}

void TDUCalDataWin::InitSysWin(void) {
    AnsiString LocationStr = LibGetValue(SVT_AI_LOCATION, SnsPtr);
    AnsiString InfoStr     = SnsInfo + "(" + LocationStr + ")";
    SetText(GUI_ID_TEXT0, 0, SnsInfo);

    switch ( SnsPtr->Type ) {
    case C_AI_1728          :
    case C_AI_P906_0110     :
    case C_AI_P906_0111     :
        {
            const char *Title[] = { "FRO", "G1", "G2", "G3", "NL1", "NL2" };
            //WM_SetScrollbarV(SnsListView, 1);
            LISTVIEW_SetGridVis(SnsListView, 1); //Sets the visibility
            LISTVIEW_SetLBorder(SnsListView, 2);
            LISTVIEW_SetRBorder(SnsListView, 1);
            LISTVIEW_AddColumn(SnsListView,  30,  "", GUI_TA_LEFT);
            LISTVIEW_AddColumn(SnsListView,  50,  "0%", GUI_TA_RIGHT);
            LISTVIEW_AddColumn(SnsListView,  50,  "40%", GUI_TA_RIGHT);
            LISTVIEW_AddColumn(SnsListView,  50,  "60%", GUI_TA_RIGHT);
            LISTVIEW_AddColumn(SnsListView,  50,  "100%", GUI_TA_RIGHT);
            for ( int l = 0; l < NELEMENTS(Title); l++ ) {
                LISTVIEW_AddRow(SnsListView, NULL);
            }
            ClearList(Title);
        }
        break;
    case C_AI_ATM_N_Ex      :
    case C_AI_ATM_Ex        :
    case C_AI_ATM_Ex_H      :
    case C_AI_ATM_N_Ex_0_1  :
    case C_AI_Gen_4_20mA    :
        {
            const char *Title[] = { "FRO" };
            LISTVIEW_SetGridVis(SnsListView, 1); //Sets the visibility
            LISTVIEW_SetLBorder(SnsListView, 2);
            LISTVIEW_SetRBorder(SnsListView, 1);
            LISTVIEW_AddColumn(SnsListView,  30,  "", GUI_TA_LEFT);
            LISTVIEW_AddColumn(SnsListView,  50,  "0%", GUI_TA_RIGHT);
            LISTVIEW_AddColumn(SnsListView,  50,  "100%", GUI_TA_RIGHT);
            for ( int l = 0; l < NELEMENTS(Title); l++ ) {
                LISTVIEW_AddRow(SnsListView, NULL);
            }
            ClearList(Title);
        }
        break;
    case C_AI_INC1_N2        :
    case C_AI_INC2_N2        :
        break;               
    case C_AI_Radar_4_20mA   :
    case C_AI_Radar_Hart     :
    case C_AI_AirPurge       :
    case C_AI_Float_4_20mA   :
    case C_AI_Pt100          :
    case C_AI_Pt1000         :
    case C_AI_TEMP_AD590     :
    case C_AI_TEMP_mA        :
    case C_AI_LeSw_ADCard    :
    case C_AI_WATERINGRESS   :
    case C_AI_WATERINGR_MAIN :
    case C_AI_WATERINGR_PRE  :
    case C_AI_WATERINGR_TEMP :
    case C_AI_WashTrackSensor:
    case C_AI_INC1_MACRON    :
    case C_AI_INC2_MACRON    :

        {

            GUIUpdateKey UpdateValues[] = {
                { GUI_ID_EDIT4, 0, SensorDetails->GetOwner(), SVT_TABLE_OFFSET, 0, 0, L_WORD983, NULL },
                { GUI_ID_EDIT5, 0, SensorDetails->GetOwner(), SVT_LEVEL_OFFSET, 0, 0, L_WORD550, NULL },
            };
            for ( unsigned i = 0; i < NELEMENTS(UpdateValues); i++ ) {
                SensorDetails->ChangeDWord(UpdateValues[i].GUIId, UpdateValues[i].InputMsgWord, UpdateValues[i].ValueKey, UpdateValues[i].Obj);
            }
        }
        break;
    case C_AI_LeSw_Vega     :
    case C_AI_LeSw_Vega62   :
    case C_AI_LeSw_Vega64   :
        {
            GUIUpdateKey UpdateValues[] = {
                { GUI_ID_EDIT4, 0, SensorDetails->GetSnsPtr(), SVT_MA_OFF, 0, 0, L_WORD1000, NULL },
                { GUI_ID_EDIT5, 0, SensorDetails->GetSnsPtr(), SVT_MA_ON, 0, 0, L_WORD1001, NULL },
            };
            for ( unsigned i = 0; i < NELEMENTS(UpdateValues); i++ ) {
                SensorDetails->ChangeDWord(UpdateValues[i].GUIId, UpdateValues[i].InputMsgWord, UpdateValues[i].ValueKey, UpdateValues[i].Obj);
            }
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Note that numbe of elements in title must match the number of rows!
//
////////////////////////////////////////////////////////////////////////

void TDUCalDataWin::ClearList(const char *Title[]) {
    int NRow = LISTVIEW_GetNumRows(SnsListView);
    int NCol = LISTVIEW_GetNumColumns(SnsListView);
    for ( int Row = 0; Row < NRow; Row++ ) {
        LISTVIEW_SetItemText(SnsListView, 0, Row, Title[Row]);
        for ( int Col = 1; Col < NCol; Col++ ) {
            LISTVIEW_SetItemText(SnsListView, Col, Row, "");
        }
    }
    //UpdateSysWin();
}

PROIOComponent* 	TDUCalDataWin::GetSnsPtr(void) {
    return SnsPtr;
}
PRogramObjectBase*  TDUCalDataWin::GetOwner(void) {
    return Owner;
}


void TDUCalDataWin::cbSysWin(WM_MESSAGE *pMsg) {
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch ( pMsg->MsgId ) {
    case WM_DELETE:
        //SensorDetails->CloseWin(&SensorDetails->IsClosed);
        SensorDetails->IsClosed = true;
        break;
    case WM_PAINT:
        GUI_DrawLine(286 / 2 - 10, 15, 286 / 2 - 10, 70);
        SensorDetails->UpdateLanguage();
        break;
    case WM_INIT_DIALOG:
        SensorDetails->FirstTime = true;
        break;
    case WM_KEY:
        switch ( ((WM_KEY_INFO *)(pMsg->Data.p))->Key ) {
        case GUI_KEY_ESCAPE:
            GUI_EndDialog(hWin, 1);
            break;
        case GUI_KEY_ENTER:
            GUI_EndDialog(hWin, 0);
            break;
        }
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
        NCode = pMsg->Data.v;                               /* Notification code */
        switch ( NCode ) {
        case WM_NOTIFICATION_SEL_CHANGED:       /* React only if released */
            switch ( Id ) {
            case GUI_ID_DROPDOWN0: /* Select TCU */
                break;
            default:
                break;
            }
            break;
        case WM_NOTIFICATION_RELEASED:      /* React only if released */
            switch ( Id ) {
            case GUI_ID_CHECK0:
            case GUI_ID_CHECK1:
            case GUI_ID_CHECK2:
            case GUI_ID_CHECK3:
            case GUI_ID_CHECK4:
                SensorDetails->CHECKBOX_UpdateValue(Id);
                break;
            case GUI_ID_CLOSE: /* Close Button */
                if ( !SensorDetails->IsClosed ) {
                    GUI_EndDialog(hWin, 0);
                }
                SystemWindow->ChangeSystemWindow(SensorDetails->PreviousSysWin);
                ButWindow->EnableButton(0, true);
                ButWindow->EnableButton(1, true);
                break;
            default:
                break;
            }
            break;
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            SensorDetails->EDIT_InputValue(ValueId, StringBuf);
        }
        break;
    case WM_TOUCH_CHILD:
        {
            Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
            NCode = pMsg->Data.v;                               /* Notification code */
            //char *Msg;
            switch ( Id ) {
            case GUI_ID_EDIT0:
            case GUI_ID_EDIT1:
            case GUI_ID_EDIT2:
            case GUI_ID_EDIT3:
            case GUI_ID_EDIT4:
            case GUI_ID_EDIT5:
                SensorDetails->EDIT_ExecKeyboard(Id);
                break;
            }
        }
        break;

    default:
        WM_DefaultProc(pMsg);
        break;

    }
}

void TDUCalDataWin::ChangeText(int Index) {
    switch ( Index ) {
    case 0:
        {
            const GUIKey Words[] = {
                { GUI_ID_TEXT9, 0, L_WORD983 },   // Table Offset
                { GUI_ID_TEXT10, 0, L_WORD550 },   // Level Offset
            };
            GUIUpdateKey UpdateValues[] = {
                { GUI_ID_EDIT4, 0, SensorDetails->GetOwner(), SVT_TABLE_OFFSET, 0, 0, L_WORD983, NULL },
                { GUI_ID_EDIT5, 0, SensorDetails->GetOwner(), SVT_LEVEL_OFFSET, 0, 0, L_WORD550, NULL },
            };
            for ( unsigned i = 0; i < NELEMENTS(Words); i++ ) {
                ChangeSWord(Words[i].GUIId, Words[i].GUIIndex, Words[i].WordKey);
            }
            for ( unsigned i = 0; i < NELEMENTS(UpdateValues); i++ ) {
                ChangeDWord(UpdateValues[i].GUIId, UpdateValues[i].InputMsgWord, UpdateValues[i].ValueKey, UpdateValues[i].Obj);
            }

        }
        break;
    case 1:
        {
            const GUIKey Words[] = {
                { GUI_ID_TEXT9, 0, L_WORD1000 },   // Normal text
                { GUI_ID_TEXT10, 0, L_WORD1001 },   // Threshold text
            };
            GUIUpdateKey UpdateValues[] = {
                { GUI_ID_EDIT4, 0, SensorDetails->GetSnsPtr(), SVT_MA_OFF, 0, 0, L_WORD1000, NULL },
                { GUI_ID_EDIT5, 0, SensorDetails->GetSnsPtr(), SVT_MA_ON, 0, 0, L_WORD1001, NULL },
            };
            for ( unsigned i = 0; i < NELEMENTS(Words); i++ ) {
                ChangeSWord(Words[i].GUIId, Words[i].GUIIndex, Words[i].WordKey, false);
            }
            UpdateSFields();
            for ( unsigned i = 0; i < NELEMENTS(UpdateValues); i++ ) {
                ChangeDWord(UpdateValues[i].GUIId, UpdateValues[i].InputMsgWord, UpdateValues[i].ValueKey, UpdateValues[i].Obj);
            }
            Hide(GUI_ID_TEXT3);
        }
        break;
    }
}

