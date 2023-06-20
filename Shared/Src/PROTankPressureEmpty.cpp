#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

PROTankPressureEmpty::PROTankPressureEmpty(void):PROTankPressure(false)
{
	IDNumber      = (C_PRO_TANKPRESS_EMPTY << 16 );
	Type          = C_PRO_TANKPRESS_EMPTY;
	Name          = "";
}

PROTankPressureEmpty::~PROTankPressureEmpty(void)
{
}
//---------------------------------------------------------------------------
int PROTankPressureEmpty::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
	int Status  = GETVAL_NO_DISPLAY;
	Unit        = 0;
	MyRetValue  = 0;
	return(Status);
}

int PROTankPressureEmpty::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status  = GETVAL_NO_DISPLAY;
	MyString    = "";
	return(Status);
}


int PROTankPressureEmpty::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status      =E_LOCAL_ONLY;
	int ValUnitId   = NO_UNIT;
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int PROTankPressureEmpty::PutFloatValue( int ValueId, float NewValue)
{
	int Status = E_LOCAL_ONLY;
	return(Status);
}


