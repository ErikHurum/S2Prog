#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

///////////////////////////////////////////////////////////////////////
//
//  WagoIn object routines
//
///////////////////////////////////////////////////////////////////////

set<PRogramObjectBase *>ModbusCoilIn::ModbusSet;

ModbusCoilIn::ModbusCoilIn(bool pIsCreatedFromMultiple) {
    ModbusSet.insert(this);
    if ( pIsCreatedFromMultiple ) {
        unsigned newIDNumber    = (C_PRO_MODBUS_COIL_IN << 16) + ModbusSet.size() + 0x1000;

        if ( FindPROFromIDNumber(newIDNumber) ) {
            do {
                newIDNumber++;
            }while ( FindPROFromIDNumber(newIDNumber) );
        }
        IDNumber 		  = newIDNumber;
    } else {
        IDNumber 		  = 0;
    }
    DefaultId         	  = false;
    Type                  = C_PRO_MODBUS_COIL_IN;
    AlarmPtr              = NULL;
    RefIDNumber           = 0;
    ValueKey              = 0;
    IsCreatedFromMultiple = pIsCreatedFromMultiple;
    AutoReset             = false;
    NotInitiated          = true;
}

ModbusCoilIn::~ModbusCoilIn() {
}
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString ModbusCoilIn::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString = ModbusObject::MakeConfigString();

    if ( DefaultId ) {
        AnsiString ObjectIdStr;
        ObjectIdStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += TabStr1 + KeyWord(C_OBJECT_ID) + (AnsiString)ObjectIdStr;
    }
    if ( RefIDNumber ) {
        AnsiString ObjectIdStr;
        ObjectIdStr.cat_sprintf("0x%0x", RefIDNumber);
        LocalString += TabStr1 + KeyWord(C_REF_OBJECT_ID) + (AnsiString)ObjectIdStr;
    }
    if ( ValueKey ) {
        LocalString += TabStr1 + KeyWord(C_VALUE_KEY) + ValueKeyWord(ValueKey);
    }
    LocalString += TabStr1 + KeyWord(C_PRO_NAME) + Name;
    LocalString += TabStr1 + KeyWord(C_DESCRIPTION) + Description;
    if ( AlarmDelay ) {
        LocalString += TabStr1 + KeyWord(C_CTRL_AL_DELAY) + (AnsiString)AlarmDelay;
    }
    LocalString += TabStr1 + KeyWord(NormalState);
    if ( AutoReset ) {
        LocalString += TabStr1 + KeyWord(C_AUTORESET);
    }
    LocalString += TabStr1 + KeyWord(C_MODBUS_END) + CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------

