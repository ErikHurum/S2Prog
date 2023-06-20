#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIModbusDiffPressSensor_mA::AIModbusDiffPressSensor_mA(bool IsAtmRef):AIDiffPressSensor_mA(C_AI_MB_DiffPre_mA)
{
    IOType              = C_IO_MODBUS;
    Location            = C_AI_LOC_BOTTOM;
}

AIModbusDiffPressSensor_mA::~AIModbusDiffPressSensor_mA(void)
{
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
int AIModbusDiffPressSensor_mA::PutFloatValue(int ValueId, float NewValue) {
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


