#include "TDUIncludes.h"

TDUMultipageTankDetails::~TDUMultipageTankDetails(void) {
}

TDUMultipageTankDetails::TDUMultipageTankDetails(void) {
    Closed          = true;

    if (PROProjectInfo::PROProjectInfoPtr != NULL) {
        // Read default locked/unlocked state for the alarm settings dialog from config:
        alarmSettingsLocked = PROProjectInfo::PROProjectInfoPtr->AlarmSettingsPINLock;
    } else {
        // No config, so lock the alarm dialog by default:
        alarmSettingsLocked    = true;
    }
}

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialogs.
*
*/
const GUI_WIDGET_CREATE_INFO TDUMultipageTankDetails::aDialogCreate1[] = {
    { WINDOW_CreateIndirect,  "Dialog 1",             0,   0,   0, 274, 156, FRAMEWIN_CF_MOVEABLE },
    { BUTTON_CreateIndirect,   "Apply\n group",     GUI_ID_YES, 220,   4,  50, 30 },
    { RADIO_CreateIndirect,      NULL, GUI_ID_RADIO0,   6,  14,  90,  40, 0, 2 },

    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK0, 124,  40,   0,  0 },
    { TEXT_CreateIndirect, "Use measured density", GUI_ID_TEXT3, 144,  40, 110, 15, TEXT_CF_LEFT },
    { DROPDOWN_CreateIndirect,  NULL, GUI_ID_DROPDOWN1, 110,  70, 100,  60, 0, 3 },
    { TEXT_CreateIndirect, "Reference temperature", GUI_ID_TEXT11,   6, 100, 120, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT11, 130, 100,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT12, 182, 100,  50, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "Density", GUI_ID_TEXT13,   6, 120, 120, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT13, 130, 120,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT14, 182, 120,  50, 15, TEXT_CF_LEFT },
    // EHSMark What do we do here,  Simple linear
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK2,   6,  70,   0,  0 },
    { TEXT_CreateIndirect, "Use reference density", GUI_ID_TEXT20,  26,  70, 120, 15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect, "Density", GUI_ID_TEXT21,   6, 100, 120, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT21, 130, 100,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT22, 182, 100,  50, 15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect, "Reference 1", GUI_ID_TEXT23,   6,  90,  60, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT24,  70,  90,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT24, 122,  90,  40, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "Reference 2", GUI_ID_TEXT25,   6, 110,  60, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT26,  70, 110,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT26, 122, 110,  40, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT28, 165,  90,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT28, 217,  90,  40, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT30, 165, 110,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT30, 217, 110,  40, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "Coefficient", GUI_ID_TEXT31,   6, 130,  60, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT32,  70, 130,  50, 15, GUI_TA_RIGHT, 20 },
    { TEXT_CreateIndirect, "unit", GUI_ID_TEXT32, 122, 130,  50, 15, TEXT_CF_LEFT },
};

unsigned TDUMultipageTankDetails::IdSet1[] = {
    GUI_ID_YES,
    GUI_ID_RADIO0,
    GUI_ID_CHECK0,
    GUI_ID_DROPDOWN1,
    GUI_ID_EDIT11,
    GUI_ID_EDIT13,
    GUI_ID_CHECK2,
    GUI_ID_EDIT21,
    GUI_ID_EDIT24,
    GUI_ID_EDIT26,
    GUI_ID_EDIT28,
    GUI_ID_EDIT30,
    GUI_ID_EDIT32,
};

const GUI_WIDGET_CREATE_INFO TDUMultipageTankDetails::aDialogCreate2[] = {
    { WINDOW_CreateIndirect,  "Dialog2",  0,   0,   0, 274, 156, FRAMEWIN_CF_MOVEABLE },
    { BUTTON_CreateIndirect, "Unlock", GUI_ID_BUTTON8, 220, 4, 50, 20 },
    { BUTTON_CreateIndirect, "Apply\n group", GUI_ID_OK, 220,  28,  50, 30 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK41,  10,  10,   0,  0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK42,  10,  30,   0,  0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK43,  10,  50,   0,  0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK44,  10,  70,   0,  0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK45,  10,  90,   0,  0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK46,  10, 110,   0,  0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK47,  10, 130,   0,  0 },

    { TEXT_CreateIndirect, "Overfill", GUI_ID_TEXT41,  30,  10, 100, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "High Level", GUI_ID_TEXT42,  30,  30, 100, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "Low Level", GUI_ID_TEXT43,  30,  50, 100, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "High Temp", GUI_ID_TEXT44,  30,  70, 100, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "Low Temp", GUI_ID_TEXT45,  30,  90, 100, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "High Tank Press", GUI_ID_TEXT46,  30, 110, 100, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "Low Tank Press", GUI_ID_TEXT47,  30, 130, 100, 16, TEXT_CF_LEFT },

    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT41, 130,  10,  50, 16, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT42, 130,  30,  50, 16, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT43, 130,  50,  50, 16, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT44, 130,  70,  50, 16, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT45, 130,  90,  50, 16, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT46, 130, 110,  50, 16, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT47, 130, 130,  50, 16, GUI_TA_RIGHT, 20 },

    { TEXT_CreateIndirect, "", GUI_ID_TEXT34, 184,  10,  60, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT35, 184,  30,  60, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT36, 184,  50,  60, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT37, 184,  70,  60, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT38, 184,  90,  60, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT39, 184, 110,  60, 16, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT40, 184, 130,  60, 16, TEXT_CF_LEFT },
};
unsigned TDUMultipageTankDetails::IdSet2[] = {
    GUI_ID_OK,
    GUI_ID_BUTTON8,
    GUI_ID_CHECK41,
    GUI_ID_CHECK42,
    GUI_ID_CHECK43,
    GUI_ID_CHECK44,
    GUI_ID_CHECK45,
    GUI_ID_CHECK46,
    GUI_ID_CHECK47,
    GUI_ID_EDIT41,
    GUI_ID_EDIT42,
    GUI_ID_EDIT43,
    GUI_ID_EDIT44,
    GUI_ID_EDIT45,
    GUI_ID_EDIT46,
    GUI_ID_EDIT47,
};

const GUI_WIDGET_CREATE_INFO TDUMultipageTankDetails::aDialogCreate3[] = {
    { WINDOW_CreateIndirect, "Dialog 3",           0,   0,   0, 274, 156, FRAMEWIN_CF_MOVEABLE },
    { BUTTON_CreateIndirect, "Zero adjust tank \npressure sensor", GUI_ID_BUTTON0,  10,  20, 110, 40 },
    { BUTTON_CreateIndirect, "Zero adjust level \nsensor(s).", GUI_ID_BUTTON1,  10,  80, 110, 40 },
    { BUTTON_CreateIndirect, "Adjust Level", GUI_ID_BUTTON2, 150,  35, 110, 20 },  //  10
    { BUTTON_CreateIndirect, "Adjust Sounding", GUI_ID_BUTTON3, 150,  60, 110, 20 },  //  35
    { BUTTON_CreateIndirect, "Adjust Ullage", GUI_ID_BUTTON4, 150,  85, 110, 20 },  //  60
    { BUTTON_CreateIndirect, "Adjust Volume", GUI_ID_BUTTON5, 150, 110, 110, 20 },  //  85
    { BUTTON_CreateIndirect, "Adjust Weight", GUI_ID_BUTTON6, 150, 135, 110, 20 },  // 110
    { BUTTON_CreateIndirect, "Unlock", GUI_ID_BUTTON9, 150,  10, 110, 20 },
};
unsigned TDUMultipageTankDetails::IdSet3[] = {
    GUI_ID_BUTTON0,
    GUI_ID_BUTTON1,
    GUI_ID_BUTTON2,
    GUI_ID_BUTTON3,
    GUI_ID_BUTTON4,
    GUI_ID_BUTTON5,
    GUI_ID_BUTTON6,
    GUI_ID_BUTTON9,
};

const GUI_WIDGET_CREATE_INFO TDUMultipageTankDetails::aDialogCreate4[] = {
    { WINDOW_CreateIndirect, "Dialog 4", TDU_MULTIPAGE_D4_WIN,  0,   0, 274, 156, FRAMEWIN_CF_MOVEABLE },
    { BUTTON_CreateIndirect, "Unlock", GUI_ID_BUTTON7, 210,   4,  60, 20 },

    { TEXT_CreateIndirect, "Location", GUI_ID_TEXT50,   2,  23, 50, 15, TEXT_CF_HCENTER },
    { TEXT_CreateIndirect, "Ena", GUI_ID_TEXT51,  52,  23, 20, 15, TEXT_CF_HCENTER },
    { TEXT_CreateIndirect, "Gain", GUI_ID_TEXT52,  70,  23, 50, 15, TEXT_CF_HCENTER },
    { TEXT_CreateIndirect, "Offset", GUI_ID_TEXT53, 120,  23, 50, 15, TEXT_CF_HCENTER },
    { TEXT_CreateIndirect, "Value", GUI_ID_TEXT54, 170,  23, 50, 15, TEXT_CF_HCENTER },

    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK51,  52,  40,  0, 0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK52,  52,  60,  0, 0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK53,  52,  80,  0, 0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK54,  52, 100,  0, 0 },
    { CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK55,  52, 120,  0, 0 },

    { TEXT_CreateIndirect, "", GUI_ID_TEXT60,   2,  40, 50, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT61,   2,  60, 50, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT62,   2,  80, 50, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT63,   2, 100, 50, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT64,   2, 120, 50, 15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect, "", GUI_ID_TEXT65, 223,  40, 60, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT66, 223,  60, 60, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT67, 223,  80, 60, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT68, 223, 100, 60, 15, TEXT_CF_LEFT },
    { TEXT_CreateIndirect, "", GUI_ID_TEXT69, 223, 120, 60, 15, TEXT_CF_LEFT },

    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT50,  70,  40, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT51,  70,  60, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT52,  70,  80, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT53,  70, 100, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT54,  70, 120, 50, 15, GUI_TA_RIGHT, 20 },

    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT55, 120,  40, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT56, 120,  60, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT57, 120,  80, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT58, 120, 100, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT59, 120, 120, 50, 15, GUI_TA_RIGHT, 20 },

    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT60, 170,  40, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT61, 170,  60, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT62, 170,  80, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT63, 170, 100, 50, 15, GUI_TA_RIGHT, 20 },
    { EDIT_CreateIndirect, NULL, GUI_ID_EDIT64, 170, 120, 50, 15, GUI_TA_RIGHT, 20 },
};

unsigned TDUMultipageTankDetails::IdSet4[] = {
    GUI_ID_BUTTON7,
//	GUI_ID_BUTTON8,
    /*
    GUI_ID_CHECK51,
    GUI_ID_CHECK52,
    GUI_ID_CHECK53,
    GUI_ID_CHECK54,
    GUI_ID_EDIT50,
    GUI_ID_EDIT51,
    GUI_ID_EDIT52,
    GUI_ID_EDIT53,
    GUI_ID_EDIT54,
    GUI_ID_EDIT55,
    GUI_ID_EDIT56,
    GUI_ID_EDIT57,
    GUI_ID_EDIT58,
    GUI_ID_EDIT59,
    GUI_ID_EDIT60,
    GUI_ID_EDIT61,
    */
};


const GUI_WIDGET_CREATE_INFO TDUMultipageTankDetails::aDialogCreate5[] = {
    { WINDOW_CreateIndirect, "Dialog 5"         , TDU_MULTIPAGE_D5_WIN,  0,   0, 274, 156, FRAMEWIN_CF_MOVEABLE },
    { BUTTON_CreateIndirect, "Unlock"           , GUI_ID_BUTTON10, 210,   4,  60, 20 },

    { TEXT_CreateIndirect, "Level offset"       , GUI_ID_TEXT70,   2, 40, 70, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT65,  60, 40, 60, 15, TEXT_CF_RIGHT },
    { TEXT_CreateIndirect, ""                   , GUI_ID_TEXT71, 125, 40, 30, 15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect, "Table offset"       , GUI_ID_TEXT72,   2, 60, 60, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT66,  60, 60, 60, 15, TEXT_CF_RIGHT },
    { TEXT_CreateIndirect, ""                   , GUI_ID_TEXT73, 125, 60, 30, 15, TEXT_CF_LEFT },

    { TEXT_CreateIndirect, "Exp. factor"        , GUI_ID_TEXT74,   2, 80, 70, 15, TEXT_CF_LEFT },
    { EDIT_CreateIndirect,     NULL             , GUI_ID_EDIT67,  60, 80, 60, 15, TEXT_CF_RIGHT },
    { TEXT_CreateIndirect, ""                   , GUI_ID_TEXT75, 125, 80, 30, 15, TEXT_CF_LEFT },

};

unsigned TDUMultipageTankDetails::IdSet5[] = {
    GUI_ID_BUTTON10,
//	GUI_ID_BUTTON8,
    /*
    GUI_ID_CHECK51,
    GUI_ID_CHECK52,
    GUI_ID_CHECK53,
    GUI_ID_CHECK54,
    GUI_ID_EDIT50,
    GUI_ID_EDIT51,
    GUI_ID_EDIT52,
    GUI_ID_EDIT53,
    GUI_ID_EDIT54,
    GUI_ID_EDIT55,
    GUI_ID_EDIT56,
    GUI_ID_EDIT57,
    GUI_ID_EDIT58,
    GUI_ID_EDIT59,
    GUI_ID_EDIT60,
    GUI_ID_EDIT61,
    */
};

