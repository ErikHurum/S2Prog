#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif



///////////////////////////////////////////////////////////////////////
//
//  WagoOutmA object routines
//
///////////////////////////////////////////////////////////////////////

set<PRogramObjectBase *>ModbusRegister::ModbusSet;

ModbusRegister::ModbusRegister(void) {
    ModbusSet.insert(this);
    IDNumber        = (C_PRO_MODBUS_REG << 16) + ModbusSet.size();
    Type            = C_PRO_MODBUS_REG;


    TCUAddress          = 0;
    TCUPortNo           = 0;
    Address             = 0;
    Channel             = 0;
    RefObjectId         = 0;
    MinRange            = 0.0;
    MaxRange            = 1.0;
    RegMax              = 0xffff;
    Scale               = 1.0;
    Offset              = 0.0;
    HasSign             = false;
    HasDecimalScaling   = false;
    ModbusDataFormat    = Float_None;
    HasRange            = false;
    DecimalPoint        = 0;
    DecimalScaling      = 0.0;
}

ModbusRegister::~ModbusRegister() {
    ModbusSet.erase(this);
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString ModbusRegister::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString = ModbusObject::MakeConfigString();
    AnsiString ObjectIdStr;
    ObjectIdStr.cat_sprintf("0x%0x", RefObjectId);

    LocalString += TabStr1 + KeyWord(C_REF_OBJECT_ID) + (AnsiString)ObjectIdStr;
    LocalString += TabStr1 + KeyWord(C_VALUE_KEY) + ValueKeyWord(ValueKey);
    switch (ModbusDataFormat) {
    case String10 :
        LocalString += TabStr1 + KeyWord(C_STRING10);
        break;
    case String20 :
        LocalString += TabStr1 + KeyWord(C_STRING20);
        break;
    case Float_L_Endian:
        LocalString += TabStr1 + KeyWord(C_FLOAT_LITTLE_ENDIAN);
        break;
    case Float_B_Endian   :
        LocalString += TabStr1 + KeyWord(C_FLOAT_BIG_ENDIAN);
        break;
    case Float_B_Endian_ByteSwap:
        LocalString += TabStr1 + KeyWord(C_FLOAT_B_END_BYTE_SWAP);
        break;
    case Float_L_Endian_ByteSwap :
        LocalString += TabStr1 + KeyWord(C_FLOAT_L_END_BYTE_SWAP);
        break;
    case Float_None       :
        {
            if (HasDecimalScaling) {
                LocalString += TabStr1 + KeyWord(C_DECIMAL_POINT) + (AnsiString)DecimalPoint;
            }
            if (HasRange) {
                LocalString += TabStr1 + KeyWord(C_RANGE);
                LocalString += FloatToAnsiString(MinRange, 10, 4);
                LocalString += TabStr1 + FloatToAnsiString(MaxRange, 10, 4);
            }
            if (HasSign) {
                LocalString += TabStr1 + KeyWord(C_SIGNED);
            } else {
                LocalString += TabStr1 + KeyWord(C_UNSIGNED);
            }
            AnsiString MaxRegStr;
            MaxRegStr.cat_sprintf("0x%0x", RegMax);
            LocalString += MaxRegStr;
        }
        break;
    }
    LocalString += TabStr1 + KeyWord(C_MODBUS_END) + CrLfStr;
    return (LocalString);
}
//---------------------------------------------------------------------------
bool ModbusRegister::LoadConfigString(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    int ErrorLine = 0;
    bool NoError = true;
    if (ModbusObject::LoadConfigString(ConfigString)) {
        int Key;
        do {
            AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
            if (ErrorLine) {
                if (ErrorLine != EOF) {
                    GiveConfigWarning("Modbus Register", ErrorLine);
                }
            } else {
                Key = FindConfigKey(InputKeyWord);
                switch (Key) {
                default:
                    NoError = false;
                    GiveConfigWarning("Modbus Register", InputKeyWord, ConfigString.LineCount);
                    break;
                case C_VALUE_KEY        :
                    {
                        AnsiString tempStr = ConfigString.NextWord(ErrorLine);
                        NoError = !ErrorLine;
                        if (NoError) {
                            ValueKey = FindValueConfigKey(tempStr);
                            if (ValueKey == NOT_FOUND) {
                                ErrorLine = ConfigString.LineCount;
                                NoError = false;
                                GiveConfigWarning("Modbus Register value", tempStr, ConfigString.LineCount);
                            }
                        }
                    }
                    break;
                case C_PRO_END_COMMON   :
                case C_PRO_END          :
                case C_CTRL_END_COMMON  :
                case C_CTRL_END         :
                    NoError = false;
                case C_MODBUS_END       :
                    Key = C_MODBUS_END;
                    break;
                case C_PRO_NAME         :
                    Name = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_UNSIGNED         :
                    HasSign = false;
                    RegMax  = ConfigString.ReadInteger(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_SIGNED           :
                    HasSign = true;
                    RegMax  = ConfigString.ReadInteger(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                case C_RANGE:
                    HasRange = true;
                    MinRange = ConfigString.ReadDouble(ErrorLine);
                    if (!ErrorLine) {
                        MaxRange = ConfigString.ReadDouble(ErrorLine);
                        if (MinRange == MaxRange) {
                            HasRange = false;
                            GiveConfigWarning("Modbus Register MinRange and MaxRange can not be equal!", ConfigString.LineCount);
                        }
                    }
                    NoError = !ErrorLine;
                    break;
                case C_DECIMAL_POINT:
                    HasDecimalScaling = true;
                    DecimalPoint = ConfigString.ReadInteger(ErrorLine);
                    if (ErrorLine) {
                        NoError = false;
                    } else {
                        DecimalScaling = pow(10.0, DecimalPoint);
                    }
                    break;
                case C_FLOAT_BIG_ENDIAN:
                    ModbusDataFormat = Float_B_Endian;
                    break;
                case C_FLOAT_LITTLE_ENDIAN:
                    ModbusDataFormat = Float_L_Endian;
                    break;
                case C_FLOAT_B_END_BYTE_SWAP:
                    ModbusDataFormat = Float_B_Endian_ByteSwap;
                    break;
                case C_FLOAT_L_END_BYTE_SWAP:
                    ModbusDataFormat = Float_L_Endian_ByteSwap;
                    break;
                case C_INT_BIG_ENDIAN:
                    ModbusDataFormat = Integer_B_Endian;
                    break;
                case C_INT_LITTLE_ENDIAN:
                    ModbusDataFormat = Integer_L_Endian;
                    break;
                case C_INT_B_END_BYTE_SWAP:
                    ModbusDataFormat = Integer_B_Endian_ByteSwap;
                    break;
                case C_INT_L_END_BYTE_SWAP:
                    ModbusDataFormat = Integer_L_Endian_ByteSwap;
                    break;
                case C_STRING10:
                    ModbusDataFormat = String10;
                    break;
                case C_STRING20:
                    ModbusDataFormat = String20;
                    break;
                case C_REF_OBJECT_ID:
                case C_OBJECT_ID:
                    RefObjectId = ConfigString.ReadInteger(ErrorLine);
                    NoError = !ErrorLine;
                    break;
                }
            }
        }while (NoError && (ErrorLine != EOF) && (Key != C_MODBUS_END));
        if (HasDecimalScaling && !ModbusDataFormat && HasRange) {
            float MaxVal;
            float MinVal;
            if (HasSign) {
                MaxVal = float(RegMax);
                MinVal = float(-RegMax);
            } else {
                MaxVal = float(unsigned(RegMax));
                MinVal = 0.0;
            }

            if (DecimalScaling * MaxRange > MaxVal) {
                GiveConfigWarning("Modbus Register. Overflow of integer aritmetic when checking max range against decimal point! Line number " + ConfigString.GetCurrentLineStr());
                NoError = false;
            } else if (DecimalScaling * MinRange < MinVal) {
                GiveConfigWarning("Modbus Register. Overflow of integer aritmetic when checking min range against decimal point! Line number " + ConfigString.GetCurrentLineStr());
                NoError = false;
            }
        }
    }
    if (NoError) {
        if (HasRange) {
            CalculateScale();
        }
        if (HasSign) {
            //Offset -= Scale*((float)(RegMax+1));
        }
        if (!IsCreatedFromMultiple) {
            ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel, RefObjectId);
            if (ModbusDataFormat) { // Check if two registers are required
                ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel + 1, RefObjectId);
            }
        }
    }
    return (NoError);
}
//---------------------------------------------------------------------------


