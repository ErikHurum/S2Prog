#include "TSNIncludes.h"
#ifdef ANWIN
    #include "LiteCall.hpp"
    #include "LiteAccess.hpp"
    #pragma hdrstop
    #include "MainUnit.h"
#endif
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
PROSafeLinkedList  AlarmBasic::PROActiveAlarmList;
PROSafeLinkedList  AlarmBasic::PROAcknowAlarmList;
set<AlarmBasic *>AlarmBasic::AlarmSet;
ANCriticalSection AlarmBasic::AlarmSema;
ANCriticalSection AlarmBasic::LogSema;

int AlCnt = 0;
AnsiString AlarmBasic::LogFileName = "AlarmLog.txt";

// Array used for a cyclic update of alarms
bool AlarmBasic::AlarmSilence           = true;
int  AlarmBasic::LocalResetCnt          = 0;
U32  AlarmBasic::CurrentAlarmNo         = 0;
volatile bool AlarmBasic::AlarmSound    = true;
#ifdef S2TXU
extern OS_RSEMA LanguageSema;
OS_TIMER AlarmSilenceTimer;
#endif


AlarmBasic::AlarmBasic(void) {
    Initiate();
}

AlarmBasic::AlarmBasic(PRogramObjectBase *PROPtr) {
    Initiate();
    PROPointer = PROPtr;
    AlarmSet.insert(this);
    DataTransferSet.insert(this);
}

AlarmBasic::AlarmBasic(PRogramObjectBase *PROPtr, float Lim) {
    Initiate();
    PROPointer = PROPtr;
    Limit      = Lim;
    AlarmSet.insert(this);
    DataTransferSet.insert(this);
}

AlarmBasic::AlarmBasic(PRogramObjectBase *PROPtr, float Lim, float Dband, bool AlEnable) {
    Initiate();
    Limit      = Lim;
    Deadband   = Dband;
    Enable     = AlEnable;
    AlarmSet.insert(this);
    DataTransferSet.insert(this);
}

void AlarmBasic::Initiate(void) {
    AlCnt++;
    PROPointer           = NULL;
    IsHWAlarm            = false;
    MessageKey           = L_WORD485;
    TPCMessageKey        = L_WORD499;
    IDNumber             = ID_AL_BASIC << 16;
    Type                 = ID_AL_BASIC;
    Limit                = 0.0;
    Deadband             = 0.0;
    IsVisible            = true;
    IsExtraAlarm         = false;
    LastActiveTime       = clock();
    Locked               = true;
    CanDisableOnly       = false;
    Enable               = true;
    PreviousEnable       = true;
    State                = AlIdle;
    StateAtLastSend      = AlIdle;
    OutsideLimit         = false;
    AlarmNo              = 0;

    AlarmDelay           = 0;

    LastInactiveTime     = clock();
    Time_Rised           = time(NULL);
    Time_Acknowledged    = time(NULL);
    Time_Disappeared     = time(NULL);
    Time_Changed         = time(NULL);

}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString AlarmBasic::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(Type) + CrLfStr;

    if (IsExtraAlarm) {
        if (IsVisible) {
            LocalString += TabStr2 + KeyWord(C_AL_VISIBLE) + CrLfStr;
        }
        if (!FindDictionaryWord(MessageKey).IsEmpty()) {
            LocalString += TabStr2 + KeyWord(C_AL_DESCRIPTION) + (AnsiString)MessageKey + CrLfStr;
        }
        if (!FindDictionaryWord(TPCMessageKey).IsEmpty()) {
            LocalString += TabStr2 + KeyWord(C_AL_TCP_DESCRIPTION) + (AnsiString)TPCMessageKey + CrLfStr;
        }
    } else {
        if (!Enable) LocalString += TabStr2 + KeyWord(C_DISABLE) + CrLfStr;
    }
    if (Limit != 0.0) LocalString += TabStr2 + KeyWord(C_AL_LIMIT) + FloatToAnsiString(Limit) + CrLfStr;
    if (Locked) {
        LocalString += TabStr2 + KeyWord(C_AL_LOCKED) + CrLfStr;
    } else {
        LocalString += TabStr2 + KeyWord(C_AL_NOT_LOCKED) + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_AL_END) + CrLfStr;
    LocalString += CrLfStr;
    return (LocalString);
}
//---------------------------------------------------------------------------

bool AlarmBasic::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    //Enable  = true;
    Limit   = 0.0;
    //Locked = true;
    AnsiString PROName = "Alarm";
    if (PROPointer)   PROName += (AnsiString)", for " + PROPointer->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning(PROName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning(PROName, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AL_LIMIT:
                Limit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AL_VISIBLE:
                IsVisible = true;
                break;
            case C_AL_DESCRIPTION:
                MessageKey = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AL_TCP_DESCRIPTION:
                TPCMessageKey = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_ENABLE:
                Enable = true;
                break;
            case C_DISABLE:
                Enable = false;
                break;
            case C_AL_LOCKED:
                Locked = true;
                break;
            case C_AL_NOT_LOCKED :
            case C_AL_NOT_LOCKED2:
                Locked = false;
                break;
            case C_AL_END:
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_AL_END));
    return (NoError);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////
AnsiString AlarmBasic::SaveSettings(void) {
    AnsiString LocalString;
    if (IsModified || WriteAll) {
        IsModified = false;
        if (!Locked && !CanDisableOnly) {
            LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
            LocalString += TabStr2 + KWrdEnableDisable(Enable, C_ENABLE, C_DISABLE) + CrLfStr;
            LocalString += TabStr2 + KWrdEnableDisable(PreviousEnable, C_PREVIOUS_ENABLE, C_PREVIOUS_DISABLE) + CrLfStr;

            LocalString += TabStr2 + KeyWord(C_AL_LIMIT) + FloatToAnsiString(Limit) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_AL_END) + CrLfStr;

            LocalString += CrLfStr;
        }
    }
    return (LocalString);
}

