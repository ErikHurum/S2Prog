#include "TDUIncludes.h"

#define SELECT_TIMEOUT  5000
TDUSysWin3::TDUSysWin3(void)
{
   CurrentIOUnit   = NULL;
   UserTouch       = false;
   TimerCount      = 0;
}

TDUSysWin3::~TDUSysWin3(void)
{
}

const GUI_WIDGET_CREATE_INFO TDUSysWin3::aDialogCreate[] =
{
   { FRAMEWIN_CreateIndirect, "System page 3: IO units", TDU_SYSTEM3_WIN, 0, 0, 286, 198, FRAMEWIN_CF_MAXIMIZED, 0 },
   { TEXT_CreateIndirect,     "Select:", GUI_ID_TEXT0,  2,   2,  46,  15, TEXT_CF_LEFT },
   { DROPDOWN_CreateIndirect, NULL,    GUI_ID_DROPDOWN0, 50,   0, 220, 100, 0, 3 },
   { LISTVIEW_CreateIndirect, NULL,    GUI_ID_LISTVIEW0,  0,  18, 281, 163, 0 },
};


void TDUSysWin3::SetListViewColor(void)
{
   LISTVIEW_SetBkColor(hListviewIO, 0, BackColor);
   LISTVIEW_SetBkColor(hListviewIO, 1, TextColor);
   LISTVIEW_SetBkColor(hListviewIO, 2, TextColor);
   LISTVIEW_SetTextColor(hListviewIO, 0, TextColor);
   LISTVIEW_SetTextColor(hListviewIO, 1, BackColor);
   LISTVIEW_SetTextColor(hListviewIO, 2, BackColor);
}

void TDUSysWin3::ExecDialogBox(WM_HWIN hCurrentWin)
{
   SystemWindow->Protect();
   if (SystemWindow->SysWin3IsClosed)
   {
      SystemWindow->SysWin3IsClosed = false;
      WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), &cbSysWin,
                                     hCurrentWin, 0, 0);
      SystemWindow->CurrentSysWin = TDU_SYSWIN3;
      WM_EnableMemdev(WinHandl);
      GetDialogHandles();
   }
   else
   {
      WM_BringToTop(WinHandl);
   }
   ButWindow->EnableButton(2, false);
   SystemWindow->UnProtect();
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSysWin3::GetDialogHandles(void)
{
   hDropdPRO     = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN0);
   DROPDOWN_SetAutoScroll(hDropdPRO, 1);
   hListviewIO   = WM_GetDialogItem(WinHandl, GUI_ID_LISTVIEW0);
   LISTVIEW_SetFont(hListviewIO, &TDU_FONT_ST);
   InitSysWin();
}

void TDUSysWin3::SetListviewRow(int Row, int Ch, AnsiString NameStr, AnsiString LocStr, AnsiString TypeStr, AnsiString RawValStr, AnsiString ValStr, AnsiString GainStr, AnsiString OffsetStr, AnsiString EnableStr, AnsiString UnitStr)
{
   //NumItems = LISTVIEW_GetNumRows(hObj);
   if (!(NameStr.IsEmpty() && LocStr.IsEmpty() && TypeStr.IsEmpty()))
   {
      AnsiString ChStr = (AnsiString)(Ch + 1);
      LISTVIEW_SetItemText(hListviewIO, 0, Row, ChStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 1, Row, NameStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 2, Row, LocStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 3, Row, TypeStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 4, Row, RawValStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 5, Row, ValStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 6, Row, GainStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 7, Row, OffsetStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 8, Row, UnitStr.c_str());
      LISTVIEW_SetItemText(hListviewIO, 9, Row, EnableStr.c_str());
   }
}

void TDUSysWin3::SetListviewRow2(int Row, AnsiString CalVal, AnsiString CnvCalErr, AnsiString PromStat, AnsiString PCStat, AnsiString UsePCSetUp, AnsiString ADSns, AnsiString PCSns, AnsiString UseFromPc)
{
   LISTVIEW_SetItemText(hListviewIO, 10, Row, CalVal.c_str());
   LISTVIEW_SetItemText(hListviewIO, 11, Row, CnvCalErr.c_str());
   LISTVIEW_SetItemText(hListviewIO, 12, Row, PromStat.c_str());
   LISTVIEW_SetItemText(hListviewIO, 13, Row, PCStat.c_str());
   LISTVIEW_SetItemText(hListviewIO, 14, Row, UsePCSetUp.c_str());
   LISTVIEW_SetItemText(hListviewIO, 15, Row, ADSns.c_str());
   LISTVIEW_SetItemText(hListviewIO, 16, Row, PCSns.c_str());
   LISTVIEW_SetItemText(hListviewIO, 17, Row, UseFromPc.c_str());
}


