#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

PROTempSum::PROTempSum(vector<PRogramObjectBase*>&TTable,bool Fixed):PROTemperature(false),
TempTable(TTable)
{
	IDNumber      = (C_PRO_TEMP_SUM << 16 );
	Type          = C_PRO_TEMP_SUM;
	IsFixed       = Fixed;
	Name          = "Average";

}

PROTempSum::~PROTempSum(void)
{
}
//---------------------------------------------------------------------------

int PROTempSum::FindMyEntry(void)
{
	unsigned i=0;
	while ( i < TempTable.size() ) {
		if ( TempTable[i] == this ) {
			return(i);
		} else {
			i++;
		}
	}
	return(-1);	// If we get her, we found nothing!!!
}

int PROTempSum::FindStart(int MyEnd)
{
	int MyStart=0;
	if ( MyEnd > 0 ) {
		int i=MyEnd-1;
		bool OtherSum=false;
		while ( !OtherSum && ( i > 0) ) {
			if ( TempTable[i]->Type == C_PRO_TEMP_SUM ) {
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


bool PROTempSum::FindRange(int &MyStart, int &MyEnd)
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

int PROTempSum::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit){
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_TEMP:
		DecPnt     = 1;
		Unit       = TEMP_UNIT;
		{
			int MyStart,MyEnd;
			if ( FindRange(MyStart,MyEnd ) ) {
				double tmpTempE  = 0.0;
				double tmpTempV  = 0.0;
				int TmpCntE     = 0;
				int TmpCntV     = 0;
				for ( int i=MyStart; i < MyEnd; i++ ) {
					PROTemperature *TPtr = (PROTemperature*)TempTable[i];
					if ( TPtr && TPtr->IsNewData && TPtr->HasTemp ) {
						if ( TPtr->Level ) {
							TmpCntV++;
							tmpTempV += TPtr->Temperature;
						} else {
							TmpCntE++;
							tmpTempE += TPtr->Temperature;
						}
					}
				}
				if ( TmpCntV ) {
					Temperature = tmpTempV/double(TmpCntV);
					MyRetValue  = Temperature;
				} else if ( TmpCntE ) {
					Temperature = tmpTempE/double(TmpCntE);
					MyRetValue  = Temperature;
				} else {
					Status       = GETVAL_NOT_AVAILABLE;
				}
			} else {
				Status       = GETVAL_NOT_AVAILABLE;
			}
		}
		break;
	default:
		Status = GETVAL_NO_DISPLAY;
//			Status = PROTemperature::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
		break;
	}
	return(Status);
}

int PROTempSum::GetStringValue(int ValueId, int Index, AnsiString &MyString){
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_PRO_STATUS:
		FindPROStatus(MyString);
		break;
	default:
// 			Status = GETVAL_NO_DISPLAY;
		Status = PROTemperature::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}


int PROTempSum::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId){
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_TEMP       :
    case SVT_VAPOR_TEMP :
        Status = E_NO_INPUT_PERMISSION;
        break;
    case SVT_HI_TEMP_ENABLE:
    case SVT_LO_TEMP_ENABLE:
    case SVT_HI_TEMP_LIMIT:
    case SVT_LO_TEMP_LIMIT:
    case SVT_HI_BOT_TEMP_ENABLE:
    case SVT_LO_BOT_TEMP_ENABLE:
    case SVT_HI_BOT_TEMP_LIMIT:
	case SVT_LO_BOT_TEMP_LIMIT:
    case SVT_T1  :
    case SVT_T1_GAIN :
    case SVT_T1_OFFSET :
    case SVT_T2  :
    case SVT_T2_GAIN :
    case SVT_T2_OFFSET :
    case SVT_T3  :
    case SVT_T3_GAIN :
    case SVT_T3_OFFSET :
    case SVT_T4  :
    case SVT_T4_GAIN :
    case SVT_T4_OFFSET :
    case SVT_T5  :
    case SVT_T5_GAIN :
    case SVT_T5_OFFSET :
    case SVT_TT  :
    case SVT_TT_GAIN :
    case SVT_TT_OFFSET :
    case SVT_T1_ENABLE :
    case SVT_T2_ENABLE :
    case SVT_T5_ENABLE :
    case SVT_T3_ENABLE :
    case SVT_T4_ENABLE :
    case SVT_TP_ENABLE :
        {
            int MyStart, MyEnd;
			int tmpStatus = E_NO_ERR;
			if (FindRange(MyStart, MyEnd)) {
                for (int i = MyStart; i < MyEnd; i++) {
					PROTemperature *TPtr = (PROTemperature *)TempTable[i];
                    if (TPtr) {
                        tmpStatus |= LibPutValue(ValueId, TPtr, NewValue, Local, true);
                    }
                }
                if (tmpStatus != E_NO_ERR) {
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
    if (Status == E_NO_ERR) {
        Status = E_LOCAL_ONLY;
        SetModifiedFlag();
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROTempSum::PutFloatValue( int ValueId, float NewValue){
	int Status = E_NO_ERR;
	// int ValUnitId = NO_UNIT;
	//switch ( ValueId ) {
	//default:
//	Status = PROTemperature::PutFloatValue(ValueId,NewValue);
	//    break;
	//}
	return(Status);
}

int PROTempSum::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}