bool AlarmBasic::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine   = 0;
    int Key         = C_UNDEFINED;
    AnsiString PROName = "Alarm setting";
    if (PROPointer)   PROName += (AnsiString)", for " + PROPointer->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning(PROName + (AnsiString)"Unknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                NoError = false;
                RestoreSettingsWarning(PROName + (AnsiString)"The keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AL_LIMIT:
                {
                    double tmpLimit = SettingsString->ReadDouble(ErrorLine);
                    if (!Locked  && !CanDisableOnly) {
                        Limit = tmpLimit;
                    }
                }
                NoError = !ErrorLine;
                break;
            case C_ENABLE:
                if (!Locked && !CanDisableOnly) {
                    Enable = true;
                }
                break;
            case C_DISABLE:
                if (!Locked && !CanDisableOnly) {
                    Enable = false;
                }
                break;
            case C_PREVIOUS_ENABLE:
                if (!Locked && !CanDisableOnly) {
                    PreviousEnable = true;
                }
                break;
            case C_PREVIOUS_DISABLE:
                if (!Locked && !CanDisableOnly) {
                    PreviousEnable = false;
                }
                break;
            case C_AL_END:
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_AL_END));
    return (NoError);
}

void AlarmBasic::Check(void) {
    //SendData(CMD_PRO_ALARM_STATUS); // To update all the nodes
}

// This function can ONLY be called from Check() This to ensure only ONE alarm master!!
void AlarmBasic::UpdateAlarm(int ValueStatus) {
#ifdef S2TXU
    if ( RunningTime > PROProjectInfo::AlarmSystemStartUpDelay ){
        AlarmSema.Acquire();
        if (IsVisible) {
            switch (State) {
            case AlActive       :
                LastActiveTime = clock();
                break;
            case AlAknowledged  :
                switch (ValueStatus) {
                case AL_STAT_IN_NORMAL  :
                    RemoveAlarm();
                    break;
                case AL_STAT_IN_ALARM   :
                    LastActiveTime = clock();
                case AL_STAT_IN_DEADBAND:
                    if (!Enable) {
                        RemoveAlarm();
                    }
                    break;
                }
                break;
            case AlIdle         :
                switch (ValueStatus) {
                case AL_STAT_IN_NORMAL  :
                case AL_STAT_IN_DEADBAND:
                    break;
                case AL_STAT_IN_ALARM   :
                    if (Enable) {
                        AddAlarm();
                        if (PROProjectInfo::AutoAcknowledge) {
                            MoveAlarmToAknowledge();
                        }
                    }
                    break;
                }
                break;
            }
        }
        switch (ValueStatus) {
        case AL_STAT_IN_ALARM   :
            OutsideLimit = true;
            break;
        case AL_STAT_IN_DEADBAND:
            OutsideLimit = false;
            break;
        case AL_STAT_IN_NORMAL  :
            OutsideLimit = false;
            break;
        }
        AlarmSema.Release();
    }
#endif
}
// This function can ONLY be called from Check() This to ensure only ONE alarm master!!
void AlarmBasic::AddAlarm(void) {
    // Should use a semaphore??
    AlarmNo    = ++CurrentAlarmNo;
    Time_Rised = time(NULL);
    AlarmSilence = false;   // For Buzzer, Flash, Siren, ....
    LogAlarm(AlActive);
    PROActiveAlarmList.insertInOrder(this);
    SendData(CMD_PRO_ALARM_STATUS);
    //RBMARK program error log
    if (PROSystemData::LogAlarms && Master) {
#ifdef S2TXU
        OS_Use(&LanguageSema);
#endif
        int CLanguage = PROSystemData::CurrentLanguage;
        SetCurrentLanguage(L_ENGLISH);
        AnsiString tmpStr = Get_LogMessage();
        PROPrinter::Print(PROPrinter::LogPrinterId, (char *)tmpStr.c_str());
        SetCurrentLanguage(CLanguage);
#ifdef S2TXU
        OS_Unuse(&LanguageSema);
#endif
    }
    AnPro3object::AddAlarm(this);
}

// This function can ONLY be called from Check() This to ensure only ONE alarm master!!
void AlarmBasic::RemoveAlarm(void) {
    Time_Disappeared = time(NULL);
    LogAlarm(AlIdle);
    PROAcknowAlarmList.removeNode(this);
    if (PROSystemData::LogAlarms && Master) {
#ifdef S2TXU
        OS_Use(&LanguageSema);
#endif
        int CLanguage = PROSystemData::CurrentLanguage;
        SetCurrentLanguage(L_ENGLISH);
        AnsiString tmpStr = Get_LogMessage();
        PROPrinter::Print(PROPrinter::LogPrinterId, (char *)tmpStr.c_str());
        SetCurrentLanguage(CLanguage);
#ifdef S2TXU
        OS_Unuse(&LanguageSema);
#endif
    }
    SendData(CMD_PRO_ALARM_STATUS);
    //RBMARK program error log
}

// This function can ONLY be called from Check() This to ensure only ONE alarm master!!
void AlarmBasic::MoveAlarmToAknowledge(void) {
    AlarmSema.Acquire();
    if (State != AlAknowledged) {
        Time_Acknowledged = time(NULL);
        LogAlarm(AlAknowledged);


        PROActiveAlarmList.removeNode(this);
#ifdef S2TXU
        switch (CurrentDeviceId) {
        case DEVICE_TCU:    // TCU
            break;
        case DEVICE_TDU:    // TDU
            if (OS_IsTask(&aTCB[4])) {
                OS_WakeTask(&aTCB[4]);
            }
            break;
        }
#endif
        bool NewAlarmAck = PROAcknowAlarmList.insertInOrderIfUnique(this);
        if (NewAlarmAck) {
            if (PROSystemData::LogAlarms && Master) {
#ifdef S2TXU
                OS_Use(&LanguageSema);
#endif
                int CLanguage = PROSystemData::CurrentLanguage;
                SetCurrentLanguage(L_ENGLISH);
                AnsiString tmpStr = Get_LogMessage();
                PROPrinter::Print(PROPrinter::LogPrinterId, (char *)tmpStr.c_str());
                SetCurrentLanguage(CLanguage);
#ifdef S2TXU
                OS_Unuse(&LanguageSema);
#endif
            }
        }
        if (PROActiveAlarmList.isEmpty())    AlarmSilence = true; // For Buzzer, Flash, Siren, ....
                                                                  //RBMARK program error log

    }
    // Originally sent only if alarm state was active. Changed to Send regardless.
    // This is so that if an alarm message was not received on a TDU or ANWin, the
    // user can re-aknowledge and get proper update of the alarm
    SendData(CMD_PRO_ALARM_STATUS);
    AlarmSema.Release();
}

