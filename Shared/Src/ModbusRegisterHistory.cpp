#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
set<PRogramObjectBase*>ModbusRegisterHistory::ModbusSet;

ModbusRegisterHistory::ModbusRegisterHistory(bool pIsCreatedFromMultiple) {
    ModbusSet.insert(this);
    IDNumber = (C_PRO_MODBUS_REG_HIST << 16 )+ModbusSet.size();
    Type     = C_PRO_MODBUS_REG_HIST;
    LogTime  = clock();
    IsCreatedFromMultiple = pIsCreatedFromMultiple;
}

ModbusRegisterHistory::~ModbusRegisterHistory() {
}

void ModbusRegisterHistory::CalculateScale(void) {
    Scale = (float(RegMax)-0.0)/( MaxRange - MinRange ) ;
    Offset = -Scale*MinRange;
}

//---------------------------------------------------------------------------

int ModbusRegisterHistory::GetOutputVal(void) {
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
        if ( HasRange ) {
            if ( OutVal < MinRange ) {
                OutVal = MinRange;
            } else if ( OutVal > MaxRange ) {
                OutVal = MaxRange;
            }
        }
        if ( HasDecimalScaling ) {
            float rValue = DecimalScaling * OutVal;
            return( floor(rValue) + 0.5 ) > rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
        } else {
            float rValue = Scale * OutVal+ Offset;
            return( floor(rValue) + 0.5 ) > rValue ? ((U16)floor(rValue) ) : ((U16) ceil(rValue) );
        }
    } else {
        return 0;
    }

}
float ModbusRegisterHistory::GetOutputValFloat(void) {
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
}


void ModbusRegisterHistory::Update(void) {
    clock_t CurrentTime = clock();
    if ( CurrentTime >= LogTime + TSNUart::Channels[TCUPortNo]->LogTime ) {
        LogTime = clock();
        ModbusUnit *tmpPtr = FindUnit();
        if ( tmpPtr ) {
            switch ( ModbusDataFormat ) {
            case Float_B_Endian:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    float OutVal = GetOutputValFloat();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[0]);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[1]);
                }
                break;
            case Float_B_Endian_ByteSwap:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    float OutVal = GetOutputValFloat();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[0],true);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[1],true);
                }
                break;
            case Float_L_Endian:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    float OutVal = GetOutputValFloat();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[1], true);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[0], true);
                }
                break;
            case Float_L_Endian_ByteSwap:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    float OutVal = GetOutputValFloat();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[1]);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[0]);
                }
                break;
            case Integer_B_Endian:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    int OutVal = GetOutputVal();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[0]);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[1]);
                }
                break;
            case Integer_B_Endian_ByteSwap:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    int OutVal = GetOutputVal();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[0],true);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[1],true);
                }
                break;
            case Integer_L_Endian:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    int OutVal = GetOutputVal();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[1], true);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[0], true);
                }
                break;
            case Integer_L_Endian_ByteSwap:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 2);
                    int OutVal = GetOutputVal();
                    U16 *OutValPtr = (U16*)&OutVal;
                    tmpPtr->SetRegister(Channel+1,OutValPtr[1]);
                    tmpPtr->SetRegister(Channel  ,OutValPtr[0]);
                }
                break;
            case Float_None:
                {
                    tmpPtr->MoveRegisters(Channel, TSNUart::Channels[TCUPortNo]->LogEntries, 1);
                    U16 OutVal    = (U16)GetOutputVal();
                    tmpPtr->SetRegister(Channel,OutVal);
                }
                break;
            }
        }
    }
}

