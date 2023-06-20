#ifndef AlarmmAmpOpenLoopH
#define AlarmmAmpOpenLoopH
class AlarmmAmpOpenLoop :
	public AlarmBasic
{
public:
	~AlarmmAmpOpenLoop(void);

	static unsigned NumberOfAlarmSettings;
	AlarmmAmpOpenLoop(PRogramObjectBase *PROPtr, int AlDelay=0);

	void Check(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};
#endif