void ModbusRegister::SetProList(void) {
    ObjectPtr = (PRogramObject *)FindPROFromIDNumber(RefObjectId);
    if (!ObjectPtr) {
        AnsiString InfoStr;
        if (IsCreatedFromMultiple) {
            InfoStr.cat_sprintf("Created by ModbusMultiple (Line number %i): ModbusRegister RefIDNumber %i (0x%0x) is incorrect", LineNumber, RefObjectId,RefObjectId);
        } else {
            InfoStr.cat_sprintf("ModbusRegister RefIDNumber %i (0x%0x) is incorrect. Line Number %i", RefObjectId, RefObjectId,LineNumber);
        }
        GiveConfigWarning(InfoStr);
    }

}

//---------------------------------------------------------------------------

int ModbusRegister::GetOutputVal(void) {
    if (ObjectPtr) {
        float OutVal;
        int DecPnt, Unit; // These variables are not used

        int Status = ObjectPtr->GetValue(ValueKey, 0, OutVal, DecPnt, Unit);
        if (HasRange) {
            if (OutVal < MinRange) {
                OutVal = MinRange;
            } else if (OutVal > MaxRange) {
                OutVal = MaxRange;
            }
        }
        if (HasDecimalScaling) {
            float rValue = OutVal * DecimalScaling;
            return (floor(rValue) + 0.5)> rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
        } else {
            float rValue = Scale * OutVal + MinRange;
            return (floor(rValue) + 0.5)> rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
        }
    }
    return 0;
}

void  ModbusRegister::Update(void) {
    ModbusUnit *tmpPtr = FindUnit();
    if (tmpPtr) {
        U16 OutVal    = (U16)GetOutputVal();
        tmpPtr->SetRegister(Channel, OutVal);
    }
}

void ModbusRegister::SetRefObjectId(unsigned pRefObjectId) {
    RefObjectId = pRefObjectId;
}

int ModbusRegister::GetObjectId(void) {
    return RefObjectId;
}

AnsiString ModbusRegister::GetValueKey(void) {
    return ValueKeyWord(ValueKey);
}

AnsiString ModbusRegister::GetRegisterType(void) {
    AnsiString RegType;
    switch(ModbusDataFormat){
    case Integer_L_Endian_ByteSwap:
    case Integer_L_Endian:
    case Integer_B_Endian_ByteSwap:
    case Integer_B_Endian:
        RegType = "Integer32";
        break;
    case Float_L_Endian_ByteSwap:
    case Float_L_Endian:
    case Float_B_Endian_ByteSwap:
    case Float_B_Endian:
         RegType = "Floating point";
         break;
    case Float_None:
        if (DecimalPoint){
            RegType = "Decimal point:" + AnsiString(DecimalPoint);
        }else{
            RegType = "Normal";
        }
        break;
    case String10 :
        RegType = KeyWord(C_STRING10);
        break;
    case String20 :
        RegType = KeyWord(C_STRING20);
        break;

    }
    return RegType;
}
