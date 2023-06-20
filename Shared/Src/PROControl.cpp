#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

int PROControl::NumberOfPRO = 0;

PROControl::PROControl(int RIndex) : PRogramObjectBase(false) {
    NumberOfPRO++;
    IDNumber          = (C_PRO_CONTROL << 16) + NumberOfPRO;
    NormalState       = C_CTRL_NS_UNPOWERED;
    DeactivateBy      = C_CTRL_DE_VALUE;
    AlarmDelay        = 0;
    TCUAddress        = 0;
    AlarmAlternative  = C_CTRL_ALT_ALL;
    RelayIndex        = RIndex;
    Priority          = R_INACTIVE;
    ActiveAl          = 0;
    AcknowledgedAl    = 0;
    IdleAl            = 0;
    SuspAl            = 0;
    OutsideLim        = 0;
    PrevAlCnt         = 0;



#ifdef S2TXU
    OS_CREATERSEMA(&CtrlSema);
#endif
}

PROControl::~PROControl(void) {
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString PROControl::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr;
    for (int i = 0; i < ExtraTabs; i++) TabStr += TabStr1;
    AnsiString LocalString;
    LocalString += TabStr + TabStr2 + KeyWord(C_CTRL_START_COMMON) + CrLfStr;
    // LocalString += PogramObjectBase::MakeConfigString(ConfigString);

    LocalString += TabStr + TabStr3 + KeyWord(C_CTRL_NORMAL_STATE) + KeyWord(NormalState) + CrLfStr;
    LocalString += TabStr + TabStr3 + KeyWord(C_CTRL_DEACTIVATE) + KeyWord(DeactivateBy) + CrLfStr;

    LocalString += TabStr + TabStr3 + KeyWord(C_CTRL_AL_DELAY) + (AnsiString)AlarmDelay + CrLfStr;
    LocalString += TabStr + TabStr3 + KeyWord(C_CTRL_ALTERNATIVE) + KeyWord(AlarmAlternative) + CrLfStr;
    LocalString += TabStr + TabStr3;
    for (unsigned j = 0; j < AlarmTypeList.size(); j++) {
        LocalString += KeyWord(AlarmTypeList[j]);
    }
    LocalString += CrLfStr;
    if (!PROList.empty()) {
        int ListSize = PROList.size();
        LocalString += TabStr + TabStr3 + KeyWord(C_OBJECT_ID) + CrLfStr;
        set<PRogramObjectBase *>::iterator pBIt;
        for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
            PRogramObject *Element = (PRogramObject *)*pBIt;
            int PROIDNumber = Element->IDNumber;
            AnsiString IdNumStr;
            IdNumStr.cat_sprintf("0x%0X", PROIDNumber);
            LocalString += TabStr + TabStr4 + IdNumStr + CrLfStr;
        }
        LocalString += TabStr + TabStr3 + KeyWord(C_PROLIST_END) + CrLfStr;
    }
    LocalString += TabStr + TabStr2 + KeyWord(C_CTRL_END_COMMON) + CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------

