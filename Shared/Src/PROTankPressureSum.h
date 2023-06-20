#pragma once
//---------------------------------------------------------------------------
#ifndef PROTankPressureSumH
#define PROTankPressureSumH

class PROTankPressureSum :
	public PROTankPressure
{
private:
	vector<PRogramObjectBase*>&TankTable;
	bool IsFixed;

public:
	PROTankPressureSum(vector<PRogramObjectBase*>&TTable,bool Fixed);
	~PROTankPressureSum(void);

	int FindMyEntry(void);
	int FindStart(int MyEnd);
	bool FindRange(int &MyStart, int &MyEnd);

	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	int FindPROStatus(AnsiString &MyString);

};

//---------------------------------------------------------------------------
#endif
