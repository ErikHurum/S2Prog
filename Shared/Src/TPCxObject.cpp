#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
set<PRogramObjectBase *>TPCxObject::ObjectSet;
bool TPCxObject::ShowAlarmMsg      = false;

set<PRogramObjectBase *>TPCxObject::tPCLists[TPC_MAX_PRIM_ADRESSES];
vector<int> TPCxObject::PrimaryAddressTable;



TPCxObject::TPCxObject(void) : PRogramObject(false)
{
   ObjectSet.insert(this);
   IDNumber = (C_PRO_T_PANEL_CONTR << 16) + ObjectSet.size();
   Initiate();
}
//---------------------------------------------------------------------------

TPCxObject::TPCxObject(int number): PRogramObject(false)
{
   ObjectSet.insert(this);
   if (number == 0)
   {
      IDNumber = (C_PRO_T_PANEL_CONTR << 16) + ObjectSet.size();
   }
   else
   {
      IDNumber = number;
   }
   Initiate();
}
//---------------------------------------------------------------------------

void TPCxObject::Initiate(void)
{
   Type              = C_PRO_T_PANEL_CONTR;
   TCUAddress        = 0;
   //TCUPort               = C_TCU_COM_485_TPC;
   //TCUPortNo         = 0;
   TPCType           = C_PRO_T_PANEL_CONTR;
   PrimaryAddress    = 0;
   SecondaryAddress  = 0;
   TPCAlarmWinPtr    = NULL;
   for (int ind = 0; ind < TPC_MAX_DISPLAY_WINDOWS; ind++)
   {
      TPCWindows[ind] = NULL;
   }
   TPCWindowCount    = 0;
   OnePROPtrOnly     = true;
   FirstTime         = 0;
   CurrentAlarmPtr   = NULL;

//  CurrentComponentType = 0;
}
//---------------------------------------------------------------------------