bool ModbusCoilIn::LoadConfigString(TSNConfigString &ConfigString) {
    int ErrorLine = 0;
    bool NoError = true;
    if ( ModbusObject::LoadConfigString(ConfigString) ) {
        int Key;
        do {
            AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
            if ( ErrorLine ) {
                if ( ErrorLine != EOF ) {
                    GiveConfigWarning("Modbus Coil In", ErrorLine);
                }
            } else {
                Key = FindConfigKey(InputKeyWord);
                switch ( Key ) {
                default:
                    GiveConfigWarning("Modbus Coil In", InputKeyWord, ConfigString.LineCount);
                    break;
                case C_VALUE_KEY        :
                    {
                        AnsiString tempStr = ConfigString.NextWord(ErrorLine);
                        NoError = !ErrorLine;
                        if ( NoError ) {
                            ValueKey = FindValueConfigKey(tempStr);
                            if ( ValueKey == NOT_FOUND ) {
                                ErrorLine = ConfigString.LineCount;
                                NoError = false;
                                GiveConfigWarning("Modbus coil value", tempStr, ConfigString.LineCount);
                            }
                        }
                    }
                    break;
                case C_PRO_END_COMMON   :
                case C_PRO_END          :
                case C_CTRL_END_COMMON  :
                case C_CTRL_END         :
                    NoError = false;
                    break;
                case C_MODBUS_END       :
                    Key = C_MODBUS_END;
                    break;
                case C_PRO_NAME         :
                    Name = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_DESCRIPTION      :
                    Description = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_CTRL_NS_POWERED  :
                case C_CTRL_NS_UNPOWERED:
                    NormalState = Key;
                    break;
                case C_CTRL_AL_DELAY:
                    AlarmDelay = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_AUTORESET    :
                    AutoReset = true;
                    break;
                case C_OBJECT_ID    :
                    {
                        unsigned tmpIDNumber    = ConfigString.ReadInteger(ErrorLine);
                        if ( NoError ) {
                            DefaultId   = true;
                            tmpIDNumber = CheckAndCorrectId(tmpIDNumber);
                            unsigned ObjTypeId = tmpIDNumber >> 16;
                            if (  ObjTypeId != C_PRO_MODBUS_COIL_IN )  {
                                // Check that object ID type is correct
                                tmpIDNumber = (C_PRO_MODBUS_COIL_IN << 16) | (tmpIDNumber & 0xffff);
                                GiveConfigWarning("Modbus CoilIn IDNumber Error, Line " + AnsiString(ConfigString.LineCount) + "!");
                            } else {
                                if ( FindPROFromIDNumber(tmpIDNumber) ) {
                                    unsigned tmpOrgIDNumber = tmpIDNumber;
                                    do {
                                        ++tmpIDNumber;
                                    }while ( FindPROFromIDNumber(tmpIDNumber) );
                                    AnsiString IdNumStr;
                                    IdNumStr.cat_sprintf("CoilIn IDNumber changed from 0x%0X to 0x%0X", tmpOrgIDNumber, tmpIDNumber);
                                    GiveConfigWarning("Modbus CoilIn duplicate IDNumber line " + AnsiString(ConfigString.LineCount) + "!");
                                    GiveConfigWarning(IdNumStr);
                                } else {}
                            }
                            IDNumber = tmpIDNumber;
                        }
                    }
                    DefaultId = false;
                    NoError = !ErrorLine;
                    break;

                case C_REF_OBJECT_ID:
                    RefIDNumber = ConfigString.ReadInteger(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                }
            }
        }while ( NoError && (ErrorLine != EOF) && (Key != C_MODBUS_END) );
    }
    if ( NoError ) {
        if ( !IsCreatedFromMultiple ) {
            if ( !RefIDNumber ) {
                AlarmPtr  = new AlarmModbusInCoil(this, Name, Description);
                AlarmSet.insert(AlarmPtr);
                AddAlarms(CompleteAlarmInfoList);
            }
            ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel, RefIDNumber);
        }
    }
    return (NoError);
}


void ModbusCoilIn::SetProList(void) {
    if ( RefIDNumber ) {
        ObjectPtr = FindPROFromIDNumber(RefIDNumber);
        if ( ObjectPtr ) {
            if ( IsCreatedFromMultiple ) {
                Name = ObjectPtr->Name;
            }
        } else {
            AnsiString InfoStr;
            if ( IsCreatedFromMultiple ) {
                InfoStr.cat_sprintf("Created by ModbusMultiple(Line number %i): ModbusCoilIn RefIDNumber %i (0x%0x) is incorrect", LineNumber, RefIDNumber, RefIDNumber);
            } else {
                InfoStr.cat_sprintf("ModbusCoilIn RefIDNumber %i (0x%0x) is incorrect. Line Number %i", RefIDNumber, RefIDNumber, LineNumber);
            }
            GiveConfigWarning(InfoStr);


        }
        // PRogramObjectBase::FindObject(RefIDNumber);
    }
}
//---------------------------------------------------------------------------