/*********************************************************************
*
*       _cbDialog1
*/
void TDUMultipageTankDetails::cbDialog1(WM_MESSAGE *pMsg) {
    WM_HWIN hDlg;
    int NCode, Id;
    hDlg = pMsg->hWin;
    PROTank *TankPtr = (PROTank *)TankDetails->CurrentPROPtr;
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        TankDetails->FirstTime = true;
        break;
    case WM_PAINT:
        GUI_DrawRect(2,  10, 110,  56);
        GUI_DrawRect(120,  36, 260,  56);
        GUI_DrawRect(2,  66, 270, 150);
        TankDetails->UpdateLanguage();
        break;
    case MESSAGE_YES_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_YES:
                //Density setting:
                TankDetails->SetAllNewValueDialog1();
                break;
            }
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            TankDetails->SetNewValueDialog1(ValueId, StringBuf);
        }
        break;
    case WM_TOUCH_CHILD:
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
        NCode = pMsg->Data.v;                               /* Notification code */
        switch (NCode) {
        case WM_NOTIFICATION_GOT_FOCUS:
            switch (Id) {
            case GUI_ID_EDIT11: //API1
            case GUI_ID_EDIT13: //API2
            case GUI_ID_EDIT21: //Density
            case GUI_ID_EDIT24:
            case GUI_ID_EDIT26:
            case GUI_ID_EDIT28:
            case GUI_ID_EDIT30:
            case GUI_ID_EDIT32:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD129, Id);; // New Value
                break;
            }
            break;
        case WM_NOTIFICATION_SEL_CHANGED:
            switch (Id) {
            case GUI_ID_DROPDOWN1:
                {
                    int APItype;
                    switch (DROPDOWN_GetSel(TankDetails->hDropdAPI)) {
                    case 0:
                        APItype = CTY_API_6A;       break;
                    case 1:
                        APItype = CTY_API_6B;       break;
                    case 2:
                        APItype = CTY_API_6D;       break;
                    case 3:
                        APItype = CTY_API_53A;      break;
                    case 4:
                        APItype = CTY_API_53B;      break;
                    case 5:
                        APItype = CTY_API_53D;      break;
                    case 6:
                        APItype = CTY_API_53E;      break;
                    case 7:
                        APItype = CTY_API_54A;      break;
                    case 8:
                        APItype = CTY_API_54B;      break;
                    case 9:
                        APItype = CTY_API_54D;      break;
                    case 10:
                        APItype = CTY_API_54E;      break;
                    case 11:
                        APItype = CTY_API_59A;      break;
                    case 12:
                        APItype = CTY_API_59B;      break;
                    case 13:
                        APItype = CTY_API_59D;      break;
                    case 14:
                        APItype = CTY_API_59E;      break;
                    case 15:
                        APItype = CTY_API_60A;      break;
                    case 16:
                        APItype = CTY_API_60B;      break;
                    case 17:
                        APItype = CTY_API_60D;      break;
                    case 18:
                        APItype = CTY_API_60E;      break;
                    default:
                        APItype = CTY_NOT_DEFINED;  break;
                    }

                    if (APItype != CTY_NOT_DEFINED) {
                        LibPutValue(SVT_BASIC_TYPE, TankPtr, APItype);
                        RADIO_SetValue(TankDetails->hRadioLinAPI, 1);
                        TankDetails->UseAPI();
                    }
                }
                break;
            }
            break;
        case WM_NOTIFICATION_VALUE_CHANGED:
            switch (Id) {
            case GUI_ID_RADIO0:
                if (RADIO_GetValue(TankDetails->hRadioLinAPI) == 0) {
                    if (CHECKBOX_IsChecked(TankDetails->hCheckLin)) {
                        LibPutValue(SVT_BASIC_TYPE, TankPtr, CTY_LINEAR);
                    } else {
                        LibPutValue(SVT_BASIC_TYPE, TankPtr, CTY_SIMPLE_LIN);
                    }
                    TankDetails->UseLinear();
                } else {
                    switch (DROPDOWN_GetSel(TankDetails->hDropdAPI)) {
                    case CTY_API_6A     :
                    case CTY_API_6B     :
                    case CTY_API_6D     :
                    case CTY_API_53A    :
                    case CTY_API_53B    :
                    case CTY_API_53D    :
                    case CTY_API_53E    :
                    case CTY_API_54A    :
                    case CTY_API_54B    :
                    case CTY_API_54D    :
                    case CTY_API_54E    :
                    case CTY_API_59A    :
                    case CTY_API_59B    :
                    case CTY_API_59D    :
                    case CTY_API_59E    :
                    case CTY_API_60A    :
                    case CTY_API_60B    :
                    case CTY_API_60D    :
                    case CTY_API_60E    :
                        TankDetails->UseAPI();
                        break;
                    default:
                        //LibPutValue(SVT_BASIC_TYPE,TankPtr,CTY_API_54B);
                        TankDetails->UseAPI();
                        break;
                    }
                }
                break;
            }
            break;
        case WM_NOTIFICATION_RELEASED:      /* React only if released */
            switch (Id) {
            case GUI_ID_YES:
                {
                    int Text1  = L_WORD130; // Confirm operation
                    int  Text2 = L_WORD0;
                    switch (CurrentWinID) {
                    case TDU_CARGO_WIN:
                        Text2 = L_WORD131; // Apply current density settings to all cargo tanks.
                        break;
                    case TDU_TANKFARM_WIN:
                        Text2 = L_WORD894; // Apply current density settings to all cargo tanks.
                        break;
                    case TDU_BALLAST_WIN:
                        Text2 = L_WORD132; // Apply current density settings to all ballast tanks.
                        break;
                    case TDU_SERVICE_WIN:
                        Text2 = L_WORD133; // Apply current density settings to all Service tanks.
                        break;
                    case TDU_VOIDSPACE_WIN:
                        Text2 = L_WORD646; // Apply current density settings to all void spaces.
                        break;
                    case TDU_TANKPRESS_WIN:
                    case TDU_LINEPRESS_WIN:
                    case TDU_TEMP_WIN:
                    case TDU_LEVELSWITCH_WIN:
                    case TDU_WATERINGR_WIN:
                    default:
                        break;
                    }
                    ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                }
                break;
            case GUI_ID_CHECK0:
                LibPutValue(SVT_USE_MSRD_DNS, TankPtr, CHECKBOX_IsChecked(TankDetails->hCheckMeasDens));
                //TankDetails->UseLinear();
                break;
            case GUI_ID_CHECK2:
                if (CHECKBOX_IsChecked(TankDetails->hCheckLin)) {
                    LibPutValue(SVT_BASIC_TYPE, TankPtr, CTY_LINEAR);
                } else {
                    LibPutValue(SVT_BASIC_TYPE, TankPtr, CTY_SIMPLE_LIN);
                }
                RADIO_SetValue(TankDetails->hRadioLinAPI, 0);
                TankDetails->UseLinear();
                break;
            }
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

/*********************************************************************
*
*       _cbDialog2
*/
void TDUMultipageTankDetails::cbDialog2(WM_MESSAGE *pMsg) {
    WM_HWIN hDlg;
    int NCode, Id;
    hDlg = pMsg->hWin;
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        TankDetails->FirstTime = true;
        break;
    case WM_PAINT:
        TankDetails->EnableOrDisableAllControls();
        TankDetails->UpdateLanguage();
        break;
    case MESSAGE_YES_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_OK:
                //Alarm setting:
                TankDetails->SetAllNewValueDialog2();
                break;
            }
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            TankDetails->SetNewValueDialog2(ValueId, StringBuf);
        }
        break;
        // Unlock the Alarm screen and other PIN locked dialogs if the correct PIN code was input:
    case MESSAGE_PINCODE_RETURN:
        {
            // Unlock alarm settings dialog (if configured to be locked):
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_BUTTON8:
                // Unlock dialogs if the unlock button was initially pressed on the alarm settings dialog
                //EditEvent = false;

                CheckPinCode(StringBuf);
                TankDetails->EnableOrDisableAllControls();
                break;
            }
            break;
        }
    case WM_TOUCH_CHILD:
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
        NCode = pMsg->Data.v;                               /* Notification code */
        switch (NCode) {
        case WM_NOTIFICATION_GOT_FOCUS:
            switch (Id) {
            case GUI_ID_EDIT41:
            case GUI_ID_EDIT42:
            case GUI_ID_EDIT43:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD134, Id);   // New Alarm limit
                break;
            case GUI_ID_EDIT44:
            case GUI_ID_EDIT45:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD134, Id);   // New Alarm limit
                break;
            case GUI_ID_EDIT46:
            case GUI_ID_EDIT47:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD134, Id);   // New Alarm limit
                break;
            }
            break;
        case WM_NOTIFICATION_RELEASED:      /* React only if released */
            switch (Id) {
            case GUI_ID_OK:
                {
                    int Text1 = L_WORD130;  // Confirm operation
                    int Text2 = L_WORD0;
                    switch (CurrentWinID) {
                    case TDU_CARGO_WIN:
                        Text2 = L_WORD135; // Apply current alarm settings to all cargo tanks.
                        break;
                    case TDU_TANKFARM_WIN:
                        Text2 = L_WORD895; // Apply current alarm settings to all tanks.
                        break;
                    case TDU_BALLAST_WIN:
                        Text2 = L_WORD136; // Apply current alarm settings to all ballast tanks.
                        break;
                    case TDU_SERVICE_WIN:
                        Text2 = L_WORD137; // Apply current alarm settings to all Service tanks.
                        break;
                    case TDU_TANKPRESS_WIN:
                        Text2 = L_WORD138; // Apply current alarm settings to all Tank pressure points
                        break;
                    case TDU_LINEPRESS_WIN:
                        break;
                    case TDU_TEMP_WIN:
                        Text2 = L_WORD139; // Apply current alarm settings to all Temperature points.
                        break;
                    case TDU_LEVELSWITCH_WIN:
                    case TDU_WATERINGR_WIN:
                    case TDU_VOIDSPACE_WIN:
                    default:
                        break;
                    }
                    ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                }
                break;
            case GUI_ID_CHECK41:
            case GUI_ID_CHECK42:
            case GUI_ID_CHECK43:
            case GUI_ID_CHECK44:
            case GUI_ID_CHECK45:
            case GUI_ID_CHECK46:
            case GUI_ID_CHECK47:
                TankDetails->SetNewValueDialog2(Id, " ");
                break;
            case GUI_ID_BUTTON8:
                if (PinUnlock) {
                    PinUnlock = false;
                } else {
                    // Open PIN code dialog for entering PIN code and unlocking the alarm settings dialog
                    KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hDlg), L_WORD150, Id);
                }
                break;
            }
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

