#include "TDUIncludes.h"

const GUI_POINT ShipLine[] = {
    {   0,   0},
    { 220,   0},
    { 275,  52},
    { 220, 104},
    {   0, 104},
    {   0,   0},
};
/*
const GUI_POINT BargeLine[] = {
    {   0,   0},
    { 220,   0},
    { 275,  52},
    { 220, 104},
    {   0, 104},
    {   0,   0},
};
*/
const GUI_POINT DraftLine[] = {
    {   0,   0},
    {  62,   0},
    {  62,  52},
    {  62,   0},
    { 134,   0},
    { 134,  52},
    {   0,  52},
    {   0,   0},
};

TDUSysWin2::~TDUSysWin2(void)
{
//       Initialize all widgets
    while ( DROPDOWN_GetNumItems(hDropAtmRef)>0 ) {
        DROPDOWN_DeleteItem(hDropAtmRef, 0);
    }
    while ( DROPDOWN_GetNumItems(hDropTrim)>0 ) {
        DROPDOWN_DeleteItem(hDropTrim, 0);
    }
    while ( DROPDOWN_GetNumItems(hDropList)>0 ) {
        DROPDOWN_DeleteItem(hDropList, 0);
    }
}

TDUSysWin2::TDUSysWin2(void)
{
}

const GUI_WIDGET_CREATE_INFO TDUSysWin2::aDialogCreate[] =
{
    { FRAMEWIN_CreateIndirect,"System page 2" , TDU_SYSTEM2_WIN ,   0,   0, 286, 198, FRAMEWIN_CF_MAXIMIZED, 0},
    { TEXT_CreateIndirect,"Atmospheric ref."  , GUI_ID_TEXT0    ,  10,   4,  80,  15, TEXT_CF_LEFT},
    { DROPDOWN_CreateIndirect,NULL            , GUI_ID_DROPDOWN1,  90,   4,  90,  30, 0, 3},
    { EDIT_CreateIndirect, NULL               , GUI_ID_EDIT1    , 190,   4,  50,  15, GUI_TA_RIGHT, 20},
    { TEXT_CreateIndirect, "meter"            , GUI_ID_TEXT1    , 242,   4,  50,  15, TEXT_CF_LEFT},

    { TEXT_CreateIndirect, "Trim     Source:" , GUI_ID_TEXT4    ,  10,  27,  80,  15, TEXT_CF_LEFT},
    { DROPDOWN_CreateIndirect,NULL            , GUI_ID_DROPDOWN2,  90,  27,  90,  45, 0, 3},
    { EDIT_CreateIndirect, NULL               , GUI_ID_EDIT2    , 190,  27,  50,  15, GUI_TA_RIGHT, 20},
    { TEXT_CreateIndirect, "degree"           , GUI_ID_TEXT2    , 242,  27,  50,  15, TEXT_CF_LEFT},

    { TEXT_CreateIndirect,"List      Source:" , GUI_ID_TEXT5    ,  10,  50,  80,  15, TEXT_CF_LEFT},
    { DROPDOWN_CreateIndirect,NULL            , GUI_ID_DROPDOWN3,  90,  50,  90,  45, 0, 3},
    { EDIT_CreateIndirect, NULL               , GUI_ID_EDIT3    , 190,  50,  50,  15, GUI_TA_RIGHT, 20},
    { TEXT_CreateIndirect, "degree"           , GUI_ID_TEXT3    , 242,  50,  50,  15, TEXT_CF_LEFT},

    { EDIT_CreateIndirect, "DA"               , GUI_ID_EDIT11   ,   8, 119,  50,  15, GUI_TA_RIGHT, 20},
    { EDIT_CreateIndirect, "DP"               , GUI_ID_EDIT12   ,  95,  78,  50,  15, GUI_TA_RIGHT, 20},
    { EDIT_CreateIndirect, "DS"               , GUI_ID_EDIT13   ,  95, 160,  50,  15, GUI_TA_RIGHT, 20},
    { EDIT_CreateIndirect, "DF"               , GUI_ID_EDIT14   , 210, 119,  50,  15, GUI_TA_RIGHT, 20},

    { EDIT_CreateIndirect, "DFP"              , GUI_ID_EDIT15   , 170,  78,  50,  15, GUI_TA_RIGHT, 20},
    { EDIT_CreateIndirect, "DFS"              , GUI_ID_EDIT16   , 170, 160,  50,  15, GUI_TA_RIGHT, 20},
    { EDIT_CreateIndirect, "DAP"              , GUI_ID_EDIT17   ,  20,  78,  50,  15, GUI_TA_RIGHT, 20},
    { EDIT_CreateIndirect, "DAS"              , GUI_ID_EDIT18   ,  20, 160,  50,  15, GUI_TA_RIGHT, 20},

    { RADIO_CreateIndirect,      NULL         , GUI_ID_RADIO0   ,  70, 106,  60,  40, 0, 2},

    { TEXT_CreateIndirect, "Seawater"         , GUI_ID_TEXT12   , 138, 102,  50,  15, TEXT_CF_LEFT},
    { EDIT_CreateIndirect, "0.000"            , GUI_ID_EDIT20   , 136, 118,  50,  15, GUI_TA_RIGHT, 20},
    { TEXT_CreateIndirect, "Unit"             , GUI_ID_TEXT20   , 135, 134,  55,  15, TEXT_CF_LEFT},

};