AnsiString AlarmBasic::Get_Message(void) {
    return (FindDictionaryWord(MessageKey));
}

AnsiString AlarmBasic::Get_TPCMessage(void) {
    return (FindDictionaryWord(TPCMessageKey));
}

AnsiString AlarmBasic::Get_CompleteMessage(void) {
    if (PROPointer)   return (PROPointer->Name + " " + Get_Message());
    else return (Get_Message());
}

AnsiString AlarmBasic::Get_LogMessage(void) {
    AnsiString AlarmNoStr(AlarmNo);
    AnsiString UnitStr;
    AnsiString Location  = Get_Location();
    AnsiString Type      = Get_Message();
    AnsiString Val       = LibGetValue(SVT_AL_VALUE, this, &UnitStr) + SpaceStr + UnitStr;
    AnsiString MsgStr    = Location + SpaceStr + Type + SpaceStr;
    switch (State) {
    case AlIdle       :
        {
            AnsiString DisApp    = GetDisappearedTime("%d %b %y %T");
            MsgStr  = FindDictionaryWord(L_WORD493) + "  [" + DisApp + "]:" + MsgStr;
        }
        break;
    case AlActive     :
        {
            AnsiString Rised     = GetRisedTime("%d %b %y %T");
            MsgStr = FindDictionaryWord(L_WORD494) + "[" + Rised + "]:" + MsgStr;
        }
        break;
    case AlAknowledged:
        {
            AnsiString Reset     = GetResetTime("%d %b %y %T");
            MsgStr = FindDictionaryWord(L_WORD495) + " [" + Reset + "]:" + MsgStr;
        }
        break;
    case AlBlocked  :
        break;
    }
    MsgStr = AlarmNoStr + ":" + MsgStr + SpaceStr + FindDictionaryWord(L_WORD497) + Val + CrLfStr;  //Lim: Val:
    return (MsgStr);
}

AnsiString AlarmBasic::Get_ANPro3Message(void) {
    AnsiString AlarmNoStr(AlarmNo);
    AnsiString UnitStr;
    AnsiString Location  = Get_Location();
    AnsiString Type      = Get_Message();
    AnsiString Val       = LibGetValue(SVT_AL_VALUE, this, &UnitStr) + SpaceStr + UnitStr;
    AnsiString MsgStr    = Location + SpaceStr + Type + SpaceStr;
    AnsiString Rised     = GetRisedTime("%d %b %y %T");
    MsgStr = FindDictionaryWord(L_WORD494) + "[" + Rised + "]:" + MsgStr;
    MsgStr = AlarmNoStr + ":" + MsgStr + SpaceStr + FindDictionaryWord(L_WORD497) + Val + CrLfStr;  //Lim: Val:
    return (MsgStr);
}


AnsiString AlarmBasic::Get_Location(void) {
    if (PROPointer)   return (PROPointer->GetName());
    else return (FindDictionaryWord(L_WORD498)); //Ptr Error
}

AnsiString AlarmBasic::GetRisedTime(void) {
    return (TSNTime(Time_Rised, "%H:%M"));
}

AnsiString AlarmBasic::GetRisedTime(char *FormatStr) {
    return (TSNTime(Time_Rised, (const char *)FormatStr));
}

AnsiString AlarmBasic::GetResetTime(void) {
    AnsiString tmpStr;
    if (State == AlAknowledged) {
        tmpStr = TSNTime(Time_Acknowledged, "%H:%M");
    }
    return (tmpStr);
}

AnsiString AlarmBasic::GetResetTime(char *FormatStr) {
    AnsiString tmpStr;
    if (State == AlAknowledged) {
        tmpStr = TSNTime(Time_Acknowledged, (const char *)FormatStr);
    }
    return (tmpStr);
}

AnsiString AlarmBasic::GetDisappearedTime(void) {
    AnsiString tmpStr;
    if (State == AlIdle) {
        tmpStr = TSNTime(Time_Disappeared, "%H:%M");
    }
    return (tmpStr);
}

AnsiString AlarmBasic::GetDisappearedTime(char *FormatStr) {
    AnsiString tmpStr;
    if (State == AlIdle) {
        tmpStr = TSNTime(Time_Disappeared, FormatStr);
    }
    return (tmpStr);
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmBasic::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AL_ENABLE:
        MyRetValue = (float)Enable;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        if (!Enable) {
            Status     = GETVAL_DISABLED;
        }
        break;
    case SVT_AL_STATE     :
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)State;
        break;
    default:
        Status = GETVAL_NOT_AVAILABLE;
        break;
    }
    return (Status);
}

