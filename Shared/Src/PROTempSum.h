#pragma once
//---------------------------------------------------------------------------
#ifndef PROTempSumH
#define PROTempSumH

class PROTempSum :
	public PROTemperature
{
private:
	vector<PRogramObjectBase*>&TempTable;
	bool IsFixed;


public:
	PROTempSum(vector<PRogramObjectBase*>&TTable,bool Fixed);
	~PROTempSum(void);

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