unsigned TDUSysWin2::IdSet1[] ={
    GUI_ID_DROPDOWN1,
    GUI_ID_EDIT1    ,

    GUI_ID_DROPDOWN2,
    GUI_ID_EDIT2    ,
    GUI_ID_DROPDOWN3,
    GUI_ID_EDIT3    ,

    GUI_ID_EDIT20       ,

    GUI_ID_EDIT11       ,
    GUI_ID_EDIT12       ,
    GUI_ID_EDIT13       ,
    GUI_ID_EDIT14       ,

    GUI_ID_EDIT15       ,
    GUI_ID_EDIT16       ,
    GUI_ID_EDIT17       ,
    GUI_ID_EDIT18       ,

    GUI_ID_RADIO0       ,
    GUI_ID_EDIT20       ,
};

unsigned TDUSysWin2::IdSet2[] ={
    GUI_ID_TEXT4        ,
    GUI_ID_DROPDOWN2    ,

    GUI_ID_EDIT2        ,
    GUI_ID_TEXT2        ,
    GUI_ID_TEXT5        ,
    GUI_ID_EDIT3        ,

    GUI_ID_DROPDOWN3    ,

    GUI_ID_EDIT3        ,
    GUI_ID_TEXT3        ,
    GUI_ID_EDIT11       ,
    GUI_ID_EDIT12       ,
    GUI_ID_EDIT13       ,
    GUI_ID_EDIT14       ,
    GUI_ID_EDIT15       ,
    GUI_ID_EDIT16       ,
    GUI_ID_EDIT17       ,
    GUI_ID_EDIT18       ,

    GUI_ID_RADIO0       ,
    GUI_ID_TEXT12       ,
    GUI_ID_EDIT20       ,
    GUI_ID_TEXT20       ,
};



void TDUSysWin2::ExecDialogBox(WM_HWIN hCurrentWin)
{
    SystemWindow->Protect();
    if ( SystemWindow->SysWin2IsClosed ) {
        SystemWindow->SysWin2IsClosed = false;
        WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbSysWin,
                                       hCurrentWin, 0, 0);
        //   GUI_DrawPolyLine(ShipLine, GUI_COUNTOF(ShipLine), 10,10);
        SystemWindow->CurrentSysWin = TDU_SYSWIN2;
        WM_EnableMemdev(WinHandl);
        GetDialogHandles();
    } else {
        WM_BringToTop(WinHandl);
    }
    SystemWindow->UnProtect();
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSysWin2::GetDialogHandles(void)
{
    hEditAtm      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT1);
    hEditTrim     = WM_GetDialogItem(WinHandl, GUI_ID_EDIT2);
    hEditList     = WM_GetDialogItem(WinHandl, GUI_ID_EDIT3);
    hDropAtmRef   = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
    hDropTrim     = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2);
    hDropList     = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN3);
    hTextAtmUnit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT1);
    hTextTrimUnit = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
    hTextListUnit = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
    hEditDA       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT11);
    hEditDP       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT12);
    hEditDS       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT13);
    hEditDF       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT14);
    hEditDFP      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT15);
    hEditDFS      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT16);
    hEditDAP      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT17);
    hEditDAS      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT18);
    hRadioDraft   = WM_GetDialogItem(WinHandl, GUI_ID_RADIO0);
    hEditSeaWater = WM_GetDialogItem(WinHandl, GUI_ID_EDIT20);
    hTextSWUnit   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT20);
    InitSysWin();
}

