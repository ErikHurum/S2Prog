//---------------------------------------------------------------------------
#ifndef AIDiffPressSensor_mAH
#define AIDiffPressSensor_mAH

class AIDiffPressSensor_mA:public AIPressSensor_mA {
public:
	AIDiffPressSensor_mA(int SnsType);
//	AIDiffPressSensor_mA(AnalogInput *Sns);
	~AIDiffPressSensor_mA(void);

	virtual float Calculate(void);
// Routines for the librarian
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);

	//virtual int ReceiveData(U8* data);
	//virtual int SendData(U16 cmd);

	void AdjustOffset(float OffsetAdjust);


};

//---------------------------------------------------------------------------
#endif
