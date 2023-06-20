#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
set<PRogramObjectBase *>ModbusRegBitOut::ModbusSet;

ModbusRegBitOut::ModbusRegBitOut(bool pIsCreatedFromMultiple) : ModbusRegisterOut(pIsCreatedFromMultiple, C_PRO_MODBUS_REG_BIT_OUT, false) {
    ModbusSet.insert(this);
    IDNumber             = (C_PRO_MODBUS_REG_BIT_OUT << 16) + ModbusSet.size();
    Type                 = C_PRO_MODBUS_REG_BIT_OUT;
    PulseTime            = 0;
    ActivatedTime        = clock();
    CurrentState         = 0;
    BitOffset            = 0;
    IsCreatedFromMultiple = pIsCreatedFromMultiple;
    isVolatile            = false;
}

ModbusRegBitOut::~ModbusRegBitOut() {
}


//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
//
//    ModbusRegBitOut 0   6   1   815   ObjectId 0x49F0001 Bit     0       Unpowered  Name WBDB-4     Description Failure      ModbusEnd
///////////////////////////////////////////////////////////////
AnsiString ModbusRegBitOut::MakeConfigString(int ExtraTabs) {
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
    if (isVolatile) {
        LocalString += TabStr1 + KeyWord(C_VOLATILE);
    }

    LocalString += TabStr1 + KeyWord(NormalState);
    LocalString += TabStr1 + KeyWord(C_CTRL_DEACTIVATE) + KeyWord(DeactivateBy);
    LocalString += TabStr1 + KeyWord(C_BIT_OFFSET) + (AnsiString)BitOffset;
    LocalString += TabStr1 + KeyWord(C_CTRL_PULSE_WIDTH) + (AnsiString)PulseTime;
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

bool ModbusRegBitOut::LoadConfigString(TSNConfigString &ConfigString) {

    int ErrorLine = 0;
    bool NoError = true;
    if (ModbusObject::LoadConfigString(ConfigString)) {
        int Key;
        do {
            AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            case C_OBJECT_ID_LIST:
            case C_OBJECT_ID     :
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
            case C_REF_OBJECT_ID :
                {
                    unsigned tmpIDNumber = ConfigString.ReadInteger(ErrorLine, C_PROLIST_END);
                    if (!ErrorLine) {
                        IdNumbers.push_back(tmpIDNumber);
                    }
                }
                break;
            case C_CTRL_AL_DELAY:
                AlarmDelay = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_VOLATILE:
                isVolatile = true;
                break;
            case C_CTRL_DEACTIVATE      :
                {
                    AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                    if (!ErrorLine) {
                        int tmpKey = FindConfigKey(TempStr);
                        switch (tmpKey) {
                        case C_CTRL_DE_ACKNOW       :
                        case C_CTRL_DE_IDLE         :
                        case C_CTRL_DE_VALUE        :
                        case C_CTRL_DE_SILENCE      :
                        case C_CTRL_DE_VAL_ENABLED  :
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
            case C_CTRL_NS_POWERED              :
            case C_CTRL_NS_UNPOWERED            :
                NormalState = Key;
                break;
            case C_CTRL_ALT_ALL                 :
            case C_CTRL_ALT_AL_TYPES            :
            case C_CTRL_ALT_PRO_LIST            :
            case C_CTRL_ALT_TYPE_PRO            :
                AlarmAlternative = Key;
                break;
            case ID_AL_OVERFILL                 :
            case ID_AL_HIGH_LEVEL               :
            case ID_AL_LOWLOW_LEVEL               :
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
            case ID_AL_LOW_VOLTAGE_1            :
            case ID_AL_LOW_VOLTAGE_2            :
            case ID_AL_HI_VOLTAGE_1             :
            case ID_AL_HI_VOLTAGE_2             :
            case ID_AL_TWM_ELAPSED_TIME         :
            case ID_AL_TWM_LOW_SPEED            :
                AlarmTypeList.push_back(Key);
                break;
            case C_CTRL_PULSE_WIDTH             :
                PulseTime = ConfigString.ReadInteger(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_BIT_OFFSET:
                BitOffset = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PRO_END_COMMON               :
            case C_PRO_END                      :
            case C_CTRL_END_COMMON              :
            case C_CTRL_END                     :
                NoError = false;
            case C_MODBUS_END                   :
                Key = C_MODBUS_END;
                break;
            default:
                GiveConfigWarning("ModbusRegBitOut", InputKeyWord, ConfigString.LineCount);
                NoError = false;
                break;

            }
        }while (NoError && (ErrorLine != EOF) && (Key != C_MODBUS_END));
    }
    if (NoError && !IsCreatedFromMultiple) {
        ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel, 0, isVolatile);
    }
    return (NoError);
}

//--------------------------------------------------------------------------- '

void ModbusRegBitOut::SetAlarmList(void) {
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
void ModbusRegBitOut::SetProList(void) {
    if (!IdNumbers.empty()) {
        PROList.clear();
        for (unsigned i = 0; i < IdNumbers.size(); i++) {
            PRogramObject *PROPtr = (PRogramObject *)FindPROFromIDNumber(IdNumbers[i]);
            if (PROPtr) {
                PROList.insert(PROPtr);
            } else {
                AnsiString InfoStr;
                if (IsCreatedFromMultiple) {
                    InfoStr.cat_sprintf("Created by ModbusMultiple (Line number %i): ModbusRegBitOut RefIDNumber %i (0x%0x) is incorrect", LineNumber, IdNumbers[i], IdNumbers[i]);
                } else {
                    InfoStr.cat_sprintf("ModbusRegBitOut RefIDNumber %i (0x%0x) is incorrect. Line Number %i", IdNumbers[i], IdNumbers[i], LineNumber);
                }
                GiveConfigWarning(InfoStr);
            }
        }
    }
}
//---------------------------------------------------------------------------

int ModbusRegBitOut::GetOutputVal(void) {
    int AlStat = 0;
    if (!AlarmList.empty()) {
        switch (DeactivateBy) {
        case C_CTRL_DE_ACKNOW  :
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
                AlStat = ActiveAl;
            }
            break;
        case C_CTRL_DE_IDLE    :
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
                AlStat = ActiveAl + AcknowledgedAl;
            }
            break;
        case C_CTRL_DE_VALUE   :
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
                AlStat = OutsideLim;
            }
            break;
        case C_CTRL_DE_VAL_ENABLED:
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
                AlStat = OutsideLimEnabled;
            }
            break;
        case C_CTRL_DE_SILENCE:
            {
                int ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled;
                GetAlarmTotals(AlarmList, ActiveAl, AcknowledgedAl, IdleAl, SuspAl, OutsideLim, OutsideLimEnabled);
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
    case C_CTRL_NS_POWERED  :
        AlStat = !AlStat;
        break;
    }
    return AlStat;
}

//---------------------------------------------------------------------------
void ModbusRegBitOut::Update(void) {
    ModbusUnit *tmpPtr = FindUnit();
    U16 alState  = GetOutputVal();
    if (tmpPtr) {
        U16 tmpReg = 0;
        if (isVolatile) {
            tmpReg = tmpPtr->GetRegister(Channel);
        } else {
            tmpReg = tmpPtr->GetOutputRegister(Channel);
        }
        U16 OrgReg = tmpReg;
        U16 MyBit     = 1 << BitOffset;
        if (alState) {
            tmpReg |= MyBit;
        } else {
            tmpReg &= ~MyBit;
        }
        if (tmpReg != OrgReg) {
            tmpPtr->SetRegister(Channel, tmpReg);
        }
    }

}

ModbusRegBitOut& ModbusRegBitOut::operator = (ModbusRegBitOut Src) {
    Name          = Src.Name;
    Description   = Src.Description;

    IPAddress     = Src.IPAddress;
    TCUAddress    = Src.TCUAddress;
    TCUPortNo     = Src.TCUPortNo;
    Address       = Src.Address;
    Channel       = Src.Channel;


    MinRange      = Src.MinRange;
    MaxRange      = Src.MaxRange;
    RegMax        = Src.RegMax;
    ValueKey      = Src.ValueKey;
    RefObjectId   = Src.RefObjectId;

    Scale             = Src.Scale;
    Offset            = Src.Offset;
    HasSign           = Src.HasSign;
    HasDecimalScaling = Src.HasDecimalScaling;
    ModbusDataFormat   = Src.ModbusDataFormat;
    HasRange          = Src.HasRange;
    DecimalPoint      = Src.DecimalPoint;
    DecimalScaling    = Src.DecimalScaling;

    BitOffset         = Src.BitOffset;
    AlarmDelay        = Src.AlarmDelay;
    NormalState       = Src.NormalState;
    RegMax            = Src.RegMax;
    DefaultId         = Src.DefaultId;
    //IdNumbers         = Src.IdNumbers; // Set from UpdateFromMultiple
    if ((TCUAddress == CurrentDeviceAddress) && (CurrentDeviceId == DEVICE_TCU)) {
        MyModbusSet.insert(this);
    }

    return *this;
}

void ModbusRegBitOut::UpdateFromMultiple(unsigned pIdNumber, int pChannel) {
    Channel +=  pChannel;
    IdNumbers.clear();
    IdNumbers.push_back(pIdNumber);  // Can only support one reference IDNumber currently
    ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel, 0, isVolatile);
}

int ModbusRegBitOut::GetObjectId(void) {
    if (!IdNumbers.empty()) {
        return IdNumbers[0];
    } else {
        return 0;
    }
}

AnsiString ModbusRegBitOut::GetRegisterType(void) {
    return "Bit offset:" + AnsiString(BitOffset);
}


AnsiString ModbusRegBitOut::GetValueKey(void) {
    return KeyWord(AlarmAlternative);
}

