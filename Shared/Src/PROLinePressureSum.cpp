#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

PROLinePressureSum::PROLinePressureSum(vector<PRogramObjectBase*>&TTable,bool Fixed):PROLinePressure(0,false),LinePressureTable(TTable)
{
	IDNumber      = (C_PRO_LINEPRESS_SUM << 16 );
	Type          = C_PRO_LINEPRESS_SUM;
	IsFixed       = Fixed;
	Name          = "Average";
}

PROLinePressureSum::~PROLinePressureSum(void)
{
}
//---------------------------------------------------------------------------

int PROLinePressureSum::FindMyEntry(void)
{
	unsigned i=0;
	while ( i < LinePressureTable.size() ) {
		if ( LinePressureTable[i] == this ) {
			return(i);
		} else {
			i++;
		}
	}
	return(-1);	// If we get her, we found nothing!!!
}

int PROLinePressureSum::FindStart(int MyEnd)
{
	int MyStart=0;
	if ( MyEnd > 0 ) {
		int i=MyEnd-1;
		bool OtherSum=false;
		while ( !OtherSum && ( i > 0) ) {
			if ( LinePressureTable[i]->Type == C_PRO_TEMP_SUM ) {
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


bool PROLinePressureSum::FindRange(int &MyStart, int &MyEnd)
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

int PROLinePressureSum::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit){
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_PRESSURE:
	case SVT_LINE_PRESSURE:
		DecPnt     = 1;
		Unit       = PRESSURE_UNIT3;
		{
			int MyStart,MyEnd;
			if ( FindRange(MyStart,MyEnd ) ) {
				double tmpLPress  = 0.0;
				int LPCnt     = 0;
				for ( int i=MyStart; i < MyEnd; i++ ) {
					PROLinePressure *LPPtr = (PROLinePressure*)LinePressureTable[i];
					if ( LPPtr && LPPtr->HasPressure && !LPPtr->HWFailure) {
						LPCnt++;
						tmpLPress += LPPtr->Pressure;
					}
				}
				if ( LPCnt ) {
					Pressure = tmpLPress/double(LPCnt);
					MyRetValue  = Pressure;
				} else {
					Status = GETVAL_FLOAT_NOT_LEGAL;
				}
			} else {
				Status       = GETVAL_NOT_AVAILABLE;
			}
		}
		break;
	default:
		Status = GETVAL_NO_DISPLAY;
//			Status = PROLinePressure::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
		break;
	}
	return(Status);
}

int PROLinePressureSum::GetStringValue(int ValueId, int Index, AnsiString &MyString){
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_PRO_STATUS:
		FindPROStatus(MyString);
		break;
	default:
//			Status = GETVAL_NO_DISPLAY;
		Status = PROLinePressure::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}


int PROLinePressureSum::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId){
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	case SVT_LO_PRESS_ENABLE  :
	case SVT_HI_PRESS_ENABLE  :
	case SVT_LO_PRESS_LIMIT  :
	case SVT_HI_PRESS_LIMIT :
	case SVT_TP_OFFSET :
	case SVT_TP_GAIN :
	case SVT_TP :
	case SVT_PRESSURE:
		{
			int MyStart,MyEnd;
			int tmpStatus = E_NO_ERR;
			if ( FindRange(MyStart,MyEnd ) ) {
				for ( int i=MyStart; i < MyEnd; i++ ) {
					PROLinePressure *TPtr = (PROLinePressure*)LinePressureTable[i];
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

int PROLinePressureSum::PutFloatValue( int ValueId, float NewValue){
	int Status = E_NO_ERR;
	//int ValUnitId = NO_UNIT;

	//switch ( ValueId ) {
	//default:
//	Status = PROLinePressure::PutFloatValue(ValueId,NewValue);
	//    break;
	//}
	return(Status);
}

int PROLinePressureSum::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}