void TDUSysWin3::InitSysWin(void)
{
   CurrentIOUnit = NULL;
   if (PROProjectInfo::PROProjectInfoPtr)
   {
      while (DROPDOWN_GetNumItems(hDropdPRO) > 0)
      {
         DROPDOWN_DeleteItem(hDropdPRO, 0);
      }
      int Count = 0;
      int TotCount = 0;
      set<PRogramObject *>::iterator pBIt;
      for (pBIt = IOUnit::GlobalPRO_IOList.begin(); pBIt != IOUnit::GlobalPRO_IOList.end(); pBIt++)
      {
         PRogramObject *IOUnitElement = (*pBIt);
         if (IOUnitElement)
         {
            AnsiString DropdStr;
            switch (IOUnitElement->Type)
            {
            case C_SC_ADCARD:
            case C_SC_W_INGRESS:
               {
                  SignalConverter *ePtr = (SignalConverter *)IOUnitElement;
                  //int Size = ePtr->PROList->Size();
                  //PRONode *NodePtr = ePtr->PROList->getHead();
                  set<PRogramObject *>::iterator pBIt;
                  for (pBIt = ePtr->UniquePROList.begin(); pBIt != ePtr->UniquePROList.end(); pBIt++)
                  {
                     PRogramObject *Element = *pBIt;
                     if (Element && Element->ReadPermission())
                     {
                        DropdStr = Element->Name;
                        AnsiString MainObjType = LibGetValueName(MainObjectList, SizeofMainObjectList, Element->Type);
                        if (!MainObjType.IsEmpty())
                        {
                           MainObjType = (AnsiString)"(" + MainObjType + (AnsiString)")";
                        }
                        DropdStr += MainObjType + " on ZB485:" + (AnsiString)ePtr->IOAddress + " Ch." + (AnsiString)(ePtr->IOChannel + 1);
                        DropdStr += " (AD-SGCNV) ";
                        //SensorInfo[DROPDOWN_GetNumItems(hDropdPRO)] = DropdStr;
                        DROPDOWN_AddString(hDropdPRO, DropdStr.c_str());
                        DropdIOUnitList.push_back(ePtr);
                        Count++;
                     }
                  }
               }
               break;
            case C_IO_AN_ZBANA:
            case C_IO_AN_ZBHART:
               {
                  IOUnitZBAna *ePtr = (IOUnitZBAna *)IOUnitElement;
                  set<PRogramObject *>::iterator pBIt;
                  for (pBIt = ePtr->IOUniquePROSet.begin(); pBIt != ePtr->IOUniquePROSet.end(); pBIt++)
                  {
                     PRogramObject *Element = *pBIt;
                     if (Element && Element->ReadPermission())
                     {
                        AnsiString MainObjType = LibGetValueName(MainObjectList, SizeofMainObjectList, Element->Type);
                        if (!MainObjType.IsEmpty())
                        {
                           MainObjType = (AnsiString)"(" + MainObjType + (AnsiString)")";
                        }
                        DropdStr = Element->Name + MainObjType;
                        switch(IOUnitElement->Type) {
                        case C_IO_AN_ZBANA:
                            DropdStr += " on ZBANA:";
                            break;
                        case C_IO_AN_ZBHART:
                            DropdStr += " on ZBHART:";
                            break;
                        }
                        DropdStr += (AnsiString)ePtr->IOAddress;
                        //SensorInfo[DROPDOWN_GetNumItems(hDropdPRO)] = DropdStr;
                        DROPDOWN_AddString(hDropdPRO, DropdStr.c_str());
                        DropdIOUnitList.push_back(ePtr);
                        Count++;
                     }
                  }
               }
               break;
            case C_IO_AN_ZB485:
               //case C_IO_WAGO:
               //SensorInfo[DROPDOWN_GetNumItems(hDropdPRO)] = DropdStr;
               TotCount++;
               break;
            }
         }
      }
      TotCount += Count;
      DROPDOWN_SetSel(hDropdPRO, CurrentIndex);
      LISTVIEW_SetGridVis(hListviewIO, 1); //Sets the visibility
      LISTVIEW_SetLBorder(hListviewIO, 2);
      LISTVIEW_SetRBorder(hListviewIO, 1);
      HEADER_Handle ListHeadHandl = LISTVIEW_GetHeader(hListviewIO);

      WM_SetId(ListHeadHandl, GUI_ID_HEADER0);
      {
         HeaderInfo Header[] = {
            { L_WORD554, 18, GUI_TA_LEFT },   // ch
            { L_WORD74, 60, GUI_TA_LEFT },   // Name
            { L_WORD555, 25, GUI_TA_LEFT },   // Loc
            { L_WORD449, 50, GUI_TA_LEFT },   // Type
            { L_WORD556, 50, GUI_TA_RIGHT },  // RawVal
            { L_WORD128, 50, GUI_TA_RIGHT },  // Value
            { L_WORD126, 50, GUI_TA_RIGHT },  // Gain
            { L_WORD127, 50, GUI_TA_RIGHT },  // Offset
            { L_WORD36, 50, GUI_TA_LEFT },   // Unit
            { L_WORD1, 50, GUI_TA_LEFT },   // Enable
            { L_WORD557, 50, GUI_TA_LEFT },   // CalVal
            { L_WORD558, 50, GUI_TA_CENTER }, // CnvCalE
            { L_WORD559, 45, GUI_TA_CENTER }, // Prom
            { L_WORD560, 45, GUI_TA_CENTER }, // PC
            { L_WORD561, 50, GUI_TA_CENTER }, // UsPCCal
            { L_WORD562, 50, GUI_TA_CENTER }, // AD Sns
            { L_WORD563, 50, GUI_TA_CENTER }, // PC Sns
            { L_WORD564, 50, GUI_TA_CENTER }, // From PC
         };

         for (int i = 0; i < NELEMENTS(Header); i++)
         {
            AddToSKeyList(GUI_ID_HEADER0, i, Header[i].WordKey);
            LISTVIEW_AddColumn(hListviewIO, Header[i].Width, FindDictionaryWord(Header[i].WordKey).c_str(), Header[i].Align); // S
         }
      }
      for (int l = 0; l < MAX_AN_SGCNV_CHANNELS; l++)
      {
         LISTVIEW_AddRow(hListviewIO, NULL);
      }
      ClearList();
      WM_SetScrollbarH(hListviewIO, 1);
      WM_SetScrollbarV(hListviewIO, 1);
   }
   {
      const GUIKey Words[] = {
         { TDU_SYSTEM3_WIN, 0, L_WORD39 },
         { GUI_ID_TEXT0, 0, L_WORD40 },
      };
      AddToSKeyList((GUIKey *)Words, NELEMENTS(Words));
   }
}