void ModbusCoilIn::Update(void) {
    ModbusUnit *tmpPtr = FindUnit();
    if ( tmpPtr ) {
#if defined (ANWIN) || defined (ANTDUSIM)
        if ( NotInitiated ) {
#elif S2TXU
        if ( NotInitiated && OS_Time > 30000 ) {
#endif
            NotInitiated = false;
            InitiateCoils(tmpPtr);
        } else {
            tmpPtr->AccessDigitalSema.Acquire();
            if ( tmpPtr->HasNewDigitalValue(Channel) ) {
                bool tmpIsActive = tmpPtr->GetCoilIn(Channel);
                switch ( NormalState ) {
                case C_CTRL_NS_UNPOWERED:
                    break;
                case C_CTRL_NS_POWERED  :
                    tmpIsActive = !tmpIsActive;
                    break;
                }
                IsActive = tmpIsActive;
                if ( AlarmPtr ) {
                    AlarmPtr->Check();
                } else if ( ObjectPtr ) {
                    ObjectPtr->SetTimeStamp();
                    if (tmpPtr->NewDigitalIn(Channel,IsActive)) {
                        ObjectPtr->PutBitValue(ValueKey, 0, IsActive);
                    }
                    if ( AutoReset && tmpIsActive ) {
                        tmpPtr->SetInCoil(Channel, 0);
                        tmpPtr->SetPreviousState(Channel,false);
                    }else{
                        tmpPtr->SetPreviousState(Channel,IsActive);
                    }
                }
            }
            tmpPtr->AccessDigitalSema.Release();
        }
    }
}

ModbusCoilIn& ModbusCoilIn::operator = (ModbusCoilIn Src) {
    Name          = Src.Name;
    Description   = Src.Description;

    IPAddress     = Src.IPAddress;
    TCUAddress    = Src.TCUAddress;
    TCUPortNo     = Src.TCUPortNo;
    Address       = Src.Address;
    Channel       = Src.Channel;

    AlarmDelay    = Src.AlarmDelay;
    NormalState   = Src.NormalState;

    AlarmPtr      = Src.AlarmPtr;
    ObjectPtr     = Src.ObjectPtr;
    ValueKey      = Src.ValueKey;
    RefIDNumber   = Src.RefIDNumber;
    DefaultId     = Src.DefaultId;
    AutoReset     = Src.AutoReset;


    if ( (TCUAddress == CurrentDeviceAddress) && (CurrentDeviceId == DEVICE_TCU) ) {
        MyModbusSet.insert(this);
    }
    return *this;
}

void ModbusCoilIn::UpdateFromMultiple(unsigned pIdNumber, int pChannel) {
    Channel +=  pChannel;
    RefIDNumber  = pIdNumber;
    if ( !RefIDNumber ) {
        AlarmPtr  = new AlarmModbusInCoil(this, Name, Description);
        AlarmSet.insert(AlarmPtr);
        AddAlarms(CompleteAlarmInfoList);
    }
    ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel, RefIDNumber);

}

int ModbusCoilIn::GetObjectId(void) {
    return RefIDNumber;
}

AnsiString ModbusCoilIn::GetValueKey(void) {
    if ( ValueKey == SVT_NOT_DEFINED ) {
        return "Not defined";
    }
    return ValueKeyWord(ValueKey);
}

AnsiString ModbusCoilIn::GetRegisterType(void) {
    return "Status";
}


AnsiString ModbusCoilIn::GetRegisterValue(void) {
    AnsiString Result;
    if ( AlarmPtr ) {
        Result = LibGetValue(SVT_AL_STATE, AlarmPtr);
    } else {
        //Result = LibGetValue(ValueKey, ObjectPtr);
        ModbusUnit *tmpPtr = FindUnit();
        if ( tmpPtr ) {
            switch (NormalState) {
            case C_CTRL_NS_UNPOWERED:
                if ( tmpPtr->GetCoilIn(Channel) ) {
                    Result = "On";
                } else {
                    Result = "Off";
                }
                break;
            case C_CTRL_NS_POWERED :
                if ( tmpPtr->GetCoilIn(Channel) ) {
                    Result = "Off";
                } else {
                    Result = "On";
                }
                break;
            }

        } else {
            Result = "Error";
        }
    }
    return Result;
}

AlarmBasic* ModbusCoilIn::GetAlarmPtr(void) {
    return (AlarmBasic *)AlarmPtr;
}
/////////////////////////////////////////////////////////////////////////////////////

void ModbusCoilIn::InitiateCoils(ModbusUnit *UnitPtr) {
    if ( ObjectPtr ) {
        bool tmpIsActive;
        ObjectPtr->GetBitValue(ValueKey, 0, tmpIsActive);
        if ( AutoReset  ) {
            UnitPtr->InitInCoil(Channel, 0);
        } else {
            UnitPtr->InitInCoil(Channel, tmpIsActive);
        }
    }

}


void  ModbusCoilIn::SetCoil(bool newState) {
    ModbusUnit *tmpPtr = FindUnit();
    if ( tmpPtr   ) {
        tmpPtr->SetInCoil(Channel, newState);
    }
}



