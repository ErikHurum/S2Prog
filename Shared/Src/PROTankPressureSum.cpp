#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

PROTankPressureSum::PROTankPressureSum(vector<PRogramObjectBase*>&TTable,bool Fixed):PROTankPressure(false),TankTable(TTable)
{
	IDNumber      = (C_PRO_TANKPRESS_SUM << 16 );
	Type          = C_PRO_TANKPRESS_SUM;
	//TankTable     = TTable;
	IsFixed       = Fixed;
	Name          = "Average";
}

PROTankPressureSum::~PROTankPressureSum(void)
{
}
//---------------------------------------------------------------------------

int PROTankPressureSum::FindMyEntry(void)
{
	unsigned i=0;
	while ( i < TankTable.size() ) {
		if ( TankTable[i] == this ) {
			return(i);
		} else {
			i++;
		}
	}
	return(-1);	// If we get her, we found nothing!!!
}

int PROTankPressureSum::FindStart(int MyEnd)
{
	int MyStart=0;
	if ( MyEnd > 0 ) {
		int i=MyEnd-1;
		bool OtherSum=false;
		while ( !OtherSum && ( i > 0) ) {
			if ( TankTable[i]->Type == C_PRO_TANKPRESS_SUM ) {
				OtherSum = true;
				MyStart = i+1; // We are one too far, let us go one step back!
			} else {
				i--;
			}
		}
	} else {
		MyStart = -1;
	}
	return(MyStart); // If we get her, we found nothing!!!
}


bool PROTankPressureSum::FindRange(int &MyStart, int &MyEnd)
{
	bool FoundRange=false;
	MyEnd   = FindMyEntry();
	if ( MyEnd > 0 ) {
		MyStart = FindStart(MyEnd);
		if ( MyStart >= 0 ) {
			FoundRange = true;
		}
	}
	return(FoundRange);
}

int PROTankPressureSum::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit){
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
    case SVT_PRESSURE:
        Status = E_NO_INPUT_PERMISSION;
        break;
	case SVT_TP:
		{
			int MyStart,MyEnd;
			if ( FindRange(MyStart,MyEnd ) ) {
				float tmpPress  = 0.0;
				int PCnt = 0;
				for ( int i=MyStart; i < MyEnd; i++ ) {
					PROTankPressure *TPtr = (PROTankPressure*)TankTable[i];
					if ( TPtr && TPtr->IsNewData && TPtr->HasPressure ) {
						PCnt++;
						tmpPress  += TPtr->Pressure;
					}
				}
				if ( PCnt ) {
					Pressure = tmpPress/PCnt;
					MyRetValue  = Pressure;
				} else {
					Status = GETVAL_FLOAT_NOT_LEGAL;
				}
			} else {
				Status = GETVAL_NOT_AVAILABLE;
			}
		}
		DecPnt     = 1;
		Unit       = PRESSURE_UNIT1;
		break;
	default:
		Status = GETVAL_NO_DISPLAY;
		break;
	}
	return(Status);
}

int PROTankPressureSum::GetStringValue(int ValueId, int Index, AnsiString &MyString){
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_PRO_STATUS:
		FindPROStatus(MyString);
		break;
	case SVT_TANK_STATE_STR:
		{
			int MyStart,MyEnd;
			if ( FindRange(MyStart,MyEnd ) ) {
				set<TankState>StateSet;
				TankState tmpState;
				for ( int i=MyStart; i < MyEnd; i++ ) {
					PROTankPressure *TPtr = (PROTankPressure*)TankTable[i];
					if ( TPtr ) {
						tmpState = TPtr->GetState();
						StateSet.insert(tmpState);
					}
				}
				if ( StateSet.size()==1 ) {
					State = tmpState;
				} else {
					State = tUndefined;
				}
				Status = PROTankPressure::GetStringValue(ValueId,Index, MyString);
			} else {
				Status       = GETVAL_NOT_AVAILABLE;
			}
		}
		break;
	case SVT_AL_LIMIT_TYPE_PRESS    :
		{
			int MyStart,MyEnd;
			if ( FindRange(MyStart,MyEnd ) ) {
				set<LimitState>StateSet;
				LimitState tmpState;
				for ( int i=MyStart; i < MyEnd; i++ ) {
					PROTankPressure *TPtr = (PROTankPressure*)TankTable[i];
					if ( TPtr ) {
						tmpState =TPtr->VapourAlarmSet;
						StateSet.insert(tmpState);
					}
				}
				if ( StateSet.size()==1 ) {
					VapourAlarmSet = tmpState;
				} else {
					VapourAlarmSet = pLimitUndefined;
				}
				Status = PROTankPressure::GetStringValue(ValueId,Index, MyString);
			} else {
				Status       = GETVAL_NOT_AVAILABLE;
			}
		}
		break;
	default:
		Status = PROTankPressure::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}


int PROTankPressureSum::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
    case SVT_PRESSURE:
        Status = E_NO_INPUT_PERMISSION;
        break;
	case SVT_HI_IGP_ENABLE  	:
	case SVT_LO_IGP_ENABLE  	:
	case SVT_HI_IGP_LIMIT   	:
	case SVT_LO_IGP_LIMIT   	:
	case SVT_LO_PRESS_ENABLE	:
	case SVT_HI_PRESS_ENABLE	:
	case SVT_LO_PRESS_LIMIT 	:
	case SVT_HI_PRESS_LIMIT 	:
	case SVT_TP_OFFSET 			:
	case SVT_TP_GAIN 			:
	case SVT_TP 				:
	case SVT_AL_LIMIT_TYPE_PRESS:
		{
			int MyStart,MyEnd;
			int tmpStatus = E_NO_ERR;
			if ( FindRange(MyStart,MyEnd ) ) {
				for ( int i=MyStart; i < MyEnd; i++ ) {
					PROTankPressure *TPtr = (PROTankPressure*)TankTable[i];
					if ( TPtr ) {
						tmpStatus |= LibPutValue(ValueId, TPtr, NewValue, Local,true);
					}
				}
				if ( tmpStatus != E_NO_ERR ) {
					Status = E_COMMON_INPUT_ERR;
				}
			} else {
				Status       = E_NOT_COMMON_INPUT;
			}
		}
		break;
	default:
		Status = E_NOT_COMMON_INPUT;
		break;
	}
	if ( Status==E_NO_ERR ) {
		Status = E_LOCAL_ONLY;
		SetModifiedFlag();
	}
	if ( UnitId ) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int PROTankPressureSum::PutFloatValue( int ValueId, float NewValue){
	int Status = E_NO_ERR;
	//int ValUnitId = NO_UNIT;
	//switch ( ValueId ) {
	//default:
//	Status = PROTankPressure::PutFloatValue(ValueId,NewValue);
	//    break;
	//}
	return(Status);
}


int PROTankPressureSum::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}