void TDUSysWin3::ClearList(void)
{
   int NumberOfCols = LISTVIEW_GetNumColumns(hListviewIO);
   for (int Row = 0; Row < MAX_AN_SGCNV_CHANNELS; Row++)
   {
      for (int Col = 0; Col < NumberOfCols; Col++)
      {
         LISTVIEW_SetItemText(hListviewIO, Col, Row, "");
      }
   }
   UpdateSysWin();
}

bool TDUSysWin3::SetupWin(void)
{
   bool Found = false;

   int SnsSelect = LISTVIEW_GetSel(hListviewIO);
   AnsiString SnsInfo;
   PROIOComponent *SnsPtr = NULL;
   PRogramObject  *ProPtr  = NULL;

   if (CurrentIOUnit)
   {
      switch (CurrentIOUnit->Type)
      {
      case C_SC_ADCARD:
         {
            SCADCard *ePtr = (SCADCard *)CurrentIOUnit;
            if (SnsSelect < MAX_AN_SGCNV_CHANNELS)
            {
               // First locate the sensor
               for (int i = 0, Cnt = 0; !SnsPtr && i < MAX_AN_SGCNV_CHANNELS; i++)
               {
                  if (Cnt == SnsSelect)
                  {
                     SnsPtr = ePtr->IOComponent[i];
                  }
                  else if (ePtr->IOComponent[i])
                  {
                     Cnt++;
                  }
               }
               if (SnsPtr)
               {
                  ProPtr = ((AnalogInput *)SnsPtr)->PROPtr;
                  if (ProPtr)
                  {
                     SnsInfo = ProPtr->Name;
                  }
                  else
                  {
                     SnsInfo = "???";
                  }
                  SnsInfo += " on ZB485:" + (AnsiString)SnsPtr->IOAddress + " Ch." + (AnsiString)(SnsPtr->IOChannel + 1);
                  SnsInfo += " (AD-SGCNV) ";

               }

            }
         }
         break;
      case C_SC_W_INGRESS:
         {
            SCWaterIngress *ePtr = (SCWaterIngress *)CurrentIOUnit;
            if (SnsSelect < MAX_W_INGR_CHANNELS)
            {
               for (int i = 0, Cnt = 0; !SnsPtr && i < MAX_W_INGR_CHANNELS; i++)
               {
                  if (Cnt == SnsSelect)
                  {
                     SnsPtr = ePtr->IOComponent[i];
                  }
                  else if (ePtr->IOComponent[i])
                  {
                     Cnt++;
                  }
               }
               if (SnsPtr)
               {
                  ProPtr = ((AnalogInput *)SnsPtr)->PROPtr;
                  if (ProPtr)
                  {
                     SnsInfo = ProPtr->Name;
                  }
                  else
                  {
                     SnsInfo = "???";
                  }
                  SnsInfo += " on ZB485:" + (AnsiString)SnsPtr->IOAddress + " Ch." + (AnsiString)(SnsPtr->IOChannel + 1);
               }
            }
         }
         break;
      case C_IO_AN_ZBHART:
      case C_IO_AN_ZBANA :
         {
            IOUnitZBAna *ePtr = (IOUnitZBAna *)CurrentIOUnit;
            if (SnsSelect < MAX_AN_ZBANA_CHANNELS)
            {
               for (int i = 0, Cnt = 0; !SnsPtr && i < MAX_AN_ZBANA_CHANNELS; i++)
               {
                  if (Cnt == SnsSelect)
                  {
                     SnsPtr = ePtr->IOComponent[i];
                  }
                  else if (ePtr->IOComponent[i])
                  {
                     Cnt++;
                  }
               }
               if (SnsPtr)
               {
                  ProPtr = ((AnalogInput *)SnsPtr)->PROPtr;
                  if (ProPtr)
                  {
                     SnsInfo = ProPtr->Name;
                  }
                  else
                  {
                     SnsInfo = "???";
                  }
                  switch (CurrentIOUnit->Type) {
                  case C_IO_AN_ZBHART:
                      SnsInfo += " on ZBHART:";
                      break;
                  case C_IO_AN_ZBANA :
                      SnsInfo += " on ZBANA:";
                      break;
                  }
                  SnsInfo += (AnsiString)SnsPtr->IOAddress + " Ch." + (AnsiString)(SnsPtr->IOChannel + 1);
               }
            }
         }
         break;
      case C_IO_AN_ZB485:
         //case C_IO_WAGO:
         break;
      }
   }

   if (SnsPtr && CurrentIOUnit)
   {
      SensorDetails->CreatePage(WinHandl, ProPtr, SnsPtr, SnsInfo);
      Found = true;
   }
   TimedOut = false;
   TimerCount = SELECT_TIMEOUT;
   SetGuiEvent(PWEventHandl, 1, &aTCB[1]);
   return (Found);
}


