#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
set<PRogramObjectBase*>ModbusRegisterOut::ModbusSet;

ModbusRegisterOut::ModbusRegisterOut(bool pIsCreatedFromMultiple, int ModuleType, bool InsertInSet)
{
	if (InsertInSet) {
		ModbusSet.insert(this);
	}
	IDNumber    = (ModuleType << 16) + ModbusSet.size();
	Type        = ModuleType;
    IsCreatedFromMultiple = pIsCreatedFromMultiple;
}

ModbusRegisterOut::~ModbusRegisterOut()
{
}

void ModbusRegisterOut::CalculateScale(void)
{
    float Divisor = MaxRange - MinRange;
    if (Divisor) {
        Scale = (float(RegMax)-0.0)/( MaxRange - MinRange ) ;
    }else{
        Scale = 1.0;
    }
    Offset = -Scale*MinRange;
}

//---------------------------------------------------------------------------

int ModbusRegisterOut::GetOutputVal(void)
{
    int ReturnVal = 0;
    if ( ObjPtr ) {
        float OutVal;
        int DecPnt,Unit; // These variables are not used
        int Status = ObjPtr->GetValue(ValueKey, 0, OutVal,DecPnt,Unit);
        switch ( Status ) {
        case GETVAL_HW_ALARM       :
            OutVal = RegMax;
            break;
        case GETVAL_FLOAT_NOT_LEGAL:
        case GETVAL_NOT_AVAILABLE  :
        default:
            OutVal = 0.0;
            break;
        case GETVAL_OFFLINE:
        case GETVAL_NO_ERR:
            OutVal = ConvertFromSi(NULL,OutVal,0,DecPnt,Unit);
            break;
        }
        if ( HasRange ) {
            if ( OutVal < MinRange ) {
                OutVal = MinRange;
            } else if ( OutVal > MaxRange ) {
                OutVal = MaxRange;
            }
        }

        switch ( ModbusDataFormat ) {
        case Float_None:
            if ( HasDecimalScaling ) {
                float rValue = DecimalScaling * OutVal;
                ReturnVal = ( floor(rValue) + 0.5 ) > rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
            } else {
                float rValue = Scale * OutVal+ Offset;
                ReturnVal = ( floor(rValue) + 0.5 ) > rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
            }
            break;
        case Integer_B_Endian:
        case Integer_B_Endian_ByteSwap:
        case Integer_L_Endian:
        case Integer_L_Endian_ByteSwap:
            ReturnVal = OutVal;
            break;
        }
    }
    return ReturnVal;

}
float ModbusRegisterOut::GetOutputValFloat(void)
{
    if ( ObjPtr ) {
    float OutVal;
    int DecPnt,Unit; // These variables are not used
    int Status = ObjPtr->GetValue(ValueKey, 0, OutVal,DecPnt,Unit);
    switch ( Status ) {
    case GETVAL_FLOAT_NOT_LEGAL:
    case GETVAL_NOT_AVAILABLE:
    default:
        OutVal = 0.0;
        break;
    case GETVAL_NO_ERR:
        OutVal = ConvertFromSi(NULL,OutVal,0,DecPnt,Unit);
        break;
    }
    return OutVal;
    }else{
        return 0.0;
    }
}


AnsiString ModbusRegisterOut::GetOutputString(void)
{
    AnsiString MyString;
    int ErrorStatus = GETVAL_ERROR;
    if ( ObjPtr ) {
        ErrorStatus = ObjPtr->GetStringValue(ValueKey,0,MyString);
    }
    switch(ErrorStatus){
    case GETVAL_ERROR:
        MyString = "Error";
        break;
    default:
        break;
    }
    return MyString;
}