TPCxObject::~TPCxObject(void)
{
   if (TPCAlarmWinPtr)
   {
      delete TPCAlarmWinPtr;
      TPCAlarmWinPtr = NULL;
   }
   for (int ind = 0; ind < TPCWindowCount; ind++)
   {
      if (TPCWindows[ind])
      {
         delete TPCWindows[ind];
         TPCWindows[ind] = NULL;
      }
   }
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString TPCxObject::MakeConfigString(int ExtraTabs)
{
   AnsiString LocalString;
   LocalString += TabStr2 + KeyWord(C_TPC_START_COMMON) + CrLfStr;
   LocalString += TabStr3 + KeyWord(C_TPC_TYPE) + KeyWord(TPCType) + CrLfStr;
   LocalString += TabStr3 + KeyWord(C_TPC_PRI_ADDR) + (AnsiString)PrimaryAddress + CrLfStr;
   LocalString += TabStr3 + KeyWord(C_TPC_SEC_ADDR) + (AnsiString)SecondaryAddress + CrLfStr;
   LocalString += TabStr3 + KeyWord(C_TCU_ADDRESS) + (AnsiString)TCUAddress + CrLfStr;
   int OneProPtr = 0;
   if (OnePROPtrOnly) OneProPtr = 1;
   LocalString += TabStr3 + KeyWord(C_TCU_ONE_PROPTR) + (AnsiString)OneProPtr + CrLfStr;
   LocalString += TabStr2 + KeyWord(C_TPC_END_COMMON) + CrLfStr;

   if (TPCAlarmWinPtr)
   {
      LocalString += TPCAlarmWinPtr->MakeConfigString();
   }
   for (int ind = 0; ind < TPC_MAX_DISPLAY_WINDOWS; ind++)
   {
      if (TPCWindows[ind]) LocalString += TPCWindows[ind]->MakeConfigString();
   }

   // LocalString += PogramObjectBase::MakeConfigString();
   return (LocalString);
}
//---------------------------------------------------------------------------

bool TPCxObject::LoadConfigString(TSNConfigString& ConfigString)
{
   bool NoError = true;
   int ErrorLine = 0;
   int Key;
   do
   {
      AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
      if (ErrorLine)
      {
         if (ErrorLine != EOF)
         {
            GiveConfigWarning((AnsiString)"TPC " + (AnsiString)PrimaryAddress + "-" + (AnsiString)SecondaryAddress, ErrorLine);
         }
      }
      else
      {
         Key = FindConfigKey(InputKeyWord);
         switch (Key)
         {
         default:
            GiveConfigWarning((AnsiString)"TPC " + (AnsiString)PrimaryAddress + "-" + (AnsiString)SecondaryAddress, InputKeyWord, ConfigString.LineCount);
            break;
         case C_TPC_END_COMMON:
            break;
         case C_TPC_TYPE:
            {
               AnsiString temp = ConfigString.NextWord(ErrorLine);
               TPCType = FindConfigKey(temp);
               NoError = !ErrorLine;
            }
            break;
         case C_TPC_PRI_ADDR:
            {
               PrimaryAddress = ConfigString.ReadLong(ErrorLine);
               NoError = !ErrorLine;
            }
            break;
         case C_TPC_SEC_ADDR:
            {
               SecondaryAddress = ConfigString.ReadLong(ErrorLine);
               Name = (AnsiString)PrimaryAddress + "_" + (AnsiString)SecondaryAddress;
               NoError = !ErrorLine;
            }
            break;
         case C_TCU_ONE_PROPTR:
            {
               int OneProPtr = ConfigString.ReadLong(ErrorLine);
               if (OneProPtr == 1) OnePROPtrOnly = true;
               else OnePROPtrOnly = false;
               NoError = !ErrorLine;
            }
            break;
         case C_TCU_ADDRESS:
            {
               TCUAddress = ConfigString.ReadLong(ErrorLine);
               NoError = !ErrorLine;
            }
            break;
         }
      }
   }
   while (NoError && (ErrorLine != EOF) && (Key != C_TPC_END_COMMON));
   return (NoError);
}
//---------------------------------------------------------------------------

void TPCxObject::WriteConfigToFile(TSNConfigString& ConfigString)
{
   AnsiString LocalString;
   AnsiString IdNumStr;
   IdNumStr.cat_sprintf("0x%0x", IDNumber);
   LocalString += KeyWord(C_PRO_T_PANEL_CONTR) + IdNumStr + CrLfStr;

   LocalString += MakeConfigString();   //common

   LocalString += KeyWord(C_PRO_END) + CrLfStr;
   LocalString += CrLfStr;

   ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int TPCxObject::LoadConfigFromFile(TSNConfigString& ConfigString)
{
   SetLineNumber(ConfigString.LineCount);
   bool NoError = true;
   int ErrorLine = 0;
   int Key;
   do
   {
      AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
      if (ErrorLine)
      {
         if (ErrorLine != EOF)
         {
            GiveConfigWarning((AnsiString)"TPC " + (AnsiString)PrimaryAddress + "-" + (AnsiString)SecondaryAddress, ErrorLine);
         }
      }
      else
      {
         Key = FindConfigKey(InputKeyWord);
         switch (Key)
         {
         default:
            GiveConfigWarning((AnsiString)"TPC " + (AnsiString)PrimaryAddress + "-" + (AnsiString)SecondaryAddress, InputKeyWord, ConfigString.LineCount);
            break;
         case C_TPC_END_WINDOW: //fault in config
         case C_AI_END:      // If AI type not found can continue with this
         case C_AL_END:
         case C_PRO_END:
         case C_PRO_END_COMMON:
         case C_PRO_END_PRO:
            break;
         case C_TPC_START_COMMON:
            LoadConfigString(ConfigString);
            break;
         case C_TPC_WINDOW:
            {
               TPCWindow *WindowPtr;
               switch (TPCType)
               {
               case C_TPC_140:
                  WindowPtr = (TPCWindow *)new TPCWindow140();
                  break;
               case C_TPC_350:
                  WindowPtr = (TPCWindow *)new TPCWindow350();
                  break;
               case C_TPC_196:
                  WindowPtr = (TPCWindow *)new TPCWindow196();
                  break;
               default:
                  WindowPtr = new TPCWindow();
               }
               WindowPtr->LoadConfigString(ConfigString);
               TPCWindows[TPCWindowCount++] = WindowPtr;
               NoError = !ErrorLine;
            }
            break;
         case C_TPC_ALARM_WINDOW:
            {
               TPCAlarmWindow *WindowPtr = new TPCAlarmWindow();
               WindowPtr->LoadConfigString(ConfigString);
               TPCAlarmWinPtr = WindowPtr;
               NoError = !ErrorLine;
            }
            break;
         }
      }
   }
   while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
   return ErrorLine;
}
//--------------------------------------------------------------------------- '
///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void TPCxObject::SaveSettings(TSNConfigString *SettingsString)
{

}


//--------------------------------------------------------------------------- '

///////////////////////////////////////////////////////////////////////////////
//
//  Other tPCx routines
//
///////////////////////////////////////////////////////////////////////////////


TPCxObject* FindtPCx(U8 SecAddress, set<PRogramObjectBase *>CurentTPCxList)
{
   set<PRogramObjectBase *>::iterator pBIt;
   for (pBIt = CurentTPCxList.begin(); pBIt != CurentTPCxList.end(); pBIt++)
   {
      if (((TPCxObject *)(*pBIt))->SecondaryAddress == SecAddress) return ((TPCxObject *)(*pBIt));
   }
   return (NULL);
}

void TPCxObject::InitializetPCxSystem(void)
{
   for (int PrimAddress = TPC_FIRST_ADDRESS; PrimAddress <= TPC_LAST_ADDRESS; PrimAddress++)
   {
      set<PRogramObjectBase *>CurrentPROSet;
      set<PRogramObjectBase *>::iterator pBIt;
      for (pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++)
      {
         TPCxObject *tPCx = (TPCxObject *)(*pBIt);
         if (tPCx->PrimaryAddress == PrimAddress)
         {
            CurrentPROSet.insert(tPCx);
         }
      }
      if (!CurrentPROSet.empty())
      {
         tPCLists[PrimaryAddressTable.size()] = CurrentPROSet;
         PrimaryAddressTable.push_back(PrimAddress);
      }
   }

}

U16 TPCxObject::AddAlarmWindow(U8 *TxBuf, U16 Ptr, bool Update, bool ShowAlarm)
{
   PRogramObject *LastProPtr = NULL;
   CurrentAlMessage  = "";
   CurrentAlLocName  = "";
   CurrentLEDStatus  = TPC_LED_OFF;
   int NumberOfWin;
   if (OnePROPtrOnly)
   {
      NumberOfWin = min(1, TPCWindowCount); // To prevent any mistakes
   }
   else
   {
      NumberOfWin = TPCWindowCount;
   }
   for (int WinIndex = 0; WinIndex < NumberOfWin; WinIndex++)
   {
      TPCWindow *Win = TPCWindows[WinIndex];
      PRogramObject *PROPtr = Win->PROPtr;
      if (PROPtr)
      {
         LastProPtr              = PROPtr;
         bool ActiveAlarm        = false;
         time_t NewestAlarmAct   = 0;
         time_t NewestAlarmAck   = 0;
         set<AlarmBasic *>::iterator pBIt;
         for (pBIt = PROPtr->CompleteAlarmInfoList.begin(); pBIt != PROPtr->CompleteAlarmInfoList.end(); pBIt++)
         {
            AlarmBasic *TempElement = *pBIt;
            if (TempElement)
            {
               switch (TempElement->State)
               {
               case AlarmBasic::AlIdle    :
                  AlarmSet.erase(TempElement);
                  break;
               case AlarmBasic::AlActive  :
                  if (TempElement->Time_Rised > NewestAlarmAct)
                  {
                     NewestAlarmAct    = TempElement->Time_Rised;
                     ActiveAlarm       = true;
                     CurrentAlMessage  = TempElement->Get_TPCMessage();
                     CurrentAlLocName  = PROPtr->Name;
                     CurrentLEDStatus  = TPC_LED_FLASH;
                     CurrentAlarmPtr   = TempElement;
                  }
                  AlarmSet.insert(TempElement);
                  break;
               case AlarmBasic::AlAknowledged :
                  if (!ActiveAlarm && (TempElement->Time_Acknowledged > NewestAlarmAck))
                  {
                     NewestAlarmAck    = TempElement->Time_Acknowledged;
                     CurrentAlMessage  = TempElement->Get_TPCMessage();
                     CurrentAlLocName  = PROPtr->Name;
                     CurrentLEDStatus  = TPC_LED_ON;
                     CurrentAlarmPtr   = TempElement;
                  }
                  AlarmSet.erase(TempElement);
                  break;
               }
            }
         }
      }
   }

   if (ShowAlarm)
   {
      bool IsAlarm = !CurrentAlMessage.IsEmpty();
      // See if we have an alarm message
      if (!IsAlarm)
      {
         CurrentAlMessage  = "OK";
      }
      if (OnePROPtrOnly)
      {
         CurrentAlLocName = LastProPtr->Name;
      }
      else
      {
         CurrentAlLocName = "***";
      }

      switch (TPCType)
      {
      case C_TPC_140:
         {
			U8 tPCData[BUF_SIZE] = { (U8)SecondaryAddress, 0 };
            U8 *AsciiVal        = &tPCData[2];
            strcpy((char *)AsciiVal, CurrentAlMessage.c_str());
            Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_LOTXT, tPCData, (CurrentAlMessage.Length() + 2));
         }
         break;
      case C_TPC_350:
         {
			U8 tPCData[BUF_SIZE] = { (U8)SecondaryAddress, 0 };
            U8 *AsciiVal        = &tPCData[2];
            strncpy((char *)AsciiVal, CurrentAlLocName.c_str(), TPC_UPPER_DISP_WIDTH + 1);
            while (*AsciiVal == ' ') AsciiVal++;
            int Length = strlen((char *)AsciiVal);
            if (AsciiVal != &tPCData[2])
            {
               memmove(&tPCData[2], AsciiVal, Length);

            }
            Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_HITXT, tPCData, Length + 2);

            strcpy((char *)AsciiVal, CurrentAlMessage.c_str());
            Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_LOTXT, tPCData, (CurrentAlMessage.Length() + 2));
         }
         break;
      case C_TPC_196:
         // Only add text if alarm and not aknowledge
         if (IsAlarm && (CurrentLEDStatus  == TPC_LED_FLASH))
         {
			U8 tPCData[BUF_SIZE] = { (U8)SecondaryAddress, 0 };
            U8 *AsciiVal        = &tPCData[2];
            strcpy((char *)AsciiVal, CurrentAlMessage.c_str());
            Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_LOTXT, tPCData, (CurrentAlMessage.Length() + 2));
         }
         break;
      }
   }
   // Always add LED status
   {
	  U8 tPCData[BUF_SIZE] = { (U8)SecondaryAddress, CurrentLEDStatus };
      Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_ALSTA, tPCData, 2);
   }
   return (Ptr);

}



