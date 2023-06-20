#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------


PROTempEmpty::PROTempEmpty(void):PROTemperature(false)
{
	IDNumber = (C_PRO_TEMP_EMPTY << 16 )+1;
	Type = C_PRO_TEMP_EMPTY;
}

PROTempEmpty::~PROTempEmpty(void)
{
}
//---------------------------------------------------------------------------

int PROTempEmpty::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
	int Status  = GETVAL_NO_DISPLAY;
	Unit        = 0;
	MyRetValue  = 0;
	return(Status);
}

int PROTempEmpty::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status  = GETVAL_NO_DISPLAY;
	MyString    = "";
	return(Status);
}


int PROTempEmpty::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int PROTempEmpty::PutFloatValue( int ValueId, float NewValue)
{
	int Status = E_NO_ERR;
	//int ValUnitId = NO_UNIT;
	return(Status);
}


