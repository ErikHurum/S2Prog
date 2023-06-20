#pragma once
//---------------------------------------------------------------------------
#ifndef PROLinePressureSumH
#define PROLinePressureSumH

class PROLinePressureSum :
	public PROLinePressure
{
private:
	vector<PRogramObjectBase*>&LinePressureTable;
	bool IsFixed;


public:
	PROLinePressureSum(vector<PRogramObjectBase*>&TTable,bool Fixed);
	~PROLinePressureSum(void);

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
