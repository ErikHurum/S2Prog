//---------------------------------------------------------------------------
#ifndef AlarmLevelChangeH
	#define AlarmLevelChangeH
class PROTank;
class AlarmLevelChange:public AlarmBasic {
private:
	PROTank *PROTankPtr;
public:
	static unsigned NumberOfAlarmSettings;
	AlarmLevelChange(PRogramObjectBase *PROPtr,float Lim, bool Lock=false);

	void Check(void);
// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	void SetEnable(EnableCmd Cmd);
};

//---------------------------------------------------------------------------
#endif
