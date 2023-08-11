#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

set<PRogramObjectBase *>ModbusRegisterIn::ModbusSet;


ModbusRegisterIn::ModbusRegisterIn(bool pIsCreatedFromMultiple, int ModuleType, bool InsertInSet) {
	NotInitiated = true;

	if (InsertInSet) {
		ModbusSet.insert(this);
	}
	IDNumber    = (ModuleType << 16) + ModbusSet.size();
	Type        = ModuleType;
    IsCreatedFromMultiple = pIsCreatedFromMultiple;
}

ModbusRegisterIn::~ModbusRegisterIn() {
}


//---------------------------------------------------------------------------
void ModbusRegisterIn::CalculateScale(void) {
    Scale = (MaxRange - MinRange) / (RegMax - 0);
    Offset = MaxRange - Scale * float(RegMax);
}

void ModbusRegisterIn::Update(void) {
    ModbusUnit *tmpPtr = FindUnit();
    if (tmpPtr) {
#if defined (ANWIN) || defined (ANTDUSIM)
        if (NotInitiated) {
#elif S2TXU
        if (NotInitiated && OS_Time > 10000) {
#endif
            NotInitiated = false;
            InitiateHoldingRegisters(tmpPtr);
        } else {
            if (tmpPtr->HasNewValue(Channel)) {
                int   intValue;
                float Value;
                switch (ModbusDataFormat) {
                case Float_B_Endian:
                    {
                        U16 *ValuePtr = (U16 *)&Value;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel + 1);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel);
                    }
                    break;
                case Float_B_Endian_ByteSwap:
                    {
                        U16 *ValuePtr = (U16 *)&Value;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel + 1, true);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel, true);
                    }
                    break;
                case Float_L_Endian:
                    {
                        U16 *ValuePtr = (U16 *)&Value;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel, true);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel + 1, true);
                    }
                    break;
                case Float_L_Endian_ByteSwap:
                    {
                        U16 *ValuePtr = (U16 *)&Value;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel + 1);
                    }
                    break;
                case Integer_B_Endian:
                    {
                        U16 *ValuePtr = (U16 *)&intValue;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel + 1);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel);
                        Value       = intValue;
                    }
                    break;
                case Integer_B_Endian_ByteSwap:
                    {
                        U16 *ValuePtr = (U16 *)&intValue;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel + 1, true);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel, true);
                        Value       = intValue;
                    }
                    break;
                case Integer_L_Endian:
                    {
                        U16 *ValuePtr = (U16 *)&intValue;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel, true);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel + 1, true);
                        Value       = intValue;
                    }
                    break;
                case Integer_L_Endian_ByteSwap:
                    {
                        U16 *ValuePtr = (U16 *)&intValue;
                        ValuePtr[0] = tmpPtr->GetRegister(Channel);
                        ValuePtr[1] = tmpPtr->GetRegister(Channel + 1);
                        Value       = intValue;
                    }
                    break;
                case Float_None:
                    {
                        if (HasDecimalScaling) {
                            U16 rInVal = tmpPtr->GetRegister(Channel);
                            float InVal = HasSign ? ((float)(I16)rInVal) : (float)rInVal;
                            Value = InVal / DecimalScaling;
                        } else {
                            U16 rInVal = tmpPtr->GetRegister(Channel);
                            float InVal = HasSign ? ((float)(I16)rInVal) : (float)rInVal;
                            Value = Scale * InVal + Offset;
                        }
                        if (HasRange) {
                            if (Value < MinRange) {
                                Value = MinRange;
                            } else if (Value > MaxRange) {
                                Value = MaxRange;
                            }
                        }
                    }
                    break;
                }
                if (ObjectPtr) {
                    if (Master) {
                        ObjectPtr->SetTimeStamp();
                        ObjectPtr->PutFloatValue(ValueKey, Value);
                    }else{
                        // Should also include the com port. Now send broadcast to all TDUs and PCs
                        // connected to this slave TCU
                        ObjectPtr->SendModbusData(ValueKey, Value);
                    }
                }
            } else {
                if (ObjectPtr) {
                    ObjectPtr->SetOffline(ValueKey);
                }
            }
        }
    }
}

void ModbusRegisterIn::CalculateScaleOut(float &ScaleOut, float &OffsetOut) {
    float Divisor = MaxRange - MinRange;
    if (Divisor) {
        ScaleOut = (float(RegMax) - 0.0) / (MaxRange - MinRange);
    } else {
        ScaleOut = 1.0;
    }
    OffsetOut = -ScaleOut * MinRange;
}

//---------------------------------------------------------------------------

