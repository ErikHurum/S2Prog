#pragma once
//---------------------------------------------------------------------------
#ifndef LevelSwitchVegaH
#define LevelSwitchVegaH
class AILevelSwitchVega:
	public AILevelSwitch_mA
{
private:
	float SwitchTest;
	int LastTestTime;
    int TestCount;
public:
	AILevelSwitchVega(int SnsType, float mA_On, float mA_Off, float mA_Win, float mA_Test);
	~AILevelSwitchVega(void);
// Routines for Saving of Settings
	AnsiString SaveAISettings(int ExtraTab=0);
	bool RestoreAISettings(TSNConfigString *ConfigString);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	float Calculate(void);


};
//---------------------------------------------------------------------------
#endif
