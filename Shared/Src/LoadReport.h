//---------------------------------------------------------------------------
#ifndef LoadReportH
#define LoadReportH

class LoadReport:
	public PRogramObject
{
private:
	vector<PRogramObjectBase*> TankVector;
	static ValueList ServiceReportTankValueList[];

public:
	static LoadReport *LoadReportPtr;
	LoadReport(void);
	~LoadReport(void);

	float BillLoading;
	float BillOfLadingVolume;
	AnsiString LoadPort;
	AnsiString DestPort;
	AnsiString Voyage;
	AnsiString Start;
	AnsiString Stop;
	AnsiString Inspection;
	AnsiString ShipName;
	AnsiString ShipTitle;
	AnsiString SurvName;
	AnsiString SurvTitle;
	AnsiString Remark1;
	float DraftFore;
	float DraftMid;
	float DraftAft;

// Routines for Saving of Settings
	void SaveSettings(TSNConfigString *SettingsString);
	bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);

 	virtual int ReceiveData(U8* data);
	virtual int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	void SetTankVector(vector<PRogramObjectBase*>TVector);
	float GetTotalWeight(void);
	float GetTotalVolume(void);


};

//---------------------------------------------------------------------------
#endif