/*********************************************************************
*
*       _cbDialog3
*/
void TDUMultipageTankDetails::cbDialog3(WM_MESSAGE *pMsg) {
    int NCode, Id;
    WM_HWIN hDlg = pMsg->hWin;
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        TankDetails->FirstTime = true;
        break;
    case WM_PAINT:
        TankDetails->UpdateLanguage();
        break;
    case MESSAGE_PINCODE_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            switch (ValueId) {
            case GUI_ID_BUTTON9:
                {
                    char StringBuf[BUF_SIZE] = { "" };
                    strcpy(StringBuf, (char *)pMsg->Data.p);
                    CheckPinCode(StringBuf);
                }
                break;
            }
        }
        break;
    case MESSAGE_YES_RETURN:
        {
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            int ValueId = pMsg->hWinSrc;
            switch (ValueId) {
            case GUI_ID_BUTTON0:    /* Pressure Button */
            case GUI_ID_BUTTON1:    /* Level Button */
                TankDetails->SetNewValueDialog3(ValueId, StringBuf);
                break;
            case GUI_ID_BUTTON2:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD145, ValueId);; // Observed Level
                break;
            case GUI_ID_BUTTON3:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD146, ValueId);; // Observed Sounding
                break;
            case GUI_ID_BUTTON4:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD147, ValueId);; // Observed Ullage
                break;
            case GUI_ID_BUTTON5:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD148, ValueId);; // Observed Volume
                break;
            case GUI_ID_BUTTON6:
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD149, ValueId);; // Observed Weight
                break;

            }
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_BUTTON2:
            case GUI_ID_BUTTON3:
            case GUI_ID_BUTTON4:
            case GUI_ID_BUTTON5:
            case GUI_ID_BUTTON6:
                TankDetails->SetNewValueDialog3(ValueId, StringBuf);
                break;
            }
        }
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
        NCode = pMsg->Data.v;                               /* Notification code */
        switch (NCode) {
        case WM_NOTIFICATION_GOT_FOCUS:
            break;
        case WM_NOTIFICATION_RELEASED:      /* React only if released */
            switch (Id) {
            case GUI_ID_BUTTON9:
                if (PinUnlock) {
                    PinUnlock = false;
                } else {
                    // Open PIN code dialog for entering PIN code and unlocking the alarm settings dialog
                    KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hDlg), L_WORD150, Id);
                }
                break;
            case GUI_ID_BUTTON0:    /* Pressure Button */
            case GUI_ID_BUTTON1:    /* Level Button */
            case GUI_ID_BUTTON2:    /* Level Adjust Button */
            case GUI_ID_BUTTON3:    /* Level Adjust Button */
            case GUI_ID_BUTTON4:    /* Level Adjust Button */
            case GUI_ID_BUTTON5:    /* Level Adjust Button */
            case GUI_ID_BUTTON6:    /* Level Adjust Button */
                switch (Id) {
                case GUI_ID_BUTTON0:    /* Pressure Button */
                    {
                        int Text1 = L_WORD140;  // Zero adjust sensor
                        int Text2 = L_WORD141;  // The sensor must be vented to atmosphere.
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_BUTTON1:    /* Level Button */
                    {
                        int Text1 = L_WORD142;  // Zero adjust level sensor(s)!
                        int Text2 = L_WORD143;  // The tank must be empty and no tank cleaning has been carried out the last 30 min.
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_BUTTON2:
                case GUI_ID_BUTTON3:
                case GUI_ID_BUTTON4:
                case GUI_ID_BUTTON5:
                case GUI_ID_BUTTON6:
                    {
                        int Text1 = L_WORD0;
                        switch (Id) {
                        case GUI_ID_BUTTON2:
                            Text1 = L_WORD657;
                            break;
                        case GUI_ID_BUTTON3:
                            Text1 = L_WORD658;
                            break;
                        case GUI_ID_BUTTON4:
                            Text1 = L_WORD659;
                            break;
                        case GUI_ID_BUTTON5:
                            Text1 = L_WORD660;
                            break;
                        case GUI_ID_BUTTON6:
                            Text1 = L_WORD661;
                            break;
                        }
                        int Text2 = L_WORD656;  // The level will be adjusted to the inserted level. Incorrect entry will cause malfunction of the system.
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
        break;
    }

}

/*********************************************************************
*
*       _cbDialog4
*/
void TDUMultipageTankDetails::cbDialog4(WM_MESSAGE *pMsg) {
    int NCode, Id;
    WM_HWIN hDlg = pMsg->hWin;
    static bool EditEvent;  // Always set to 0 by init
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        TankDetails->FirstTime = true;
        break;
    case WM_PAINT:
        TankDetails->EnableOrDisableAllControls();
        TankDetails->UpdateLanguage();
        break;
    case WM_TOUCH_CHILD:
        break;
    case MESSAGE_YES_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_EDIT50:
            case GUI_ID_EDIT51:
            case GUI_ID_EDIT52:
            case GUI_ID_EDIT53:
            case GUI_ID_EDIT54:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD151, ValueId); // Set sensor gain
                break;
            case GUI_ID_EDIT55:
            case GUI_ID_EDIT56:
            case GUI_ID_EDIT57:
            case GUI_ID_EDIT58:
            case GUI_ID_EDIT59:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD879, ValueId); // Set sensor offset
                break;
            case GUI_ID_EDIT60:
            case GUI_ID_EDIT61:
            case GUI_ID_EDIT62:
            case GUI_ID_EDIT63:
            case GUI_ID_EDIT64:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD152, ValueId); // Set sensor value
                break;
            case GUI_ID_EDIT65:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD878, ValueId); // Set level offset
                break;
            case GUI_ID_EDIT66:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD982, ValueId); // Set table offset
                break;
            }
        }
        break;
    case MESSAGE_PINCODE_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_BUTTON7:    /* PinCode Button */
                EditEvent = false;
                CheckPinCode(StringBuf);
                TankDetails->EnableOrDisableAllControls();
                break;
            }
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_EDIT50:
            case GUI_ID_EDIT51:
            case GUI_ID_EDIT52:
            case GUI_ID_EDIT53:
            case GUI_ID_EDIT54:
            case GUI_ID_EDIT55:
            case GUI_ID_EDIT56:
            case GUI_ID_EDIT57:
            case GUI_ID_EDIT58:
            case GUI_ID_EDIT59:
            case GUI_ID_EDIT60:
            case GUI_ID_EDIT61:
            case GUI_ID_EDIT62:
            case GUI_ID_EDIT63:
            case GUI_ID_EDIT64:
            case GUI_ID_EDIT65:
            case GUI_ID_EDIT66:
            case GUI_ID_EDIT67:
                EditEvent = false;
                TankDetails->SetNewValueDialog4(ValueId, StringBuf);
                break;
            }
        }
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
        NCode = pMsg->Data.v;                               /* Notification code */
        switch (NCode) {
        case WM_NOTIFICATION_GOT_FOCUS:
            if (!EditEvent || PinUnlock) {
                switch (Id) {
                case GUI_ID_EDIT50:
                case GUI_ID_EDIT51:
                case GUI_ID_EDIT52:
                case GUI_ID_EDIT53:
                case GUI_ID_EDIT54:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153; // Warning
                        int Text2 = L_WORD154; // You are about to adjust the sensor gain. This may affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_EDIT55:
                case GUI_ID_EDIT56:
                case GUI_ID_EDIT57:
                case GUI_ID_EDIT58:
                case GUI_ID_EDIT59:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153; // Warning
                        int Text2 = L_WORD880; // You are about to adjust the sensor gain. This may affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_EDIT60:
                case GUI_ID_EDIT61:
                case GUI_ID_EDIT62:
                case GUI_ID_EDIT63:
                case GUI_ID_EDIT64:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153;  // Warning
                        int Text2 = L_WORD155; // You are about to adjust the sensor. This may affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_EDIT65:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153;  // Warning
                        int Text2 = L_WORD881; // You are about to adjust the level offset. This will affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_EDIT66:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153;  // Warning
                        int Text2 = L_WORD981; // You are about to adjust the table offset. This will affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_EDIT67:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153;  // Warning
                        int Text2 = L_WORD1005; // You are about to adjust the experience factor. This will affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                }
            }
            break;
        case WM_NOTIFICATION_RELEASED:      /* React only if released */
            switch (Id) {
            case GUI_ID_CHECK51:
            case GUI_ID_CHECK52:
            case GUI_ID_CHECK53:
            case GUI_ID_CHECK54:
            case GUI_ID_CHECK55:
                TankDetails->SetNewValueDialog4(Id, "");
                break;
            case GUI_ID_BUTTON7:    /* PinCode Button */
                if (PinUnlock) {
                    PinUnlock = false;
                } else {
                    KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hDlg), L_WORD150, Id);; // Enter Pin code:
                }
                break;
            }
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       _cbDialog4
*/
void TDUMultipageTankDetails::cbDialog5(WM_MESSAGE *pMsg) {
    int NCode, Id;
    WM_HWIN hDlg = pMsg->hWin;
    static bool EditEvent;  // Always set to 0 by init
    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        TankDetails->FirstTime = true;
        break;
    case WM_PAINT:
        TankDetails->InitDialog5();
        TankDetails->UpdateLanguage();
        break;
    case WM_TOUCH_CHILD:
        break;
    case MESSAGE_YES_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_EDIT65:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD878, ValueId); // Set level offset
                break;
            case GUI_ID_EDIT66:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD982, ValueId); // Set table offset
                break;
            case GUI_ID_EDIT67:
                EditEvent = false;
                KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hDlg), L_WORD1006, ValueId); // Set experience factor
                break;
            }
        }
        break;
    case MESSAGE_PINCODE_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_BUTTON10:    /* PinCode Button */
                EditEvent = false;
                CheckPinCode(StringBuf);
                TankDetails->EnableOrDisableAllControls();
                break;
            }
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE] = { "" };
            strcpy(StringBuf, (char *)pMsg->Data.p);
            switch (ValueId) {
            case GUI_ID_EDIT65:
            case GUI_ID_EDIT66:
            case GUI_ID_EDIT67:
                EditEvent = false;
                TankDetails->SetNewValueDialog5(ValueId, StringBuf);
                break;
            }
        }
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
        NCode = pMsg->Data.v;                               /* Notification code */
        switch (NCode) {
        case WM_NOTIFICATION_GOT_FOCUS:
            if (!EditEvent || PinUnlock) {
                switch (Id) {
                case GUI_ID_EDIT65:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153;  // Warning
                        int Text2 = L_WORD881; // You are about to adjust the level offset. This will affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_EDIT66:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153;  // Warning
                        int Text2 = L_WORD981; // You are about to adjust the table offset. This will affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                case GUI_ID_EDIT67:
                    EditEvent = true;
                    if (PinUnlock) {
                        int Text1 = L_WORD153;  // Warning
                        int Text2 = L_WORD1005; // You are about to adjust the table offset. This will affect the accuracy!
                        ConfirmMessageBox->Exec(WM_GetClientWindow(hDlg), Text1, Text2, Id);
                    }
                    break;
                }
            }
            break;
        case WM_NOTIFICATION_RELEASED:      /* React only if released */
            switch (Id) {
            case GUI_ID_BUTTON10:    /* PinCode Button */
                if (PinUnlock) {
                    PinUnlock = false;
                } else {
                    KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hDlg), L_WORD150, Id);; // Enter Pin code:
                }
                break;
            }
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       _cbFrameWin
*
* Purpose:
*   Callback routine of the frame window behind the MULTIPAGE widget
*/
void TDUMultipageTankDetails::cbFrameWin(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
    case WM_PAINT:
        GUI_SetBkColor(GUI_BLUE);
        GUI_Clear();
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

/*********************************************************************
*
*       CreateMultiPage
*
*/
void TDUMultipageTankDetails::CreateMultiPage(WM_HWIN hCurrentWin, PRogramObject *PROPtr) {
    /* Create the frame window */
    CurrentPROPtr = PROPtr;
    if (Closed) {
        Closed = false;
        AnsiString Name = CurrentPROPtr->Name;
        if (CurrentPROPtr->LongName.compare(CurrentPROPtr->Name) != 0) Name += "  ( " + (AnsiString)CurrentPROPtr->LongName + " ) ";
        WinHandl = FRAMEWIN_CreateEx(0, 0, 0, 0, hCurrentWin, WM_CF_SHOW, 0, 0, Name.c_str(), &cbFrameWin);
        FRAMEWIN_SetActive(WinHandl, 1);
        /* Create the MULTIPAGE widget */
        hMultiPage = MULTIPAGE_CreateEx(0, 0, 0, 0, WM_GetClientWindow(WinHandl), WM_CF_SHOW, 0, 0);
        //  MULTIPAGE_SetBkColor(hMultiPage,TDU_C_HW_BACK,1);
        /* Create and attache the MULTIPAGE dialog windows */
        hDialog = GUI_CreateDialogBox(aDialogCreate1, GUI_COUNTOF(aDialogCreate1), &cbDialog1, WM_UNATTACHED, 0, 0);
        MULTIPAGE_AddPage(hMultiPage, hDialog, FindDictionaryWord(L_WORD83).c_str());   // Density
        hDialog = GUI_CreateDialogBox(aDialogCreate2, GUI_COUNTOF(aDialogCreate2), &cbDialog2, WM_UNATTACHED, 0, 0);
        MULTIPAGE_AddPage(hMultiPage, hDialog, FindDictionaryWord(L_WORD97).c_str());   //  Alarm
        hDialog = GUI_CreateDialogBox(aDialogCreate3, GUI_COUNTOF(aDialogCreate3), &cbDialog3, WM_UNATTACHED, 0, 0);
        MULTIPAGE_AddPage(hMultiPage, hDialog, FindDictionaryWord(L_WORD868).c_str()); // Adjust
        hDialog = GUI_CreateDialogBox(aDialogCreate4, GUI_COUNTOF(aDialogCreate4), &cbDialog4, WM_UNATTACHED, 0, 0);
        MULTIPAGE_AddPage(hMultiPage, hDialog, FindDictionaryWord(L_WORD157).c_str()); // Sensor values
        hDialog = GUI_CreateDialogBox(aDialogCreate5, GUI_COUNTOF(aDialogCreate5), &cbDialog5, WM_UNATTACHED, 0, 0);
        MULTIPAGE_AddPage(hMultiPage, hDialog, FindDictionaryWord(L_WORD10).c_str()); // Service
    } else {
        WM_BringToTop(WinHandl);
    }
    WM_EnableMemdev(WinHandl);
    GetDialog1Handles();
    GetDialog2Handles();
    GetDialog3Handles();
    GetDialog4Handles();
    GetDialog5Handles();
    switch (CurrentWinID) {
    case TDU_MAIN_WIN:
    case TDU_HEAD_WIN:
    case TDU_BUT_WIN:
    case TDU_PRESENT_WIN:
    case TDU_SYSTEM_WIN:
    case TDU_ALARM_WIN:
        DisableLevelAdjustButtons();
        break;
    case TDU_CARGO_WIN:
    case TDU_TANKFARM_WIN:
        CurrentListPtr = PROCargoTank::ObjVector;
        MULTIPAGE_SelectPage(hMultiPage, 0);
        EnableLevelAdjustButtons();
        break;
    case TDU_BALLAST_WIN:
        CurrentListPtr = PROBallastTank::ObjVector;
        MULTIPAGE_SelectPage(hMultiPage, 1);
        EnableLevelAdjustButtons();
        break;
    case TDU_SERVICE_WIN:
        CurrentListPtr = PROServiceTank::ObjVector;
        {
            PROTank *TElement = (PROTank *)CurrentPROPtr;
            if (TElement != NULL) {
                switch (TElement->TankType) {
                case TANKTYPE_BALLAST:
                case TANKTYPE_HFO    :
                case TANKTYPE_DO     :
                case TANKTYPE_LUB    :
                    break;
                case TANKTYPE_FW     :
                    MULTIPAGE_DisablePage(hMultiPage, 0);
                    break;
                case TANKTYPE_MISC   :
                    break;
                }
            }
        }
        WM_HideWin(hButApplyDensity);
        MULTIPAGE_SelectPage(hMultiPage, 1);
        EnableLevelAdjustButtons();
        break;
    case TDU_TANKPRESS_WIN:
        CurrentListPtr = PROTankPressure::ObjVector;
        MULTIPAGE_SelectPage(hMultiPage, 1);
        MULTIPAGE_DisablePage(hMultiPage, 0);
        MULTIPAGE_DisablePage(hMultiPage, 4);
        DisableLevelAdjustButtons();
        break;
    case TDU_LINEPRESS_WIN:
        CurrentListPtr = PROLinePressure::ObjVector;
        MULTIPAGE_SelectPage(hMultiPage, 1);
        MULTIPAGE_DisablePage(hMultiPage, 0);
        MULTIPAGE_DisablePage(hMultiPage, 4);
        DisableLevelAdjustButtons();
        break;
    case TDU_TEMP_WIN:
        CurrentListPtr = PROTemperature::ObjVector;
        MULTIPAGE_SelectPage(hMultiPage, 1);
        MULTIPAGE_DisablePage(hMultiPage, 0);
        MULTIPAGE_DisablePage(hMultiPage, 2);
        MULTIPAGE_DisablePage(hMultiPage, 4);
        DisableLevelAdjustButtons();
        break;
    case TDU_VOIDSPACE_WIN:
        CurrentListPtr = PROVoidSpace::ObjVector;
        MULTIPAGE_SelectPage(hMultiPage, 2);
        //MULTIPAGE_DisablePage(hMultiPage,0);
        MULTIPAGE_DisablePage(hMultiPage, 1);
        WM_HideWin(hButApplyDensity);
        MULTIPAGE_SelectPage(hMultiPage, 2);
        EnableLevelAdjustButtons();
        break;
    case TDU_LEVELSWITCH_WIN:
    case TDU_WATERINGR_WIN:
    default:
        DisableLevelAdjustButtons();
        MULTIPAGE_DisablePage(hMultiPage, 4);
        break;
    }
    ClearRWList();
    AddToRWList(IdSet1, NELEMENTS(IdSet1), PROPtr);
    AddToRWList(IdSet2, NELEMENTS(IdSet2), PROPtr);
    AddToRWList(IdSet3, NELEMENTS(IdSet3), PROPtr);
    AddToRWList(IdSet4, NELEMENTS(IdSet4), PROPtr);
    AddToRWList(IdSet5, NELEMENTS(IdSet5), PROPtr);
    UpdateReadOnly();
    //   AddToSKeyList(Words3,NELEMENTS(Words3));
}

/*********************************************************************
*
* Dialog1 procedure
*/
void TDUMultipageTankDetails::GetDialog1Handles(void) {
    hButApplyDensity = WM_GetDialogItem(WinHandl, GUI_ID_YES);
    hRadioLinAPI    = WM_GetDialogItem(WinHandl, GUI_ID_RADIO0);
    hCheckMeasDens  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK0);
    hTextMeasDens   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
    //RBMArk   CHECKBOX_SetNumStates(hCheckMeasDens,3);
//API
    hTextAPI        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT10);
    hDropdAPI       = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
    DROPDOWN_SetAutoScroll(hDropdAPI, 1);
    hTextAPI1       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT11);
    hEditAPI1       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT11);
    hTextAPI1Unit   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT12);
    hTextAPI2       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT13);
    hEditAPI2       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT13);
    hTextAPI2Unit   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT14);
//Linear
    hCheckLin       = WM_GetDialogItem(WinHandl, GUI_ID_CHECK2);
//RBMArk          CHECKBOX_SetNumStates(hCheckLin,3);
    hTextLin        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT20);

    hTextSimDens    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT21);
    hEditSimDens    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT21);
    hTextSimDensUnit = WM_GetDialogItem(WinHandl, GUI_ID_TEXT22);

    hTextRef1       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT23);
    hTextRef2       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT25);
    hTextCoeff      = WM_GetDialogItem(WinHandl, GUI_ID_TEXT31);
    hEditTemp1      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT24);
    hTextTemp1Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT24);
    hEditDens1      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT28);
    hTextDens1Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT28);
    hEditTemp2      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT26);
    hTextTemp2Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT26);
    hEditDens2      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT30);
    hTextDens2Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT30);
    hEditCoeff      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT32);
    hTextCoeffUnit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT32);
    InitDialog1();
}