U16 TPCxObject::AddExtraWindows(U8 *TxBuf, U16 Ptr, bool Update)
{
   TPCWindow *Win = TPCWindows[0]; // Allways 0
   if (Win)
   {
      int ValKeyTable[] = { Win->TopDisplay, Win->BottomDisplay };

      for (int WinIndex = 0; WinIndex < 2; WinIndex++)
      {
		 U8 tPCData[BUF_SIZE] = { (U8)SecondaryAddress, (U8)WinIndex };  // Not in alarm window
         if (ValKeyTable[WinIndex] != SVT_NOT_DEFINED)
         {
            AnsiString MyVal = GetLibValueTPCx(ValKeyTable[WinIndex], 0, Win->PROPtr, TPC_EXTRA_DISP_WIDTH);
            U8 *AsciiVal = &tPCData[2];
            strcpy((char *)AsciiVal, MyVal.c_str());
            while (*AsciiVal == ' ') AsciiVal++;
            int Length = strlen((char *)AsciiVal);
            if (AsciiVal != &tPCData[2])
            {
               memmove(&tPCData[2], AsciiVal, Length);
            }
            Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_XTXT, tPCData, Length + 2);
         }
      }
   }
   return (Ptr);
}

U16 TPCxObject::AddLowerWindow(U8 *TxBuf, U16 Ptr, bool Update, int WinOffset)
{
#ifdef S2TXU
   for (int WinIndex = 0; WinIndex < TPCWindowCount; WinIndex++)
   {
      U8 tPCData[BUF_SIZE] = { SecondaryAddress, WinIndex + WinOffset }; // Not in alarm window
      TPCWindow *Win = TPCWindows[WinIndex];
      OS_Use(&UnitSema);
      SetUserUnits();
      AnsiString MyVal = GetLibValueTPCx(Win->MainDisplay, 0, Win->PROPtr, TPC_LOWER_DISP_WIDTH);

      OS_Unuse(&UnitSema);
      U8 *AsciiVal  = &tPCData[2];
      strcpy((char *)AsciiVal, MyVal.c_str());
      while (*AsciiVal == ' ') AsciiVal++;
      int Length = strlen((char *)AsciiVal);
      // Start by removing space chars.
      if (Length < TPC_LOWER_DISP_WIDTH)
      {
         switch (Win->MainDisplay)
         {
         case SVT_VOLPERCENT:
            AsciiVal[Length++] = '%';
            AsciiVal[Length] = 0;
            break;
         case SVT_TEMP:
            AsciiVal[Length++] = 0x5e;      // ^
            AsciiVal[Length] = 0;
            break;
         }
      }
      if (AsciiVal != &tPCData[2])
      {
         memmove(&tPCData[2], AsciiVal, Length);

      }
      U8  Size = Length + 2;
      Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_LOTXT, tPCData, Size);
   }
