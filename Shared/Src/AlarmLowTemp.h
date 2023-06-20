//---------------------------------------------------------------------------
#ifndef AlarmLowTempH
	#define AlarmLowTempH
class PROTemperature;
class AlarmLowTemp:public AlarmBasic {
protected:
	PROTemperature *PROTmpPtr;
public:
	static unsigned NumberOfAlarmSettings;
	AlarmLowTemp(PRogramObjectBase *PROPtr);

	void Check(void);

// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

};

//---------------------------------------------------------------------------
#endif