int AlarmBasic::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_AL_AKN_DATE_TIME:
        MyString = GetResetTime("%d %b %H:%M:%S");
        break;
    case SVT_AL_AKN_TIME    :
        MyString = GetResetTime("%H:%M:%S");
        break;
    case SVT_AL_ACT_DATE_TIME :
        MyString = GetRisedTime("%d %b %H:%M:%S");
        break;
    case SVT_AL_ACT_TIME      :
        MyString = GetRisedTime("%H:%M:%S");
        break;
    case SVT_AL_DIS_DATE_TIME:
        MyString = GetDisappearedTime("%d %b %H:%M:%S");
        break;
    case SVT_AL_DIS_TIME    :
        MyString = GetDisappearedTime("%H:%M:%S");
        break;
    case SVT_AL_LOCATION      :
        MyString = Get_Location();
        break;
    case SVT_AL_DESCRIPTION :
        MyString = Get_Message();
        break;
    case SVT_AL_MESSAGE     :
        MyString = Get_CompleteMessage();
        break;
    case SVT_AL_ENABLE_TXT:
        if (Enable) {
            MyString = FindDictionaryWord(L_WORD1);     // Enable
        } else {
            MyString = FindDictionaryWord(L_WORD2);     // Disable
        }
        break;
    case SVT_AL_UNIT:
        {
            float MyRetValue;
            int DecPnt;
            int Unit;
            GetValue(SVT_AL_VALUE, 0, MyRetValue,  DecPnt, Unit);
            MyString = GetUnitName(Unit);
        }
        break;
    case SVT_AL_STATE     :
        switch (State) {
        case AlIdle:
            MyString = "Idle";
            break;
        case AlActive:
            MyString = "Active";
            break;
        case AlAknowledged:
            MyString = "Aknowledged";
            break;
        case AlBlocked:
            MyString = "Suspended";
            break;
        default:
            MyString = "Unknown";
        }
        break;
    default:
        MyString = "";
        Status = GETVAL_NOT_AVAILABLE;
        break;
    }
    return (Status);
}

int AlarmBasic::GetBitValue(int ValueId, int Index, bool &MyBit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AL_ENABLE:
        MyBit = Enable;
        break;
    default:
        Status = PRogramObjectBase::GetBitValue(ValueId, Index, MyBit);
        break;
    }
    return (Status);
}


int AlarmBasic::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status      = E_NO_ERR, ValUnitId = NO_UNIT;
    float OrgLimit  = Limit;
    float OrgEnable = Enable;
    // Ancestors will normally only check for Locked
    if (Locked && !CanDisableOnly) {
        Status = E_NO_INPUT_PERMISSION;
    } else {
        switch (ValueId) {
        case SVT_AL_ENABLE:
        case SVT_AL_ENABLE_TXT:
            {
                int NewStatus = FindConfigKey(NewValue);
                switch (NewStatus) {
                case C_ENABLE:
                    SetEnable(EnableTrue);
                    break;
                case C_DISABLE:
                    SetEnable(EnableFalse);
                    break;
                default:
                    {
                        EnableCmd Value = (EnableCmd)GetUnsigned(NewValue, Status);
                        if (Status == E_NO_ERR) {
                            if (Value) {
                                SetEnable(EnableTrue);
                            } else {
                                SetEnable(EnableFalse);
                            }
                        }
                    }
                    break;
                }
            }
            break;
        default:
            Status = E_INPUT_ERR;
            break;
        }
    }
    if (Status == E_NO_ERR) {
        SetModifiedFlag();
        if (Limit != OrgLimit) {
            LogEvent("New limit");
        }
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int AlarmBasic::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_AL_LIMIT:
        Limit = NewValue;
        break;
    default:
        Status = E_INPUT_ERR;
        break;
    }
    return (Status);
}

int AlarmBasic::PutBitValue(int ValueId, int Index, bool NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_AL_ENABLE:
        if (NewValue) {
            SetEnable(EnableTrue);
        } else {
            SetEnable(EnableFalse);
        }
        if (Master) {
            SendData(CMD_GENERIC_STATIC_DATA);
        }
        break;
    case SVT_AL_ACKNOWLEDGE:
        if (NewValue) {
            MoveAlarmToAknowledge();
        }
        break;
    default:
        Status = E_INPUT_ERR;
        break;
    }
    return (Status);
}


void AlarmBasic::AckAll(void) {
    if (!PROActiveAlarmList.isEmpty()) {
        if (Master) {
            PROActiveAlarmList.Protect();
            while (!PROActiveAlarmList.isEmpty()) {
                PRONode *TNode = PROActiveAlarmList.getHead();
                TNode = TNode->getNext();
                AlarmBasic *TempElement = (AlarmBasic *)TNode->getElement();
                TempElement->MoveAlarmToAknowledge();
            }
            PROActiveAlarmList.UnProtect();
        } else { // not master
            QueueANPRO10_CommandHeading Command;
            Command.TxInfo.Port    = NULL;
            Command.TxInfo.rxAddr  = DEVICE_MASTER;
            Command.TxInfo.rxId    = DEVICE_TCU;
            Command.Data.CommandNo = CMD_PRO_ALARM_ACK_ALL;
            Command.Data.ndb       = 0;
            ANPRO10SendUrgent(&Command);
        }
    }
}

void AlarmBasic::SetAllToIdle(void) {
    set<AlarmBasic *>::iterator APtrIt;
    for (APtrIt = AlarmSet.begin(); APtrIt != AlarmSet.end(); APtrIt++) {
        int ret = (*APtrIt)->State = AlIdle;
    }
    PROActiveAlarmList.RemoveAllNodes();
    PROAcknowAlarmList.RemoveAllNodes();
    AlarmSilence = true;
}


