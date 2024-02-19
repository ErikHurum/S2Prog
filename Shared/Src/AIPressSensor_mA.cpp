#ifdef ANWIN
	#include "LiteCall.hpp"
#endif
#pragma hdrstop
#include "TSNIncludes.h"
#ifdef ANWIN
	#include "ChildUnit.h"
	#include "Anpro_Net.h"
	#include "MainUnit.h"
#endif

#ifdef BORLAND
#pragma package(smart_init)
#endif

ANCriticalSection AIPressSensor_mA::LogSema;

set<AIPressSensor_mA*>AIPressSensor_mA::ObjectSet;
//---------------------------------------------------------------------------

AIPressSensor_mA::AIPressSensor_mA(int SnsType, bool IsAtmRef) : AIPressSensor(IsAtmRef) {
    //:m_iSizeAlloc(10)
    Error = false;
    Type = SnsType;
    TZS = 0.0;
    TSS = 0.0;
	PrevTemp = -TEMP_ZERO;
    TempPtr   = NULL;
	// FRO = new float(m_iSizeAlloc);
    // PCnt = new float(m_iSizeAlloc); // Sensor cal values
    switch ( SnsType ) {
	case C_AI_MB_Press_mA   :
	case C_AI_MB_DiffPre_mA :
    default:
        AlarmmAmpOpenLoop     *OpenLoopPtr      = new AlarmmAmpOpenLoop(this,10000); // Was 5000
        AlarmSet.insert(OpenLoopPtr);
        // Add the short circuit alarm separately
        break;
    }
    ObjectSet.insert(this);

}
//---------------------------------------------------------------------------

