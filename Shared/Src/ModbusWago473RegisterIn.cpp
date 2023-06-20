#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
//
// See WAGO reference documentation for the 750-473 module.
//
ModbusWago473RegisterIn::ModbusWago473RegisterIn(bool pIsCreatedFromMultiple):ModbusRegisterIn(pIsCreatedFromMultiple,C_PRO_MBUS_WAGO473_RIN)
{
    RegMax            = 0x7ff9;
    MinRange          = 0.000;
    MaxRange          = 0.032;
    HasSign           = false;
    HasDecimalScaling = false;
}

ModbusWago473RegisterIn::~ModbusWago473RegisterIn()
{
}


//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString ModbusWago473RegisterIn::MakeConfigString(int ExtraTabs)
{
    AnsiString LocalString = ModbusObject::MakeConfigString();
    AnsiString ObjectIdStr;
    ObjectIdStr.cat_sprintf("0x%0x",RefObjectId);

    LocalString +=TabStr1+KeyWord(C_OBJECT_ID)+(AnsiString)ObjectIdStr;
    LocalString +=TabStr1+KeyWord(C_VALUE_KEY)+ValueKeyWord(ValueKey);
    LocalString +=TabStr1+KeyWord(C_MODBUS_END)+CrLfStr;
    return(LocalString);
}
//---------------------------------------------------------------------------

void ModbusWago473RegisterIn::Update(void)
{
    ModbusUnit *tmpPtr = FindUnit();
    if ( tmpPtr && tmpPtr->HasNewValue(Channel)) {
        U16 rInVal   = tmpPtr->GetRegister(Channel,false);
        float InVal  = float(rInVal);
        float Current= InVal/float(RegMax )*MaxRange;

        // No need for range check since the value can't get outside 32 mA
        // Should add error check using statur register instead
        if (ObjPtr) {
            if (Master) {
                ObjPtr->SetTimeStamp();
                ObjPtr->PutFloatValue(ValueKey, Current);
                ObjPtr->RefreshData(ValueKey);
            }else{
                // Should also include the com port. Now send broadcast to all TDUs and PCs
                // connected to this slave TCU
                ObjPtr->SendModbusData(ValueKey, Current);
            }
        }
    } else {
        if (ObjPtr && Master) {
            ObjPtr->SetOffline(ValueKey);
        }
    }
}

AnsiString ModbusWago473RegisterIn::GetRegisterType(void)
{
    return "Wago 750-473";
}

