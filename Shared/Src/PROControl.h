//---------------------------------------------------------------------------
#ifndef PROControlH
#define PROControlH

#define R_ACTIVATE0 0x1
#define R_ACTIVATE1 0x2
#define R_ACTIVATE2 0x4
#define R_ACTIVATE3 0x8
#define R_INACTIVE  0x10
class AlarmBasic;
class PROControl:
public PRogramObjectBase {
private:
	int  RelayIndex;
protected:
	int ActiveAl,AcknowledgedAl,IdleAl,SuspAl,OutsideLim, OutsideLimEnabled;
	int PrevAlCnt;
public:
	static int NumberOfPRO;
	PROControl(int RIndex);
	~PROControl(void);
	int NormalState;
	int DeactivateBy;
	int AlarmDelay;
	set<PRogramObjectBase*>PROList;
	set<AlarmBasic*>AlarmList;
	int AlarmAlternative;
	vector<int>AlarmTypeList;

	vector<unsigned>IdNumbers;
	int TCUAddress;
	int TCUPortNo;
	volatile unsigned Priority;
#ifdef S2TXU
	OS_RSEMA CtrlSema;
#endif

	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	virtual bool LoadConfigString(TSNConfigString &ConfigString);
	void SetAlarmList(void);
	void SetProList(void);
	bool GetOutputVal(bool &IsChange);
	void UpdateRelay(void);
	virtual void Update(char Mode);
	virtual void Activate(int Prio, U8 Cmd, int OnPeriod, int OffPeriod);
	virtual void DeActivate(void);

};
//---------------------------------------------------------------------------
#endif