void TDUMultipageTankDetails::InitDialog1(void) {
    {
        const GUIKey Words[] = {
            { GUI_ID_YES, 0, L_WORD98 },
            { GUI_ID_RADIO0, 0, L_WORD101 },
            { GUI_ID_RADIO0, 1, L_WORD102 },
            { GUI_ID_TEXT3, 0, L_WORD103 },
            { GUI_ID_TEXT11, 0, L_WORD104 },
            { GUI_ID_TEXT13, 0, L_WORD83 },
            { GUI_ID_TEXT20, 0, L_WORD105 },
            { GUI_ID_TEXT21, 0, L_WORD83 },
            { GUI_ID_TEXT23, 0, L_WORD106 },
            { GUI_ID_TEXT25, 0, L_WORD107 },
            { GUI_ID_TEXT31, 0, L_WORD108 },
            { GUI_ID_OK, 0, L_WORD98 },
            { GUI_ID_TEXT41, 0, L_WORD109 },
            { GUI_ID_TEXT42, 0, L_WORD110 },
            { GUI_ID_TEXT43, 0, L_WORD111 },
            { GUI_ID_TEXT44, 0, L_WORD112 },
            { GUI_ID_TEXT45, 0, L_WORD113 },
            { GUI_ID_TEXT46, 0, L_WORD114 },
            { GUI_ID_TEXT47, 0, L_WORD115 },
            { GUI_ID_BUTTON0, 0, L_WORD116 },
            { GUI_ID_BUTTON1, 0, L_WORD117 },
            { GUI_ID_BUTTON2, 0, L_WORD118 },
            { GUI_ID_BUTTON3, 0, L_WORD119 },
            { GUI_ID_BUTTON4, 0, L_WORD120 },
            { GUI_ID_BUTTON5, 0, L_WORD121 },
            { GUI_ID_BUTTON6, 0, L_WORD122 },
            { GUI_ID_BUTTON7, 0, L_WORD123 },
            { GUI_ID_BUTTON10, 0, L_WORD123 },

            { GUI_ID_TEXT50, 0, L_WORD124 },
            { GUI_ID_TEXT51, 0, L_WORD125 },
            { GUI_ID_TEXT52, 0, L_WORD126 },
            { GUI_ID_TEXT53, 0, L_WORD127 },
            { GUI_ID_TEXT54, 0, L_WORD128 },
        };
        AddToSKeyList((GUIKey *)Words, NELEMENTS(Words));
    }

    if (CurrentPROPtr != NULL) {
        while (DROPDOWN_GetNumItems(hDropdAPI) > 0) {
            DROPDOWN_DeleteItem(hDropdAPI, 0);
        }
        DROPDOWN_AddString(hDropdAPI, "6A");    //0		CTY_API_6A              8
        DROPDOWN_AddString(hDropdAPI, "6B");    //1     CTY_API_6B              9
        DROPDOWN_AddString(hDropdAPI, "6D");    //2     CTY_API_6D              10
        DROPDOWN_AddString(hDropdAPI, "53A");   //3     CTY_API_53A             11
        DROPDOWN_AddString(hDropdAPI, "53B");   //4     CTY_API_53B             12
        DROPDOWN_AddString(hDropdAPI, "53D");   //5     CTY_API_53D             13
        DROPDOWN_AddString(hDropdAPI, "53E");   //6     CTY_API_54A             14
        DROPDOWN_AddString(hDropdAPI, "54A");   //7     CTY_API_54B             15
        DROPDOWN_AddString(hDropdAPI, "54B");   //8     CTY_API_54D             16
        DROPDOWN_AddString(hDropdAPI, "54D");   //9     CTY_API_59A             17
        DROPDOWN_AddString(hDropdAPI, "54E");   //10    CTY_API_59B             18
        DROPDOWN_AddString(hDropdAPI, "59A");   //11    CTY_API_59D             19
        DROPDOWN_AddString(hDropdAPI, "59B");   //12    CTY_API_60A             20
        DROPDOWN_AddString(hDropdAPI, "59D");   //13    CTY_API_60B             21
        DROPDOWN_AddString(hDropdAPI, "59E");   //14    CTY_API_60D             22
        DROPDOWN_AddString(hDropdAPI, "60A");   //15    CTY_API_53E             23
        DROPDOWN_AddString(hDropdAPI, "60B");   //16    CTY_API_54E             24
        DROPDOWN_AddString(hDropdAPI, "60D");   //17    CTY_API_59E             25
        DROPDOWN_AddString(hDropdAPI, "60E");   //18    CTY_API_60E             26

        /* Initialize all widgets */
        PROTank *TankPtr = (PROTank *)CurrentPROPtr;
        //int Type = TankPtr->CargoType->BaseCargoType;// LibGetValue(SVT_BASIC_TYPE,TankPtr);
        //int Sensors = TankPtr->AnalogInCount;
        if (TankPtr->AnalogInList.size() < 2) {
            DisableLevelMeasuredDnsCheckBox();
            //RBMark    CHECKBOX_SetState( hCheckMeasDens,2);
        } else {
            if (TankPtr->UseMeasuredDensity) {
                CHECKBOX_Check(hCheckMeasDens);
            } else {
                CHECKBOX_Uncheck(hCheckMeasDens);
            }
        }
        switch (TankPtr->TankType) {
//            case TANKTYPE_NONE   :
        case TANKTYPE_CARGO     :
        case TANKTYPE_MISC      :
        case TANKTYPE_HFO       :
        case TANKTYPE_DO        :
        case TANKTYPE_LUB       :
        case TANKTYPE_BALLAST   :
        case TANKTYPE_VOIDSPACE :
            switch (TankPtr->CargoType->BaseCargoType) {
            case CTY_NOT_DEFINED:
            case CTY_SIMPLE_LIN :
            case CTY_LINEAR     :
                RADIO_SetValue(hRadioLinAPI, 0);
                UseLinear();
                break;
            case CTY_BALLAST    :
            case CTY_HFO        :
            case CTY_DO         :
            case CTY_LUB        :
            case CTY_FW         :
                //   case CTY_MISC      :
            case CTY_SEA      :
                WM_DisableWindow(hRadioLinAPI);
                RADIO_SetValue(hRadioLinAPI, 0);
                UseLinear();
                break;
            case CTY_API_6A     :
            case CTY_API_6B     :
            case CTY_API_6D     :
            case CTY_API_53A    :
            case CTY_API_53B    :
            case CTY_API_53D    :
            case CTY_API_53E    :
            case CTY_API_54A    :
            case CTY_API_54B    :
            case CTY_API_54D    :
            case CTY_API_54E    :
            case CTY_API_59A    :
            case CTY_API_59B    :
            case CTY_API_59D    :
            case CTY_API_59E    :
            case CTY_API_60A    :
            case CTY_API_60B    :
            case CTY_API_60D    :
            case CTY_API_60E    :
                RADIO_SetValue(hRadioLinAPI, 1);
                {
                    // The list in the DropDown is sorted while the CargoType constans can't be sorted
                    // to maintainbackward compatibility
                    int CType;
                    switch (TankPtr->CargoType->BaseCargoType) {
                    case CTY_API_6A     :
                        CType = 0;  break;   //  "6A");    //0
                    case CTY_API_6B     :
                        CType = 1;  break;   //  "6B");    //1
                    case CTY_API_6D     :
                        CType = 2;  break;   //  "6D");    //2
                    case CTY_API_53A    :
                        CType = 3;  break;   //  "53A");   //3
                    case CTY_API_53B    :
                        CType = 4;  break;   //  "53B");   //4
                    case CTY_API_53D    :
                        CType = 5;  break;   //  "53D");   //5
                    case CTY_API_53E    :
                        CType = 6;  break;   //  "53E");   //6
                    case CTY_API_54A    :
                        CType = 7;  break;   //  "54A");   //7
                    case CTY_API_54B    :
                        CType = 8;  break;   //  "54B");   //8
                    case CTY_API_54D    :
                        CType = 9;  break;   //  "54D");   //9
                    case CTY_API_54E    :
                        CType = 10;  break;   //  "54E");   //10
                    case CTY_API_59A    :
                        CType = 11;  break;   //  "59A");   //11
                    case CTY_API_59B    :
                        CType = 12;  break;   //  "59B");   //12
                    case CTY_API_59D    :
                        CType = 13;  break;   //  "59D");   //13
                    case CTY_API_59E    :
                        CType = 14;  break;   //  "59E");   //14
                    case CTY_API_60A    :
                        CType = 15;  break;   //  "60A");   //15
                    case CTY_API_60B    :
                        CType = 16;  break;   //  "60B");   //16
                    case CTY_API_60D    :
                        CType = 17;  break;   //  "60D");   //17
                    case CTY_API_60E    :
                        CType = 18;  break;   //  "60E");   //18
                    }
                    DROPDOWN_SetSel(hDropdAPI, CType);
                }
                //UseAPI();
                break;
            }
            break;
        case TANKTYPE_FW     :
            WM_DisableWindow(hRadioLinAPI);
            WM_DisableWindow(hCheckLin);
            UseLinear();
            break;
        }

        //if( TankPtr->TankType < CTY_API_6A){
        //    UseLinear();
        //}else{
        //    UseAPI();
        //}
    }
}

void TDUMultipageTankDetails::UpdateDialog1(void) { }

void TDUMultipageTankDetails::UseAPI(void) {
    if (CurrentPROPtr != NULL) {
        PROTank *TankPtr = (PROTank *)CurrentPROPtr;
        //RADIO_SetValue(hRadioLinAPI,1);
//Linear
        WM_HideWindow(hCheckLin);
        WM_HideWindow(hTextLin);
        WM_HideWindow(hTextSimDens);
        WM_HideWindow(hEditSimDens);
        WM_HideWindow(hTextSimDensUnit);
        WM_HideWindow(hTextRef1);
        WM_HideWindow(hTextRef2);
        WM_HideWindow(hTextCoeff);
        WM_HideWindow(hEditTemp1);
        WM_HideWindow(hTextTemp1Unit);
        WM_HideWindow(hEditDens1);
        WM_HideWindow(hTextDens1Unit);
        WM_HideWindow(hEditTemp2);
        WM_HideWindow(hTextTemp2Unit);
        WM_HideWindow(hEditDens2);
        WM_HideWindow(hTextDens2Unit);
        WM_HideWindow(hEditCoeff);
        WM_HideWindow(hTextCoeffUnit);
//API
        WM_ShowWindow(hTextAPI);
        WM_ShowWindow(hDropdAPI);
        WM_ShowWindow(hTextAPI1);
        WM_ShowWindow(hEditAPI1);
        WM_ShowWindow(hTextAPI1Unit);
        WM_ShowWindow(hTextAPI2);
        WM_ShowWindow(hEditAPI2);
        WM_ShowWindow(hTextAPI2Unit);
        {
            int CType = TankPtr->CargoType->BaseCargoType;
            switch (CType) {
            case CTY_NOT_DEFINED :
            case CTY_SIMPLE_LIN  :
            case CTY_LINEAR      :
            case CTY_BALLAST     :
            case CTY_HFO         :
            case CTY_DO          :
            case CTY_LUB         :
            case CTY_FW          :
            case CTY_SEA         :
                switch (DROPDOWN_GetSel(TankDetails->hDropdAPI)) {
                case  0:
                    CType = CTY_API_6A; break;
                case  1:
                    CType = CTY_API_6B; break;
                case  2:
                    CType = CTY_API_6D; break;
                case  3:
                    CType = CTY_API_53A; break;
                case  4:
                    CType = CTY_API_53B; break;
                case  5:
                    CType = CTY_API_53D; break;
                case  6:
                    CType = CTY_API_53E; break;
                case  7:
                    CType = CTY_API_54A; break;
                case  8:
                    CType = CTY_API_54B; break;
                case  9:
                    CType = CTY_API_54D; break;
                case 10:
                    CType = CTY_API_54E; break;
                case 11:
                    CType = CTY_API_59A; break;
                case 12:
                    CType = CTY_API_59B; break;
                case 13:
                    CType = CTY_API_59D; break;
                case 14:
                    CType = CTY_API_59E; break;
                case 15:
                    CType = CTY_API_60A; break;
                case 16:
                    CType = CTY_API_60B; break;
                case 17:
                    CType = CTY_API_60D; break;
                case 18:
                    CType = CTY_API_60E; break;
                }
                LibPutValue(SVT_BASIC_TYPE, TankPtr, CType);
                break;
            default:
                break;
            }
        }
        /*
        switch ( Selected ) {
        case CTY_API_6A     :
            DROPDOWN_SetSel(hDropdAPI, 0);
            break;
        case CTY_API_6B     :
            DROPDOWN_SetSel(hDropdAPI, 1);
            break;
        case CTY_API_6D     :
            DROPDOWN_SetSel(hDropdAPI, 2);
            break;
        case CTY_API_53A    :
            DROPDOWN_SetSel(hDropdAPI, 3);
            break;
        case CTY_API_53B    :
            DROPDOWN_SetSel(hDropdAPI, 4);
            break;
        case CTY_API_53D    :
            DROPDOWN_SetSel(hDropdAPI, 5);
            break;
        case CTY_API_53E    :
            DROPDOWN_SetSel(hDropdAPI, 6);
            break;
        case CTY_API_54A    :
            DROPDOWN_SetSel(hDropdAPI, 7);
            break;
        case CTY_API_54B    :
            DROPDOWN_SetSel(hDropdAPI, 8);
            break;
        case CTY_API_54D    :
            DROPDOWN_SetSel(hDropdAPI, 9);
            break;
        case CTY_API_54E    :
            DROPDOWN_SetSel(hDropdAPI,10);
            break;
        case CTY_API_59A    :
            DROPDOWN_SetSel(hDropdAPI,11);
            break;
        case CTY_API_59B    :
            DROPDOWN_SetSel(hDropdAPI,12);
            break;
        case CTY_API_59D    :
            DROPDOWN_SetSel(hDropdAPI,13);
            break;
        case CTY_API_59E    :
            DROPDOWN_SetSel(hDropdAPI,14);
            break;
        case CTY_API_60A    :
            DROPDOWN_SetSel(hDropdAPI,15);
            break;
        case CTY_API_60B    :
            DROPDOWN_SetSel(hDropdAPI,16);
            break;
        case CTY_API_60D    :
            DROPDOWN_SetSel(hDropdAPI,17);
            break;
        case CTY_API_60E    :
            DROPDOWN_SetSel(hDropdAPI,18);
            break;
        }
        */
        AnsiString CurValue1, CurUnit1;
        AnsiString CurValue2, CurUnit2;
        switch (TankPtr->CargoType->BaseCargoType) {
        case CTY_API_6A     :
        case CTY_API_6B     :
        case CTY_API_6D     :
            TEXT_SetText(hTextAPI1, "API");
            TEXT_SetText(hTextAPI2, "VCF");
            CurValue1 = LibGetValue(SVT_API, TankPtr, &CurUnit1);
            CurValue2 = LibGetValue(SVT_VCF, TankPtr, &CurUnit2);
            WM_EnableWindow(hEditAPI1);
            WM_DisableWindow(hEditAPI2);
            break;
        case CTY_API_53A    :
        case CTY_API_53B    :
        case CTY_API_53D    :
        case CTY_API_53E    :
        case CTY_API_59A    :
        case CTY_API_59B    :
        case CTY_API_59D    :
        case CTY_API_59E    :
            TEXT_SetText(hTextAPI1, FindDictionaryWord(L_WORD104).c_str()); // Reference temperature
            TEXT_SetText(hTextAPI2, FindDictionaryWord(L_WORD83).c_str()); // Density
            CurValue1 = LibGetValue(SVT_REF_TMP2, TankPtr, &CurUnit1);
            CurValue2 = LibGetValue(SVT_REF_DNS2, TankPtr, &CurUnit2);
            WM_EnableWindow(hEditAPI1);
            WM_EnableWindow(hEditAPI2);
            break;
        case CTY_API_54A    :
        case CTY_API_54B    :
        case CTY_API_54D    :
        case CTY_API_54E    :
        case CTY_API_60A    :
        case CTY_API_60B    :
        case CTY_API_60D    :
        case CTY_API_60E    :
            TEXT_SetText(hTextAPI1, FindDictionaryWord(L_WORD104).c_str()); // Reference temperature
            TEXT_SetText(hTextAPI2, FindDictionaryWord(L_WORD83).c_str()); // Density
            CurValue1 = LibGetValue(SVT_REF_TMP1, TankPtr, &CurUnit1);
            CurValue2 = LibGetValue(SVT_REF_DNS1, TankPtr, &CurUnit2);
            WM_DisableWindow(hEditAPI1);
            WM_EnableWindow(hEditAPI2);
            break;
        }
        EDIT_SetText(hEditAPI1, CurValue1.c_str());
        TEXT_SetText(hTextAPI1Unit, CurUnit1.c_str());
        EDIT_SetText(hEditAPI2, CurValue2.c_str());
        TEXT_SetText(hTextAPI2Unit, CurUnit2.c_str());
    }
}