int ModbusRegisterIn::GetOutputVal(void) {
    if (ObjectPtr) {
        float OutVal;
        int DecPnt, Unit; // These variables are not used
        int Status = ObjectPtr->GetValue(ValueKey, 0, OutVal, DecPnt, Unit);
        switch (Status) {
        case GETVAL_FLOAT_NOT_LEGAL:
        case GETVAL_NOT_AVAILABLE:
        default:
            OutVal = 0.0;
            break;
        case GETVAL_NO_ERR:
            OutVal = ConvertFromSi(NULL, OutVal, 0, DecPnt, Unit);
            break;
        }
        if (HasRange) {
            if (OutVal < MinRange) {
                OutVal = MinRange;
            } else if (OutVal > MaxRange) {
                OutVal = MaxRange;
            }
        }
        if (HasDecimalScaling) {
            float rValue = DecimalScaling * OutVal;
            return (floor(rValue) + 0.5)> rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
        } else {
            // Round output to nearest integer, but let -0.6 be -1 for example
            float ScaleOut, OffsetOut;
            CalculateScaleOut(ScaleOut, OffsetOut);
            float rValue = ScaleOut * OutVal + OffsetOut;
            return (floor(rValue) + 0.5)> rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
        }
    } else {
        return 0;
    }

}
float ModbusRegisterIn::GetOutputValFloat(void) {
    float OutVal;
    int DecPnt, Unit; // These variables are not used
    int Status;
    if (ObjectPtr) {
        Status = ObjectPtr->GetValue(ValueKey, 0, OutVal, DecPnt, Unit);
    } else {
        Status = GETVAL_ERROR;
    }
    switch (Status) {
    case GETVAL_FLOAT_NOT_LEGAL:
    case GETVAL_NOT_AVAILABLE:
    case GETVAL_ERROR:
    default:
        OutVal = 0.0;
        break;
    case GETVAL_NO_ERR:
        OutVal = ConvertFromSi(NULL, OutVal, 0, DecPnt, Unit);
        break;
    }
    return OutVal;
}


void ModbusRegisterIn::InitiateHoldingRegisters(ModbusUnit *UnitPtr) {
    switch (ModbusDataFormat) {
    case Float_B_Endian:
        {
            float OutVal = GetOutputValFloat();
            U16 *OutValPtr = (U16 *)&OutVal;
            UnitPtr->SetHoldingRegister(Channel + 1, OutValPtr[0]);
            UnitPtr->SetHoldingRegister(Channel, OutValPtr[1]);
        }
        break;
    case Float_B_Endian_ByteSwap:
        {
            float OutVal = GetOutputValFloat();
            U16 *OutValPtr = (U16 *)&OutVal;
            UnitPtr->SetHoldingRegister(Channel + 1, OutValPtr[0], true);
            UnitPtr->SetHoldingRegister(Channel, OutValPtr[1], true);
        }
        break;
    case Float_L_Endian:
        {
            float OutVal = GetOutputValFloat();
            U16 *OutValPtr = (U16 *)&OutVal;
            UnitPtr->SetHoldingRegister(Channel + 1, OutValPtr[1], true);
            UnitPtr->SetHoldingRegister(Channel, OutValPtr[0], true);
        }
        break;
    case Float_L_Endian_ByteSwap:
        {
            float OutVal = GetOutputValFloat();
            U16 *OutValPtr = (U16 *)&OutVal;
            UnitPtr->SetHoldingRegister(Channel + 1, OutValPtr[1]);
            UnitPtr->SetHoldingRegister(Channel, OutValPtr[0]);
        }
        break;
    case Float_None:
        {
            U16 OutVal = (U16)GetOutputVal();
            UnitPtr->SetHoldingRegister(Channel, OutVal);
        }
        break;
    }
}


ModbusRegisterIn& ModbusRegisterIn::operator = (ModbusRegisterIn Src) {
    Name                = Src.Name;
    Description         = Src.Description;

    IPAddress           = Src.IPAddress;
    TCUAddress          = Src.TCUAddress;
    TCUPortNo           = Src.TCUPortNo;
    Address             = Src.Address;
    Channel             = Src.Channel;


    MinRange            = Src.MinRange;
    MaxRange            = Src.MaxRange;
    RegMax              = Src.RegMax;
    ValueKey            = Src.ValueKey;
    RefObjectId         = Src.RefObjectId;

    Scale               = Src.Scale;
    Offset              = Src.Offset;
    HasSign             = Src.HasSign;
    HasDecimalScaling   = Src.HasDecimalScaling;
    ModbusDataFormat    = Src.ModbusDataFormat;
    HasRange            = Src.HasRange;
    DecimalPoint        = Src.DecimalPoint;
    DecimalScaling      = Src.DecimalScaling;
    if ((TCUAddress==CurrentDeviceAddress) && (CurrentDeviceId == DEVICE_TCU)) {
        MyModbusSet.insert(this);
    }
    return *this;
}

void ModbusRegisterIn::UpdateFromMultiple(unsigned pIdNumber, int pChannel) {
    Channel +=  pChannel;
    RefObjectId = pIdNumber;
    ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel,RefObjectId);
    if (ModbusDataFormat) { // Check if two registers are required
        ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel + 1,RefObjectId);
    }
}

AnsiString ModbusRegisterIn::GetRegisterValue(void) {
    AnsiString Result;
    //Result.sprintf("%8.3f",GetOutputValFloat());
    Result = LibGetValue(ValueKey, ObjectPtr);
    return Result;
}


//---------------------------------------------------------------------------


void ModbusRegisterIn::SetProList(void) {
    ObjectPtr = (PRogramObject *)FindPROFromIDNumber(RefObjectId);
    if (!ObjectPtr) {
        AnsiString InfoStr;
        if (IsCreatedFromMultiple) {
            InfoStr.cat_sprintf("Created by ModbusMultiple (Line number %i): ModbusRegisterIn RefIDNumber %i (0x%0x) is incorrect", LineNumber, RefObjectId,RefObjectId);
        } else {
            InfoStr.cat_sprintf("ModbusRegisterIn RefIDNumber %i (0x%0x) is incorrect. Line Number %i", RefObjectId, RefObjectId,LineNumber);
        }
        GiveConfigWarning(InfoStr);
    }

}
