#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif
set<PRogramObjectBase *>ModbusRegBitIn::ModbusSet;

ModbusRegBitIn::ModbusRegBitIn(bool pIsCreatedFromMultiple) : ModbusRegisterIn(pIsCreatedFromMultiple, C_PRO_MODBUS_REG_BIT_IN, false) {
	ModbusSet.insert(this);
    if (pIsCreatedFromMultiple) {
        unsigned newIDNumber    = (C_PRO_MODBUS_REG_BIT_IN << 16) + ModbusSet.size()+0x1000;

        if (FindPROFromIDNumber(newIDNumber)) {
            do {
                newIDNumber++;
            }while (FindPROFromIDNumber(newIDNumber));
        }
        IDNumber = newIDNumber;
    }
	BitOffset   = 0;
    AlarmDelay  = 0;
    NormalState = 0;
    RegMax      = 0x01;
    DefaultId   = true;
    AlarmPtr   = NULL;
    ObjectPtr  = NULL;
}

ModbusRegBitIn::~ModbusRegBitIn() {
}


//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
//
//    ModbusRegBitIn 0   6   1   815   ObjectId 0x49F0001 Bit     0       Unpowered  Name WBDB-4     Description Failure      ModbusEnd
///////////////////////////////////////////////////////////////
AnsiString ModbusRegBitIn::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString = ModbusObject::MakeConfigString();

    if (DefaultId) {
        AnsiString ObjectIdStr;
        ObjectIdStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += TabStr1 + KeyWord(C_MY_OBJECT_ID) + ObjectIdStr;
    }

    if (PROList.size() > 1) {
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
    } else {
        PRogramObject *Element = (PRogramObject *)*PROList.begin();
		int PROIDNumber = Element->IDNumber;
		LocalString += TabStr1 + KeyWord(C_OBJECT_ID);
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0X\t", PROIDNumber);
        LocalString += IdNumStr;
    }
    if (ValueKey) {
        LocalString += TabStr1 + KeyWord(C_VALUE_KEY) + ValueKeyWord(ValueKey);
    }
    {
        AnsiString BitOffsetStr;
        BitOffsetStr.cat_sprintf("%2i", BitOffset);
        LocalString += TabStr1 + KeyWord(C_BIT_OFFSET) + BitOffsetStr;
    }
    LocalString += TabStr1 + KeyWord(C_PRO_NAME) + Name;
    LocalString += TabStr1 + KeyWord(C_DESCRIPTION) + Description;
    if (AlarmDelay) {
        LocalString += TabStr1 + KeyWord(C_CTRL_AL_DELAY) + (AnsiString)AlarmDelay;
    }
    LocalString += TabStr1 + KeyWord(NormalState);

    LocalString += TabStr1 + KeyWord(C_MODBUS_END) + CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------

