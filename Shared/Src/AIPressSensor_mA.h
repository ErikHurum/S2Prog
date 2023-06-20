//---------------------------------------------------------------------------
#ifndef AIPressSensor_mAH
#define AIPressSensor_mAH
typedef struct {
	float x,y;
} mAEntry;


class AIPressSensor_mA:public AIPressSensor {
private:
	float *TempPtr;
	float  PrevTemp;
	ANCriticalSection CalDataSema;

protected:
	bool Error;
    static ANCriticalSection LogSema;

public:
    static set<AIPressSensor_mA*>ObjectSet;
	AIPressSensor_mA(int SnsType, bool IsAtmRef=false);
//	AIPressSensor_mA(AnalogInput *Sns);
	~AIPressSensor_mA(void);
	U8 GetFilter(void);
	float  TZS,TSS;			 // Zero & Sensetivity shift
	vector<float>mACal;
	vector<float>mAPcnt;
	vector<float>mACor;
	float Calculate(void);

	void Temp_Correction(float Temp);
	float Get_Percent(float mA);
	float Get_Cor_PCnt(float Amp);
	float Get_Press(float Amp,float Temp);

// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);

	//virtual int ReceiveData(U8* data);
	//virtual int SendData(U16 cmd);
    void AddShortCircuitAlarm(void);


};

//---------------------------------------------------------------------------
#endif