void TDUSysWin3::UpdateSysWin(void)
{
   if (DROPDOWN_GetNumItems(hDropdPRO))
   {
      CurrentIOUnit = (PRogramObject *)DropdIOUnitList[CurrentIndex];
      if (CurrentIOUnit)
      {
         switch (CurrentIOUnit->Type)
         {
         case C_SC_ADCARD:
            {
               SCADCard *ePtr = (SCADCard *)CurrentIOUnit;
               int LCnt = 0;
               for (int index = 0; index < MAX_AN_SGCNV_CHANNELS; index++)
               {
                  AnsiString Name  = LibGetValue(SVT_IO_CH_NAME, index, ePtr);
                  if (!Name.IsEmpty())
                  {
                     AnsiString Loc   = LibGetValue(SVT_IO_CH_LOCATION, index, ePtr);
                     AnsiString Type  = LibGetValue(SVT_IO_CH_TYPE_TEXT, index, ePtr);
                     AnsiString RawVal = LibGetValue(SVT_IO_CH_RAW_VAL, index, ePtr);
                     AnsiString Value = LibGetValue(SVT_IO_CH_VALUE, index, ePtr);

                     AnsiString GainStr, OffsetStr, EnableStr, UnitStr;
                     PROIOComponent *SnsPtr = ePtr->IOComponent[index];
                     if (SnsPtr)
                     {
                        GainStr   = LibGetValue(SVT_AI_GAIN, index, SnsPtr);
                        OffsetStr = LibGetValue(SVT_AI_OFFSET, index, SnsPtr);
                        EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT, index, SnsPtr);
                        if (SnsPtr)
                        {
                           switch (SnsPtr->Type)
                           {
                           case C_AI_Pt100     :
                           case C_AI_Pt1000    :
                           case C_AI_TEMP_AD590:
                              UnitStr = FindDictionaryWord(L_WORD266);
                              break;
                           case C_AI_1728      :
                           case C_AI_P906_0110 :
                           case C_AI_P906_0111 :
                              UnitStr = FindDictionaryWord(L_WORD268);
                              break;
                           case C_AI_LeSw_ADCard       :
                           case C_AI_WashTrackSensor      :
                              UnitStr = FindDictionaryWord(L_WORD297);
                              break;
                           }
                        }

                     }
                     SetListviewRow(LCnt, index, Name, Loc, Type, RawVal, Value, GainStr, OffsetStr, EnableStr, UnitStr);
                     AnsiString CalVal    = LibGetValue(SVT_IO_CH_CAL_VAL, index, ePtr);
                     AnsiString CnvCalErr = LibGetValue(SVT_IO_CH_CNV_CAL_ERROR, index, ePtr);
                     AnsiString PromStat  = LibGetValue(SVT_IO_CH_EEP_SNS_STAT, index, ePtr);
                     AnsiString PCStat    = LibGetValue(SVT_IO_CH_EEP_PC_STAT, index, ePtr);
                     AnsiString UsePCSetUp = LibGetValue(SVT_IO_CH_EEP_USE_PCDATA, index, ePtr);
                     AnsiString ADSns     = LibGetValue(SVT_IO_CH_AD_SENSOR, index, ePtr);
                     AnsiString PCSns     = LibGetValue(SVT_IO_CH_FROM_PC_SENSOR, index, ePtr);
                     AnsiString UseFromPc = LibGetValue(SVT_IO_CH_USE_PC_SETUP, index, ePtr);
                     SetListviewRow2(LCnt, CalVal, CnvCalErr, PromStat, PCStat, UsePCSetUp,  ADSns,  PCSns,  UseFromPc);
                     LCnt++;
                  }
               }
            }
            break;
         case C_SC_W_INGRESS:
            {
               SCWaterIngress *ePtr = (SCWaterIngress *)CurrentIOUnit;
               for (int index = 0; index < MAX_W_INGR_CHANNELS; index++)
               {
                  AnsiString Name  = LibGetValue(SVT_IO_CH_NAME, index, ePtr);
                  AnsiString Loc   = LibGetValue(SVT_IO_CH_LOCATION, index, ePtr);
                  AnsiString Type  = LibGetValue(SVT_IO_CH_TYPE_TEXT, index, ePtr);
                  AnsiString Raw   = LibGetValue(SVT_IO_CH_RAW_VAL, index, ePtr);
                  AnsiString Value = LibGetValue(SVT_IO_CH_VALUE, index, ePtr);
                  AnsiString GainStr, OffsetStr, EnableStr, UnitStr;
                  PROIOComponent *SnsPtr = ePtr->IOComponent[index];
                  if (SnsPtr)
                  {
                     GainStr   = LibGetValue(SVT_AI_GAIN, index, SnsPtr);
                     OffsetStr = LibGetValue(SVT_AI_OFFSET, index, SnsPtr, &UnitStr);
                     EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT, index, SnsPtr);
                  }
                  SetListviewRow(index, index, Name, Loc, Type, "", Value, GainStr, OffsetStr, EnableStr, UnitStr);
               }
            }
            break;
         case C_IO_AN_ZBHART:
         case C_IO_AN_ZBANA:
            {

               IOUnitZBAna *ePtr = (IOUnitZBAna *)CurrentIOUnit;
               int LCnt = 0;
               for (int index = 0; index < MAX_AN_ZBANA_CHANNELS; index++)
               {
                  AnsiString Name  = LibGetValue(SVT_IO_CH_NAME, index, ePtr);
                  if (!Name.IsEmpty())
                  {
                     AnsiString Loc   = LibGetValue(SVT_IO_CH_LOCATION, index, ePtr);
                     AnsiString Type  = LibGetValue(SVT_IO_CH_TYPE_TEXT, index, ePtr);
                     AnsiString RawVal = LibGetValue(SVT_IO_CH_RAW_VAL, index, ePtr);

                     AnsiString ValueStr, GainStr, OffsetStr, EnableStr, UnitStr;
                     PROIOComponent *SnsPtr = ePtr->IOComponent[index];
                     if (SnsPtr)
                     {
                        GainStr   = LibGetValue(SVT_AI_GAIN, index, SnsPtr);
                        OffsetStr = LibGetValue(SVT_AI_OFFSET, index, SnsPtr);
                        EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT, index, SnsPtr);
                        ValueStr  = LibGetValue(SVT_AI_CALC_VAL, index, SnsPtr, &UnitStr);
                     }
                     SetListviewRow(LCnt++, index, Name, Loc, Type, RawVal, ValueStr, GainStr, OffsetStr, EnableStr, UnitStr);
                  }
               }
            }
            break;
         case C_IO_AN_ZB485:
            //case C_IO_WAGO:
            break;
         }
      }
      TimerCount++;
      if (UserTouch)
      {
         TimedOut = false;
         TimerCount = 0;
         UserTouch = false;
         ButWindow->EnableButton(2, true);
      }
      else if (TimerCount >= 3 && !TimedOut)
      {
         TimedOut = true;
         TimerCount = 0;
         LISTVIEW_SetSel(hListviewIO, -1);
         ButWindow->EnableButton(2, false);
      }
   }


}