void TDUSysWin2::InitDropDown(void)
{
    if ( PROAtmReference::PROAtmRefPtr && PROAtmReference::PROAtmRefPtr->AtmRefSensors[0] ) {
        int WordKey[]={L_WORD553,L_WORD190};
        AddToDropDownsList(GUI_ID_DROPDOWN1,WordKey,NELEMENTS(WordKey));
    } else {
        int WordKey[]={L_WORD190};
        AddToDropDownsList(GUI_ID_DROPDOWN1,WordKey,NELEMENTS(WordKey));
        WM_DisableWindow(hDropAtmRef);
    }
    switch (PROProjectInfo::ProjectType) {
    case 0:
    case 1:
        if ( PROInclinometer::PROInclinPtr && PRODraftSystem::PRODraftSysPtr ) {
            IncAvailable = 0;
            int WordKey[]={L_WORD551,L_WORD552,L_WORD190};
            AddToDropDownsList(GUI_ID_DROPDOWN2,WordKey,NELEMENTS(WordKey));
            AddToDropDownsList(GUI_ID_DROPDOWN3,WordKey,NELEMENTS(WordKey));
        } else if ( PROInclinometer::PROInclinPtr ) {
            IncAvailable = 1;
            int WordKey[]={L_WORD551,L_WORD190};
            AddToDropDownsList(GUI_ID_DROPDOWN2,WordKey,NELEMENTS(WordKey));
            AddToDropDownsList(GUI_ID_DROPDOWN3,WordKey,NELEMENTS(WordKey));
        } else if ( PRODraftSystem::PRODraftSysPtr ) {
            IncAvailable = 2;
            int WordKey[]={L_WORD552,L_WORD190};
            AddToDropDownsList(GUI_ID_DROPDOWN2,WordKey,NELEMENTS(WordKey));
            AddToDropDownsList(GUI_ID_DROPDOWN3,WordKey,NELEMENTS(WordKey));
        } else {
            IncAvailable = 3;
            int WordKey[]={L_WORD190};
            AddToDropDownsList(GUI_ID_DROPDOWN2,WordKey,NELEMENTS(WordKey));
            AddToDropDownsList(GUI_ID_DROPDOWN3,WordKey,NELEMENTS(WordKey));
            DROPDOWN_SetSel(hDropTrim,0);
            DROPDOWN_SetSel(hDropList,0);
            WM_DisableWindow(hDropTrim);
            WM_DisableWindow(hDropList);
        }
        break;
    case 2:
        for (int i=0; i < NELEMENTS(IdSet2); i++) {
            Hide(IdSet2[i]);
        }
        break;
    }

}
void TDUSysWin2::InitSysWin(void)
{
    InitDropDown();
    if ( !PRODraftSystem::PRODraftSysPtr ) {
        WM_HideWin(hEditDF);
        WM_HideWin(hEditDP);
        WM_HideWin(hEditDS);
        WM_HideWin(hEditDA);

        WM_HideWin(hEditDFP);
        WM_HideWin(hEditDFS);
        WM_HideWin(hEditDAP);
        WM_HideWin(hEditDAS);
        WM_HideWin(hRadioDraft);
    }else{
        switch (PRODraftSystem::PRODraftSysPtr->DraftSystem) {
        case PRODraftSystem::DftFwdMidShipAftPS:
        case PRODraftSystem::DftCorners:
            break;
        default:
            WM_HideWin(hEditDFP);
            WM_HideWin(hEditDFS);
            WM_HideWin(hEditDAP);
            WM_HideWin(hEditDAS);
            break;

        }
    }
    {
        const GUIKey Words[] ={
            {TDU_SYSTEM2_WIN    ,0,L_WORD30},
            {GUI_ID_TEXT0       ,0,L_WORD31},
            {GUI_ID_TEXT1       ,0,L_WORD32},
            {GUI_ID_TEXT2       ,0,L_WORD34},
            {GUI_ID_TEXT4       ,0,L_WORD33},
            {GUI_ID_TEXT5       ,0,L_WORD38},
            {GUI_ID_TEXT3       ,0,L_WORD34},
            {GUI_ID_TEXT12      ,0,L_WORD37},
            {GUI_ID_TEXT20      ,0,L_WORD36},
            {GUI_ID_RADIO0      ,0,L_WORD491},
            {GUI_ID_RADIO0      ,1,L_WORD492},
        };
        AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
    }
    ClearRWList();
    AddToRWList(IdSet1,NELEMENTS(IdSet1),PROProjectInfo::PROProjectInfoPtr);
    UpdateReadOnly();
}

