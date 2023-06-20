#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIModbusPressSensor_mA::AIModbusPressSensor_mA(bool IsAtmRef):AIPressSensor_mA(C_AI_MB_Press_mA,IsAtmRef)
{
    IOType              = C_IO_MODBUS;
    Location            = C_AI_LOC_BOTTOM;
}

AIModbusPressSensor_mA::~AIModbusPressSensor_mA(void)
{
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
int AIModbusPressSensor_mA::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_MB_MA_PRESSURE:
        FilteredValue = NewValue;
        break;
    default:
        Status = AnalogInput::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}

//---------------------------------------------------------------------------


