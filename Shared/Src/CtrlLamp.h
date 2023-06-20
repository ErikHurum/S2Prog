//---------------------------------------------------------------------------
#ifndef CtrlLampH
#define CtrlLampH
class CtrlLamp:
public PROControl {
protected:

	public:
	CtrlLamp(void);
	~CtrlLamp(void);

	AnsiString MakeConfigString(int ExtraTabs=0);
	bool LoadConfigString(TSNConfigString &ConfigString);
	void Update(char Mode);
//	void WriteConfigToFile(TSNConfigString &ConfigString);
//	int LoadConfigFromFile(TSNConfigString &ConfigString);

};
//---------------------------------------------------------------------------
#endif