void TDUSysWin3::cbSysWin(WM_MESSAGE *pMsg)
{
   int NCode, Id;
   WM_HWIN hWin = pMsg->hWin;
   switch (pMsg->MsgId)
   {
   case WM_DELETE:
      ButWindow->ChangeSWord(TDU_BUTTON_ID_PW3, 0,L_WORD237);
      SystemWindow->SysWin3IsClosed = true;
      break;
   case WM_PAINT:
      ButWindow->ChangeSWord(TDU_BUTTON_ID_PW3, 0, L_WORD545);
      SystemWindow->SysWin3->UpdateLanguage();
      break;
   case WM_INIT_DIALOG:
      SystemWindow->SysWin3->UserTouch = false;
      SystemWindow->SysWin3->TimedOut  = false;
      SystemWindow->SysWin3->TimerCount = SELECT_TIMEOUT;
      SystemWindow->SysWin3->FirstTime = true;
      //SystemWindow->SysWin3->SetListViewColor();
      break;
   case WM_KEY:
      switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key)
      {
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
      switch (NCode)
      {
      case WM_NOTIFICATION_SEL_CHANGED:       /* React only if released */
         switch (Id)
         {
         case GUI_ID_DROPDOWN0: /* Select TCU */
            {
               SystemWindow->SysWin3->CurrentIndex = DROPDOWN_GetSel(SystemWindow->SysWin3->hDropdPRO);
               SystemWindow->SysWin3->ClearList();
            }
            break;
         }
         break;
      case WM_NOTIFICATION_RELEASED:      /* React only if released */
         SystemWindow->SysWin3->UserTouch = true;

         switch (Id)
         {
         case GUI_ID_CLOSE:
            /* Close Button */
            SystemWindow->Protect();
            if (!SystemWindow->SysWin3IsClosed)
            {
               GUI_EndDialog(hWin, 0);
               ButWindow->EnableButton(2, true);
            }
            SystemWindow->UnProtect();
            break;
         }
         break;
      }
      break;
   default:
      WM_DefaultProc(pMsg);
   }
}