bool PROControl::LoadConfigString(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("Control unit on TCU", ErrorLine);
            }
        } else Key = FindConfigKey(InputKeyWord);
        switch (Key) {
        default:
            GiveConfigWarning("Control unit on TCU", InputKeyWord, ConfigString.LineCount);
            break;
        case C_CTRL_END_COMMON:
            break;
        case C_CTRL_NORMAL_STATE:
            {
                AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                if (!ErrorLine) {
                    NormalState = FindConfigKey(TempStr);
                }
                NoError = !ErrorLine;
            }
            break;
        case C_CTRL_DEACTIVATE:
            {
                AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                if (!ErrorLine) {
                    int tmpKey = FindConfigKey(TempStr);
                    switch (tmpKey) {
                    case C_CTRL_DE_ACKNOW       :
                    case C_CTRL_DE_IDLE         :
                    case C_CTRL_DE_VALUE        :
                    case C_CTRL_DE_VAL_ENABLED  :
                    case C_CTRL_DE_SILENCE      :
                        DeactivateBy = tmpKey;
                        break;
                    default:
                        ErrorLine = ConfigString.LineCount;
                        break;
                    }
                }
                NoError = !ErrorLine;
            }
            break;
        case C_CTRL_AL_DELAY:
            {
                AlarmDelay = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
            }
            break;
        case C_CTRL_ALTERNATIVE:
            {
                AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                if (!ErrorLine) {
                    AlarmAlternative = FindConfigKey(TempStr);
                }
                NoError = !ErrorLine;
            }
            break;
        case ID_AL_OVERFILL                 :
        case ID_AL_HIGH_LEVEL               :
        case ID_AL_LOW_LEVEL                :
        case ID_AL_LOWLOW_LEVEL               :
        case ID_AL_HIGH_TEMP                :
        case ID_AL_LOW_TEMP                 :
        case ID_AL_LOW_BOT_TEMP             :
        case ID_AL_HIGH_BOT_TEMP            :
        case ID_AL_MAIN_WATERINGR           :
        case ID_AL_PRE_WATERINGR            :
        case ID_AL_LOW_T_PRESS              :
        case ID_AL_HIGH_T_PRESS             :
        case ID_AL_LOW_INERT_GAS_PRESS      :
        case ID_AL_HIGH_INERT_GAS_PRESS     :
        case ID_AL_LOW_PRESS_VAC            :
        case ID_AL_HIGH_PRESS_VAC           :
        case ID_AL_LOW_VAPOUR_RETURN        :
        case ID_AL_HIGH_VAPOUR_RETURN       :
        case ID_AL_X_LOW_T_PRESS1           :
        case ID_AL_X_HIGH_T_PRESS1          :
        case ID_AL_X_LOW_T_PRESS2           :
        case ID_AL_X_HIGH_T_PRESS2          :
        case ID_AL_LOW_LOADRATE             :
        case ID_AL_HIGH_LOADRATE            :
        case ID_AL_LEVEL_CHANGE             :
        case ID_AL_DENS_DIFF                :
        case ID_AL_LOW_LINE_PRESS           :
        case ID_AL_HIGH_LINE_PRESS          :
        case ID_AL_HIGHHIGH_LINE_PRESS          :
        case ID_AL_SNS_OPEN_LOOP            :
        case ID_AL_LEVEL_SWITCH             :
        case ID_AL_LSWITCH_TEST             :
        case ID_AL_LSWITCH_FAILURE          :
        case ID_AL_SNS_SHORT_CIRCUIT        :
        case ID_AL_SNS_HART_COM_ERROR       :
        case ID_AL_SNS_HART_OPEN_LOOP       :
        case ID_AL_SNS_HART_SHORT_CIRCUIT   :
        case ID_AL_SNS_AIR_PURGE_FAILURE    :
        case ID_AL_SNS_CONCAL_ERROR         :
        case ID_AL_SNS_CONV_ERROR           :
        case ID_AL_IO_COM_ERROR             :
        case ID_AL_SC_COM_ERROR             :
        case ID_AL_MODBUS_COM_ERROR         :
        case ID_AL_MODBUS_INPUT_STATUS      :
        case ID_AL_WATER_DETECT             :
        case ID_AL_FUSE                     :
        case ID_AL_AC_VOLTAGE               :
        case ID_AL_LOW_VOLTAGE              :
        case ID_AL_LOW_VOLTAGE_1            :
        case ID_AL_LOW_VOLTAGE_2            :
        case ID_AL_HI_VOLTAGE               :
        case ID_AL_HI_VOLTAGE_1             :
        case ID_AL_HI_VOLTAGE_2             :
        case ID_AL_TWM_ELAPSED_TIME         :
        case ID_AL_TWM_LOW_SPEED            :
            AlarmTypeList.push_back(Key);
            break;
        case C_PROLIST_END:
            break;
        case C_PROLIST_START:
            {
                unsigned NumberOfIdNumbers = ConfigString.ReadLong(ErrorLine);
                for (unsigned Count = 0; NoError && Count < NumberOfIdNumbers; Count++) {
                    int PROIDNumber = ConfigString.ReadInteger(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        IdNumbers.push_back(PROIDNumber);
                    }
                }
            }
            break;
        case C_OBJECT_ID    :
            do {
                unsigned PROIDNumber = ConfigString.ReadInteger(ErrorLine, C_PROLIST_END);
                if (!ErrorLine) {
                    IdNumbers.push_back(PROIDNumber);
                }
            }while (!ErrorLine);
            if (ErrorLine == END_FOUND) {
                ErrorLine = 0;
            }
            NoError = !ErrorLine;
            break;
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_CTRL_END_COMMON));
    return (NoError);
}
//--------------------------------------------------------------------------- '

