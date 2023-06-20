//---------------------------------------------------------------------------
#ifndef CtrlHornH
#define CtrlHornH
class CtrlHorn:
	public PROControl
{
protected:

public:
	CtrlHorn(void);
	~CtrlHorn(void);
	AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);

//	void WriteConfigToFile(TSNConfigString &ConfigString);
//	int LoadConfigFromFile(TSNConfigString &ConfigString);
	void Update(char Mode);

};
//---------------------------------------------------------------------------
#endif