void ModbusRegisterOut::Update(void)
{
    ModbusUnit *tmpPtr = FindUnit();
    if ( tmpPtr ) {
        switch ( ModbusDataFormat ) {
        case Float_B_Endian:
            {
                float OutVal = GetOutputValFloat();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[0]);
                tmpPtr->SetRegister(Channel  ,OutValPtr[1]);
            }
            break;
        case Float_B_Endian_ByteSwap:
            {
                float OutVal = GetOutputValFloat();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[0], true);
                tmpPtr->SetRegister(Channel  ,OutValPtr[1], true);
            }
            break;
        case Float_L_Endian:
            {
                float OutVal = GetOutputValFloat();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[1], true);
                tmpPtr->SetRegister(Channel  ,OutValPtr[0], true);
            }
            break;
        case Float_L_Endian_ByteSwap:
            {
                float OutVal = GetOutputValFloat();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[1]);
                tmpPtr->SetRegister(Channel  ,OutValPtr[0]);
            }
            break;
        case Integer_B_Endian:
            {
                int OutVal = GetOutputVal();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[0]);
                tmpPtr->SetRegister(Channel  ,OutValPtr[1]);
            }
            break;
        case Integer_B_Endian_ByteSwap:
            {
                int OutVal = GetOutputVal();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[0],true);
                tmpPtr->SetRegister(Channel  ,OutValPtr[1],true);
            }
            break;
        case Integer_L_Endian:
            {
                int OutVal = GetOutputVal();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[1], true);
                tmpPtr->SetRegister(Channel  ,OutValPtr[0], true);
            }
            break;
        case Integer_L_Endian_ByteSwap:
            {
                int OutVal = GetOutputVal();
                U16 *OutValPtr = (U16*)&OutVal;
                tmpPtr->SetRegister(Channel+1,OutValPtr[1]);
                tmpPtr->SetRegister(Channel  ,OutValPtr[0]);
            }
            break;
        case Float_None:
            {
                U16 OutVal    = (U16)GetOutputVal();
                tmpPtr->SetRegister(Channel,OutVal);
            }
            break;
        case String10 :
            {
                AnsiString MyStr = GetOutputString();
                tmpPtr->SetRegisterString(Channel,MyStr,10);
            }
            break;
        case String20 :
            {
                AnsiString MyStr = GetOutputString();
                tmpPtr->SetRegisterString(Channel,MyStr,20);
            }
            break;
        }
    }
}


ModbusRegisterOut& ModbusRegisterOut::operator=(ModbusRegisterOut Src)
{
    Name          = Src.Name       ;
    Description   = Src.Description;

    IPAddress     = Src.IPAddress  ;
    TCUAddress    = Src.TCUAddress ;
    TCUPortNo     = Src.TCUPortNo  ;
    Address       = Src.Address    ;
    Channel       = Src.Channel    ;


    MinRange      = Src.MinRange   ;
    MaxRange      = Src.MaxRange   ;
    RegMax        = Src.RegMax     ;
    ValueKey      = Src.ValueKey   ;
    RefObjectId   = Src.RefObjectId   ;

    Scale             = Src.Scale            ;
    Offset            = Src.Offset           ;
    HasSign           = Src.HasSign          ;
    HasDecimalScaling = Src.HasDecimalScaling;
    ModbusDataFormat   = Src.ModbusDataFormat  ;
    HasRange          = Src.HasRange         ;
    DecimalPoint      = Src.DecimalPoint     ;
    DecimalScaling    = Src.DecimalScaling   ;
    if ((TCUAddress==CurrentDeviceAddress) && (CurrentDeviceId == DEVICE_TCU)) {
        MyModbusSet.insert(this);
    }
    return *this;
}

void ModbusRegisterOut::UpdateFromMultiple(unsigned pIdNumber, int pChannel)
{
    Channel +=  pChannel;
    RefObjectId = pIdNumber;
    ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel,RefObjectId);
    if (ModbusDataFormat) { // Check if two registers are required
        ModbusUnit::InsertInMap(TCUAddress, TCUPortNo, Address, Type, Channel + 1,RefObjectId);
    }
}


AnsiString ModbusRegisterOut::GetRegisterValue(void) {
    AnsiString Result;
    //Result.sprintf("%8.3f",GetOutputValFloat());
    Result = LibGetValue(ValueKey, ObjPtr);
	return Result;
}

//---------------------------------------------------------------------------


void ModbusRegisterOut::SetProList(void) {
    ObjPtr = (PRogramObject *)FindPROFromIDNumber(RefObjectId);
    if (!ObjPtr) {
        AnsiString InfoStr;
        if (IsCreatedFromMultiple) {
            InfoStr.cat_sprintf("Created by ModbusMultiple (Line number %i): ModbusRegisterOut RefIDNumber %i (0x%0x) is incorrect", LineNumber, RefObjectId,RefObjectId);
        } else {
            InfoStr.cat_sprintf("ModbusRegisterOut RefIDNumber %i (0x%0x) is incorrect. Line Number %i", RefObjectId, RefObjectId,LineNumber);
        }
        GiveConfigWarning(InfoStr);
    }

}

