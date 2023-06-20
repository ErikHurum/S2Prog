#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLoLoLevel::NumberOfAlarmSettings = 0;

AlarmLoLoLevel::AlarmLoLoLevel(PRogramObjectBase *PROPtr, float Lim, bool Lock) : AlarmLowLevel(PROPtr, Lim, Lock) {
    NumberOfAlarmSettings++;
    IDNumber        = (ID_AL_LOWLOW_LEVEL << 16) + NumberOfAlarmSettings;
    Type            = ID_AL_LOWLOW_LEVEL;
    MessageKey      = L_WORD1106;    // LoLoLevel
    TPCMessageKey   = L_WORD1107;    // LLLev
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmLoLoLevel::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    switch ( ValueId ) {
    case SVT_LOLO_VOLPCNT_LIM:
        ValueId = SVT_LO_VOLPCNT_LIM;
        break;
    case SVT_LOLO_VOLUME_LIM :
        ValueId = SVT_LO_VOLUME_LIM;
        break;
    case SVT_LOLO_WEIGHT_LIM :
        ValueId = SVT_LO_WEIGHT_LIM;
        break;
    case SVT_LOLO_ULLAGE_LIM :
        ValueId = SVT_LO_ULLAGE_LIM;
        break;
    case SVT_LOLO_LEVEL_LIM  :
        ValueId = SVT_LO_LEVEL_LIM;
        break;
    }
    int Status = AlarmLowLevel::PutValue(ValueId, Index, NewValue, Local, UnitId);
    return (Status);
}

int  AlarmLoLoLevel::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_LOLO_VOLPCNT_LIM:
        ValueId = SVT_LO_VOLPCNT_LIM;
        break;
    case SVT_LOLO_VOLUME_LIM :
        ValueId = SVT_LO_VOLUME_LIM;
        break;
    case SVT_LOLO_WEIGHT_LIM :
        ValueId = SVT_LO_WEIGHT_LIM;
        break;
    case SVT_LOLO_ULLAGE_LIM :
        ValueId = SVT_LO_ULLAGE_LIM;
        break;
    case SVT_LOLO_LEVEL_LIM  :
        ValueId = SVT_LO_LEVEL_LIM;
        break;
    }
    Status = AlarmLowLevel::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
    return (Status);
}

int AlarmLoLoLevel::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmLowLevel::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmLoLoLevel::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_LOLO_VOLPCNT_LIM:
        ValueId = SVT_LO_VOLPCNT_LIM;
        break;
    case SVT_LOLO_VOLUME_LIM :
        ValueId = SVT_LO_VOLUME_LIM;
        break;
    case SVT_LOLO_WEIGHT_LIM :
        ValueId = SVT_LO_WEIGHT_LIM;
        break;
    case SVT_LOLO_ULLAGE_LIM :
        ValueId = SVT_LO_ULLAGE_LIM;
        break;
    case SVT_LOLO_LEVEL_LIM  :
        ValueId = SVT_LO_LEVEL_LIM;
        break;
    }
    Status = AlarmLowLevel::PutFloatValue(ValueId, NewValue);
    return (Status);
}



