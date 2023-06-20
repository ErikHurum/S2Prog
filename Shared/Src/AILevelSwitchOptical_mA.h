#pragma once
//---------------------------------------------------------------------------
#ifndef LevAILevelSwitchOptical_mAH
#define AILevelSwitchOptical_mAH
class AILevelSwitchOptical_mA:
	public AnalogInput
{
private:
	float SwitchOn_mA ;
	float SwitchOff_mA;
	float SwitchWindow;
	float SwitchTest;
	float SwitchLight;
	vector<float>ValueVector;

public:
	float SwitchVariation;
	AILevelSwitchOptical_mA(int SnsType, float mA_On, float mA_Off, float mA_Win, float mA_Test, float mA_Light);
	~AILevelSwitchOptical_mA(void);
	U8 GetFilter(void);

// Routines for the Configuration
  AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	float Calculate(void);


};
//---------------------------------------------------------------------------
#endif