int AlarmBasic::CompareOnTimeRised(PRogramObjectBase *obj1, PRogramObjectBase *obj2) {
    // sorts descending
    int temp;
    if (((AlarmBasic *)obj1)->Time_Rised < ((AlarmBasic *)obj2)->Time_Rised) {
        temp = 1;
    } else if (((AlarmBasic *)obj1)->Time_Rised == ((AlarmBasic *)obj2)->Time_Rised) {
        temp = 0;
    } else {
        temp = -1;
    }
    return (temp);
}
int AlarmBasic::CompareOnTimeAcknowledged(PRogramObjectBase *obj1, PRogramObjectBase *obj2) {
    // sorts descending
    int temp;
    if (((AlarmBasic *)obj1)->Time_Acknowledged < ((AlarmBasic *)obj2)->Time_Acknowledged) {
        temp = 1;
    } else if (((AlarmBasic *)obj1)->Time_Acknowledged == ((AlarmBasic *)obj2)->Time_Acknowledged) {
        temp = 0;
    } else {
        temp = -1;
    }
    return (temp);
}
int AlarmBasic::CompareOnAlarmNo(PRogramObjectBase *obj1, PRogramObjectBase *obj2) {
    // sorts descending
    int temp = ((AlarmBasic *)obj1)->AlarmNo - ((AlarmBasic *)obj2)->AlarmNo;
    if (temp < 0) {
        return (1);
    } else if (temp == 0) {   // should be impossible
        return (0);
    } else {
        return (-1);
    }
}

int AlarmBasic::ReceiveData(U8 *data) {
/*******************************************************************************
// Since a slave node shall not call calculate we cannot call the functions
// AddAlarm(), RemoveAlarm() & MoveAlarm...().
// These functions set time and state and Should ONLY be called by the master.
// This function is only intended to update data based on the incomming cmd and
// keep track of the lists.
*******************************************************************************/
    AlarmSema.Acquire();
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case  CMD_PRO_ALARM_STATUS:     // 3000
        if (!Master) {
#ifdef ANWIN
            float OrgLimit    = Limit;
            float OrgEnable   = Enable;
#endif
            ANPRO10_COMMAND_3000  *pData = (ANPRO10_COMMAND_3000 *)data;
            Limit             = pData->Limit;
            Deadband          = pData->Deadband;
            //State
            AlarmNo           = pData->AlarmNo;
            CurrentAlarmNo    = max(AlarmNo, CurrentAlarmNo);
            Time_Rised        = pData->Time_Rised;
            Time_Acknowledged = pData->Time_Acknowledged;
            Time_Disappeared  = pData->Time_Disappeared;
            Time_Changed      = pData->Time_Changed;
            Enable            = pData->Enable;
            PreviousEnable    = pData->PreviousEnable;
            OutsideLimit      = pData->OutsideLimit;
            AlarmSilence      = pData->AlarmSilence;

            LocalResetCnt     = 0;
            if (ReadPermission()) {
                switch (pData->State) {
                case AlActive:   // this data handling is done on slave nodes
                    {    // Update state and lists
                        switch (State) {
                        case AlActive: // We have the right state OK
                            break;
                        case AlAknowledged:
                            PROActiveAlarmList.insertInOrder(this);
                            PROAcknowAlarmList.removeNode(this);
                            ScreenSaverOff();
                            LogAlarm(AlActive);
                            break;
                        case AlIdle:
                            //AlarmSilence = false;
                            PROActiveAlarmList.insertInOrder(this);
                            ScreenSaverOff();
                            LogAlarm(AlActive);
                            break;
                        }   // end inner switch
                        break;
                    }
                case AlAknowledged:
                    {   // Update State and lists
                        switch (State) {
                        case AlActive:
                            PROActiveAlarmList.removeNode(this);
                            PROAcknowAlarmList.insertInOrder(this);
                            LogAlarm(AlAknowledged);
                            break;
                        case AlAknowledged: // We have the right state OK
                            break;
                        case AlIdle:
                            PROAcknowAlarmList.insertInOrder(this);
                            LogAlarm(AlAknowledged);
                            break;
                        } // End inner switch
                        break;
                    }
                case AlIdle:
                    {   // Update State and lists
                        switch (State) {
                        case AlActive:
                            PROActiveAlarmList.removeNode(this);
                            LogAlarm(AlIdle);
                            break;
                        case AlAknowledged:
                            PROAcknowAlarmList.removeNode(this);
                            LogAlarm(AlIdle);
                            break;
                        case AlIdle:    // We have the right state OK
                            break;
                        } // End inner switch
                    }
                    break;
                }
#ifdef ANWIN
                if (Limit != OrgLimit) {
                    LogEvent("New limit");
                } else if (OrgEnable != Enable) {
                    if (Enable) {
                        LogEvent("Enabled");
                    } else {
                        LogEvent("Disabled");
                    }
                }
#endif
            } else {
                TSN_Delay(0);
            }
            AlarmSema.Release();
            return (E_OK);
        }

    case  CMD_PRO_ALARM_ACK:     // 3001
        if (ReadPermission()) {
            //ANPRO10_COMMAND_3001  *pData = (ANPRO10_COMMAND_3001*) data;
            AlarmSilence  = true;
            LocalResetCnt = 0;
            MoveAlarmToAknowledge();
            AlarmSema.Release();
            return (E_OK);
            // TODO or  flag on sys page
        } else {
            AlarmSema.Release();
            return (E_OK);
        }
    default:
        AlarmSema.Release();
        return (E_UNKNOWN_COMMAND);
    }
}

// This function is typically called from AddAlarm, RemoveAlarm and MoveAlarmToAcknovledge (on Master)
// every time alarmstate changes. In addition it is also called from cyclic alarmupdate routine.
#ifndef BORLAND
    #pragma diag_suppress=Pa082