void PROControl::SetAlarmList(void) {
    switch (AlarmAlternative) {
    case C_CTRL_ALT_ALL      :
        {
            set<AlarmBasic *>::iterator APtrIt;
            for (APtrIt = AlarmBasic::AlarmSet.begin(); APtrIt != AlarmBasic::AlarmSet.end(); APtrIt++) {
                AlarmList.insert(*APtrIt);
            }
        }
        break;
    case C_CTRL_ALT_AL_TYPES :
        {
            set<AlarmBasic *>::iterator APtrIt;
            for (APtrIt = AlarmBasic::AlarmSet.begin(); APtrIt != AlarmBasic::AlarmSet.end(); APtrIt++) {
                for (unsigned j = 0; j < AlarmTypeList.size(); j++) {
                    if ((*APtrIt)->Type == AlarmTypeList[j]) {
                        AlarmList.insert(*APtrIt);
                    }
                }
            }
        }
        break;
    case C_CTRL_ALT_PRO_LIST :
        if (!PROList.empty()) {
            set<PRogramObjectBase *>::iterator pBIt;
            for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
                PRogramObject *TElement = (PRogramObject *)*pBIt;
                set<AlarmBasic *>::iterator pBIt;
                for (pBIt = TElement->CompleteAlarmInfoList.begin(); pBIt != TElement->CompleteAlarmInfoList.end(); pBIt++) {
                    AlarmBasic *AlPtr = *pBIt;
                    if (AlPtr) AlarmList.insert(AlPtr);
                }
            }
        }
        break;
    case C_CTRL_ALT_TYPE_PRO :
        if (!PROList.empty()) {
            set<PRogramObjectBase *>::iterator pBIt;
            for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
                PRogramObject *TElement = (PRogramObject *)*pBIt;
                set<AlarmBasic *>::iterator pBIt;
                for (pBIt = TElement->CompleteAlarmInfoList.begin(); pBIt != TElement->CompleteAlarmInfoList.end(); pBIt++) {
                    AlarmBasic *AlPtr = *pBIt;
                    if (AlPtr) {
                        bool Found = false;
                        for (unsigned j = 0; !Found && j < AlarmTypeList.size(); j++) {
                            if (AlPtr->Type == AlarmTypeList[j]) {
                                AlarmList.insert(AlPtr);
                                Found = true;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
}
//--------------------------------------------------------------------------- '
void PROControl::SetProList(void) {
    if (!IdNumbers.empty()) {
        PROList.clear();
        for (unsigned i = 0; i < IdNumbers.size(); i++) {
            PRogramObject *PROPtr = (PRogramObject *)FindPROFromIDNumber(IdNumbers[i]);
            if (PROPtr) {
                PROList.insert(PROPtr);
            } else {
                AnsiString InfoStr;
                InfoStr.cat_sprintf("PROControl IDNumber 0x%0x is incorrect. Line number: %i", IdNumbers[i], GetLineNumber());
                GiveConfigWarning(InfoStr);
            }
        }
        //delete []IdNumbers;
        //IdNumbers         = NULL;
    }
}

//--------------------------------------------------------------------------- '

void PROControl::UpdateRelay(void) {
#ifdef S2TXU
    OS_Use(&CtrlSema);
    if (!AlarmList.empty()) {
        int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim;
        GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
        if (ActiveAl) {
            if (PROWaterIngress::ObjectSet.empty()) {
                if (!(Priority & R_ACTIVATE1)) Activate(R_ACTIVATE1, RELAY_MSG_FREQUENCY, 500, 500);
            } else if (!(Priority & R_ACTIVATE3)) {
                Activate(R_ACTIVATE3, RELAY_MSG_FREQUENCY, 750, 250);
            }
        } else if (AcknowledgedAl) {
            if (!(Priority & R_ACTIVATE0)) {
                Activate(R_ACTIVATE0, RELAY_MSG_ON, 0, 0);
            }
        } else if (!(Priority & R_INACTIVE)) {
            DeActivate();
        }
    } else {
        if (!AlarmBasic::PROActiveAlarmList.isEmpty()) {
            if (PROWaterIngress::ObjectSet.empty()) { //EHSMark Must add Highlevel
                if (!(Priority & R_ACTIVATE1)) {
                    Activate(R_ACTIVATE1, RELAY_MSG_FREQUENCY, 500, 500);
                }
            } else if (!(Priority & R_ACTIVATE3)) {
                Activate(R_ACTIVATE3, RELAY_MSG_FREQUENCY, 750, 250);
            }
        } else if (!AlarmBasic::PROAcknowAlarmList.isEmpty()) {
            if (!(Priority & R_ACTIVATE0))    Activate(R_ACTIVATE0, RELAY_MSG_ON, 0, 0);
        } else if (!(Priority & R_INACTIVE)) {
            DeActivate();
        }
    }
    OS_Unuse(&CtrlSema);
#endif
}



void PROControl::Update(char Mode) {
#ifdef S2TXU
    OS_Use(&CtrlSema);
/*
    //Follow PROList
    if Active alarms and not AlarmSilence:
    1.  Active HHL / HL alarms: light           frequenc: 1
    2.  if AlarmList?
            Active alarms                   : light         frequenc: 1
    3.  Only Acknow alarms      : off
    else                                            : off
*/
    switch (Mode) {
    case BUZZER_TEST_ON:
    case BUZZER_TEST_OFF:
        break;
    case BUZZER_NO_TEST:
        UpdateRelay();
        break;
    }
    OS_Unuse(&CtrlSema);
#endif
}
//---------------------------------------------------------------------------


void PROControl::Activate(int Prio, U8 Cmd, int OnPeriod, int OffPeriod) {
    if (AlarmBasic::AlarmSound) {
        Priority  = Prio;
#ifndef WIN32
        GiveRelayDutyMessage(RelayIndex,Cmd,OnPeriod,OffPeriod);
#endif
    }

}
//---------------------------------------------------------------------------

void PROControl::DeActivate(void) {
    Priority = R_INACTIVE;
#ifndef WIN32
    GiveRelayDutyMessage(RelayIndex,RELAY_MSG_OFF,0,0);
#endif

}
//---------------------------------------------------------------------------

bool PROControl::GetOutputVal(bool &IsChange) {
    int AlStat = 0;
    bool IsActive = false;
    if (!AlarmList.empty()) {
        switch (DeactivateBy) {
        case C_CTRL_DE_ACKNOW  :
            GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
            AlStat    = ActiveAl;
            IsChange  = (PrevAlCnt != AlStat);
            PrevAlCnt = ActiveAl;
            break;
        case C_CTRL_DE_IDLE    :
            GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
            AlStat    = ActiveAl + AcknowledgedAl;
            IsChange  = (ActiveAl > PrevAlCnt);
            PrevAlCnt = ActiveAl;
            break;
        case C_CTRL_DE_VALUE   :
            GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
            AlStat    = OutsideLim;
            IsChange  = (OutsideLim > PrevAlCnt);
            PrevAlCnt = OutsideLim;
            break;
        case C_CTRL_DE_VAL_ENABLED:
            GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
            AlStat    = OutsideLimEnabled;
            IsChange  = (OutsideLimEnabled > PrevAlCnt);
            PrevAlCnt = OutsideLimEnabled;
            break;
        case C_CTRL_DE_SILENCE:
            GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
            if (AlarmBasic::AlarmSilence) {
                AlStat = 0;
            } else {
                AlStat = ActiveAl;
            }
            break;
        }
    } else {
        switch (DeactivateBy) {
        case C_CTRL_DE_IDLE         :
        case C_CTRL_DE_VALUE        :
        case C_CTRL_DE_ACKNOW       :
        case C_CTRL_DE_SILENCE      :
        case C_CTRL_DE_VAL_ENABLED  :
            break;
        }
    }
    switch (NormalState) {
    case C_CTRL_NS_UNPOWERED:
        break;
    case C_CTRL_NS_POWERED  :
        AlStat = !AlStat;
        break;
    }
    IsActive  = (bool)AlStat;
    return (IsActive);
}

