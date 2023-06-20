//---------------------------------------------------------------------------
#ifndef AIPressSensor_mVH
#define AIPressSensor_mVH




class AIPressSensor_mV:public AIPressSensor {
private:
	AITempSensor *tmpSnsPtr;
public:
	AIPressSensor_mV(int SnsType,bool IsAtmRef=false);
//	AIPressSensor_mV(AnalogInput *Sns);
	~AIPressSensor_mV(void);
	bool ConvErr;
	bool CalErr;
	float CableLength;
	// The following declarations must have the same sequence as in CalData!!
	short   FRO[MAX_MV_CALDATA];
	short   G1[MAX_MV_CALDATA];
	short   G2[MAX_MV_CALDATA];
	short   G3[MAX_MV_CALDATA];
	short   NL1;
	short   NL2;
	float 	EEPromGain;
	float 	EEPromOffset;
	ConfigPacket ADConfigData;

	// End of citical sequence

	virtual float Calculate(void);
	//ValueList *GetCalValueInfoTable(int &Entries);

// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
	int ReceiveData(U8* data);
	int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	void PackSensorData(U8 CP[]);
	bool UnpackSensorData(U8 CP[]);
	void SetStatus(U8 *NewStatus);
	void SetTmpSnsPtr(AITempSensor *SnsPtr);
	AITempSensor *GetTmpSnsPtr(void);
	int GetEEPROM_Status(void);



};

//---------------------------------------------------------------------------
#endif
