#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

set<PRogramObjectBase *>ModbusCoilHistory::ModbusSet;

ModbusCoilHistory::ModbusCoilHistory(bool pIsCreatedFromMultiple) {
    ModbusSet.insert(this);
    IDNumber = (C_PRO_MODBUS_COIL_HIST << 16) + ModbusSet.size();
    Type = C_PRO_MODBUS_COIL_HIST;
    LogTime = clock();
    IsCreatedFromMultiple = pIsCreatedFromMultiple;
}

ModbusCoilHistory::~ModbusCoilHistory() {
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString ModbusCoilHistory::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString = ModbusObject::MakeConfigString();

    LocalString += TabStr1 + KeyWord(C_OBJECT_ID_LIST);
    set<PRogramObject *>::iterator pBIt;
    for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
        PRogramObject *Element = (PRogramObject *)*pBIt;
        int PROIDNumber = Element->IDNumber;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0X\t", PROIDNumber);
        LocalString += IdNumStr;
    }
    LocalString += TabStr1 + KeyWord(C_PROLIST_END);

    LocalString += TabStr1 + KeyWord(NormalState);
    LocalString += TabStr1 + KeyWord(C_CTRL_DEACTIVATE) + KeyWord(DeactivateBy);
    LocalString += TabStr1 + KeyWord(AlarmAlternative);

    for (unsigned j = 0; j < AlarmTypeList.size(); j++) {
        LocalString += TabStr1 + KeyWord(AlarmTypeList[j]);
    }
    if (AlarmDelay) {
        LocalString += TabStr1 + KeyWord(C_CTRL_AL_DELAY) + (AnsiString)AlarmDelay;
    }
    LocalString += TabStr1 + KeyWord(C_MODBUS_END) + CrLfStr;
    return (LocalString);
}
//---------------------------------------------------------------------------