void TDUMultipageTankDetails::UseLinear(void) {
    WM_EnableWindow(hEditTemp1);
    WM_EnableWindow(hEditTemp2);

    if (CurrentPROPtr != NULL) {
        PROTank *TankPtr = (PROTank *)CurrentPROPtr;
        //RADIO_SetValue(hRadioLinAPI,0);
//API
        WM_HideWindow(hTextAPI);
        WM_HideWindow(hDropdAPI);
        WM_HideWindow(hTextAPI1);
        WM_HideWindow(hEditAPI1);
        WM_HideWindow(hTextAPI1Unit);
        WM_HideWindow(hTextAPI2);
        WM_HideWindow(hEditAPI2);
        WM_HideWindow(hTextAPI2Unit);
        //Linear
        WM_ShowWindow(hCheckLin);
        WM_ShowWindow(hTextLin);
        AnsiString CurValue1, CurUnit1;
        switch (TankPtr->CargoType->BaseCargoType) {
        case CTY_NOT_DEFINED:
        case CTY_SIMPLE_LIN :
            CHECKBOX_Uncheck(hCheckLin);
            WM_ShowWindow(hTextSimDens);
            WM_ShowWindow(hEditSimDens);
            WM_ShowWindow(hTextSimDensUnit);
            WM_HideWindow(hTextRef1);
            WM_HideWindow(hTextRef2);
            WM_HideWindow(hTextCoeff);
            WM_HideWindow(hEditTemp1);
            WM_HideWindow(hTextTemp1Unit);
            WM_HideWindow(hEditDens1);
            WM_HideWindow(hTextDens1Unit);
            WM_HideWindow(hEditTemp2);
            WM_HideWindow(hTextTemp2Unit);
            WM_HideWindow(hEditDens2);
            WM_HideWindow(hTextDens2Unit);
            WM_HideWindow(hEditCoeff);
            WM_HideWindow(hTextCoeffUnit);
            CurValue1 = LibGetValue(SVT_REF_DNS1, TankPtr, &CurUnit1);
            EDIT_SetText(hEditSimDens, CurValue1.c_str());
            TEXT_SetText(hTextSimDensUnit, CurUnit1.c_str());
            break;
        case CTY_BALLAST:
        case CTY_HFO  :
        case CTY_DO     :
        case CTY_LUB    :
        case CTY_FW     :
//            case CTY_MISC  :
        case CTY_SEA  :
            CHECKBOX_Uncheck(hCheckLin);
            WM_ShowWindow(hTextSimDens);
            WM_ShowWindow(hEditSimDens);
            WM_ShowWindow(hTextSimDensUnit);
            WM_HideWindow(hTextRef1);
            WM_HideWindow(hTextRef2);
            WM_HideWindow(hTextCoeff);
            WM_HideWindow(hEditTemp1);
            WM_HideWindow(hTextTemp1Unit);
            WM_HideWindow(hEditDens1);
            WM_HideWindow(hTextDens1Unit);
            WM_HideWindow(hEditTemp2);
            WM_HideWindow(hTextTemp2Unit);
            WM_HideWindow(hEditDens2);
            WM_HideWindow(hTextDens2Unit);
            WM_HideWindow(hEditCoeff);
            WM_HideWindow(hTextCoeffUnit);
            CurValue1 = LibGetValue(SVT_REF_DNS1, TankPtr, &CurUnit1);
            EDIT_SetText(hEditSimDens, CurValue1.c_str());
            TEXT_SetText(hTextSimDensUnit, CurUnit1.c_str());
            break;
        case CTY_LINEAR     :
            CHECKBOX_Check(hCheckLin);
            WM_HideWindow(hTextSimDens);
            WM_HideWindow(hEditSimDens);
            WM_HideWindow(hTextSimDensUnit);
            WM_ShowWindow(hTextRef1);
            WM_ShowWindow(hTextRef2);
            WM_ShowWindow(hTextCoeff);
            WM_ShowWindow(hEditTemp1);
            WM_ShowWindow(hTextTemp1Unit);
            WM_ShowWindow(hEditDens1);
            WM_ShowWindow(hTextDens1Unit);
            WM_ShowWindow(hEditTemp2);
            WM_ShowWindow(hTextTemp2Unit);
            WM_ShowWindow(hEditDens2);
            WM_ShowWindow(hTextDens2Unit);
            WM_ShowWindow(hEditCoeff);
            WM_ShowWindow(hEditCoeff);
            WM_ShowWindow(hTextCoeffUnit);
            CurValue1 = LibGetValue(SVT_REF_TMP1, TankPtr, &CurUnit1);
            EDIT_SetText(hEditTemp1, CurValue1.c_str());
            TEXT_SetText(hTextTemp1Unit, CurUnit1.c_str());
            CurValue1 = LibGetValue(SVT_REF_DNS1, TankPtr, &CurUnit1);
            EDIT_SetText(hEditDens1, CurValue1.c_str());
            TEXT_SetText(hTextDens1Unit, CurUnit1.c_str());
            CurValue1 = LibGetValue(SVT_REF_TMP2, TankPtr, &CurUnit1);
            EDIT_SetText(hEditTemp2, CurValue1.c_str());
            TEXT_SetText(hTextTemp2Unit, CurUnit1.c_str());
            CurValue1 = LibGetValue(SVT_REF_DNS2, TankPtr, &CurUnit1);
            EDIT_SetText(hEditDens2, CurValue1.c_str());
            TEXT_SetText(hTextDens2Unit, CurUnit1.c_str());
            CurValue1 = LibGetValue(SVT_COEFF, TankPtr, &CurUnit1);
            EDIT_SetText(hEditCoeff, CurValue1.c_str());
            TEXT_SetText(hTextCoeffUnit, CurUnit1.c_str());
            break;
        }
    }
}

void TDUMultipageTankDetails::SetNewValueDialog1(int key, AnsiString ValueString) {
    if (CurrentPROPtr != NULL) {
        PROTank *TankPtr = (PROTank *)CurrentPROPtr;
        switch (key) {
        case GUI_ID_EDIT11: //API1
            switch (TankPtr->CargoType->BaseCargoType) {
            case CTY_API_6A     :
            case CTY_API_6B     :
            case CTY_API_6D     :
                LibPutValue(SVT_API, TankPtr, ValueString);
                break;
            case CTY_API_53A  :
            case CTY_API_53B  :
            case CTY_API_53D  :
            case CTY_API_53E  :
            case CTY_API_59A  :
            case CTY_API_59B  :
            case CTY_API_59D  :
            case CTY_API_59E  :
                LibPutValue(SVT_REF_TMP2, TankPtr, ValueString);
                break;
            case CTY_API_54A  :
            case CTY_API_54B  :
            case CTY_API_54D  :
            case CTY_API_54E  :
            case CTY_API_60A  :
            case CTY_API_60B  :
            case CTY_API_60D  :
            case CTY_API_60E  :
                //                  LibPutValue(SVT_REF_TMP1, TankPtr, ValueString);
                break;
            }
            break;
        case GUI_ID_EDIT13: //API2
            switch (TankPtr->CargoType->BaseCargoType) {
            case CTY_API_6A   :
            case CTY_API_6B   :
            case CTY_API_6D   :
//                      LibPutValue(SVT_VCF, TankPtr, ValueString);
                break;
            case CTY_API_53A  :
            case CTY_API_53B  :
            case CTY_API_53D  :
            case CTY_API_53E  :
            case CTY_API_59A  :
            case CTY_API_59B  :
            case CTY_API_59D  :
            case CTY_API_59E  :
                LibPutValue(SVT_REF_DNS2, TankPtr, ValueString);
                break;
            case CTY_API_54A  :
            case CTY_API_54B  :
            case CTY_API_54D  :
            case CTY_API_54E  :
            case CTY_API_60A  :
            case CTY_API_60B  :
            case CTY_API_60D  :
            case CTY_API_60E  :
                LibPutValue(SVT_REF_DNS1, TankPtr, ValueString);
                break;
            }
            break;
        case GUI_ID_EDIT21: //Density
            LibPutValue(SVT_REF_DNS1, TankPtr, ValueString);
            break;
        case GUI_ID_EDIT24:
            LibPutValue(SVT_REF_TMP1, TankPtr, ValueString);
            break;
        case GUI_ID_EDIT26:
            LibPutValue(SVT_REF_TMP2, TankPtr, ValueString);
            break;
        case GUI_ID_EDIT28:
            LibPutValue(SVT_REF_DNS1, TankPtr, ValueString);
            break;
        case GUI_ID_EDIT30:
            LibPutValue(SVT_REF_DNS2, TankPtr, ValueString);
            break;
        case GUI_ID_EDIT32:
            LibPutValue(SVT_COEFF, TankPtr, ValueString);
            break;
        }
        InitDialog1();
    }
}
void TDUMultipageTankDetails::SetAllNewValueDialog1(void) {
    if (!CurrentListPtr.empty()) {
        PROTank *TankPtr = (PROTank *)CurrentPROPtr;
        for (unsigned i = 0; i < CurrentListPtr.size(); i++) {
            PRogramObject *TElement = (PRogramObject *)CurrentListPtr[i];
            AnsiString ValueString = "";
            if ((CurrentWinID == TDU_CARGO_WIN) || (CurrentWinID == TDU_BALLAST_WIN) || (CurrentWinID == TDU_SERVICE_WIN) || (CurrentWinID == TDU_TANKFARM_WIN)) {
                ValueString = LibGetValue(SVT_BASIC_TYPE, TankPtr);
                LibPutValue(SVT_BASIC_TYPE, TElement, ValueString);

                ValueString = LibGetValue(SVT_USE_MSRD_DNS, TankPtr);
                LibPutValue(SVT_USE_MSRD_DNS, TElement, ValueString);

                switch (TankPtr->CargoType->BaseCargoType) {
                case CTY_API_6A   :
                case CTY_API_6B   :
                case CTY_API_6D   :
                    ValueString = LibGetValue(SVT_API, TankPtr);
                    LibPutValue(SVT_API, TElement, ValueString);
                    //     ValueString = LibGetValue(SVT_VCF,TankPtr);
                    //LibPutValue(SVT_VCF, TElement, ValueString);
                    break;
                case CTY_API_53A  :
                case CTY_API_53B  :
                case CTY_API_53D  :
                case CTY_API_53E  :
                case CTY_API_59A  :
                case CTY_API_59B  :
                case CTY_API_59D  :
                case CTY_API_59E  :
                    ValueString = LibGetValue(SVT_REF_TMP2, TankPtr);
                    LibPutValue(SVT_REF_TMP2, TElement, ValueString);
                    ValueString = LibGetValue(SVT_REF_DNS2, TankPtr);
                    LibPutValue(SVT_REF_DNS2, TElement, ValueString);
                    break;
                case CTY_API_54A  :
                case CTY_API_54B  :
                case CTY_API_54D  :
                case CTY_API_54E  :
                case CTY_API_60A  :
                case CTY_API_60B  :
                case CTY_API_60D  :
                case CTY_API_60E  :
                    //    ValueString = LibGetValue(SVT_REF_TMP1,TankPtr);
                    //LibPutValue( SVT_REF_TMP1, TElement, ValueString);
                    ValueString = LibGetValue(SVT_REF_DNS1, TankPtr);
                    LibPutValue(SVT_REF_DNS1, TElement, ValueString);
                    break;
                default:
                    ValueString = LibGetValue(SVT_REF_TMP1, TankPtr);
                    LibPutValue(SVT_REF_TMP1, TElement, ValueString);

                    ValueString = LibGetValue(SVT_REF_TMP2, TankPtr);
                    LibPutValue(SVT_REF_TMP2, TElement, ValueString);

                    ValueString = LibGetValue(SVT_REF_DNS1, TankPtr);
                    LibPutValue(SVT_REF_DNS1, TElement, ValueString);

                    ValueString = LibGetValue(SVT_REF_DNS2, TankPtr);
                    LibPutValue(SVT_REF_DNS2, TElement, ValueString);

                    ValueString = LibGetValue(SVT_COEFF, TankPtr);
                    LibPutValue(SVT_COEFF, TElement, ValueString);
                    break;
                }
            }
        }
//      UpdateDialog1();
    }
}

/*********************************************************************
*
* Dialog2 procedure
*/
void TDUMultipageTankDetails::GetDialog2Handles(void) {
    /* Get window handles for all widgets */
    hButApplyAlarm  = WM_GetDialogItem(WinHandl, GUI_ID_OK);
    hButUnlock2     = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON8);
    hTextOverfill   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT34);
    hTextHighLev    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT35);
    hTextLowLev     = WM_GetDialogItem(WinHandl, GUI_ID_TEXT36);
    hTextHighTemp   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT37);
    hTextLowTemp    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT38);
    hTextHighPress  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT39);
    hTextLowPress   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT40);
    hOverfill       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT41);
    hHighLev        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT42);
    hLowLev         = WM_GetDialogItem(WinHandl, GUI_ID_TEXT43);
    hHighTemp       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT44);
    hLowTemp        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT45);
    hHighPress      = WM_GetDialogItem(WinHandl, GUI_ID_TEXT46);
    hLowPress       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT47);
    hEditOverfill   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT41);
    hEditHighLev    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT42);
    hEditLowLev     = WM_GetDialogItem(WinHandl, GUI_ID_EDIT43);
    hEditHighTemp   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT44);
    hEditLowTemp    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT45);
    hEditHighPress  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT46);
    hEditLowPress   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT47);
    hCheckOverfill  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK41);
    hCheckHighLev   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK42);
    hCheckLowLev    = WM_GetDialogItem(WinHandl, GUI_ID_CHECK43);
    hCheckHighTemp  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK44);
    hCheckLowTemp   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK45);
    hCheckHighPress = WM_GetDialogItem(WinHandl, GUI_ID_CHECK46);
    hCheckLowPress  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK47);
    InitDialog2();
}

