#include "TDUIncludes.h"

TDUSysWin4::TDUSysWin4(void)
{
   CurrentHWUnit = NULL;
   CurrentIndex = 0;
}

TDUSysWin4::~TDUSysWin4(void)
{
}

const GUI_WIDGET_CREATE_INFO TDUSysWin4::aDialogCreate[] =
{
   { FRAMEWIN_CreateIndirect, "System page 4: Hardware units", TDU_SYSTEM4_WIN, 0, 0, 286, 198, FRAMEWIN_CF_MAXIMIZED, 0 },
   { TEXT_CreateIndirect,     "Select:",   GUI_ID_TEXT0,  2,   2,  46,  15, TEXT_CF_LEFT },
   { DROPDOWN_CreateIndirect, NULL,    GUI_ID_DROPDOWN0, 50,   0, 220, 100, 0, 3 },
   { LISTVIEW_CreateIndirect, NULL,    GUI_ID_LISTVIEW0,  0,  18, 281, 163, 0 },
};


void TDUSysWin4::ExecDialogBox(WM_HWIN hCurrentWin)
{
   SystemWindow->Protect();
   if (SystemWindow->SysWin4IsClosed)
   {
      SystemWindow->SysWin4IsClosed = false;
      WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), &cbSysWin,
                                     hCurrentWin, 0, 0);
      SystemWindow->CurrentSysWin = TDU_SYSWIN4;
      WM_EnableMemdev(WinHandl);
      GetDialogHandles();
   }
   else
   {
      WM_BringToTop(WinHandl);
   }
   SystemWindow->UnProtect();
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSysWin4::GetDialogHandles(void)
{
   hDropdHWUnit      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN0);
   DROPDOWN_SetAutoScroll(hDropdHWUnit, 1);
   hListviewHWUnit   = WM_GetDialogItem(WinHandl, GUI_ID_LISTVIEW0);
   LISTVIEW_SetFont(hListviewHWUnit, &TDU_FONT_ST);
   InitSysWin();
}