bool ModbusRegBitIn::LoadConfigString(TSNConfigString &ConfigString) {

    SetLineNumber(ConfigString.LineCount);
    int ErrorLine = 0;
    bool NoError = true;
    if (ModbusObject::LoadConfigString(ConfigString)) {
        int Key;
        do {
            AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
            if (ErrorLine) {
                if (ErrorLine != EOF) {
                    GiveConfigWarning("Modbus RegBitIn", ErrorLine);
                }
            } else {
                Key = FindConfigKey(InputKeyWord);
                switch (Key) {
                default:
                    GiveConfigWarning("Modbus RegBitIn", InputKeyWord, ConfigString.LineCount);
                    break;
                case C_VALUE_KEY :
                    {
                        AnsiString tempStr = ConfigString.NextWord(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            ValueKey = FindValueConfigKey(tempStr);
                            if (ValueKey == NOT_FOUND) {
                                ErrorLine = ConfigString.LineCount;
                                NoError = false;
                                GiveConfigWarning("Modbus RegBitIn value", InputKeyWord, ConfigString.LineCount);
                            }
                        }
                    }
                    break;
                case C_PRO_END_COMMON :
                case C_PRO_END :
                case C_CTRL_END_COMMON :
                case C_CTRL_END :
                    NoError = false;
                    break;
                case C_MODBUS_END :
                    Key = C_MODBUS_END;
                    break;
                case C_PRO_NAME :
                    Name = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_DESCRIPTION :
                    Description = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_CTRL_NS_POWERED :
                case C_CTRL_NS_UNPOWERED:
                    NormalState = Key;
                    break;
                case C_CTRL_AL_DELAY:
                    AlarmDelay = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_BIT_OFFSET:
                    BitOffset = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_MY_OBJECT_ID :
                    {
                        unsigned tmpIDNumber    = ConfigString.ReadInteger(ErrorLine);
                        if (NoError) {
							unsigned ObjTypeId = tmpIDNumber >> 16;
                            if ((ObjTypeId != C_PRO_MODBUS_REG_BIT_IN)) {
                                IDNumber = (C_PRO_MODBUS_REG_BIT_IN << 16) | (tmpIDNumber & 0xffff);
                                GiveConfigWarning("Modbus RegBitIn IDNumber Err", ConfigString.LineCount);
                            } else {
                                if (FindPROFromIDNumber(tmpIDNumber)) {
                                    unsigned tmpOrgIDNumber = tmpIDNumber;
									do {
                                        tmpIDNumber++;
                                    }while (FindPROFromIDNumber(tmpIDNumber));
                                    AnsiString IdNumStr;
									IdNumStr.cat_sprintf("RegBitIn IDNumber changed from 0x%0X to 0x%0X", tmpOrgIDNumber, tmpIDNumber);
									GiveConfigWarning("RegBitIn duplicate IDNumber in line "+ AnsiString(ConfigString.LineCount)+"!");
                                    GiveConfigWarning(IdNumStr);
								}
								IDNumber = tmpIDNumber;
							}
                        }
                    }
                    DefaultId = false;
                    NoError = !ErrorLine;
                    break;
                case C_OBJECT_ID_LIST:
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
                case C_OBJECT_ID:
                case C_REF_OBJECT_ID:
                    {
                        RefObjectId = ConfigString.ReadInteger(ErrorLine);
                        NoError = !ErrorLine;
                        if (!ErrorLine) {
                            IdNumbers.push_back(RefObjectId);
                        }
                    }
                    break;
                }
            }
        }while (NoError && (ErrorLine != EOF) && (Key != C_MODBUS_END));
    }
    if (NoError) {
        if (( IDNumber >> 16  ) != C_PRO_MODBUS_REG_BIT_IN) {
            unsigned newIDNumber    = (C_PRO_MODBUS_REG_BIT_IN << 16) + ModbusSet.size();

            if (FindPROFromIDNumber(newIDNumber)) {
                do {
                    newIDNumber++;
                }while (FindPROFromIDNumber(newIDNumber));
            }
            IDNumber = newIDNumber;
        }
        if (!IsCreatedFromMultiple) {
            if (!RefObjectId) {
                AlarmPtr = new AlarmModbusInCoil(this, Name, Description);
                AlarmSet.insert(AlarmPtr);
                AddAlarms(CompleteAlarmInfoList);
            }
            ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel);
        }
    }
    return (NoError);
}

