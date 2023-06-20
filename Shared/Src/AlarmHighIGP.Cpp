#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmHighIGP::NumberOfAlarmSettings = 0;
AlarmHighIGP::AlarmHighIGP(PRogramObjectBase *PROPtr) {
    Init(PROPtr);
}

AlarmHighIGP::AlarmHighIGP(PRogramObjectBase *PROPtr, float Lim, bool Visible) {
    Init(PROPtr);
	IsVisible    	  = Visible;
	Limit        	  = Lim;
}

void AlarmHighIGP::Init(PRogramObjectBase *PROPtr){
    NumberOfAlarmSettings++;
    IDNumber          = (ID_AL_HIGH_INERT_GAS_PRESS << 16) + NumberOfAlarmSettings;
    Type              = ID_AL_HIGH_INERT_GAS_PRESS;
    PROPointer        = PROPtr;
    PROTPressPtr      = (PROTankPressure*)PROPtr;
    IsExtraAlarm      = true;
    Locked            = PROTPressPtr->HighTankPressLocked;
    Limit             = PROTPressPtr->HighTankPressLimit;
    MessageKey        = L_WORD1099;  // Hi IGP
    TPCMessageKey     = L_WORD1100;  // H IGP
    PROTPressPtr->hasIGPAlarms = true;
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmHighIGP::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
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
                Status = AlarmHighPressure::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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