void TDUSysWin4::InitSysWin(void)
{
   CurrentHWUnit = NULL;
   if (PROProjectInfo::PROProjectInfoPtr)
   {
      while (DROPDOWN_GetNumItems(hDropdHWUnit) > 0)
      {
         DROPDOWN_DeleteItem(hDropdHWUnit, 0);
      }
      set<PRogramObject *>::iterator pBIt;
      for (pBIt = IOUnit::GlobalHW_UnitSet.begin(); pBIt != IOUnit::GlobalHW_UnitSet.end(); pBIt++)
      {
         PRogramObjectBase *HWUnitElement = (*pBIt);
         if (HWUnitElement)
         {
            AnsiString DropdStr;
            switch (HWUnitElement->Type)
            {
            case C_PRO_TANKSYS_UNIT:
               {
                  PROTanksystemUnit *ePtr = (PROTanksystemUnit *)HWUnitElement;
                  if (ePtr)
                  {
                     switch (ePtr->UnitID)
                     {
                     case DEVICE_TCU:
                        //     case DEVICE_TCU_R1:
                     case DEVICE_TCU_R2:
                        DropdStr = ePtr->Name; //"TCU:"+(AnsiString)ePtr->Address;
                        break;
                     case DEVICE_TDU:
                        //     case DEVICE_TDU_R1:
                     case DEVICE_TDU_R2:
                        DropdStr = ePtr->Name; //"TDU:"+(AnsiString)ePtr->Address;
                        DropdStr += " " + FindDictionaryWord(L_WORD481) + (AnsiString)ePtr->TCUAddress; // on TCU
                        break;
                     case DEVICE_PCSW:
                        DropdStr = ePtr->Name; //"PC:"+(AnsiString)ePtr->Address;
                        DropdStr += " " + FindDictionaryWord(L_WORD481) + (AnsiString)ePtr->TCUAddress; // on TCU
                        break;
                     }
                     DROPDOWN_AddString(hDropdHWUnit, DropdStr.c_str());
                     DropdHWUnitList.push_back((PRogramObject *)ePtr);
                  }
               }
               break;
            case C_SC_W_INGRESS :
            case C_SC_ADCARD    :
               {
                  SCADCard *ePtr = (SCADCard *)HWUnitElement;
                  if (ePtr)
                  {
                     DropdStr = ePtr->Name; //"ADCard";//+(AnsiString)ePtr->SCAddress;
                     DropdStr += " " + FindDictionaryWord(L_WORD482) + (AnsiString)ePtr->IOAddress + " Ch." + (AnsiString)(ePtr->IOChannel + 1); // on ZB485
                     DropdStr += " " + FindDictionaryWord(L_WORD481) + (AnsiString)ePtr->TCUAddress; // on TCU
                     DROPDOWN_AddString(hDropdHWUnit, DropdStr.c_str());
                     DropdHWUnitList.push_back((PRogramObject *)ePtr);
                  }
               }
               break;
            case C_IO_AN_ZBANA :
            case C_IO_AN_ZB485 :
            case C_IO_AN_ZBHART:
               {
                  IOUnit *ePtr = (IOUnit *)HWUnitElement;
                  if (ePtr)
                  {
                     DropdStr = ePtr->Name; //"ZBANA:"+(AnsiString)ePtr->IOAddress;
                     DropdStr += " " + FindDictionaryWord(L_WORD481) + (AnsiString)ePtr->TCUAddress; // on TCU
                     DROPDOWN_AddString(hDropdHWUnit, DropdStr.c_str());
                     DropdHWUnitList.push_back((PRogramObject *)ePtr);
                  }
               }
               break;
            case C_IO_MODBUS:
               /*{
                   IOUnitWAGO *ePtr = (IOUnitWAGO*)HWUnitElement;
                   if ( ePtr ) {
                       DropdStr = ePtr->Name;//"WAGO:"+(AnsiString)ePtr->IOAddress;
                       DropdStr += " " + FindDictionaryWord(L_WORD481) +(AnsiString)ePtr->TCUAddress; //on TCU
                       DROPDOWN_AddString(hDropdHWUnit, DropdStr.c_str());
                       DropdHWUnitList.push_back((PRogramObject*)ePtr);
                   }
               }*/
               break;
            }
         }
      }
      DROPDOWN_SetSel(hDropdHWUnit, CurrentIndex);
      WM_SetScrollbarV(hListviewHWUnit, 1);
      LISTVIEW_SetGridVis(hListviewHWUnit, 1); //Sets the visibility
      LISTVIEW_SetLBorder(hListviewHWUnit, 2);
      LISTVIEW_SetRBorder(hListviewHWUnit, 1);
      LISTVIEW_AddColumn(hListviewHWUnit,  80,  FindDictionaryWord(L_WORD449).c_str(), GUI_TA_LEFT); // Type
      LISTVIEW_AddColumn(hListviewHWUnit,  70,  FindDictionaryWord(L_WORD128).c_str(), GUI_TA_LEFT); // Value
      LISTVIEW_AddColumn(hListviewHWUnit,  50,  FindDictionaryWord(L_WORD36).c_str(), GUI_TA_LEFT); // Unit
      LISTVIEW_AddColumn(hListviewHWUnit,  50,  FindDictionaryWord(L_WORD237).c_str(), GUI_TA_LEFT); // " "
      for (int l = 0; l < NumberOfRows; l++)
      {
         LISTVIEW_AddRow(hListviewHWUnit, NULL);
      }
      ClearList();
   }
   {
      const GUIKey Words[] = {
         { TDU_SYSTEM4_WIN, 0, L_WORD41 },
         { GUI_ID_TEXT0, 0, L_WORD40 },
      };
      AddToSKeyList((GUIKey *)Words, NELEMENTS(Words));
   }
}

void TDUSysWin4::ClearList(void)
{
   for (int Row = 0; Row < NumberOfRows; Row++)
   {
      LISTVIEW_SetItemText(hListviewHWUnit, 0, Row, "");
      LISTVIEW_SetItemText(hListviewHWUnit, 1, Row, "");
      LISTVIEW_SetItemText(hListviewHWUnit, 2, Row, "");
      LISTVIEW_SetItemText(hListviewHWUnit, 3, Row, "");
      LISTVIEW_SetItemText(hListviewHWUnit, 4, Row, "");
      LISTVIEW_SetItemText(hListviewHWUnit, 5, Row, "");
   }
   UpdateSysWin();
}