void TDUSysWin2::UpdateSysWin(void)
{
    AnsiString str,unitstr;
//Atm.
    if ( PROAtmReference::PROAtmRefPtr ) {
        //str =  LibGetValue(SVT_ATM_P_ENABLE, PROAtmReference::PROAtmRefPtr);
        if ( PROAtmReference::PROAtmRefPtr->UseManual ) {
            DROPDOWN_SetSel(hDropAtmRef,1);
            WM_EnableWindow(hEditAtm);
        } else {
            DROPDOWN_SetSel(hDropAtmRef,0);
            WM_DisableWindow(hEditAtm);
        }
        str = LibGetValue(SVT_ATM_PRESSURE, PROAtmReference::PROAtmRefPtr,&unitstr);
        EDIT_SetText(hEditAtm,str.c_str());
        TEXT_SetText(hTextAtmUnit, unitstr.c_str());
    } else {
        str = FindDictionaryWord(L_WORD181).c_str();    // No value
        EDIT_SetText(hEditAtm,str.c_str());
        TEXT_SetText(hTextAtmUnit, unitstr.c_str());
    }
// Trim / List
    if ( PROSystemData::TXUSystemData ) {
        WM_DisableWindow(hEditTrim);
        WM_DisableWindow(hEditList);
        switch ( IncAvailable ) {
        case 0:
            switch ( PROSystemData::TXUSystemData->TrimSource ) {
            case C_SD_MAN_SOURCE  :
                DROPDOWN_SetSel(hDropTrim,2);
                WM_EnableWindow(hEditTrim);
                break;
            case C_SD_DRAFT_SOURCE:
                DROPDOWN_SetSel(hDropTrim,1);
                break;
            case C_SD_INC_SOURCE  :
                DROPDOWN_SetSel(hDropTrim,0);
                break;
            }
            switch ( PROSystemData::TXUSystemData->ListSource ) {
            case C_SD_MAN_SOURCE  :
                DROPDOWN_SetSel(hDropList,2);
                WM_EnableWindow(hEditList);
                break;
            case C_SD_DRAFT_SOURCE:
                DROPDOWN_SetSel(hDropList,1);
                break;
            case C_SD_INC_SOURCE  :
                DROPDOWN_SetSel(hDropList,0);
                break;
            }
            break;
        case 1:
            switch ( PROSystemData::TXUSystemData->TrimSource ) {
            case C_SD_MAN_SOURCE  :
                DROPDOWN_SetSel(hDropTrim,1);
                WM_EnableWindow(hEditTrim);
                break;
            case C_SD_INC_SOURCE  :
                DROPDOWN_SetSel(hDropTrim,0);
                break;
            }
            switch ( PROSystemData::TXUSystemData->ListSource ) {
            case C_SD_MAN_SOURCE  :
                DROPDOWN_SetSel(hDropList,1);
                WM_EnableWindow(hEditList);
                break;
            case C_SD_INC_SOURCE  :
                DROPDOWN_SetSel(hDropList,0);
                break;
            }
            break;
        case 2:
            switch ( PROSystemData::TXUSystemData->TrimSource ) {
            case C_SD_MAN_SOURCE  :
                DROPDOWN_SetSel(hDropTrim,1);
                WM_EnableWindow(hEditTrim);
                break;
            case C_SD_DRAFT_SOURCE:
                DROPDOWN_SetSel(hDropTrim,0);
                break;
            }
            switch ( PROSystemData::TXUSystemData->ListSource ) {
            case C_SD_MAN_SOURCE  :
                DROPDOWN_SetSel(hDropList,1);
                WM_EnableWindow(hEditList);
                break;
            case C_SD_DRAFT_SOURCE:
                DROPDOWN_SetSel(hDropList,0);
                break;
            }
            break;
        }
        str = LibGetValue( SVT_TRIM_M_NOSIGN, PROSystemData::TXUSystemData,&unitstr);
        EDIT_SetText(hEditTrim,str.c_str());
        TEXT_SetText(hTextTrimUnit,unitstr.c_str());
        str = LibGetValue(SVT_LIST_ANGLE_NOSIGN, PROSystemData::TXUSystemData,&unitstr);
        EDIT_SetText(hEditList,str.c_str());
        TEXT_SetText(hTextListUnit,unitstr.c_str());
    } else {
        str = FindDictionaryWord(L_WORD181).c_str();    // No value
        EDIT_SetText(hEditTrim,str.c_str());
        EDIT_SetText(hEditList,str.c_str());
    }
//Draft system
    if ( PRODraftSystem::PRODraftSysPtr ) {
        if ( PRODraftSystem::PRODraftSysPtr->DraftIndicationAtPP ) {
            RADIO_SetValue(hRadioDraft,0);
        } else {
            RADIO_SetValue(hRadioDraft,1);
        }

        switch (PRODraftSystem::PRODraftSysPtr->DraftSystem) {
        case PRODraftSystem::DftFwdMidShipAftPS:
        case PRODraftSystem::DftCorners:
            str = LibGetValue( SVT_DFP, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDFP,str.c_str());
            str = LibGetValue( SVT_DFS, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDFS,str.c_str());
            str = LibGetValue( SVT_DAP, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDAP,str.c_str());
            str = LibGetValue( SVT_DAS, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDAS,str.c_str());
            str = LibGetValue( SVT_DS, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDS,str.c_str());
            str = LibGetValue( SVT_DP, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDP,str.c_str());
        default:
            str = LibGetValue( SVT_DA, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDA,str.c_str());
            str = LibGetValue( SVT_DF, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDF,str.c_str());
            str = LibGetValue( SVT_DS, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDS,str.c_str());
            str = LibGetValue( SVT_DP, PRODraftSystem::PRODraftSysPtr,&unitstr);
            EDIT_SetText(hEditDP,str.c_str());
            break;

        }
    } else {
        str = FindDictionaryWord(L_WORD182).c_str();    // No sensors
    }
//Sea water density
    if ( PROSystemData::TXUSystemData ) {
        str = LibGetValue( SVT_SEAWATER_DNS, PROSystemData::TXUSystemData,&unitstr);
        EDIT_SetText(hEditSeaWater,str.c_str());
        TEXT_SetText(hTextSWUnit,unitstr.c_str());
    }
}

