//---------------------------------------------------------------------------
#ifndef TPCAlarmWindowH
#define TPCAlarmWindowH

class TPCAlarmWindow
{
public:
	TPCAlarmWindow(void);
	~TPCAlarmWindow(void);
//	UCHAR   LocationType;
//	int   Index;
	short MainDisplay;
	short UpperDisplay;
  short MainGraph;
//	short Graph[TPC_MAX_GRAPHS];
//	short BottomDisplay;
//	short TopDisplay;
//	AnsiString ValName;
//	AnsiString LocName;
//	AnsiString MsgPtr;
//	float DispUVal;
//	float DispLVal;
//	UCHAR  GraphVal[TPC_MAX_GRAPHS];

// Routines for the Configuration
  AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);

};
#endif
