#include "TDUIncludes.h"

static void cbWin1(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    switch ( pMsg->MsgId ) {
    case WM_NOTIFY_PARENT:
        {
            int NCode, Id;
            Id    = WM_GetId(pMsg->hWinSrc);        /* Id of widget */
            NCode = pMsg->Data.v;                               /* Notification code */
            switch ( NCode ) {
            case WM_NOTIFICATION_RELEASED:
                {
                    WaterIngrWindow->UnitClicked(hWin,Id);
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

static void cbWin0(WM_MESSAGE * pMsg)
{
    //WM_HWIN hWin = pMsg->hWin;
    switch ( pMsg->MsgId ) {
    case WM_PAINT:
//			GUI_SetBkColor(GUI_RED);
        GUI_SetBkColor(TDU_C_PW_BACK);
        GUI_Clear();
        break;
    case WM_CREATE:
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

const int TDUWaterIngressWin::Col0 =  0;    //Status
const int TDUWaterIngressWin::Col1 = 14;    //Name
const int TDUWaterIngressWin::Col2 = 88;    //Main
const int TDUWaterIngressWin::Col3 =130;    //Pre
const int TDUWaterIngressWin::Col4 =172;    //Over
const int TDUWaterIngressWin::Col5 =208;    //Prot
const int TDUWaterIngressWin::Col6 =244;    //Temp

const int TDUWaterIngressWin::NumUnitsOnPage = 9;

TDUWaterIngressWin::~TDUWaterIngressWin(void)
{
}

TDUWaterIngressWin::TDUWaterIngressWin(void)
{
    MainWinHandl= 0;
    ScrollHandl = 0;
    HeaderHandl = 0;
    for ( int i=0; i < MAX_ENTRIES_ON_WI; i++ ) {
        UnitHandl[  i] = 0;
        MainButton[ i] = 0;
        PreButton[  i] = 0;
        ProtChBox[  i] = 0;
        OverChBox[  i] = 0;
        TempText[   i] = 0;
        NameText[   i] = 0;
        StatusText[ i] = 0;
        EnableText[ i] = 0;
    }

    AddToSKeyList(TDU_WATERINGR_WIN  ,0,L_WORD94);
    CurrentWIPtr = NULL;
    LineHeight = 20;
    StartX = 0;
    StartY = (LineHeight-2);
    CurrentPage = 0;
    PageSize = NumUnitsOnPage*LineHeight;
    if ( !PROWaterIngress::ObjVector.empty() ) {
        NumberOfUnits = PROWaterIngress::ObjVector.size();
        PageCount = NumberOfUnits/NumUnitsOnPage;
        NumberOfUnitsLastPage = NumberOfUnits - PageCount*NumUnitsOnPage;
        if ( NumberOfUnitsLastPage ) PageCount++;
        int YSize = (((NumberOfUnits+2))*(LineHeight-1)+StartY);
        if ( YSize<200 ) YSize=200;

        MainWinHandl  = WM_CreateWindowAsChild( StartX, StartY, PWinXSize, YSize,  WinHandl, WM_CF_SHOW, cbWin0, 0);
        WM_SetId(MainWinHandl,TDU_WATERINGR_WIN);
        //	ScrollHandl   = SCROLLBAR_Create(PWinXSize-19, 0, 18, PWinYSize,WinHandl, 999, WM_CF_SHOW, SCROLLBAR_CF_VERTICAL);
        {
            HeaderInfo Header[]={
                { L_WORD468 ,Col1-Col0  ,GUI_TA_BOTTOM | GUI_TA_HCENTER},
                { L_WORD74  ,Col2-Col1  ,GUI_TA_BOTTOM | GUI_TA_HCENTER},
                { L_WORD475 ,Col3-Col2  ,GUI_TA_BOTTOM | GUI_TA_HCENTER},
                { L_WORD476 ,Col4-Col3  ,GUI_TA_BOTTOM | GUI_TA_HCENTER},
                { L_WORD477 ,Col5-Col4  ,GUI_TA_BOTTOM | GUI_TA_HCENTER},
                { L_WORD478 ,Col6-Col5  ,GUI_TA_BOTTOM | GUI_TA_HCENTER},
                { L_WORD338 ,Col6-Col5+5,GUI_TA_BOTTOM | GUI_TA_HCENTER},
            } ;

            HeaderHandl = HEADER_Create(Col0, 0, PWinXSize, (LineHeight-2), WinHandl, GUI_ID_HEADER0, WM_CF_SHOW, 0);

            for ( int i=0; i< NELEMENTS(Header); i++ ) {
                AddToSKeyList(GUI_ID_HEADER0,i,Header[i].WordKey);
                HEADER_AddItem(HeaderHandl, Header[i].Width, FindDictionaryWord(Header[i].WordKey).c_str(), Header[i].Align);   // S
            }
        }
        //	SCROLLBAR_SetNumItems(ScrollHandl,(NumberOfUnits+1));
        //	SCROLLBAR_SetPageSize(ScrollHandl,NumUnitsOnPage);
        //


        for ( int index=0; index<(NumUnitsOnPage*PageCount); index++ ) { //AStmark possible fault when more pages
            int IdKey = index+GUI_ID_USER;
            if ( index < NumberOfUnits ) {
                PROWaterIngress *TElement = (PROWaterIngress*)PROWaterIngress::ObjVector[index];
                AnsiString tempName = LibGetValue(SVT_PRO_NAME, TElement);

                UnitHandl[index]  = WM_CreateWindowAsChild( Col0, index*LineHeight, PWinXSize, (LineHeight-1), MainWinHandl, WM_CF_SHOW, cbWin1, 0);

                StatusText[index] = TEXT_CreateAsChild(   Col0+2, 1,   Col1-Col0, (LineHeight-2), UnitHandl[index],IdKey+100, WM_CF_SHOW, "", TEXT_CF_LEFT);
                NameText[index]   = TEXT_CreateAsChild(   Col1+2, 1,   Col2-Col1, (LineHeight-2), UnitHandl[index],IdKey+200, WM_CF_SHOW, tempName.c_str(), TEXT_CF_LEFT);
                MainButton[index] = BUTTON_CreateAsChild( Col2+1, 1, Col3-Col2-2, (LineHeight-2), UnitHandl[index],IdKey+300, WM_CF_SHOW);
                PreButton[index]  = BUTTON_CreateAsChild( Col3+1, 1, Col4-Col3-2, (LineHeight-2), UnitHandl[index],IdKey+400, WM_CF_SHOW);
                OverChBox[index]  = CHECKBOX_Create(     Col4+10, 1,          17, (LineHeight-2), UnitHandl[index],IdKey+500, WM_CF_SHOW);
                // Add the widgets to the widget table
                WM_SetId(UnitHandl[index],IdKey+600);


                if ( TElement->DisableOverride ) {
                    WM_DisableWindow(OverChBox[index]);
                } else {
                }
                ProtChBox[index]  = CHECKBOX_Create(     Col5+10, 1,          17, (LineHeight-2), UnitHandl[index],400+index, WM_CF_SHOW);
                TempText[index]   = TEXT_CreateAsChild(     Col6, 1,   Col5-Col4, (LineHeight-2), UnitHandl[index],500+index, WM_CF_SHOW, "",TEXT_CF_RIGHT);

                TEXT_SetTextColor(NameText[index]  ,TDU_C_TEXT_DEFAULT); TEXT_SetFont(NameText[index]  ,&TDU_FONT_PW);
                TEXT_SetFont(StatusText[index]  ,&TDU_FONT_PW);
                BUTTON_SetFont(MainButton[index],&TDU_FONT_PW);BUTTON_SetBkColor(  MainButton[index], 0, TDU_C_AL_BACK_NOAL);
                BUTTON_SetText(MainButton[index],FindDictionaryWord(L_WORD475).c_str());      BUTTON_SetTextColor(MainButton[index], 0, TDU_C_AL_TEXT_NOAL);
                BUTTON_SetFont(PreButton[index], &TDU_FONT_PW);BUTTON_SetBkColor(  PreButton[index], 0, TDU_C_AL_BACK_NOAL);
                BUTTON_SetText(PreButton[index],FindDictionaryWord(L_WORD476).c_str());        BUTTON_SetTextColor(PreButton[index], 0, TDU_C_AL_TEXT_NOAL);
            } else {
                UnitHandl[index]  = WM_CreateWindowAsChild( Col0, index*LineHeight, PWinXSize, (LineHeight-1), MainWinHandl, WM_CF_SHOW, cbWin1, 0);
            }
        }
    }
}

void TDUWaterIngressWin::SetButton(void)
{
    bool Enable[NUMBER_OF_BUTTONS]={
        (bool)(PageCount>1),
        (bool)(PageCount>1),
        false,
        false,
        false
    };
    ButWindow->EnableButtons(Enable);

    ButWindow->ChangeButtonText(L_WORD87,L_WORD88,L_WORD237,L_WORD237,L_WORD237);
    Paintnew();
}

void TDUWaterIngressWin::PWTimer(void)
{
    if ( !PROWaterIngress::ObjVector.empty() ) {
        Paintnew();
        UpdateFields(true);
    }
}

void TDUWaterIngressWin::Paintnew(void)
{
    if ( !PROWaterIngress::ObjVector.empty() ) {
        int ListSize = PROWaterIngress::ObjVector.size();
        for ( int index=0; index<ListSize; index++ ) {
            PROWaterIngress *TElement = (PROWaterIngress*)PROWaterIngress::ObjVector[index];
            if ( TElement ) {
                AnsiString str;
                //str = LibGetValue(SVT_PRO_NAME, TElement);
                //TEXT_SetText(NameText[index],str.c_str());
                str = LibGetValue(SVT_PRO_STATUS, TElement);
                int color = TextColor;
                if ( (!str.compare("A")) || (!str.compare("E")) )   color = TDU_C_AL_BACK_ACTIVE;
                if ( !str.compare("W") ) color = TDU_C_AL_BACK_WARNING;
                TEXT_SetTextColor(StatusText[index]  ,color);
                TEXT_SetText(StatusText[index],str.c_str());
                str = LibGetValue(SVT_TEMP, TElement);
                TEXT_SetText(TempText[index],str.c_str());
                //main alarm
                if ( TElement->MainWaterIngrSensor ) {
                    switch ( TElement->MainWaterIngressPtr->State ) {
                    case AlarmBasic::AlActive:
                        // Let us blink
                        if ( BUTTON_GetBkColor(  MainButton[index], 0)!=TDU_C_AL_BACK_ACTIVE ) {
                            BUTTON_SetBkColor(  MainButton[index], 0, TDU_C_AL_BACK_ACTIVE);
                            BUTTON_SetTextColor(MainButton[index], 0, TDU_C_AL_TEXT_ACTIVE);
                        } else {
                            BUTTON_SetBkColor(  MainButton[index], 0, TDU_C_AL_TEXT_ACTIVE);
                            BUTTON_SetTextColor(MainButton[index], 0, TDU_C_AL_BACK_ACTIVE);
                        }
                        break;
                    case AlarmBasic::AlAknowledged:
                        if ( BUTTON_GetBkColor(  MainButton[index], 0)!=TDU_C_AL_BACK_ACTIVE ) {
                            BUTTON_SetBkColor(  MainButton[index], 0, TDU_C_AL_BACK_ACTIVE);
                            BUTTON_SetTextColor(MainButton[index], 0, TDU_C_AL_TEXT_ACTIVE);
                        }
                        break;
                    case AlarmBasic::AlIdle:
                    default:
                        if ( TElement->Override ) {
                            if ( BUTTON_GetBkColor(  MainButton[index], 0)!=TDU_C_AL_BACK_WARNING ) {
                                BUTTON_SetBkColor(  MainButton[index], 0, TDU_C_AL_BACK_WARNING);
                                BUTTON_SetTextColor(MainButton[index], 0, TDU_C_AL_TEXT_WARNING);
                            }
                        } else if ( BUTTON_GetBkColor(  MainButton[index], 0)!=TDU_C_AL_BACK_NOAL ) {
                            BUTTON_SetBkColor(  MainButton[index], 0, TDU_C_AL_BACK_NOAL);
                            BUTTON_SetTextColor(MainButton[index], 0, TDU_C_AL_TEXT_NOAL);
                        }
                        break;
                    }
                } else {
                    if ( BUTTON_GetBkColor(  MainButton[index], 0)!=TDU_C_BU_BACK ) {
                        WM_HideWindow(MainButton[index]);
                        BUTTON_SetBkColor(  MainButton[index],  0, TDU_C_BU_BACK);
                        BUTTON_SetTextColor(MainButton[index],  0, TDU_C_BU_TEXT);
                    }
                }
                //pre alarm
                if ( TElement->PreWaterIngrSensor ) {
                    switch ( TElement->PreWaterIngressPtr->State ) {
                    case AlarmBasic::AlActive:
                        // Let us blink
                        if ( BUTTON_GetBkColor(  PreButton[index], 0)!=TDU_C_AL_BACK_ACTIVE ) {
                            BUTTON_SetBkColor(  PreButton[index],  0, TDU_C_AL_BACK_ACTIVE);
                            BUTTON_SetTextColor(PreButton[index],  0, TDU_C_AL_TEXT_ACTIVE);
                        } else {
                            BUTTON_SetBkColor(  PreButton[index],  0, TDU_C_AL_TEXT_ACTIVE);
                            BUTTON_SetTextColor(PreButton[index],  0, TDU_C_AL_BACK_ACTIVE);
                        }
                        break;
                    case AlarmBasic::AlAknowledged:
                        if ( BUTTON_GetBkColor(  PreButton[index], 0)!=TDU_C_AL_BACK_ACTIVE ) {
                            BUTTON_SetBkColor(  PreButton[index],  0, TDU_C_AL_BACK_ACTIVE);
                            BUTTON_SetTextColor(PreButton[index],  0, TDU_C_AL_TEXT_ACTIVE);
                        }
                        break;
                    case AlarmBasic::AlIdle:
                    default:
                        if ( TElement->Override ) {
                            if ( BUTTON_GetBkColor(  PreButton[index], 0)!=TDU_C_AL_BACK_WARNING ) {
                                BUTTON_SetBkColor(  PreButton[index],  0, TDU_C_AL_BACK_WARNING);
                                BUTTON_SetTextColor(PreButton[index],  0, TDU_C_AL_TEXT_WARNING);
                            }
                        } else if ( BUTTON_GetBkColor(  PreButton[index], 0)!=TDU_C_AL_BACK_NOAL ) {
                            BUTTON_SetBkColor(  PreButton[index],  0, TDU_C_AL_BACK_NOAL);
                            BUTTON_SetTextColor(PreButton[index],  0, TDU_C_AL_TEXT_NOAL);
                        }
                        break;
                    }
                } else {
                    if ( BUTTON_GetBkColor(  PreButton[index], 0)!=TDU_C_BU_BACK ) {
                        WM_HideWindow(PreButton[index]);
                        BUTTON_SetBkColor(  PreButton[index],  0, TDU_C_BU_BACK);
                        BUTTON_SetTextColor(PreButton[index],  0, TDU_C_BU_TEXT);
                    }
                }
                if ( !TElement->DisableOverride ) {
                    if ( TElement->Override ) {
                        if ( !CHECKBOX_IsChecked(OverChBox[index]) )
                            CHECKBOX_Check(OverChBox[index]);
                    } else {
                        if ( CHECKBOX_IsChecked(OverChBox[index]) )
                            CHECKBOX_Uncheck(OverChBox[index]);
                    }
                }
                if ( TElement->HasProtection ) {
                    if ( !CHECKBOX_IsChecked(ProtChBox[index]) )
                        CHECKBOX_Check(ProtChBox[index]);
                } else {
                    if ( CHECKBOX_IsChecked(ProtChBox[index]) )
                        CHECKBOX_Uncheck(ProtChBox[index]);
                }
            }
        }
    }
}

void TDUWaterIngressWin::MoveWin(void)
{
    int extra = 0;
    int Y = 0;
    if ( ((CurrentPage+1)==PageCount) && NumberOfUnitsLastPage ) {
        extra = (NumUnitsOnPage-NumberOfUnitsLastPage)*LineHeight;
    }
    Y = -(CurrentPage*PageSize-extra)+StartY;
    // if(Y==0) Y=StartY;
//  WM_MoveWindow(MainWinHandl, StartX, Y);
    WM_MoveChildTo(MainWinHandl, StartX, Y);
}

void TDUWaterIngressWin::ButtonClicked(int ButtID)
{
    if ( !PROWaterIngress::ObjVector.empty() ) {
        switch ( ButtID ) {
        case TDU_BUTTON_ID_PW1:
            if ( CurrentPage<=0 ) {
                //	CurrentPage = PageCount-1;
                CurrentPage = 0;
            } else {
                CurrentPage--;
            }
            MoveWin();
            break;
        case TDU_BUTTON_ID_PW2:
            if ( CurrentPage >= (PageCount-1) ) {
//					CurrentPage = 0;
                CurrentPage = (PageCount-1);
            } else {
                CurrentPage++;
            }
            MoveWin();
            break;
        case TDU_BUTTON_ID_PW3:
            break;
        case TDU_BUTTON_ID_PW4:
            break;
        case TDU_BUTTON_ID_PW5:
            break;
        }
    }
}

void TDUWaterIngressWin::UnitClicked(WM_HWIN hWin,int ButtID)
{
//	for(int i=0,j=hWin; i<NumberOfUnits && j<(hWin+NumberOfUnits*10); i++,j+=10)
//		if(hWin+6 == MainButton[i])
    bool Found = false;
    int index = 0;
    for ( int i=0; !Found && (i<NumberOfUnits); i++ ) {
        if ( ButtID == WM_GetId(OverChBox[i]) ) {
            Found = true;
            index = i;
        } else if ( ButtID == WM_GetId(ProtChBox[i]) ) {
            Found = true;
            index = i;
        }
    }
    if ( Found ) {
        CurrentWIPtr = (PROWaterIngress*)PROWaterIngress::ObjVector[index];
        if ( ButtID == WM_GetId(OverChBox[index]) ) {
            if ( CHECKBOX_IsChecked(OverChBox[index]) ) {
                LibPutValue( SVT_WI_OVERRIDE,CurrentWIPtr,"1");
            } else {
                LibPutValue( SVT_WI_OVERRIDE,CurrentWIPtr,"0");
            }
        } else if ( ButtID == WM_GetId(ProtChBox[index]) ) {
            ProtPlate = (bool)CHECKBOX_IsChecked(ProtChBox[index]);
            int Text2;
            if ( ProtPlate ) {
                Text2 =L_WORD662;       //"The protection plate must be installed on the sensor.";
            } else {
                Text2 = L_WORD662; //"The protection plate must be removed from the sensor.";
            }
            ConfirmMessageBox->Exec(WM_GetClientWindow(WinHandl), L_WORD144, Text2, ButtID); //"Protection plate!",
        }
    }
}

void TDUWaterIngressWin::cbEventHandler(WM_MESSAGE * pMsg)
{
    //WM_HWIN hWin = pMsg->hWin;
    switch ( pMsg->MsgId ) {
    case MESSAGE_YES_RETURN:
        {
            //int ValueId = pMsg->hWinSrc;
            char StringBuf[BUF_SIZE]={""};
            strncpy( StringBuf,(char *)pMsg->Data.p,BUF_SIZE);
            LibPutValue( SVT_WI_PROTECTION,CurrentWIPtr,ProtPlate);
            WaterIngrWindow->Paintnew();
        }
        break;
    case WM_NOTIFY_PARENT:
        {
            int NCode;//, Id;
//			Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
            NCode = pMsg->Data.v;                               /* Notification code */
            switch ( NCode ) {
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
    case WM_INIT_DIALOG:
        WaterIngrWindow->FirstTime = true;
        break;
    case WM_PAINT:
        //if ( CurrentWinID == TDU_WATERINGR_WIN ) {
        //}
        WaterIngrWindow->UpdateLanguage();
        break;
    case WM_CREATE:
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