void TDUSysWin2::SetTrimSource(int Index)
{
    int Source = C_SD_MAN_SOURCE;
    if ( PROInclinometer::PROInclinPtr && PRODraftSystem::PRODraftSysPtr ) {
        switch ( Index ) {
        case 0:
            Source = C_SD_INC_SOURCE;
            break;
        case 1:
            Source = C_SD_DRAFT_SOURCE;
            break;
        case 2:
            Source = C_SD_MAN_SOURCE;
            break;
        }
    } else if ( PROInclinometer::PROInclinPtr ) {
        switch ( Index ) {
        case 0:
            Source = C_SD_INC_SOURCE;
            break;
        case 1:
            Source = C_SD_MAN_SOURCE;
            break;
        }
    } else if ( PRODraftSystem::PRODraftSysPtr ) {
        switch ( Index ) {
        case 0:
            Source = C_SD_DRAFT_SOURCE;
            break;
        case 1:
            Source = C_SD_MAN_SOURCE;
            break;
        }
    } else {
        Source = C_SD_MAN_SOURCE;
    }
    LibPutValue(SVT_TRIM_SOURCE,PROSystemData::TXUSystemData,Source);
}

void TDUSysWin2::SetListSource(int Index)
{
    int Source = C_SD_MAN_SOURCE;
    if ( PROInclinometer::PROInclinPtr && PRODraftSystem::PRODraftSysPtr ) {
        switch ( Index ) {
        case 0:
            Source = C_SD_INC_SOURCE;
            break;
        case 1:
            Source = C_SD_DRAFT_SOURCE;
            break;
        case 2:
            Source = C_SD_MAN_SOURCE;
            break;
        }
    } else if ( PROInclinometer::PROInclinPtr ) {
        switch ( Index ) {
        case 0:
            Source = C_SD_INC_SOURCE;
            break;
        case 1:
            Source = C_SD_MAN_SOURCE;
            break;
        }
    } else if ( PRODraftSystem::PRODraftSysPtr ) {
        switch ( Index ) {
        case 0:
            Source = C_SD_DRAFT_SOURCE;
            break;
        case 1:
            Source = C_SD_MAN_SOURCE;
            break;
        }
    } else {
        Source = C_SD_MAN_SOURCE;
    }
    LibPutValue(SVT_LIST_SOURCE,PROSystemData::TXUSystemData,Source);
}