#endif
   return (Ptr);
}




U16 TPCxObject::AddUpperWindow(U8 *TxBuf, U16 Ptr, bool Update)
{
   for (int WinIndex = 0; WinIndex < TPCWindowCount; WinIndex++)
   {
	  U8 tPCData[BUF_SIZE] = { (U8)SecondaryAddress, (U8)(WinIndex + 1) }; // Not in alarm window
      TPCWindow *Win  = TPCWindows[WinIndex];
      AnsiString MyVal;
      switch (Win->UpperDisplay)
      {
      case SVT_UNIT       :
         GetLibValueTPCx(SVT_UNIT, Win->MainDisplay, Win->PROPtr, TPC_UPPER_DISP_WIDTH, SVT_FLAG_NORMAL, &MyVal);
         break;
      case SVT_VALUE_NAME       :
      case SVT_VALUE_SHORT_NAME :
         MyVal = GetLibValueTPCx(SVT_VALUE_SHORT_NAME, Win->MainDisplay,Win->PROPtr, TPC_UPPER_DISP_WIDTH);
         break;
      default             :
         MyVal = GetLibValueTPCx(Win->UpperDisplay, 0,Win->PROPtr, TPC_UPPER_DISP_WIDTH);
         break;
      }
      U8 *AsciiVal    = &tPCData[2];
      strncpy((char *)AsciiVal, MyVal.c_str(), TPC_UPPER_DISP_WIDTH + 1);
      while (*AsciiVal == ' ') AsciiVal++;
      int Length = strlen((char *)AsciiVal);
      if (AsciiVal != &tPCData[2])
      {
         memmove(&tPCData[2], AsciiVal, Length);

      }
      Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_HITXT, tPCData, Length + 2);
   }
   return (Ptr);
}

