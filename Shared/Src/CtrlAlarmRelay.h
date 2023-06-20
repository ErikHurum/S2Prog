//---------------------------------------------------------------------------
#ifndef CtrlAlarmRelayH
#define CtrlAlarmRelayH

class CtrlAlarmRelay:
	public PROControl
{
protected:

public:
	CtrlAlarmRelay(int Number);
	~CtrlAlarmRelay(void);
  int NumberOnTCU;

	AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);
//	void WriteConfigToFile(TSNConfigString &ConfigString);
//	int LoadConfigFromFile(TSNConfigString &ConfigString);
  void Update(char Mode);


};
//---------------------------------------------------------------------------
#endif