AIPressSensor_mA::~AIPressSensor_mA(void) {
//  delete FRO;
//  delete PCnt;
}
//---------------------------------------------------------------------------
U8 AIPressSensor_mA::GetFilter(void) {
    return (FILTER_MA_PRESS);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIPressSensor_mA::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_CAL_DATA_FRO    :
    case SVT_AI_CAL_DATA_G1     :
        if ( Index >= 0 && Index < int(mAPcnt.size()) ) {
            if ( Status == E_NO_ERR ) {
                switch ( ValueId ) {
                case SVT_AI_CAL_DATA_FRO:
                    {
                        float Value = ConvertToSi(NewValue, PERCENT_UNIT, Status, 0.0, 100.0);
                        if ( Status == E_NO_ERR ) {
                            mAPcnt[Index] = Value / 100.0;
                            TimeModified = time(NULL);
                        }
                    }
                    break;
                case SVT_AI_CAL_DATA_G1 :
                    {
                        float Value = ConvertToSi(NewValue, CURRENT_UNIT, Status, 0.0, 20.0);
                        if ( Status == E_NO_ERR ) {
                            mACal[Index] = Value;
                            TimeModified = time(NULL);
                        }
                    }
                    break;
                }
            }
        }
        break;
    case SVT_AI_CAL_DATA_TSS:
        {
            short Value = GetInt(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                TSS             = Value;
                TimeModified    = time(NULL);
            }
        }
        break;
    case SVT_AI_CAL_DATA_TZS:
        {
            short Value = GetInt(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                TZS             = Value;
                TimeModified    = time(NULL);
            }
        }
        break;
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        Status = AIPressSensor::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if ( Status == E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int  AIPressSensor_mA::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_CAL_DATA_ENTRY	:
    case SVT_AI_CAL_DATA_FRO	:
    case SVT_AI_CAL_DATA_G1 	:
        if ( Index >= 0 && Index < int(mAPcnt.size()) ) {
            switch ( ValueId ) {
            case SVT_AI_CAL_DATA_ENTRY	:
                MyRetValue = Index + 1;
                Unit       = NO_UNIT;
                DecPnt     = 0;
                break;
            case SVT_AI_CAL_DATA_FRO:
                MyRetValue = mAPcnt[Index] * 100.0;
                Unit       = PERCENT_UNIT;
                DecPnt     = 1;
                break;
            case SVT_AI_CAL_DATA_G1 :
                MyRetValue = mACal[Index];
                Unit       = CURRENT_UNIT;
                DecPnt     = 1;
                break;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_AI_CAL_DATA_ENTRIES:
        MyRetValue = mAPcnt.size();
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CAL_DATA_TSS:
        MyRetValue = TSS;
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CAL_DATA_TZS:
        MyRetValue = TZS;
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        Status = AIPressSensor::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AIPressSensor_mA::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    return (AIPressSensor::GetStringValue(ValueId, Index, MyString));
}

int AIPressSensor_mA::PutFloatValue(int ValueId, float NewValue) {
    return (AIPressSensor::PutFloatValue(ValueId, NewValue));
}

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////
float AIPressSensor_mA::Calculate(void) {
    if ( CanCalculate() ) {
        float CurrentTemp;
        if ( TempPtr ) {
            CurrentTemp = *TempPtr;
        } else {
            CurrentTemp = PROSystemData::SeaWaterTemp;
        }
        float NewCalcValue = Gain * (Get_Press(FilteredValue, CurrentTemp) - NORMAL_ATM) + NORMAL_ATM - AtmPressure - Offset;
        switch ( Location ) {
        case C_AI_LOC_REDUNDANCY1   :
        case C_AI_LOC_REDUNDANCY2   :
        case C_AI_LOC_REDUNDANCY3   :
        case C_AI_LOC_BOTTOM        :
        case C_AI_LOC_MIDDLE        :
        case C_AI_LOC_UPPER         :
            NewCalcValue -= CalcRefPressure();
            break;
        default:
            break;

        }
        CalcValue = NewCalcValue;
        ResultOK  = true;
    }
    return (CalcValue);
}

void AIPressSensor_mA::Temp_Correction(float Temp) {
    CalDataSema.Acquire();
    mACor.clear();
    if ( !mACal.empty() ) {
        float FRODiff = mACal.back() - mACal[0];
        float TZSCor = FRODiff * TZS * (Temp - 25.0) / 100.0;
        float TSSCor = FRODiff * TSS * (Temp - 25.0) / 100.0;
        for ( unsigned i = 0; i < mACal.size(); i++ ) {
            mACor.push_back(mACal[i] + TSSCor * mACal[i] + TZSCor);
        }
    }
    CalDataSema.Release();
}

float AIPressSensor_mA::Get_Percent(float mA) {
    int Index = 1;
    int LastI = mACal.size() - 1;
    while ( (Index < LastI) && (mA > mACal[Index]) )	Index++;

    return (IntPol1stDeg(mACal[Index - 1], mACal[Index], mAPcnt[Index - 1], mAPcnt[Index], mA));
}
float AIPressSensor_mA::Get_Cor_PCnt(float mA) {
    CalDataSema.Acquire();
    int Index = 1;
    int LastI = mACal.size() - 1;
    while ( (Index < LastI) && (mA > mACor[Index]) ) Index++;
    float CorPcnt = IntPol1stDeg(mACor[Index - 1], mACor[Index], mAPcnt[Index - 1], mAPcnt[Index], mA);
    CalDataSema.Release();
    return CorPcnt;

}
float AIPressSensor_mA::Get_Press(float Amp, float Temp) {
    // We do not want to make a new temp correction unless we
    // have a significant temperature change
    if ( fabs(Temp - PrevTemp) > 1.0 ) {
        Temp_Correction(Temp);
        PrevTemp = Temp;
    }
    float  Percent = Get_Cor_PCnt(Amp);
    return ((MaxRange - MinRange) * Percent + MinRange) / MH2O_TO_BAR;
}


void AIPressSensor_mA::AddShortCircuitAlarm(void) {
    AlarmmAmpShortCircuit *ShortCircuitPtr = new AlarmmAmpShortCircuit( this );
    AlarmSet.insert( ShortCircuitPtr );
}