U16 TPCxObject::AddGraphs(U8 *TxBuf, U16 Ptr, bool Update)
{
   for (int WinIndex = 0; WinIndex < TPCWindowCount; WinIndex++)
   {
      TPCWindow *Win  = TPCWindows[WinIndex];
      switch (Win->MainGraph)
      {
      case SVT_DS           :
      case SVT_DP           :
      case SVT_DA           :
      case SVT_DF           :
         {
            float MyVal;
            int DecPnt, Unit;
            int Status = Win->PROPtr->GetValue(Win->MainGraph, 0, MyVal, DecPnt, Unit);
            U8 Percent;
            if (Status == GETVAL_NO_ERR)
            {
               Percent = (U8)(MyVal / PRODraftSystem::MaxSummerDraft * 100.0 + 0.5);
            }
            else
            {
               Percent = 0;
            }
			U8 tPCData[TPC_GRAPH_SIZE] = { (U8)SecondaryAddress, (U8)WinIndex, (U8)Percent };
			Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_BAVAL, tPCData, TPC_GRAPH_SIZE);

         }
         break;
      case SVT_VOLPERCENT   :
         {
            float MyVal;
            int DecPnt, Unit;
            int Status = Win->PROPtr->GetValue(SVT_VOLPERCENT, 0, MyVal, DecPnt, Unit);
            U8 Percent;
            if (Status == GETVAL_NO_ERR)
            {
               Percent = (U8)(MyVal + 0.5);
            }
            else
            {
               Percent = 0;
            }
			U8 tPCData[TPC_GRAPH_SIZE] = { (U8)SecondaryAddress, (U8)WinIndex, (U8)Percent };
            Ptr += AddCommand(TxBuf, Ptr, ANP1_SND_BAVAL, tPCData, TPC_GRAPH_SIZE);
         }
         break;
      }
   }
   return (Ptr);
}



