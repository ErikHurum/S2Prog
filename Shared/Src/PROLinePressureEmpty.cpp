#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------


PROLinePressureEmpty::PROLinePressureEmpty(void):PROLinePressure(0,false)
{
	IDNumber = (C_PRO_LINEPRESS_EMPTY << 16 );
	Type = C_PRO_LINEPRESS_EMPTY;
}


PROLinePressureEmpty::~PROLinePressureEmpty(void)
{
 	//Only increase: NumberOfPRO--;
}
//---------------------------------------------------------------------------

int PROLinePressureEmpty::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
	int Status  = GETVAL_NO_DISPLAY;
	Unit        = 0;
	MyRetValue  = 0;
	return(Status);
}

int PROLinePressureEmpty::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status  = GETVAL_NO_DISPLAY;
	MyString    = "";
	return(Status);
}


int PROLinePressureEmpty::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int PROLinePressureEmpty::PutFloatValue( int ValueId, float NewValue)
{
	int Status = E_NO_ERR;
	//int ValUnitId = NO_UNIT;
	return(Status);
}


