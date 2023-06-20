//---------------------------------------------------------------------------
#ifndef AlarmLowLevelH
#define AlarmLowLevelH
class PROTank;
class AlarmLowLevel:public AlarmBasic{
protected:
	PROTank *PROTankPtr;
	TSNTable1Degree *VolumeTab;
	TSNTable1Degree *LevVolumeTab;
	TSNTable1Degree *UllVolumeTab;
	int LimitType;
	bool OnlyLevel;

public:
	static unsigned NumberOfAlarmSettings;
	AlarmLowLevel(PRogramObjectBase *PROPtr,float Lim, bool Lock);

	void Check(void);

// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
