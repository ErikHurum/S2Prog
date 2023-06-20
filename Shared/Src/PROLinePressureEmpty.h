//---------------------------------------------------------------------------
#ifndef PROLinePressureEmptyH
#define PROLinePressureEmptyH

class PROLinePressureEmpty :
	public PROLinePressure
{
public:
	PROLinePressureEmpty(void);
	~PROLinePressureEmpty(void);
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

};

//---------------------------------------------------------------------------
#endif