void TDUMultipageTankDetails::InitDialog2(void) {
    UpdateDialog2();
}

void TDUMultipageTankDetails::UpdateDialog2(void) {
    if (CurrentPROPtr != NULL) {
        switch (CurrentWinID) {
        case TDU_MAIN_WIN:
        case TDU_HEAD_WIN:
        case TDU_BUT_WIN:
        case TDU_PRESENT_WIN:
        case TDU_SYSTEM_WIN:
        case TDU_ALARM_WIN:
            break;
        case TDU_CARGO_WIN:
        case TDU_BALLAST_WIN:
        case TDU_SERVICE_WIN:
        case TDU_TANKFARM_WIN:
            {
                PROTank *TElement = (PROTank *)CurrentPROPtr;
                if (TElement != NULL) {
                    /* Initialize all widgets */
                    AnsiString str = "";
                    AnsiString UnitStr = "";
                    if (TElement->OverfillPtr) {
                        if (TElement->OverfillPtr->Enable) {
                            CHECKBOX_Check(hCheckOverfill);
                        } else {
                            CHECKBOX_Uncheck(hCheckOverfill);
                        }
                        str = LibGetValue(SVT_HIHI_VOLPCNT_LIM, TElement, &UnitStr);
                        EDIT_SetText(hEditOverfill, str.c_str());
                        TEXT_SetText(hTextOverfill, UnitStr.c_str());
                    } else {
                        WM_HideWindow(hOverfill);
                        WM_HideWindow(hEditOverfill);
                        WM_HideWindow(hTextOverfill);
                        WM_HideWindow(hCheckOverfill);
                    }
                    if (TElement->HighLevelPtr->Enable) {
                        CHECKBOX_Check(hCheckHighLev);
                    } else {
                        CHECKBOX_Uncheck(hCheckHighLev);
                    }
                    if (TElement->LowLevelPtr->Enable) {
                        CHECKBOX_Check(hCheckLowLev);
                    } else {
                        CHECKBOX_Uncheck(hCheckLowLev);
                    }
                    str = LibGetValue(SVT_HI_LEVEL_LIMIT, TElement, &UnitStr);
                    EDIT_SetText(hEditHighLev, str.c_str());
                    TEXT_SetText(hTextHighLev, UnitStr.c_str());
                    str = LibGetValue(SVT_LO_LEVEL_LIMIT, TElement, &UnitStr);
                    EDIT_SetText(hEditLowLev, str.c_str());
                    TEXT_SetText(hTextLowLev, UnitStr.c_str());

                    if (TElement->TemperaturePtr) {
                        if (TElement->TemperaturePtr->HighTempPtr->Enable) {
                            CHECKBOX_Check(hCheckHighTemp);
                        } else {
                            CHECKBOX_Uncheck(hCheckHighTemp);
                        }
                        if (TElement->TemperaturePtr->LowTempPtr->Enable) {
                            CHECKBOX_Check(hCheckLowTemp);
                        } else {
                            CHECKBOX_Uncheck(hCheckLowTemp);
                        }
                        str = LibGetValue(SVT_HI_TEMP_LIMIT, TElement, &UnitStr);
                        EDIT_SetText(hEditHighTemp, str.c_str());
                        TEXT_SetText(hTextHighTemp, UnitStr.c_str());
                        str = LibGetValue(SVT_LO_TEMP_LIMIT, TElement, &UnitStr);
                        EDIT_SetText(hEditLowTemp, str.c_str());
                        TEXT_SetText(hTextLowTemp, UnitStr.c_str());
                    } else {
                        WM_HideWindow(hHighTemp);
                        WM_HideWindow(hLowTemp);
                        WM_HideWindow(hCheckHighTemp);
                        WM_HideWindow(hCheckLowTemp);
                        WM_HideWindow(hEditHighTemp);
                        WM_HideWindow(hEditLowTemp);
                        WM_HideWindow(hTextHighTemp);
                        WM_HideWindow(hTextLowTemp);
                    }
                    if (TElement->PressurePtr) {
                        if (TElement->PressurePtr->HighPressurePtr->Enable) {
                            CHECKBOX_Check(hCheckHighPress);
                        } else {
                            CHECKBOX_Uncheck(hCheckHighPress);
                        }
                        if (TElement->PressurePtr->LowPressurePtr->Enable) {
                            CHECKBOX_Check(hCheckLowPress);
                        } else {
                            CHECKBOX_Uncheck(hCheckLowPress);
                        }
                        str = LibGetValue(SVT_HI_PRESS_LIMIT, TElement, &UnitStr);
                        EDIT_SetText(hEditHighPress, str.c_str());
                        TEXT_SetText(hTextHighPress, UnitStr.c_str());
                        str = LibGetValue(SVT_LO_PRESS_LIMIT, TElement, &UnitStr);
                        EDIT_SetText(hEditLowPress, str.c_str());
                        TEXT_SetText(hTextLowPress, UnitStr.c_str());
                    } else {
                        WM_HideWindow(hHighPress);
                        WM_HideWindow(hLowPress);
                        WM_HideWindow(hCheckHighPress);
                        WM_HideWindow(hCheckLowPress);
                        WM_HideWindow(hTextHighPress);
                        WM_HideWindow(hTextLowPress);
                        WM_HideWindow(hEditHighPress);
                        WM_HideWindow(hEditLowPress);
                    }
                }
            }
            break;
        case TDU_LINEPRESS_WIN:
            TEXT_SetText(hHighPress, FindDictionaryWord(L_WORD158).c_str()); // High Line Press
            TEXT_SetText(hLowPress, FindDictionaryWord(L_WORD159).c_str()); // Low Line Press
        case TDU_TANKPRESS_WIN:
            {
                if (CurrentPROPtr != NULL) {
                    WM_HideWindow(hOverfill);
                    WM_HideWindow(hHighLev);
                    WM_HideWindow(hLowLev);
                    WM_HideWindow(hHighTemp);
                    WM_HideWindow(hLowTemp);
                    WM_HideWindow(hEditOverfill);
                    WM_HideWindow(hEditHighLev);
                    WM_HideWindow(hEditLowLev);
                    WM_HideWindow(hEditHighTemp);
                    WM_HideWindow(hEditLowTemp);
                    WM_HideWindow(hTextOverfill);
                    WM_HideWindow(hTextHighLev);
                    WM_HideWindow(hTextLowLev);
                    WM_HideWindow(hTextHighTemp);
                    WM_HideWindow(hTextLowTemp);
                    WM_HideWindow(hCheckOverfill);
                    WM_HideWindow(hCheckHighLev);
                    WM_HideWindow(hCheckLowLev);
                    WM_HideWindow(hCheckHighTemp);
                    WM_HideWindow(hCheckLowTemp);
                    /* Initialize all widgets */
                    AnsiString str;
                    AnsiString UnitStr;
                    str = LibGetValue(SVT_HI_PRESS_LIMIT, CurrentPROPtr, &UnitStr);
                    EDIT_SetText(hEditHighPress, str.c_str());
                    TEXT_SetText(hTextHighPress, UnitStr.c_str());
                    str = LibGetValue(SVT_LO_PRESS_LIMIT, CurrentPROPtr, &UnitStr);
                    EDIT_SetText(hEditLowPress, str.c_str());
                    TEXT_SetText(hTextLowPress, UnitStr.c_str());

                    str = LibGetValue(SVT_HI_PRESS_ENABLE, CurrentPROPtr);
                    if (str == "1") {
                        CHECKBOX_Check(hCheckHighPress);
                    } else {
                        CHECKBOX_Uncheck(hCheckHighPress);
                    }
                    str = LibGetValue(SVT_LO_PRESS_ENABLE, CurrentPROPtr);
                    if (str == "1") {
                        CHECKBOX_Check(hCheckLowPress);
                    } else {
                        CHECKBOX_Uncheck(hCheckLowPress);
                    }
                }
            }
            break;
        case TDU_VOIDSPACE_WIN:
            WM_HideWindow(hOverfill);
            WM_HideWindow(hHighLev);
            WM_HideWindow(hLowLev);
            WM_HideWindow(hHighTemp);
            WM_HideWindow(hLowTemp);
            WM_HideWindow(hEditOverfill);
            WM_HideWindow(hEditHighLev);
            WM_HideWindow(hEditLowLev);
            WM_HideWindow(hEditHighTemp);
            WM_HideWindow(hEditLowTemp);
            WM_HideWindow(hTextOverfill);
            WM_HideWindow(hTextHighLev);
            WM_HideWindow(hTextLowLev);
            WM_HideWindow(hTextHighTemp);
            WM_HideWindow(hTextLowTemp);
            WM_HideWindow(hCheckOverfill);
            WM_HideWindow(hCheckHighLev);
            WM_HideWindow(hCheckLowLev);
            WM_HideWindow(hCheckHighTemp);
            WM_HideWindow(hCheckLowTemp);
            break;
        case TDU_TEMP_WIN:
            {
                PROTemperature *TElement = (PROTemperature *)CurrentPROPtr;
                WM_HideWindow(hOverfill);
                WM_HideWindow(hHighLev);
                WM_HideWindow(hLowLev);
                WM_HideWindow(hHighPress);
                WM_HideWindow(hLowPress);
                WM_HideWindow(hEditOverfill);
                WM_HideWindow(hEditHighLev);
                WM_HideWindow(hEditLowLev);
                WM_HideWindow(hEditHighPress);
                WM_HideWindow(hEditLowPress);
                WM_HideWindow(hTextOverfill);
                WM_HideWindow(hTextHighLev);
                WM_HideWindow(hTextLowLev);
                WM_HideWindow(hTextHighPress);
                WM_HideWindow(hTextLowPress);
                WM_HideWindow(hCheckOverfill);
                WM_HideWindow(hCheckHighLev);
                WM_HideWindow(hCheckLowLev);
                WM_HideWindow(hCheckHighPress);
                WM_HideWindow(hCheckLowPress);

                /* Initialize all widgets */
                AnsiString str = "";
                AnsiString UnitStr = "";
                str = LibGetValue(SVT_HI_TEMP_LIMIT, TElement, &UnitStr);
                EDIT_SetText(hEditHighTemp, str.c_str());
                TEXT_SetText(hTextHighTemp, UnitStr.c_str());
                str = LibGetValue(SVT_LO_TEMP_LIMIT, TElement, &UnitStr);
                EDIT_SetText(hEditLowTemp, str.c_str());
                TEXT_SetText(hTextLowTemp, UnitStr.c_str());

                if (TElement->HighTempPtr->Enable) {
                    CHECKBOX_Check(hCheckHighTemp);
                } else {
                    CHECKBOX_Uncheck(hCheckHighTemp);
                }
                if (TElement->LowTempPtr->Enable) {
                    CHECKBOX_Check(hCheckLowTemp);
                } else {
                    CHECKBOX_Uncheck(hCheckLowTemp);
                }
            }
            break;
        case TDU_LEVELSWITCH_WIN:
        case TDU_GASSAMPL_WIN:
        case TDU_WATERINGR_WIN:
        default:
            break;
        }
    }

    EnableOrDisableAlarmSettingsControls(PinUnlock, alarmSettingsLocked);
    if (PinUnlock) {
        BUTTON_SetText(hButUnlock2, FindDictionaryWord(L_WORD1002).c_str());   // Lock
    } else {
        BUTTON_SetText(hButUnlock2, FindDictionaryWord(L_WORD123).c_str());   // Unlock
    }
}

void TDUMultipageTankDetails::SetNewValueDialog2(int key, AnsiString ValueString) {
    if (CurrentPROPtr != NULL) {
        if (CurrentPROPtr != NULL) {
            switch (key) {
            case GUI_ID_EDIT41:
                LibPutValue(SVT_HIHI_VOLPCNT_LIM, CurrentPROPtr, ValueString);
                EDIT_SetText(hEditOverfill, ValueString.c_str());
                break;
            case GUI_ID_EDIT42:
                LibPutValue(SVT_HI_LEVEL_LIMIT, CurrentPROPtr, ValueString);
                EDIT_SetText(hEditHighLev, ValueString.c_str());
                break;
            case GUI_ID_EDIT43:
                LibPutValue(SVT_LO_LEVEL_LIMIT, CurrentPROPtr, ValueString);
                EDIT_SetText(hEditLowLev, ValueString.c_str());
                break;
            case GUI_ID_EDIT44:
                LibPutValue(SVT_HI_TEMP_LIMIT, CurrentPROPtr, ValueString);
                EDIT_SetText(hEditHighTemp, ValueString.c_str());
                break;
            case GUI_ID_EDIT45:
                LibPutValue(SVT_LO_TEMP_LIMIT, CurrentPROPtr, ValueString);
                EDIT_SetText(hEditLowTemp, ValueString.c_str());
                break;
            case GUI_ID_EDIT46:
                LibPutValue(SVT_HI_PRESS_LIMIT, CurrentPROPtr, ValueString);
                EDIT_SetText(hEditHighPress, ValueString.c_str());
                break;
            case GUI_ID_EDIT47:
                LibPutValue(SVT_LO_PRESS_LIMIT, CurrentPROPtr, ValueString);
                EDIT_SetText(hEditLowPress, ValueString.c_str());
                break;
            case GUI_ID_CHECK41:
                LibPutValue(SVT_HIHI_LEVEL_ENABLE, CurrentPROPtr, CHECKBOX_IsChecked(hCheckOverfill));
                break;
            case GUI_ID_CHECK42:
                LibPutValue(SVT_HI_LEVEL_ENABLE, CurrentPROPtr, CHECKBOX_IsChecked(hCheckHighLev));
                break;
            case GUI_ID_CHECK43:
                LibPutValue(SVT_LO_LEVEL_ENABLE, CurrentPROPtr, CHECKBOX_IsChecked(hCheckLowLev));
                break;
            case GUI_ID_CHECK44:
                LibPutValue(SVT_HI_TEMP_ENABLE, CurrentPROPtr, CHECKBOX_IsChecked(hCheckHighTemp));
                break;
            case GUI_ID_CHECK45:
                LibPutValue(SVT_LO_TEMP_ENABLE, CurrentPROPtr, CHECKBOX_IsChecked(hCheckLowTemp));
                break;
            case GUI_ID_CHECK46:
                LibPutValue(SVT_HI_PRESS_ENABLE, CurrentPROPtr, CHECKBOX_IsChecked(hCheckHighPress));
                break;
            case GUI_ID_CHECK47:
                LibPutValue(SVT_LO_PRESS_ENABLE, CurrentPROPtr, CHECKBOX_IsChecked(hCheckLowPress));
                break;
            }
        }
        UpdateDialog2();
    }
}

