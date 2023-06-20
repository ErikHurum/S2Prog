//---------------------------------------------------------------------------
#ifndef AIAtmPressSensor_mVH
#define AIAtmPressSensor_mVH




class AIAtmPressSensor_mV:public AIPressSensor_mV {
public:
	AIAtmPressSensor_mV(int SnsType);
//	AIAtmPressSensor_mV(AnalogInput *Sns);
	~AIAtmPressSensor_mV(void);
// Routines for the librarian
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);

	float Calculate(void);
};

//---------------------------------------------------------------------------
#endif
