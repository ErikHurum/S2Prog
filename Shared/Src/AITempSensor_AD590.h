//---------------------------------------------------------------------------
#ifndef AITempSensor_AD590H
#define AITempSensor_AD590H

class AITempSensor_AD590:public AITempSensor {
private:
	ConfigPacket ADConfigData;
public:
	AITempSensor_AD590(void);
	~AITempSensor_AD590(void);
	void Initialize(void);
	AnsiString MakeConfigString(int ExtraTabs=0);

    void NewValue(float NewValue);
// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	void SetStatus(U8 *NewStatus);

};

//---------------------------------------------------------------------------
#endif