#endif
int AlarmBasic::SendData(U16 cmd) {
    bool SendAlarmUpdate = false;
    switch (cmd) {
    case  CMD_PRO_ALARM_STATUS:     // 3000
        if (!Master) {
            return (E_OK);
        }
    case  CMD_GENERIC_STATIC_DATA:
        SendAlarmUpdate = true;
    case  CMD_GENERIC_REALTIME_DATA:
        if ((StateAtLastSend != State) || SendAlarmUpdate) {
            QueueANPRO10_COMMAND_3000 Cmd;
            Cmd.TxInfo.Port            = NULL;
            Cmd.TxInfo.rxAddr          = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId            = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId          = IDNumber;
            Cmd.Data.ndb               = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo         = CMD_PRO_ALARM_STATUS;

            Cmd.Data.Limit             = Limit;
            Cmd.Data.Deadband          = Deadband;
            Cmd.Data.State             = State;
            Cmd.Data.AlarmNo           = AlarmNo;

            Cmd.Data.Time_Rised        = Time_Rised;
            Cmd.Data.Time_Acknowledged = Time_Acknowledged;
            Cmd.Data.Time_Disappeared  = Time_Disappeared;
            Cmd.Data.Time_Changed      = Time_Changed;
            Cmd.Data.Enable            = Enable;
            Cmd.Data.PreviousEnable    = PreviousEnable;
            Cmd.Data.OutsideLimit      = OutsideLimit;
            Cmd.Data.AlarmSilence      = AlarmSilence;
            // Possible bug as return before removeNode
            switch (cmd) {
            case  CMD_PRO_ALARM_STATUS:     // 3000
            case  CMD_GENERIC_REALTIME_DATA:
                if (StateAtLastSend != State) {
                    if (ANPRO10SendUrgent(&Cmd)) return (E_OK);
                } else if ( IsTimeToSend() )     {
                    LastRTTxTime = clock();
                    if (ANPRO10SendNormal(&Cmd)) return (E_OK);
                }
                break;
            case  CMD_GENERIC_STATIC_DATA:
                if (IsTimeToSend())     {
                    LastRTTxTime = clock();
                    if (ANPRO10SendNormal(&Cmd)) return (E_OK);
                }
                break;
            }
            StateAtLastSend = State;
            switch (State) {
            case AlIdle:
                PROActiveAlarmList.removeNode(this);
                PROAcknowAlarmList.removeNode(this);
                break;
            case AlActive:
            case AlAknowledged:
            case AlBlocked:
            default:
                break;
            }

        }
        return (E_QUEUE_FULL);
    case  CMD_PRO_ALARM_ACK:
        if (WritePermission()) {
            QueueANPRO10_COMMAND_3001 Cmd;
            Cmd.TxInfo.Port            = NULL;
            Cmd.TxInfo.rxAddr          = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId            = DEVICE_BROADCAST_TXU;

            Cmd.Data.CommandNo = CMD_PRO_ALARM_ACK;
            Cmd.Data.ndb       = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId  = IDNumber;
            if (ANPRO10SendUrgent(&Cmd)) return (E_OK);
        }
        return (E_QUEUE_FULL);

    default:
        return (E_UNKNOWN_COMMAND);
    }
}



void AlarmBasic::SetModifiedFlag(void) {
    IsModified = true;
    if (PROPointer) {
        PROPointer->SetModifiedFlag();
    } else {
        SignalSaveSettings(FLASH_SAVE_SETTINGS);
    }
}
void AlarmBasic::LogAlarm(AlarmState NewState) {
    State = NewState;
#ifdef ANWIN
    if (PROSystemData::LogToFile) {

        short SeqTable[] = { SVT_AL_LOCATION, SVT_AL_DESCRIPTION, SVT_AL_LIMIT, SVT_AL_UNIT,
            SVT_AL_VALUE, SVT_AL_UNIT, };
        static short Width[] = { 24, 16, 12, 4, 12, 4 };
        FILE *OutFile = fopen(LogFileName.c_str(), "a+t");
        if (OutFile) {
            AnsiString StateStr;
            AnsiString ActTimeInfo;
            AnsiString OtherTimeInfo;
            GetStringValue(SVT_AL_STATE, 0, StateStr);
            GetStringValue(SVT_AL_ACT_DATE_TIME, 0, ActTimeInfo);
            switch (State) {
            case AlIdle:
                GetStringValue(SVT_AL_DIS_DATE_TIME, 0, OtherTimeInfo);
                break;
            case AlActive:
                break;
            case AlAknowledged:
                GetStringValue(SVT_AL_AKN_DATE_TIME, 0, OtherTimeInfo);
                break;
            case AlBlocked:
                break;
            }
            fprintf(OutFile, "%-18s%-18s%-12s", ActTimeInfo.c_str(), OtherTimeInfo.c_str(), StateStr.c_str());
            for (unsigned Column = 0; Column < NELEMENTS(SeqTable); Column++) {
                AnsiString tmpStr = LibGetValue(SeqTable[Column], this);
                switch (SeqTable[Column]) {
                default:
                    fprintf(OutFile, "%-*s ", Width[Column], tmpStr.c_str());
                    break;
                case SVT_AL_LIMIT:
                case SVT_AL_VALUE:
                    fprintf(OutFile, "%*s ", Width[Column], tmpStr.c_str());
                    break;
                }

            }
            fprintf(OutFile, "\n");
            fclose(OutFile);

        }
    }
    if (!IsalreadyLogged())	{
        TLiteQuery *LiteQuery = new TLiteQuery(NULL);
        //LogSema.Acquire();
        try {
            // LiteConnection is either TLiteConnection already set up
            LiteQuery->Connection = MainForm->AlarmLogLiteConnection;

            // retrieve data
            LiteQuery->SQL->Text = "SELECT * FROM AlarmLog";
            LiteQuery->Open();

            // append record
            LiteQuery->Append();
            LiteQuery->FieldByName("AlarmId")->AsInteger = IDNumber;
            AnsiString Fields[4] = { "Location", "Description", "AlarmLimit", "AlarmValue" };
            short SeqTable2[] = { SVT_AL_LOCATION, SVT_AL_DESCRIPTION, SVT_AL_LIMIT,
                SVT_AL_VALUE, };
            AnsiString UnitStr = LibGetValue(SVT_AL_UNIT, this);

            for (unsigned Column = 0; Column < NELEMENTS(SeqTable2); Column++) {
                AnsiString tmpStr = LibGetValue(SeqTable2[Column], this);
                switch (SeqTable2[Column]) {
                default:
                    break;
                case SVT_AL_LIMIT:
                case SVT_AL_VALUE:
                    tmpStr += " " + UnitStr;
                    break;
                }
                LiteQuery->FieldByName(Fields[Column])->AsString = tmpStr;
            }
            AnsiString StateStr;
            GetStringValue(SVT_AL_STATE, 0, StateStr);
            LiteQuery->FieldByName("Event")->AsString           = StateStr;
            LiteQuery->FieldByName("Enabled")->AsInteger        = Enable;
            LiteQuery->FieldByName("AlarmState")->AsString      = StateStr;
            LiteQuery->FieldByName("EventTimeGMT")->AsInteger   = GetEventTime();
            LiteQuery->Post();
        }
        __finally{
            LiteQuery->Free();

        }
        //LogSema.Release();
    }
#endif
}

