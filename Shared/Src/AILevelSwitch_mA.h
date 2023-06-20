#pragma once
//---------------------------------------------------------------------------
#ifndef LevelSwitch_mAH
#define LevelSwitch_mAH
class AILevelSwitch_mA:
	public AnalogInput
{
private:
	bool OverrideSwitchLimits;
protected:
	float SwitchOn_mA ;
	float SwitchOff_mA;
	float SwitchWindow;
	float SwitchMax_mA;
    AlarmBasic  *ShortCircuitPtr;
    AlarmBasic  *OpenLoopPtr;
public:
	AILevelSwitch_mA(int SnsType, float mA_On, float mA_Off, float mA_Win);
	~AILevelSwitch_mA(void);
	U8 GetFilter(void);

// Routines for the Configuration
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	virtual bool LoadConfigString(TSNConfigString &ConfigString);

// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	virtual float Calculate(void);


};
//---------------------------------------------------------------------------
#endif