void TDUSysWin2::UpdateSystem(WM_HWIN hWin,int Key)
{
    WM_HWIN hDropDown;
    hDropDown = WM_GetDialogItem(hWin, Key);
    switch ( Key ) {
    case GUI_ID_DROPDOWN1:
        {
            if ( PROAtmReference::PROAtmRefPtr ) {
                if ( DROPDOWN_GetSel(hDropDown)==0 ) {
                    LibPutValue(SVT_ATM_P_ENABLE, PROAtmReference::PROAtmRefPtr,"1");
                } else {
                    LibPutValue(SVT_ATM_P_ENABLE, PROAtmReference::PROAtmRefPtr,"0");
                }
            } else {
            }
        }
        break;
    case GUI_ID_DROPDOWN2:
        SetTrimSource(DROPDOWN_GetSel(hDropDown));
        break;
    case GUI_ID_DROPDOWN3:
        SetListSource(DROPDOWN_GetSel(hDropDown));
        break;
    }
    UpdateSysWin();
}

void TDUSysWin2::cbSysWin(WM_MESSAGE *pMsg)
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch ( pMsg->MsgId ) {
    case WM_DELETE:
        SystemWindow->SysWin2IsClosed = true;
        break;
    case WM_PAINT:
        switch (PROProjectInfo::ProjectType) {
        case 0:
        case 1:
            {
                GUI_DrawPolyLine(ShipLine, GUI_COUNTOF(ShipLine), 2, 74);
                int CurColor = GUI_GetColor();
                GUI_SetColor(GUI_DARKGRAY);
                GUI_DrawPolyLine(DraftLine, GUI_COUNTOF(DraftLine), 66, 100);
                GUI_SetColor(CurColor);
                SystemWindow->SysWin2->UpdateLanguage();
            }
            break;
        case 2:
            break;
        }
        break;
    case MESSAGE_LANGUAGE_CHANGE:
        SystemWindow->SysWin2->UpdateLanguage();
        break;
    case WM_INIT_DIALOG:
        SystemWindow->SysWin2->FirstTime = true;
        break;
    case WM_KEY:
        switch ( ((WM_KEY_INFO*)(pMsg->Data.p))->Key ) {
        case GUI_KEY_ESCAPE:
            GUI_EndDialog(hWin, 1);
            break;
        case GUI_KEY_ENTER:
            GUI_EndDialog(hWin, 0);
            break;
        }
        break;
    case MESSAGE_PINCODE_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE]={""};
            strcpy( StringBuf,(char *)pMsg->Data.p);
            switch ( ValueId ) {
            case GUI_ID_EDIT11:
            case GUI_ID_EDIT12:
            case GUI_ID_EDIT13:
            case GUI_ID_EDIT14:
            case GUI_ID_EDIT15:
            case GUI_ID_EDIT16:
            case GUI_ID_EDIT17:
            case GUI_ID_EDIT18:
            case GUI_ID_EDIT20:
                if ( CheckPinCode(StringBuf) ) {
                    KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD180, ValueId); // Enter new value:
                }
                break;
            }
        }
        break;
    case MESSAGE_KEYPAD_RETURN:
        {
            int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE]={""};
            strcpy( StringBuf,(char *)pMsg->Data.p);
            switch ( ValueId ) {
            case GUI_ID_EDIT1 :
                LibPutValue(SVT_ATM_PRESSURE, PROAtmReference::PROAtmRefPtr, StringBuf);
                break;
            case GUI_ID_EDIT2 :
                LibPutValue(SVT_TRIM_M,PROSystemData::TXUSystemData,StringBuf);
                break;
            case GUI_ID_EDIT3 :
                LibPutValue(SVT_LIST_ANGLE,PROSystemData::TXUSystemData,StringBuf);
                break;
            case GUI_ID_EDIT11:
            case GUI_ID_EDIT12:
            case GUI_ID_EDIT13:
            case GUI_ID_EDIT14:
            case GUI_ID_EDIT15:
            case GUI_ID_EDIT16:
            case GUI_ID_EDIT17:
            case GUI_ID_EDIT18:
                {
                    int ValKey;
                    switch(ValueId){
                    case GUI_ID_EDIT11:ValKey = SVT_DA ;break;
                    case GUI_ID_EDIT12:ValKey = SVT_DP ;break;
                    case GUI_ID_EDIT13:ValKey = SVT_DS ;break;
                    case GUI_ID_EDIT14:ValKey = SVT_DF ;break;
                    case GUI_ID_EDIT15:ValKey = SVT_DFP;break;
                    case GUI_ID_EDIT16:ValKey = SVT_DFS;break;
                    case GUI_ID_EDIT17:ValKey = SVT_DAP;break;
                    case GUI_ID_EDIT18:ValKey = SVT_DAS;break;
                    }
                    LibPutValue(ValKey,PRODraftSystem::PRODraftSysPtr,StringBuf);
                }
                break;
            case GUI_ID_EDIT20:
                LibPutValue(SVT_SEAWATER_DNS,PROSystemData::TXUSystemData,StringBuf);
                break;
            }
        }
        break;
    case WM_TOUCH_CHILD:
        {
            GUI_PID_STATE State;
            /* Wait until touch is pressed */
            GUI_TOUCH_GetState(&State);
            if ( State.Pressed == 1 ) {
                Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
                NCode = pMsg->Data.v;                               /* Notification code */
                switch ( Id ) {
                case GUI_ID_EDIT1 :
                    KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD180,Id);   // Enter new value:
                    break;
                case GUI_ID_EDIT2 :
                    KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD183,Id);   // Enter trim. (Aft is -):
                    break;
                case GUI_ID_EDIT3 :
                    KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD184,Id);   // Enter list. (Port is -)
                    break;
                case GUI_ID_EDIT11:
                case GUI_ID_EDIT12:
                case GUI_ID_EDIT13:
                case GUI_ID_EDIT14:
                case GUI_ID_EDIT15:
                case GUI_ID_EDIT16:
                case GUI_ID_EDIT17:
                case GUI_ID_EDIT18:
                    if ( PinUnlock ) {
                        KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD180,Id);   // Enter new value:
                    } else {
                        KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hWin),L_WORD150,Id);   // Enter Pin code:
                    }
                    break;
                case GUI_ID_EDIT20:
                    KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD185,Id);   // Enter new density:
                    break;
                }
            }
        }
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
        NCode = pMsg->Data.v;                               /* Notification code */
        switch ( NCode ) {
        case WM_NOTIFICATION_RELEASED:      /* React only if released */
            switch ( Id ) {
            case GUI_ID_RADIO0:
                {
                    AnsiString NewLoc;
                    if ( RADIO_GetValue(SystemWindow->SysWin2->hRadioDraft) ) {
                        NewLoc = "0";
                        PRODraftSystem::PRODraftSysPtr->DraftIndicationAtPP = false;
                    } else {
                        NewLoc = "1";
                        PRODraftSystem::PRODraftSysPtr->DraftIndicationAtPP = true;
                    }
                    LibPutValue(SVT_DRAFT_POINT,PRODraftSystem::PRODraftSysPtr,NewLoc);
                }
                break;
            case GUI_ID_CLOSE:
                /* Close Button */
                SystemWindow->Protect();
                    if ( !SystemWindow->SysWin2IsClosed ) {
                        GUI_EndDialog(hWin, 0);
                    }
					SystemWindow->UnProtect();
                break;
            }
            break;
        case WM_NOTIFICATION_SEL_CHANGED:
            switch ( Id ) {
            case GUI_ID_DROPDOWN1: /* Atm. Enable  */
            case GUI_ID_DROPDOWN2: /* Trim  */
            case GUI_ID_DROPDOWN3: /* List  */
                SystemWindow->SysWin2->UpdateSystem(hWin,Id);
                break;
            }
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}