PRogramObjectBase* AlarmBasic::GetPROPointer(void) {
    return PROPointer;
}

void AlarmBasic::operator=(const AlarmBasic &Alarm2) {
    Enable = Alarm2.Enable;
    Limit  = Alarm2.Limit;
}

void AlarmBasic::SetEnable(EnableCmd Cmd) {
    switch (Cmd) {
    case EnableNoChange     :
        // Don't do anything
        break;
    case EnableNoMemTrue :
        if (!Enable) {
            Enable          = true;
            LogEvent("Enabled");
        }
        break;
    case EnableNoMemFalse:
        if (Enable) {
            Enable          = false;
            LogEvent("Disabled");
        }
        break;
    case EnableUsePrevious  :
        if (PreviousEnable) {
            Enable = true;
            LogEvent("Enabled");
        } else  {
            Enable = false;
            LogEvent("Disabled");
        }
        break;
    case EnableFalse             :
        if (Enable) {
            Enable          = false;
            PreviousEnable 	= false;
            LogEvent("Disabled");
        }
        break;
    case EnableTrue              :
    default                      :
        if (!Enable) {
            Enable          = true;
            PreviousEnable  = true;
            LogEvent("Enabled");
        }
        break;
    }
}

void AlarmBasic::SetAlarmToNormal(void) {
//  MoveAlarmToAknowledge();
    switch (State) {
    case AlActive       :
        MoveAlarmToAknowledge();
        break;
    case AlAknowledged  :
        break;
    case AlIdle         :
        break;
    }
    UpdateAlarm(AL_STAT_IN_NORMAL);
}

void AlarmBasic::InitAlarmSystem(void) {
    PROActiveAlarmList.Compare = CompareOnTimeRised;
    PROAcknowAlarmList.Compare = CompareOnTimeAcknowledged;
}

void AlarmBasic::SetAlarmDelay(int Dly) {
    AlarmDelay = Dly;
}


void AlarmBasic::SetAlarmLimit(float NewLim) {
    Limit = NewLim;
}

void AlarmBasic::SetRWPermissions(void) {
    set<AlarmBasic *>::iterator APtrIt;
    for (APtrIt = AlarmSet.begin(); APtrIt != AlarmSet.end(); APtrIt++) {
        if ((*APtrIt)->PROPointer) {
            (*APtrIt)->ReadPermissionSet   = (*APtrIt)->PROPointer->ReadPermissionSet;
            (*APtrIt)->WritePermissionSet  = (*APtrIt)->PROPointer->WritePermissionSet;
        }
    }
}

void AlarmBasic::LogEvent(AnsiString NewState) {
#ifdef S2TXU
    Time_Changed = time(NULL);
#elif defined(ANWIN)
    if (!IsalreadyLogged(true))	{
        Time_Changed = time(NULL);
        //LogSema.Acquire();
        TLiteQuery *LiteQuery = new TLiteQuery(NULL);
        try {
            // LiteConnection is either TLiteConnection already set up
            LiteQuery->Connection = MainForm->AlarmLogLiteConnection;

            // retrieve data
            LiteQuery->SQL->Text = "SELECT * FROM AlarmLog";
            LiteQuery->Open();

            // append record
            LiteQuery->Append();
            TField *tmpFiledPtr1 = LiteQuery->FindField("AlarmId");
            TField *tmpFiledPtr2 = LiteQuery->FindField("EventTimeGMT");
            if (tmpFiledPtr1 && tmpFiledPtr2) {
                LiteQuery->FieldByName("AlarmId")->AsInteger = IDNumber;
                AnsiString Fields[4] = { "Location", "Description", "AlarmLimit", "AlarmValue" };
                short SeqTable2[] = { SVT_AL_LOCATION, SVT_AL_DESCRIPTION, SVT_AL_LIMIT,
                    SVT_AL_VALUE, };
                AnsiString UnitStr = LibGetValue(SVT_AL_UNIT, this);

                for (unsigned Column = 0; Column < NELEMENTS(SeqTable2); Column++) {
                    AnsiString tmpStr = LibGetValue(SeqTable2[Column], this);
                    switch (SeqTable2[Column]) {
                    default:
                        break;
                    case SVT_AL_LIMIT:
                    case SVT_AL_VALUE:
                        tmpStr += " " + UnitStr;
                        break;
                    }
                    LiteQuery->FieldByName(Fields[Column])->AsString = tmpStr;
                }
                AnsiString StateStr;
                GetStringValue(SVT_AL_STATE, 0, StateStr);
                LiteQuery->FieldByName("Enabled")->AsInteger        = Enable;
                LiteQuery->FieldByName("Event")->AsString           = NewState;
                LiteQuery->FieldByName("AlarmState")->AsString      = StateStr;
                LiteQuery->FieldByName("EventTimeGMT")->AsInteger      = GetEventTime(true);
                LiteQuery->Post();
            } else {
                InitDatabase();
            }
        }
        __finally{
            LiteQuery->Free();

        }

        //LogSema.Release();
    }
#endif
}

