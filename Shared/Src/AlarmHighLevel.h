//---------------------------------------------------------------------------
#ifndef AlarmHighLevelH
#define AlarmHighLevelH
class PROTank;
class AlarmHighLevel:public AlarmBasic{
private:
	PROTank *PROTankPtr;
	TSNTable1Degree *VolumeTab;
	TSNTable1Degree *LevVolumeTab;
	TSNTable1Degree *UllVolumeTab;
	int LimitType;
	bool OnlyLevel;

public:
	static unsigned NumberOfAlarmSettings;
	AlarmHighLevel(PRogramObjectBase *PROPtr,float Lim, bool Lock);

	void Check(void);
// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