bool ModbusCoilHistory::LoadConfigString(TSNConfigString &ConfigString) {
    int ErrorLine = 0;
    bool NoError = true;
    if (ModbusObject::LoadConfigString(ConfigString)) {
        int Key;
        do {
            AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            case C_OBJECT_ID_LIST:
            case C_OBJECT_ID :
                do {
                    unsigned tmpIDNumber = ConfigString.ReadInteger(ErrorLine, C_PROLIST_END);
                    if (!ErrorLine) {
                        IdNumbers.push_back(tmpIDNumber);
                    }
                }while (!ErrorLine);
                if (ErrorLine == END_FOUND) {
                    ErrorLine = 0;
                }
                NoError = !ErrorLine;
                break;
            case C_CTRL_AL_DELAY:
                AlarmDelay = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CTRL_DEACTIVATE :
                {
                    AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                    if (!ErrorLine) {
                        int tmpKey = FindConfigKey(TempStr);
                        switch (tmpKey) {
                        case C_CTRL_DE_ACKNOW :
                        case C_CTRL_DE_IDLE :
                        case C_CTRL_DE_VALUE :
                        case C_CTRL_DE_SILENCE :
                        case C_CTRL_DE_VAL_ENABLED:
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
            case C_CTRL_NS_POWERED :
            case C_CTRL_NS_UNPOWERED :
                NormalState = Key;
                break;
            case C_CTRL_ALT_ALL :
            case C_CTRL_ALT_AL_TYPES :
			case C_CTRL_ALT_PRO_LIST :
			case C_CTRL_ALT_TYPE_PRO :
				AlarmAlternative = Key;
				break;
			case ID_AL_OVERFILL                 :
			case ID_AL_HIGH_LEVEL               :
			case ID_AL_LOWLOW_LEVEL             :
			case ID_AL_LOW_LEVEL                :
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
			case ID_AL_SNS_HART_OPEN_LOOP       :
			case ID_AL_SNS_HART_SHORT_CIRCUIT   :
			case ID_AL_SNS_HART_COM_ERROR       :
			case ID_AL_SNS_AIR_PURGE_FAILURE    :
			case ID_AL_X_LOW_T_PRESS1           :
            case ID_AL_X_HIGH_T_PRESS1          :
            case ID_AL_X_LOW_T_PRESS2           :
            case ID_AL_X_HIGH_T_PRESS2          :
            case ID_AL_SNS_ERROR                :
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
            case C_PRO_END_COMMON :
            case C_PRO_END :
            case C_CTRL_END_COMMON :
            case C_CTRL_END :
                NoError = false;
            case C_MODBUS_END :
                Key = C_MODBUS_END;
                break;
            default:
                GiveConfigWarning("ModbusCoilHistory", InputKeyWord, ConfigString.LineCount);
                NoError = false;
                break;

            }
        }while (NoError && (ErrorLine != EOF) && (Key != C_MODBUS_END));
    }
    if (NoError && !IsCreatedFromMultiple ) {
        ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel);
    }
    return (NoError);
}

//--------------------------------------------------------------------------- '

void ModbusCoilHistory::SetAlarmList(void) {
    switch (AlarmAlternative) {
    case C_CTRL_ALT_ALL :
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
            set<PRogramObject *>::iterator pBIt;
            for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
                PRogramObject *TElement = (PRogramObject *)*pBIt;
                set<AlarmBasic *>::iterator APtrIt;
                for (APtrIt = TElement->CompleteAlarmInfoList.begin(); APtrIt != TElement->CompleteAlarmInfoList.end(); APtrIt++) {
                    for (unsigned j = 0; j < AlarmTypeList.size(); j++) {
                        if ((*APtrIt)->Type == AlarmTypeList[j]) {
                            AlarmList.insert(*APtrIt);
                        }
                    }
                }
            }
        }
        break;
    case C_CTRL_ALT_TYPE_PRO :
        if (!PROList.empty()) {
            set<PRogramObject *>::iterator pBIt;
            for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
                PRogramObject *TElement = (PRogramObject *)*pBIt;
                set<AlarmBasic *>::iterator APtrIt;
                for (APtrIt = TElement->CompleteAlarmInfoList.begin(); APtrIt != TElement->CompleteAlarmInfoList.end(); APtrIt++) {
                    AlarmBasic *AlPtr = *APtrIt;
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

//---------------------------------------------------------------------------
void ModbusCoilHistory::SetProList(void) {
    if (!IdNumbers.empty()) {
        PROList.clear();
        for (unsigned i = 0; i < IdNumbers.size(); i++) {
            PRogramObject *PROPtr = (PRogramObject *)FindPROFromIDNumber(IdNumbers[i]);
            if (PROPtr) {
                PROList.insert(PROPtr);
            } else {
                AnsiString InfoStr;
                InfoStr.cat_sprintf("ModbusCoilHistory IDNumber 0x%0x is incorrect", IdNumbers[i]);
                GiveConfigWarning(InfoStr);
            }
        }
    }
}

//---------------------------------------------------------------------------

bool ModbusCoilHistory::GetOutputVal(void) {
    int AlStat = 0;
    if (!AlarmList.empty()) {
        switch (DeactivateBy) {
        case C_CTRL_DE_ACKNOW :
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled);
                AlStat = ActiveAl;
            }
            break;
        case C_CTRL_DE_IDLE :
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled);
                AlStat = ActiveAl + AcknowledgedAl;
            }
            break;
        case C_CTRL_DE_VALUE :
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled);
                AlStat = OutsideLim;
            }
            break;
        case C_CTRL_DE_VAL_ENABLED:
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled);
                AlStat = OutsideLimEnabled;
            }
            break;
        case C_CTRL_DE_SILENCE:
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim,OutsideLimEnabled);
                if (AlarmBasic::AlarmSilence) {
                    AlStat = 0;
                } else {
                    AlStat = ActiveAl;
                }
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
    case C_CTRL_NS_POWERED :
        AlStat = !AlStat;
        break;
    }
    return AlStat;
}

void ModbusCoilHistory::Update(void) {
    clock_t CurrentTime = clock();
    if (CurrentTime >= LogTime + TSNUart::Channels[TCUPortNo]->LogTime) {
        LogTime = clock();
        ModbusUnit *tmpPtr = FindUnit();
        if (tmpPtr) {
            bool alState = GetOutputVal();
            tmpPtr->SetCoilHistory(Channel, alState, TSNUart::Channels[TCUPortNo]->LogEntries);
        }
    }
}
