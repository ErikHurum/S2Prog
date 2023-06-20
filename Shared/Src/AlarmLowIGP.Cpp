#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
unsigned AlarmLowIGP::NumberOfAlarmSettings=0;
AlarmLowIGP::AlarmLowIGP(PRogramObjectBase *PROPtr)  {
    Init(PROPtr);
}


AlarmLowIGP::AlarmLowIGP(PRogramObjectBase *PROPtr, float Lim, bool Visible) : AlarmLowPressure(PROPtr)
{
    Init(PROPtr);
    IsVisible         = Visible;
    Limit             = Lim;
}

void AlarmLowIGP::Init(PRogramObjectBase *PROPtr){
    NumberOfAlarmSettings++;
    IDNumber          = (ID_AL_LOW_INERT_GAS_PRESS << 16) + NumberOfAlarmSettings;
    Type              = ID_AL_LOW_INERT_GAS_PRESS;
    PROPointer        = PROPtr;
    PROTPressPtr      = (PROTankPressure*)PROPtr;
    IsExtraAlarm      = true;
    Limit             = PROTPressPtr->LowIGP_Limit;
    Locked            = PROTPressPtr->LowIGP_Locked;
    MessageKey        = L_WORD1101;  // Lo IGP
    TPCMessageKey     = L_WORD1102;  // L IGP
    PROTankPressure::hasIGPAlarms = true;
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmLowIGP::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    bool tmpLock = Locked;
    if (Locked) {
        Status = E_NO_INPUT_PERMISSION;
    } else {
        float OrgLimit = Limit;
        int Key = FindConfigKey(NewValue);
        switch ( Key ) {
        case C_ON:
        case C_OPEN:
        case C_ENABLE:
            SetEnable(EnableTrue);
            PROTPressPtr->SetState(tUndefined);
            break;
        case C_OFF:
        case C_CLOSE:
        case C_DISABLE:
            SetEnable(EnableFalse);
            PROTPressPtr->SetState(tUndefined);
            break;
        default:
            switch ( ValueId ) {
            case SVT_AL_LIMIT:
                {
                    float Value = ConvertToSi(NewValue, ValUnitId = PRESSURE_UNIT1, Status, PROTPressPtr->LowIGP_Limit, PROTPressPtr->HighIGP_Limit);
                    if ( Status == E_NO_ERR ) {
                        Limit = Value;
                    }
                }
                break;
            default:
                Status = AlarmLowPressure::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
                break;
            }
            break; // switch ( ValueId )
        } //switch ( Key )
        if ( Status == E_NO_ERR ) {
			SetModifiedFlag();
			if ( Limit != OrgLimit ) {
				LogEvent("New limit");
			}
        }
    } // if ( Locked ) else
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