U16 TPCxObject::AddWindows(U8 *TxBuf, U16 Ptr, bool Update, bool ShowAlarm)
{
   switch (FirstTime)
   {
   case 1:
      FirstTime++;
      switch (TPCType)
      {
      case C_TPC_140:
      case C_TPC_350:
         Ptr = SetWindow(TxBuf, Ptr, 1);
         break;
      case C_TPC_196:
         Ptr = SetWindow(TxBuf, Ptr, 1);
         break;
      }
      break;
   case 0:
      FirstTime++;
   case 2:
      switch (TPCType)
      {
      case C_TPC_140:
         Ptr = AddAlarmWindow(TxBuf, Ptr, Update);
         Ptr = AddLowerWindow(TxBuf, Ptr, Update);
         break;
      case C_TPC_350:
         Ptr = AddAlarmWindow(TxBuf, Ptr, Update);
         Ptr = AddLowerWindow(TxBuf, Ptr, Update);
         Ptr = AddUpperWindow(TxBuf, Ptr, Update);
         Ptr = AddGraphs(TxBuf, Ptr, Update);
         break;
      case C_TPC_196:
         {
            // First call AddAlarmWindow.
            // The CurrentLEDStatus will be set
            // Alarm message only added if TPC_LED_FLASH and ShowAlarm are true
            Ptr = AddAlarmWindow(TxBuf, Ptr, Update, ShowAlarm);   // Må signalisere om Message skal inkluderes
            switch (CurrentLEDStatus)
            {
            case TPC_LED_OFF    :
            case TPC_LED_ON     :
               Ptr = AddLowerWindow(TxBuf, Ptr, Update, 0);
               break;
            case TPC_LED_FLASH  :
               if (!ShowAlarm)
               {
                  Ptr = AddLowerWindow(TxBuf, Ptr, Update, 0);
               }
            }
         }
         Ptr = AddExtraWindows(TxBuf, Ptr, Update);
         break;
      }
   }

   return (Ptr);
}

U16 TPCxObject::SetWindow(U8 *TxBuf, U16 Ptr, U8 WinIndex)
{
   U8 Data[BUF_SIZE] = { (U8)SecondaryAddress, (U8)WinIndex };
   return (AddCommand(TxBuf, Ptr, ANP1_SND_DVAL, Data, 2));
}
void TPCxObject::AckAlarms(void)
{
   set<AlarmBasic *>::iterator pBIt;
   for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++)
   {
      AlarmBasic *Element = *pBIt;
      if (Element->State == AlarmBasic::AlActive)
      {
         if (Master) Element->MoveAlarmToAknowledge();
         else Element->SendData(CMD_PRO_ALARM_ACK);
      }
   }

}

bool TPCxObject::UnpackPacket(TSNUart *PortPtr, U8 *Buf, int Size, set<PRogramObjectBase *>CurrenttpPCxList)
{
   U8 *MaxPtr    = &Buf[Size];
   bool MoreData = true;
   do
   {
      U8 Command = Buf[0];
      U8 Size    = Buf[1];
      Buf += 2;
      switch (Command)
      {
      case ANP1_REP_DATA :
         {
            int SecAddress = Buf[0];
            TPCxObject *Display = FindtPCx(SecAddress, CurrenttpPCxList);
            if (Display)
            {
               Display->AckAlarms();
               Display->SendtPCxAcknowledge(PortPtr);
            }
         }
         break;
      case ANP1_REP_STAT  :
         {
            int SecAddress = Buf[0];
            TPCxObject *Display = FindtPCx(SecAddress, CurrenttpPCxList);
            if (Display)
            {
               Display->Version     = Buf[1];
               Display->PCB_Type    = Buf[2];
               Display->RxBufSize   = (Buf[4] << 8) | Buf[3];
               Display->TxBufSize   = (Buf[6] << 8) | Buf[5];
               Display->Restart     = Buf[7];
               Display->SerialNumber = (Buf[11] << 24) | (Buf[10] << 16) | (Buf[9] << 8) | Buf[8];
            }
         }
         break;
      case ANP1_REP_EEPSER:
         break;
      case ANP1_ECMD_NMDWOACK:
      case ANP1_ECMD_NMDRQACK:
         MoreData = false;
      default:
         break;
      }
      Buf += Size;
   }
   while (MoreData && (Buf < MaxPtr));
   return (true);
}

