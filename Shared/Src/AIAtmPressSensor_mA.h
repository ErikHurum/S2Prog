//---------------------------------------------------------------------------
#ifndef AIAtmPressSensor_mAH
#define AIAtmPressSensor_mAH

class AIAtmPressSensor_mA:public AIPressSensor_mA {
private:
	bool IsOnTCU;

public:
	AIAtmPressSensor_mA(int SnsType, bool TCUFlag);
//	AIAtmPressSensor_mA(AnalogInput *Sns);
	~AIAtmPressSensor_mA(void);

	virtual float Calculate(void);
	void NewValue(float NewValue);
	void FilterValue(float NewVal,float FilterDegree);
// Routines for the librarian
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);

	//virtual int ReceiveData(U8* data);
	//virtual int SendData(U16 cmd);


};

//---------------------------------------------------------------------------
#endif