//---------------------------------------------------------------------------
void ModbusRegBitIn::SetProList(void) {
    for (unsigned i = 0; i < IdNumbers.size(); i++) {
        PRogramObject *PROPtr = (PRogramObject *)FindPROFromIDNumber(IdNumbers[i]);
        if (PROPtr) {
            PROList.insert(PROPtr);
            if (IsCreatedFromMultiple) {
                Name = PROPtr->Name;
            }
		} else {
			AnsiString InfoStr;
            if (IsCreatedFromMultiple) {
                InfoStr.cat_sprintf("Created by ModbusMultiple (Line number %i): ModbusRegBitIn RefIDNumber %i (0x%0x) is incorrect", LineNumber, RefObjectId,RefObjectId);
            } else {
                InfoStr.cat_sprintf("ModbusRegBitIn RefIDNumber %i (0x%0x) is incorrect. Line Number %i", RefObjectId, RefObjectId,LineNumber);
            }
        }
    }
    if (IdNumbers.size() == 1) {
        ObjectPtr = (PRogramObject *)FindPROFromIDNumber(IdNumbers[0]);
    }


}
//---------------------------------------------------------------------------
void ModbusRegBitIn::Update(void) {
    ModbusUnit *tmpPtr = FindUnit();

    if (tmpPtr && tmpPtr->HasNewValue(Channel)) {
        U16 rInVal = tmpPtr->GetRegister(Channel);

        bool tmpIsActive = (rInVal >> BitOffset) & 1;
        switch (NormalState) {
        case C_CTRL_NS_UNPOWERED:
            break;
        case C_CTRL_NS_POWERED :
            tmpIsActive = !tmpIsActive;
            break;
        }
        IsActive = tmpIsActive;
        if (AlarmPtr) {
            AlarmPtr->Check();
        }
        if (!PROList.empty()) {
            clock_t tm = clock();
            set<PRogramObject *>::iterator pBIt;

            for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
                PRogramObject *ObjectPtr = (PRogramObject *)*pBIt;
                ObjectPtr->TimeStamp = tm;
                ObjectPtr->PutFloatValue(ValueKey, float(tmpIsActive));
            }
        }
    }
}

ModbusRegBitIn& ModbusRegBitIn::operator = (ModbusRegBitIn Src) {
    Name              = Src.Name;
    Description       = Src.Description;

    IPAddress         = Src.IPAddress;
    TCUAddress        = Src.TCUAddress;
    TCUPortNo         = Src.TCUPortNo;
    Address           = Src.Address;
    Channel           = Src.Channel;


    MinRange          = Src.MinRange;
    MaxRange          = Src.MaxRange;
    RegMax            = Src.RegMax;
    ValueKey          = Src.ValueKey;
    RefObjectId       = Src.RefObjectId;

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
    if ((TCUAddress==CurrentDeviceAddress) && (CurrentDeviceId == DEVICE_TCU)) {
        MyModbusSet.insert(this);
    }

    return *this;
}

void ModbusRegBitIn::UpdateFromMultiple(unsigned pIdNumber, int pChannel) {
    Channel     +=  pChannel;
    RefObjectId  = pIdNumber;
    IdNumbers.push_back(RefObjectId);
    if (!RefObjectId) {
        AlarmPtr = new AlarmModbusInCoil(this, Name, Description);
        AlarmSet.insert(AlarmPtr);
        AddAlarms(CompleteAlarmInfoList);
    }
    ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel, RefObjectId);
}

int ModbusRegBitIn::GetObjectId(void)
{
    if (RefObjectId) {
        return RefObjectId;
    }else{
        return IDNumber;
    }
}

AnsiString ModbusRegBitIn::GetRegisterType(void) {
    return "Bit offset:" + AnsiString(BitOffset);
}

AnsiString ModbusRegBitIn::GetRegisterValue(void) {
    AnsiString Result;
    if (ObjectPtr) {
        Result = LibGetValue(ValueKey, ObjectPtr);
        if (!Result.IsEmpty()) {
            switch (NormalState) {
            case C_CTRL_NS_UNPOWERED:
                break;
            case C_CTRL_NS_POWERED :
                if (Result[1] == '0' ) {
                    Result[1] = '1';
                } else {
                    Result[1] = '0';
                }
                break;
            }
        }

	} else if ( AlarmPtr ){
		Result = LibGetValue(SVT_AL_STATE, AlarmPtr);
	} else {
		Result = "Multiple";
	}
	return Result;
}