void TDUMultipageTankDetails::SetAllNewValueDialog2(void) {
    if (!CurrentListPtr.empty()) {
        for (unsigned i = 0; i < CurrentListPtr.size(); i++) {
            PRogramObject *TElement = (PRogramObject *)CurrentListPtr[i];
            AnsiString ValueString;
            if ((CurrentWinID == TDU_CARGO_WIN) || (CurrentWinID == TDU_BALLAST_WIN) || (CurrentWinID == TDU_SERVICE_WIN) || (CurrentWinID == TDU_TANKFARM_WIN)) {
                ValueString = LibGetValue(SVT_HIHI_VOLPCNT_LIM, CurrentPROPtr);
                LibPutValue(SVT_HIHI_VOLPCNT_LIM, TElement, ValueString);

                ValueString = LibGetValue(SVT_HI_LEVEL_LIMIT, CurrentPROPtr);
                LibPutValue(SVT_HI_LEVEL_LIMIT, TElement, ValueString);

                ValueString = LibGetValue(SVT_LO_LEVEL_LIMIT, CurrentPROPtr);
                LibPutValue(SVT_LO_LEVEL_LIMIT, TElement, ValueString);

                ValueString = LibGetValue(SVT_HIHI_LEVEL_ENABLE, CurrentPROPtr);
                LibPutValue(SVT_HIHI_LEVEL_ENABLE, TElement, CHECKBOX_IsChecked(hCheckOverfill));

                ValueString = LibGetValue(SVT_HI_LEVEL_ENABLE, CurrentPROPtr);
                LibPutValue(SVT_HI_LEVEL_ENABLE, TElement, CHECKBOX_IsChecked(hCheckHighLev));

                ValueString = LibGetValue(SVT_HI_LEVEL_ENABLE, CurrentPROPtr);
                LibPutValue(SVT_LO_LEVEL_ENABLE, TElement, CHECKBOX_IsChecked(hCheckLowLev));
            }
            if ((CurrentWinID == TDU_CARGO_WIN) || (CurrentWinID == TDU_BALLAST_WIN) || (CurrentWinID == TDU_SERVICE_WIN) ||
                (CurrentWinID == TDU_TEMP_WIN) || (CurrentWinID == TDU_TANKFARM_WIN)) {
                ValueString = LibGetValue(SVT_HI_TEMP_LIMIT, CurrentPROPtr);
                LibPutValue(SVT_HI_TEMP_LIMIT, TElement, ValueString);

                ValueString = LibGetValue(SVT_LO_TEMP_LIMIT, CurrentPROPtr);
                LibPutValue(SVT_LO_TEMP_LIMIT, TElement, ValueString);

                ValueString = LibGetValue(SVT_HI_TEMP_ENABLE, CurrentPROPtr);
                LibPutValue(SVT_HI_TEMP_ENABLE, TElement, CHECKBOX_IsChecked(hCheckHighTemp));

                ValueString = LibGetValue(SVT_LO_TEMP_ENABLE, CurrentPROPtr);
                LibPutValue(SVT_LO_TEMP_ENABLE, TElement, CHECKBOX_IsChecked(hCheckLowTemp));
            }
            if ((CurrentWinID == TDU_CARGO_WIN) || (CurrentWinID == TDU_BALLAST_WIN) || (CurrentWinID == TDU_SERVICE_WIN) ||
                (CurrentWinID == TDU_TANKPRESS_WIN) || (CurrentWinID == TDU_TANKFARM_WIN)) {
                ValueString = LibGetValue(SVT_HI_PRESS_LIMIT, CurrentPROPtr);
                LibPutValue(SVT_HI_PRESS_LIMIT, TElement, ValueString);

                ValueString = LibGetValue(SVT_LO_PRESS_LIMIT, CurrentPROPtr);
                LibPutValue(SVT_LO_PRESS_LIMIT, TElement, ValueString);

                ValueString = LibGetValue(SVT_HI_PRESS_ENABLE, CurrentPROPtr);
                LibPutValue(SVT_HI_PRESS_ENABLE, TElement, CHECKBOX_IsChecked(hCheckHighPress));

                ValueString = LibGetValue(SVT_LO_PRESS_ENABLE, CurrentPROPtr);
                LibPutValue(SVT_LO_PRESS_ENABLE, TElement, CHECKBOX_IsChecked(hCheckLowPress));
            }
        }
//      UpdateDialog2();
    }
}

/*********************************************************************
*
* Dialog3 procedure
*/
void TDUMultipageTankDetails::GetDialog3Handles(void) {
    /* Get window handles for all widgets */
    hButZeroPress   = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON0);
    hButZeroLevel   = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON1);
    hButLevelAdj    = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON2);
    hButSoundingAdj = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON3);
    hButUllageAdj   = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON4);
    hButVolumeAdj   = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON5);
    hButWeightAdj   = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON6);
    hButUnlock3     = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON9);

    InitDialog3();
}


void TDUMultipageTankDetails::InitDialog3(void) {
    if (CurrentPROPtr != NULL) {
        switch (CurrentPROPtr->Type) {
        case C_PRO_TANK     :
        case C_PRO_CARGO    :
        case C_PRO_BALLAST  :
        case C_PRO_HFO      :
        case C_PRO_DO       :
        case C_PRO_LUB      :
        case C_PRO_FW       :
        case C_PRO_MISC     :
        case C_PRO_VOIDSPACE:
            /* Initialize all widgets */
            if (!((PROTank *)CurrentPROPtr)->PressurePtr) {
                WM_HideWin(hButZeroPress);
            } else {
                ChangeSWord(GUI_ID_BUTTON0, 0, L_WORD116);
                //BUTTON_SetText(hButZeroPress, FindDictionaryWord(L_WORD116).c_str());   // Zero adjust tank \npressure sensor
            }
            //    WM_DisableWindow(hButZeroPress);
            break;
        case C_PRO_TANKPRESS:
            ChangeSWord(GUI_ID_BUTTON0, 0, L_WORD116);
            //BUTTON_SetText(hButZeroPress, FindDictionaryWord(L_WORD116).c_str());   // Zero adjust tank \npressure sensor
            WM_HideWin(hButZeroLevel);
            WM_HideWin(hButLevelAdj);
            WM_HideWin(hButSoundingAdj);
            WM_HideWin(hButUllageAdj);
            WM_HideWin(hButVolumeAdj);
            WM_HideWin(hButWeightAdj);
            break;
        case C_PRO_LINEPRESS:
            ChangeSWord(GUI_ID_BUTTON0, 0, L_WORD160);
            //BUTTON_SetText(hButZeroPress, FindDictionaryWord(L_WORD160).c_str());   // Zero adjust line \npressure sensor
            WM_HideWin(hButZeroLevel);
            WM_HideWin(hButLevelAdj);
            WM_HideWin(hButSoundingAdj);
            WM_HideWin(hButUllageAdj);
            WM_HideWin(hButVolumeAdj);
            WM_HideWin(hButWeightAdj);
            break;
        case C_PRO_TEMP:
            //ChangeSWord(GUI_ID_BUTTON0,0,L_WORD116);
            WM_HideWin(hButZeroPress);
            WM_HideWin(hButZeroLevel);
            WM_HideWin(hButLevelAdj);
            WM_HideWin(hButSoundingAdj);
            WM_HideWin(hButUllageAdj);
            WM_HideWin(hButVolumeAdj);
            WM_HideWin(hButWeightAdj);
            break;
        }

    }

    UpdateDialog3();
}
// EHSMark. Dette forstår jeg ikke!!!!
void TDUMultipageTankDetails::UpdateDialog3(void) {
    void (*toggleFunction)(WM_HWIN);

    if (PinUnlock) {
        toggleFunction = WM_EnableWindow;
        BUTTON_SetText(hButUnlock3, FindDictionaryWord(L_WORD1002).c_str());   // Lock
    } else {
        toggleFunction = WM_DisableWindow;
        BUTTON_SetText(hButUnlock3, FindDictionaryWord(L_WORD123).c_str());   // Unlock
    }
    toggleFunction(hButZeroPress);
    toggleFunction(hButZeroLevel);
    toggleFunction(hButLevelAdj);
    toggleFunction(hButSoundingAdj);
    toggleFunction(hButUllageAdj);
    toggleFunction(hButVolumeAdj);
    toggleFunction(hButWeightAdj);
}

void TDUMultipageTankDetails::SetNewValueDialog3(int key, AnsiString ValueString) {
    if (CurrentPROPtr != NULL) {
        //PROTank* TankPtr = (PROTank*)CurrentPROPtr;
        switch (key) {
        case GUI_ID_BUTTON0:    /* Pressure Button */
            LibPutValue(SVT_ZEROSET_PRESS, CurrentPROPtr, "0.0", true);
            break;
        case GUI_ID_BUTTON1:    /* Level Button */
            LibPutValue(SVT_ZEROSET_LEVEL, CurrentPROPtr, "0.0", true);
            break;
        case GUI_ID_BUTTON2:
            LibPutValue(SVT_ADJUST_LEVEL, CurrentPROPtr, ValueString, true);
            break;
        case GUI_ID_BUTTON3:
            LibPutValue(SVT_ADJUST_SOUNDING, CurrentPROPtr, ValueString, true);
            break;
        case GUI_ID_BUTTON4:
            LibPutValue(SVT_ADJUST_ULLAGE, CurrentPROPtr, ValueString, true);
            break;
        case GUI_ID_BUTTON5:
            LibPutValue(SVT_ADJUST_VOLUME, CurrentPROPtr, ValueString, true);
            break;
        case GUI_ID_BUTTON6:
            LibPutValue(SVT_ADJUST_WEIGHT, CurrentPROPtr, ValueString, true);
            break;
        }
    }
    UpdateDialog3();
}

/*********************************************************************
*
* Dialog4 procedure
*/
void TDUMultipageTankDetails::GetDialog4Handles(void) {
    /* Get window handles for all widgets */
    hTextSnsLoc1    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT60);
    hTextSnsLoc2    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT61);
    hTextSnsLoc3    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT62);
    hTextSnsLoc4    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT63);
    hTextSnsLoc5    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT64);
    hTextSnsUnit1   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT65);
    hTextSnsUnit2   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT66);
    hTextSnsUnit3   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT67);
    hTextSnsUnit4   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT68);
    hTextSnsUnit5   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT69);
    hEditSnsGain1   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT50);
    hEditSnsGain2   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT51);
    hEditSnsGain3   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT52);
    hEditSnsGain4   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT53);
    hEditSnsGain5   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT54);
    hEditSnsOffset1 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT55);
    hEditSnsOffset2 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT56);
    hEditSnsOffset3 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT57);
    hEditSnsOffset4 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT58);
    hEditSnsOffset5 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT59);
    hEditSnsValue1  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT60);
    hEditSnsValue2  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT61);
    hEditSnsValue3  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT62);
    hEditSnsValue4  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT63);
    hEditSnsValue5  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT64);
    hCheckSnsEna1   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK51);
    hCheckSnsEna2   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK52);
    hCheckSnsEna3   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK53);
    hCheckSnsEna4   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK54);
    hCheckSnsEna5   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK55);
    hButUnlock4     = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON7);

    InitDialog4();
}

void TDUMultipageTankDetails::InitDialog4(void) {
    if (CurrentPROPtr != NULL) {
        /* Initialize all widgets */
        if (PinUnlock) {
            WM_EnableWindow(hCheckSnsEna1);
            WM_EnableWindow(hCheckSnsEna2);
            WM_EnableWindow(hCheckSnsEna3);
            WM_EnableWindow(hCheckSnsEna4);
            WM_EnableWindow(hCheckSnsEna5);
            WM_EnableWindow(hEditSnsGain1);
            WM_EnableWindow(hEditSnsOffset1);
            WM_EnableWindow(hEditSnsValue1);
            WM_EnableWindow(hEditSnsGain2);
            WM_EnableWindow(hEditSnsOffset2);
            WM_EnableWindow(hEditSnsValue2);
            WM_EnableWindow(hEditSnsGain3);
            WM_EnableWindow(hEditSnsOffset3);
            WM_EnableWindow(hEditSnsValue3);
            WM_EnableWindow(hEditSnsGain4);
            WM_EnableWindow(hEditSnsOffset4);
            WM_EnableWindow(hEditSnsValue4);
            WM_EnableWindow(hEditSnsGain5);
            WM_EnableWindow(hEditSnsOffset5);
            WM_EnableWindow(hEditSnsValue5);
        } else {
            WM_DisableWindow(hCheckSnsEna1);
            WM_DisableWindow(hCheckSnsEna2);
            WM_DisableWindow(hCheckSnsEna3);
            WM_DisableWindow(hCheckSnsEna4);
            WM_DisableWindow(hCheckSnsEna5);
            WM_DisableWindow(hEditSnsGain1);
            WM_DisableWindow(hEditSnsOffset1);
            WM_DisableWindow(hEditSnsValue1);
            WM_DisableWindow(hEditSnsGain2);
            WM_DisableWindow(hEditSnsOffset2);
            WM_DisableWindow(hEditSnsValue2);
            WM_DisableWindow(hEditSnsGain3);
            WM_DisableWindow(hEditSnsOffset3);
            WM_DisableWindow(hEditSnsValue3);
            WM_DisableWindow(hEditSnsGain4);
            WM_DisableWindow(hEditSnsOffset4);
            WM_DisableWindow(hEditSnsValue4);
            WM_DisableWindow(hEditSnsGain5);
            WM_DisableWindow(hEditSnsOffset5);
            WM_DisableWindow(hEditSnsValue5);
        }
        UpdateDialog4();
    }

}

