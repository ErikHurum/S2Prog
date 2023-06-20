#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------


PROTankEmpty::PROTankEmpty(void):PROTank(0,false)
{
	IDNumber = (C_PRO_TANK_EMPTY << 16 );
	Type = C_PRO_TANK_EMPTY;
	TankType = TANKTYPE_EMPTY;
}

PROTankEmpty::PROTankEmpty(int type,int number):PROTank(type,number,false)
{
	if ( number == 0 ) {
		IDNumber = (C_PRO_TANK_EMPTY << 16 );
	} else {
		IDNumber = number;
	}
	Type = C_PRO_TANK_EMPTY;
	TankType = TANKTYPE_EMPTY;
//	SetTankType(type);
}

PROTankEmpty::~PROTankEmpty(void)
{
}
//---------------------------------------------------------------------------

int PROTankEmpty::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_DISPLAY;
	Unit 		= 0;
	MyRetValue 	= 0;
	Name 		= "";
	return(Status);
}

int PROTankEmpty::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status  = GETVAL_NO_DISPLAY;
	MyString    = "";
	return(Status);
}


int PROTankEmpty::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status      =E_LOCAL_ONLY;
	int ValUnitId   = NO_UNIT;
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int PROTankEmpty::PutFloatValue( int ValueId, float NewValue)
{
	int Status = E_LOCAL_ONLY;
	return(Status);
}