void TDUSysWin4::UpdateSysWin(void)
{
   CurrentHWUnit = DropdHWUnitList[CurrentIndex];
   if (CurrentHWUnit)
   {
      switch (CurrentHWUnit->Type)
      {
      case C_PRO_TANKSYS_UNIT:
         {
            PROTanksystemUnit *ePtr = (PROTanksystemUnit *)CurrentHWUnit;
            switch (ePtr->HWDeviceId)
            {
            case TCU_R1:
            case TCU_R2:
            case TDU_R1:
            case TDU_R2:
               {
                  int LCnt = 0;
                  {
                     for (int Count = 0; Count < MAX_COM_PORTS; Count++)
                     {
                        if (ePtr->Channels[Count])
                        {
                           AnsiString Str[4];
                           Str[0] = FindDictionaryWord(L_WORD479) + " " + (AnsiString)Count + " " + FindDictionaryWord(L_WORD480); //Com+ (Rx/Tx)
                           Str[1] = LibGetValue(SVT_TXU_RX_LOAD, Count, ePtr) + "%/";
                           Str[1] += LibGetValue(SVT_TXU_TX_LOAD, Count, ePtr) + "%";
                           Str[2] = LibGetValue(SVT_PROTOCOL, Count, ePtr);
                           Str[3] = LibGetValue(SVT_DEVICE, Count, ePtr);
                           for (int j = 0; j < 4; j++)
                           {
                              LISTVIEW_SetItemText(hListviewHWUnit, j, LCnt, Str[j].c_str());
                           }
                           LCnt++;
                        }
                     }
                  }
                  {
                     int Entries;
                     ValueList *VList = ePtr->GetValueInfoTable(Entries) + 1;
                     Entries--;
                     if (VList)
                     {
                        for (int Count = 0; Count < Entries; Count++)
                        {
                           AnsiString Str[3];
                           Str[0] = FindDictionaryWord(VList[Count].Name);
                           Str[1] = LibGetValue(VList[Count].Value, ePtr, &Str[2]);
                           for (int j = 0; j < 3; j++)
                           {
                              LISTVIEW_SetItemText(hListviewHWUnit, j, LCnt, Str[j].c_str());
                           }
                           LCnt++;
                        }
                     }
                  }
               }
               break;
            case DEVICE_PCSW:
               break;
            }
         }
         break;
      case C_IO_AN_ZBANA :
      case C_IO_AN_ZB485 :
      case C_IO_AN_ZBHART:
      case C_SC_ADCARD   :
      case C_SC_W_INGRESS:
         {
            int Entries;
            ValueList *VList = CurrentHWUnit->GetValueInfoTable(Entries) + 1;
            Entries--;
            if (VList)
            {
               for (int Count = 0; Count < Entries; Count++)
               {
                  AnsiString Str[3];
                  Str[0] = FindDictionaryWord(VList[Count].Name);
                  Str[1] = LibGetValue(VList[Count].Value, CurrentHWUnit, &Str[2]);
                  for (int j = 0; j < 3; j++)
                  {
                     LISTVIEW_SetItemText(hListviewHWUnit, j, Count, Str[j].c_str());
                  }
               }
            }
         }
         break;
         /*
     case C_IO_AN_ZBANA:
         {
             IOUnitZBAna *ePtr = (IOUnitZBAna*)CurrentHWUnit;
                 int Entries;
                 ValueList *VList = ePtr->GetValueInfoTable(Entries)+1;
                 Entries--;
                 if ( VList ) {
                     for ( int Count=0; Count < Entries; Count++ ) {
                         AnsiString Str[3];
                         Str[0] = VList[Count].Name;
                         Str[1] = LibGetValue(VList[Count].Value, ePtr, &Str[2]);
                         for ( int j=0; j < 3; j++ ) {
                             LISTVIEW_SetItemText(hListviewHWUnit, j, Count, Str[j].c_str());
                         }
                 }
             }
         }
         break;
         */
      case C_IO_MODBUS:
         {
            //IOUnitWAGO *ePtr = (IOUnitWAGO*)CurrentHWUnit;
         }
         break;
      }
   }
}


void TDUSysWin4::cbSysWin(WM_MESSAGE *pMsg)
{
   int NCode, Id;
   WM_HWIN hWin = pMsg->hWin;
   switch (pMsg->MsgId)
   {
   case WM_DELETE:
      SystemWindow->SysWin4IsClosed = true;
      break;
   case WM_PAINT:
      SystemWindow->SysWin4->UpdateLanguage();
      break;
   case WM_INIT_DIALOG:
      SystemWindow->SysWin4->FirstTime = true;
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
               SystemWindow->SysWin4->CurrentIndex = DROPDOWN_GetSel(SystemWindow->SysWin4->hDropdHWUnit);
               SystemWindow->SysWin4->ClearList();
            }
            break;
         }
         break;
      case WM_NOTIFICATION_RELEASED:      /* React only if released */
         switch (Id)
         {
         case GUI_ID_CLOSE:
            /* Close Button */
            SystemWindow->Protect();
            if (!SystemWindow->SysWin4IsClosed)
            {
               GUI_EndDialog(hWin, 0);
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
