#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

ModbusWago485RegisterIn::ModbusWago485RegisterIn(bool pIsCreatedFromMultiple):ModbusRegisterIn(pIsCreatedFromMultiple,C_PRO_MBUS_WAGO485_RIN)
{
    MinRange          =   0.0;
    MaxRange          =  20.0;
    HasSign           = false;
    HasDecimalScaling = false;
}

ModbusWago485RegisterIn::~ModbusWago485RegisterIn()
{
}


//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString ModbusWago485RegisterIn::MakeConfigString(int ExtraTabs)
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

void ModbusWago485RegisterIn::Update(void)
{
    ModbusUnit *tmpPtr = FindUnit();
    if ( tmpPtr &&  tmpPtr->HasNewValue(Channel) ) {
        U16 rInVal   = tmpPtr->GetRegister(Channel,true);
        float InVal  = HasSign ? ((float)(I16)rInVal) : (float)rInVal;
        float Voltage= InVal/float(0x7fff)*10.0;

        // No need for range check since the value can't get outside 10 Volt
        // Should add error check using statur register instead
        if (ObjectPtr) {
            if (Master) {
                ObjectPtr->SetTimeStamp();
                ObjectPtr->PutFloatValue(ValueKey, Voltage);
            }else{
                // Should also include the com port. Now send broadcast to all TDUs and PCs
                // connected to this slave TCU
                ObjectPtr->SendModbusData(ValueKey, Voltage);
            }
        }
    } else {
        if (ObjectPtr && Master) {
            ObjectPtr->SetOffline(ValueKey);
        }
    }
}

AnsiString ModbusWago485RegisterIn::GetRegisterType(void)
{
    return "Wago 750-485";
}

