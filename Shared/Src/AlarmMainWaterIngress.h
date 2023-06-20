//---------------------------------------------------------------------------
#ifndef AlarmMainWaterIngressH
#define AlarmMainWaterIngressH

class AlarmMainWaterIngress:public AlarmBasic{
public:
	static unsigned NumberOfAlarmSettings;
  static float TimeOut;
	AlarmMainWaterIngress(PRogramObjectBase *PROPtr);

	void Check(void);


// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

};

//---------------------------------------------------------------------------
#endif
