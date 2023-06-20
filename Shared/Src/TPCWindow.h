//--------------------------------------------------------------------------
#ifndef TPCWindowH
#define TPCWindowH

class TPCWindow
{
public:
	TPCWindow(void);
  TPCWindow(PRogramObject *PRO, int Lower, int Upper, int Main);
	~TPCWindow(void);
//	UCHAR   LocationType;
//	int   Index;
	short MainDisplay;
	union
	{
		short UpperDisplay;
		short TopDisplay;
	};
	union
	{
		short MainGraph;
		short BottomDisplay;
	};
//	short Graph[TPC_MAX_GRAPHS];
//	short BottomDisplay;
//	short TopDisplay;
//	AnsiString ValName;
//	AnsiString LocName;
//	AnsiString MsgPtr;
//	float DispUVal;
//	float DispLVal;
//	UCHAR  GraphVal[TPC_MAX_GRAPHS];
  int PROIDNumber;
  PRogramObject *PROPtr;
// Routines for the Configuration
  virtual AnsiString MakeConfigString(int ExtraTabs=0);
  virtual bool LoadConfigString(TSNConfigString &ConfigString);
	virtual U16 MakeWindow(U8 *TxBuf,U16 Ptr, bool Update);
};
#endif