void TDUMultipageTankDetails::UpdateDialog4(void) {
    if (CurrentPROPtr != NULL) {
        AnsiString str;
        AnsiString UnitStr;

        if (!CurrentPROPtr->AnalogInList.empty()) {
            if (CurrentPROPtr->AnalogInList[0]->Enable) {
                CHECKBOX_Check(hCheckSnsEna1);
            } else {
                CHECKBOX_Uncheck(hCheckSnsEna1);
            }
            str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[0], &UnitStr);
            TEXT_SetText(hTextSnsLoc1, str.c_str());
            str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[0], &UnitStr);
            EDIT_SetText(hEditSnsGain1, str.c_str());
            str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[0], &UnitStr);
            EDIT_SetText(hEditSnsOffset1, str.c_str());
            str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[0], &UnitStr);
            EDIT_SetText(hEditSnsValue1, str.c_str());
            TEXT_SetText(hTextSnsUnit1, UnitStr.c_str());

        } else {
            WM_DisableWindow(hCheckSnsEna1);
            WM_DisableWindow(hEditSnsGain1);
            WM_DisableWindow(hEditSnsOffset1);
            WM_DisableWindow(hEditSnsValue1);
        }
        if (CurrentPROPtr->AnalogInList.size() >= 2) {
            if (CurrentPROPtr->AnalogInList[1]->Enable) {
                CHECKBOX_Check(hCheckSnsEna2);
            } else {
                CHECKBOX_Uncheck(hCheckSnsEna2);
            }
            str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[1], &UnitStr);
            TEXT_SetText(hTextSnsLoc2, str.c_str());
            str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[1], &UnitStr);
            EDIT_SetText(hEditSnsGain2, str.c_str());
            str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[1], &UnitStr);
            EDIT_SetText(hEditSnsOffset2, str.c_str());
            str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[1], &UnitStr);
            EDIT_SetText(hEditSnsValue2, str.c_str());
            TEXT_SetText(hTextSnsUnit2, UnitStr.c_str());
        } else {
            WM_DisableWindow(hCheckSnsEna2);
            WM_DisableWindow(hEditSnsGain2);
            WM_DisableWindow(hEditSnsOffset2);
            WM_DisableWindow(hEditSnsValue2);
        }
        if (CurrentPROPtr->AnalogInList.size() >= 3) {
            if (CurrentPROPtr->AnalogInList[2]->Enable) {
                CHECKBOX_Check(hCheckSnsEna3);
            } else {
                CHECKBOX_Uncheck(hCheckSnsEna3);
            }
            str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[2], &UnitStr);
            TEXT_SetText(hTextSnsLoc3, str.c_str());
            str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[2], &UnitStr);
            EDIT_SetText(hEditSnsGain3, str.c_str());
            str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[2], &UnitStr);
            EDIT_SetText(hEditSnsOffset3, str.c_str());
            str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[2], &UnitStr);
            EDIT_SetText(hEditSnsValue3, str.c_str());
            TEXT_SetText(hTextSnsUnit3, UnitStr.c_str());
        } else {
            WM_DisableWindow(hCheckSnsEna3);
            WM_DisableWindow(hEditSnsGain3);
            WM_DisableWindow(hEditSnsOffset3);
            WM_DisableWindow(hEditSnsValue3);
        }
        if (CurrentPROPtr->AnalogInList.size() >= 4) {
            if (CurrentPROPtr->AnalogInList[3]->Enable) {
                CHECKBOX_Check(hCheckSnsEna4);
            } else {
                CHECKBOX_Uncheck(hCheckSnsEna4);
            }
            str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[3], &UnitStr);
            TEXT_SetText(hTextSnsLoc4, str.c_str());
            str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[3], &UnitStr);
            EDIT_SetText(hEditSnsGain4, str.c_str());
            str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[3], &UnitStr);
            EDIT_SetText(hEditSnsOffset4, str.c_str());
            str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[3], &UnitStr);
            EDIT_SetText(hEditSnsValue4, str.c_str());
            TEXT_SetText(hTextSnsUnit4, UnitStr.c_str());
        } else {
            WM_DisableWindow(hCheckSnsEna4);
            WM_DisableWindow(hEditSnsGain4);
            WM_DisableWindow(hEditSnsOffset4);
            WM_DisableWindow(hEditSnsValue4);
        }
        if (CurrentPROPtr->AnalogInList.size() >= 5) {
            if (CurrentPROPtr->AnalogInList[4]->Enable) {
                CHECKBOX_Check(hCheckSnsEna5);
            } else {
                CHECKBOX_Uncheck(hCheckSnsEna5);
            }
            str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[4], &UnitStr);
            TEXT_SetText(hTextSnsLoc5, str.c_str());
            str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[4], &UnitStr);
            EDIT_SetText(hEditSnsGain5, str.c_str());
            str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[4], &UnitStr);
            EDIT_SetText(hEditSnsOffset5, str.c_str());
            str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[4], &UnitStr);
            EDIT_SetText(hEditSnsValue5, str.c_str());
            TEXT_SetText(hTextSnsUnit5, UnitStr.c_str());
        } else {
            WM_DisableWindow(hCheckSnsEna5);
            WM_DisableWindow(hEditSnsGain5);
            WM_DisableWindow(hEditSnsOffset5);
            WM_DisableWindow(hEditSnsValue5);
        }
    }
    if (PinUnlock) {
        BUTTON_SetText(hButUnlock4, FindDictionaryWord(L_WORD1002).c_str());   // Lock
    } else {
        BUTTON_SetText(hButUnlock4, FindDictionaryWord(L_WORD123).c_str());   // Unlock
    }
}

void TDUMultipageTankDetails::SetNewValueDialog4(int key, AnsiString ValueString) {
    if (CurrentPROPtr != NULL) {
        switch (key) {
        case GUI_ID_CHECK51:
            if (CurrentPROPtr->AnalogInList.size() >= 1) LibPutValue(SVT_AI_ENABLE, CurrentPROPtr->AnalogInList[0], CHECKBOX_IsChecked(hCheckSnsEna1));
            break;
        case GUI_ID_CHECK52:
            if (CurrentPROPtr->AnalogInList.size() >= 2) LibPutValue(SVT_AI_ENABLE, CurrentPROPtr->AnalogInList[1], CHECKBOX_IsChecked(hCheckSnsEna2));
            break;
        case GUI_ID_CHECK53:
            if (CurrentPROPtr->AnalogInList.size() >= 3) LibPutValue(SVT_AI_ENABLE, CurrentPROPtr->AnalogInList[2], CHECKBOX_IsChecked(hCheckSnsEna3));
            break;
        case GUI_ID_CHECK54:
            if (CurrentPROPtr->AnalogInList.size() >= 4) LibPutValue(SVT_AI_ENABLE, CurrentPROPtr->AnalogInList[3], CHECKBOX_IsChecked(hCheckSnsEna4));
            break;
        case GUI_ID_CHECK55:
            if (CurrentPROPtr->AnalogInList.size() >= 5) LibPutValue(SVT_AI_ENABLE, CurrentPROPtr->AnalogInList[4], CHECKBOX_IsChecked(hCheckSnsEna5));
            break;
        case GUI_ID_EDIT50:
            if (CurrentPROPtr->AnalogInList.size() >= 1) LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[0], ValueString);
            break;
        case GUI_ID_EDIT51:
            if (CurrentPROPtr->AnalogInList.size() >= 2) LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[1], ValueString);
            break;
        case GUI_ID_EDIT52:
            if (CurrentPROPtr->AnalogInList.size() >= 3) LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[2], ValueString);
            break;
        case GUI_ID_EDIT53:
            if (CurrentPROPtr->AnalogInList.size() >= 4) LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[3], ValueString);
            break;
        case GUI_ID_EDIT54:
            if (CurrentPROPtr->AnalogInList.size() >= 5) LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[4], ValueString);
            break;
        case GUI_ID_EDIT55:
            if (CurrentPROPtr->AnalogInList.size() >= 1) LibPutValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[0], ValueString);
            break;
        case GUI_ID_EDIT56:
            if (CurrentPROPtr->AnalogInList.size() >= 2) LibPutValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[1], ValueString);
            break;
        case GUI_ID_EDIT57:
            if (CurrentPROPtr->AnalogInList.size() >= 3) LibPutValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[2], ValueString);
            break;
        case GUI_ID_EDIT58:
            if (CurrentPROPtr->AnalogInList.size() >= 4) LibPutValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[3], ValueString);
            break;
        case GUI_ID_EDIT59:
            if (CurrentPROPtr->AnalogInList.size() >= 5) LibPutValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[4], ValueString);
            break;
        case GUI_ID_EDIT60:
            if (CurrentPROPtr->AnalogInList.size() >= 1) LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[0], ValueString);
            break;
        case GUI_ID_EDIT61:
            if (CurrentPROPtr->AnalogInList.size() >= 2) LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[1], ValueString);
            break;
        case GUI_ID_EDIT62:
            if (CurrentPROPtr->AnalogInList.size() >= 3) LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr, ValueString);
            break;
        case GUI_ID_EDIT63:
            if (CurrentPROPtr->AnalogInList.size() >= 4) LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[3], ValueString);
            break;
        case GUI_ID_EDIT64:
            if (CurrentPROPtr->AnalogInList.size() >= 5) LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[4], ValueString);
            break;
        }
        UpdateDialog4();
    }
}


/*********************************************************************
*
* Dialog4 procedure
*/
void TDUMultipageTankDetails::GetDialog5Handles(void) {
    /* Get window handles for all widgets */
    hTextLevOffset      = WM_GetDialogItem(WinHandl, GUI_ID_TEXT70);
    hTextLevOffsetU     = WM_GetDialogItem(WinHandl, GUI_ID_TEXT71);
    hEditLevOffset      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT65);

    hTextTabOffset      = WM_GetDialogItem(WinHandl, GUI_ID_TEXT72);
    hTextTabOffsetU     = WM_GetDialogItem(WinHandl, GUI_ID_TEXT73);
    hEditTabOffset      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT66);

    hTextExpFactOffset  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT74);
    hTextExpFactOffsetU = WM_GetDialogItem(WinHandl, GUI_ID_TEXT75);
    hEditExpFactOffset  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT67);


    hButUnlock5     = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON10);

    InitDialog5();
}

void TDUMultipageTankDetails::InitDialog5(void) {
    if (CurrentPROPtr != NULL) {
        /* Initialize all widgets */
        if (PinUnlock) {
            WM_EnableWindow(hEditLevOffset);
            WM_EnableWindow(hEditTabOffset);
            WM_EnableWindow(hEditExpFactOffset);
        } else {
            WM_DisableWindow(hEditLevOffset);
            WM_DisableWindow(hEditTabOffset);
            WM_DisableWindow(hEditExpFactOffset);
        }
        UpdateDialog5();
    }

}

void TDUMultipageTankDetails::UpdateDialog5(void) {
    if (CurrentPROPtr != NULL) {
        AnsiString str;
        AnsiString UnitStr;
        str = LibGetValue(SVT_LEVEL_OFFSET, CurrentPROPtr, &UnitStr);
        EDIT_SetText(hEditLevOffset, str.c_str());
        TEXT_SetText(hTextLevOffsetU, UnitStr.c_str());
        str = LibGetValue(SVT_TABLE_OFFSET, CurrentPROPtr, &UnitStr);
        EDIT_SetText(hEditTabOffset, str.c_str());
        TEXT_SetText(hTextTabOffsetU, UnitStr.c_str());
        str = LibGetValue(SVT_VOLUME_CORRECTION, CurrentPROPtr, &UnitStr);
        EDIT_SetText(hEditExpFactOffset, str.c_str());
        TEXT_SetText(hTextExpFactOffsetU, UnitStr.c_str());
    }
    if (PinUnlock) {
        BUTTON_SetText(hButUnlock5, FindDictionaryWord(L_WORD1002).c_str());   // Lock
    } else {
        BUTTON_SetText(hButUnlock5, FindDictionaryWord(L_WORD123).c_str());   // Unlock
    }
}

void TDUMultipageTankDetails::SetNewValueDialog5(int key, AnsiString ValueString) {
    if (CurrentPROPtr != NULL) {
        switch (key) {
        case GUI_ID_EDIT65:
            LibPutValue(SVT_LEVEL_OFFSET        , CurrentPROPtr, ValueString);
            break;
        case GUI_ID_EDIT66:
            LibPutValue(SVT_TABLE_OFFSET        , CurrentPROPtr, ValueString);
            break;
        case GUI_ID_EDIT67:
            LibPutValue(SVT_VOLUME_CORRECTION   , CurrentPROPtr, ValueString);
            break;
        }
        UpdateDialog5();
    }
}
void TDUMultipageTankDetails::Update(void) {
    UpdateDialog1();
    UpdateDialog2();
    UpdateDialog3();
    UpdateDialog4();
    UpdateDialog5();
}

void TDUMultipageTankDetails::DisableLevelAdjustButtons(void) {
    for (int i = GUI_ID_BUTTON1; i <= GUI_ID_BUTTON6; i++) {
        WM_HWIN Butt = WM_GetDialogItem(WinHandl, i);
        WM_HideWin(Butt);
    }
}


void TDUMultipageTankDetails::EnableLevelAdjustButtons(void) {
    for (int i = GUI_ID_BUTTON1; i <= GUI_ID_BUTTON6; i++) {
        WM_HWIN Butt = WM_GetDialogItem(WinHandl, i);
        WM_ShowWin(Butt);
    }
}

void TDUMultipageTankDetails::DisableLevelMeasuredDnsCheckBox(void) {
    WM_HideWin(hCheckMeasDens); //GUI_ID_CHECK0
    WM_HideWin(hTextMeasDens);  //GUI_ID_TEXT3
}



/// Lock or unlock controls in all tabs (those that are PIN lock protected)
///
void TDUMultipageTankDetails::EnableOrDisableAllControls() {
    EnableOrDisableAlarmSettingsControls(PinUnlock, alarmSettingsLocked);
    InitDialog4();
    InitDialog5();
}


/// Lock or unlock the alarm settings tab
///
void TDUMultipageTankDetails::EnableOrDisableAlarmSettingsControls(bool notLocked, bool LockedByConfig) {
    // Set function pointer to enable or disable function which should be called
    void (*toggleFunction)(WM_HWIN);

    if (!notLocked && LockedByConfig) {
        toggleFunction = WM_DisableWindow;
    } else {
        toggleFunction = WM_EnableWindow;
    }

    toggleFunction(hButApplyAlarm);
    toggleFunction(hOverfill);
    toggleFunction(hHighLev);
    toggleFunction(hLowLev);
    toggleFunction(hHighTemp);
    toggleFunction(hLowTemp);
    toggleFunction(hHighPress);
    toggleFunction(hLowPress);
    toggleFunction(hEditOverfill);
    toggleFunction(hEditHighLev);
    toggleFunction(hEditLowLev);
    toggleFunction(hEditHighTemp);
    toggleFunction(hEditLowTemp);
    toggleFunction(hEditHighPress);
    toggleFunction(hEditLowPress);
    toggleFunction(hTextOverfill);
    toggleFunction(hTextHighLev);
    toggleFunction(hTextLowLev);
    toggleFunction(hTextHighTemp);
    toggleFunction(hTextLowTemp);
    toggleFunction(hTextHighPress);
    toggleFunction(hTextLowPress);
    toggleFunction(hCheckOverfill);
    toggleFunction(hCheckHighLev);
    toggleFunction(hCheckLowLev);
    toggleFunction(hCheckHighTemp);
    toggleFunction(hCheckLowTemp);
    toggleFunction(hCheckHighPress);
    toggleFunction(hCheckLowPress);
}