bool AlarmBasic::IsalreadyLogged(bool isEvent){
    bool AlreadyLogged = false;
#ifdef ANWIN
    //LogSema.Acquire();
    TLiteQuery *LiteQuery = new TLiteQuery(NULL);
    try {
        LiteQuery->Connection = MainForm->AlarmLogLiteConnection;
        LiteQuery->SQL->Text = "SELECT * FROM AlarmLog";
        LiteQuery->Open();
        TField *tmpFiledPtr1 = LiteQuery->FindField("AlarmId");
        TField *tmpFiledPtr2 = LiteQuery->FindField("EventTimeGMT");

        LiteQuery->Close();
        if (tmpFiledPtr1 && tmpFiledPtr2) {
            AnsiString StateStr;
            GetStringValue(SVT_AL_STATE, 0, StateStr);
            // LiteConnection is either TLiteConnection already set up
            AnsiString SQLText = "SELECT * FROM AlarmLog";
            SQLText += " WHERE AlarmId=" + AnsiString(IDNumber);
            SQLText += " AND AlarmState='" + StateStr + "'";
            SQLText += " AND EventTimeGMT=" + AnsiString(GetEventTime(isEvent));
            SQLText += " AND Enabled=" + AnsiString(int(Enable));
            // retrieve data
            LiteQuery->SQL->Text = SQLText;

            LiteQuery->Open();
            // retrieve data
            //	ShowMessage("Records of this alarm= "+IntToStr(LiteQuery->FetchRows));

            AlreadyLogged =  bool(LiteQuery->RecordCount);
        } else {
            InitDatabase();
        }
    }
    __finally{
        LiteQuery->Free();
    }
    //LogSema.Release();
#endif
    return AlreadyLogged;
}


//---------------------------------------------------------------------------
#ifdef ANWIN
void __fastcall AlarmBasic::PrepareDatabase(void) {
    //LogSema.Acquire();
    TLiteQuery *LiteQuery = new TLiteQuery(NULL);
    try {
        MainForm->AlarmLogLiteConnection->Connected = true;
        LiteQuery->Connection = MainForm->AlarmLogLiteConnection;
        LiteQuery->SQL->Text = "SELECT * FROM AlarmLog";
        LiteQuery->Open();
        TField *tmpFiledPtr1 = LiteQuery->FindField("AlarmId");
        TField *tmpFiledPtr2 = LiteQuery->FindField("EventTimeGMT");

        LiteQuery->Close();
        if (!tmpFiledPtr1 || !tmpFiledPtr2) {
            InitDatabase();
        }
    }
    __finally{
        LiteQuery->Free();
        MainForm->AlarmLogLiteConnection->Connected = false;
    }
    //LogSema.Release();
}
//---------------------------------------------------------------------------
void __fastcall AlarmBasic::InitDatabase(void) {
    //LogSema.Acquire();
    MainForm->AlarmLogLiteConnection->Connected = true;

    TLiteSQL *LiteSQL = new TLiteSQL(NULL);
    try {
        // LiteConnection is either TLiteConnection already set up
        LiteSQL->Connection = MainForm->AlarmLogLiteConnection;
        LiteSQL->SQL->Clear();
        LiteSQL->SQL->Add("PRAGMA foreign_keys = OFF;");
        LiteSQL->SQL->Add("DROP TABLE IF EXISTS AlarmLog");
        LiteSQL->SQL->Add("PRAGMA foreign_keys = ON;");
        LiteSQL->Execute();
        // set SQL script for creating tables
        // We create the whole table instead of just alter by e.g. adding a missing coloumn
        LiteSQL->SQL->Clear();
        LiteSQL->SQL->Add("CREATE TABLE if not exists AlarmLog (");
        LiteSQL->SQL->Add("  Id integer PRIMARY KEY AUTOINCREMENT,");
        LiteSQL->SQL->Add("  AlarmId integer,");
        //LiteSQL->SQL->Add("  AlarmNo integer,");
        LiteSQL->SQL->Add("  Event text,");
        LiteSQL->SQL->Add("  Location	text,");
        LiteSQL->SQL->Add("  Description text,");
        LiteSQL->SQL->Add("  AlarmLimit text,");
        LiteSQL->SQL->Add("  AlarmValue text,");
        LiteSQL->SQL->Add("  AlarmState text,");
        LiteSQL->SQL->Add("  Enabled integer default 0,");
        LiteSQL->SQL->Add("  EventTimeGMT integer);");
        //LiteSQL->SQL->Add("  FOREIGN KEY(AlarmId) REFERENCES AlarmTable(Id)	);");
        LiteSQL->Execute();

    }
    __finally{
        LiteSQL->Free();
    }
    //LiteTable1->Active         = false;
    MainForm->AlarmLogLiteConnection->Connected = false;
    //LogSema.Release();
}

void __fastcall AlarmBasic::CleanAlarmLogData(TLiteQuery *LiteQuery, int MaxAge) {

    try {
        if (MaxAge < 2) {
            MaxAge = 2;
        }
        AnsiString MaxAgeStr = MaxAge;
        LiteQuery->SQL->Text = "DELETE FROM AlarmLog WHERE EventTimeGMT < strftime('%s', datetime('now', '-" + MaxAgeStr + " days'))";
        LiteQuery->Execute();
        LiteQuery->SQL->Clear();
    }
    __finally{}

}



#endif 	// ANWIN

time_t AlarmBasic::GetEventTime(bool NewEvent) {
    time_t EventTime = 0;
    if (NewEvent) {
        EventTime = Time_Changed;
    } else {
        switch (State) {
        case AlActive       :
            EventTime = Time_Rised;
            break;
        case AlAknowledged  :
            EventTime = Time_Acknowledged;
            break;
        case AlIdle         :
            EventTime = Time_Disappeared;
            break;
        case AlBlocked    :
            break;
        default:
            break;
        }
    }
    return EventTime;
}



////////////////////////////////////////////////////////////////////////
///
/// Function to enable/disable sound
///
///////////////////////////////////////////////////////////////////////
///
void SetAlarmSoundOff(void) {
    AlarmBasic::AlarmSound = false;
}

void SetAlarmSoundOn(void) {
    AlarmBasic::AlarmSound = true;
}

