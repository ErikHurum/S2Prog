//---------------------------------------------------------------------------
#ifndef AlarmLoLoLevelH
#define AlarmLoLoLevelH
class PROTank;
class AlarmLoLoLevel:public AlarmLowLevel{
public:
	static unsigned NumberOfAlarmSettings;
	AlarmLoLoLevel(PRogramObjectBase *PROPtr,float Lim, bool Lock);
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