U16 TPCxObject::MakeAcknowledge(U8 *TxBuf, U16 Ptr)
{
   U8 Data[BUF_SIZE] = { (U8)SecondaryAddress, true };
   return (AddCommand(TxBuf, Ptr, ANP1_REQ_ACKSTAT, Data, 2));
}

void TPCxObject::SendtPCxAcknowledge(TSNUart *PortPtr)
{
   U8 TxBuf[BUF_SIZE];
   U16 Ptr = AddPacketHeading(TxBuf, PrimaryAddress);
   Ptr += MakeAcknowledge(TxBuf, Ptr);
   Ptr += AddPacketTail(TxBuf, Ptr, ANP1_ECMD_NMDWOACK);
   PortPtr->Send(TxBuf, Ptr, SEND_COMPLETE_EVENT);
}

void TPCxObject::Handle(TSNUart *PortPtr)
{
   U8 TxBuf[2 * TPC_DISPLAY_BUF_SIZE];
   bool Update  = true;
   ShowAlarmMsg = !ShowAlarmMsg;
   for (unsigned i = 0; i < PrimaryAddressTable.size(); i++)
   {
      if (!tPCLists[i].empty())
      {
         U16 Ptr = AddPacketHeading(TxBuf, PrimaryAddressTable[i]);
         set<PRogramObjectBase *>::iterator pBIt;
         unsigned j = 0;
         for (pBIt = tPCLists[i].begin(); pBIt != tPCLists[i].end(); j++, pBIt++)
         {
            TPCxObject *tPCx = (TPCxObject *)(*pBIt);
            U8 TmpBuf[TPCX_MAX_PACKET_SIZE];
            int NewPtr = tPCx->AddWindows(TmpBuf, 0, Update, ShowAlarmMsg);
            if (NewPtr)
            {
               if ((unsigned(Ptr + NewPtr) >= TPCX_MAX_PACKET_SIZE) && (j < tPCLists[i].size() - 1))
               {
                  Ptr += AddPacketTail(TxBuf, Ptr, ANP1_ECMD_NMDWOACK);
                  PortPtr->Send(TxBuf, Ptr, SEND_COMPLETE_EVENT);
                  ANPRO1Receive(PortPtr, 1000, (U8)PrimaryAddressTable[i], tPCLists[i], UnpackPacket);
                  TSN_Delay(500);
                  Ptr = AddPacketHeading(TxBuf, PrimaryAddressTable[i]);
               }
               memcpy(&TxBuf[Ptr], TmpBuf, NewPtr);
               Ptr += NewPtr;
            }
         }
         // Always send a packet to enable a reply from any tPCx
         Ptr += AddPacketTail(TxBuf, Ptr, ANP1_ECMD_SNDOK);
         PortPtr->Send(TxBuf, Ptr, SEND_COMPLETE_EVENT);
         ANPRO1Receive(PortPtr, 1000, PrimaryAddressTable[i], tPCLists[i], UnpackPacket);
         TSN_Delay(500);
      }
      // Here we can listen and see if we have any messages for us
   }
}

void TPCxObject::TPCxTask(TSNUart *PortPtr)
{
#ifdef S2TXU
   InitializetPCxSystem();

   OS_TASK *TxTaskPtr = OS_GetpCurrentTask();
   OS_SetPriority(TxTaskPtr, TPCX_TASK_PRIORITY);
   while (true)
   {
      TPCxObject::Handle(PortPtr);
      TSN_Delay(1000);
   }
#endif
}


AnsiString TPCxObject::GetLibValueTPCx(int ValueId, int ValueId2, PRogramObjectBase *ObjPtr, int Width, int Flag, AnsiString *UnitStr)
{
#ifdef S2TXU
   OS_Use(&UnitSema);
   SetUserUnits();
   AnsiString MyVal = LibGetValue(ValueId, ValueId2, 0, ObjPtr, Width, Flag, UnitStr);
   switch (PROSystemData::TXUSystemData->CurrentUnitSystem)
   {
   case 0:
	  SetStdSIUnits();
	  break;
   case 1:
	  SetStdUSUnits();
	  break;
   case 2:
	   // Not required as User units already selected
	  //SetUserUnits();
	  break;
   }
   OS_Unuse(&UnitSema);

   return MyVal;
#else
    return "";
#endif
}


