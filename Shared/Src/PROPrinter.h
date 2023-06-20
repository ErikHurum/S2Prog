//---------------------------------------------------------------------------
#ifndef PROPrinterH
#define PROPrinterH

class PROPrinter:
public PRogramObjectBase {

private:
	bool Offline;
	U32  Progress;
	char *PrintBuf;
	int  PrintSize;
//#ifdef S2TXU
//	static OS_STACKPTR int TaskStack[2024];
//	static OS_TASK TaskHandle;			 /* Task control blocks */
//#endif
	TSNMessageQ PrintQueue;

public:
	static set<PRogramObjectBase*>ObjectSet;
	static int CurPrinterId;
	static int LogPrinterId;
	static PROPrinter *LastDefPrinter;
	int UnitID;
	int Address;
	int PortNum;
#ifdef S2TXU
	static OS_TASK* PrinterTaskPtr;
#endif
	PROPrinter(int PortNo, int TxId, int TxAddr);
	~PROPrinter(void);
// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
// Routines for Saving of Settings
	void SaveSettings(TSNConfigString *SettingsString);
	virtual bool RestoreSettings(TSNConfigString *SettingsString);

	int ReceiveData(U8* data);
	int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	static PROPrinter* FindPrinter(unsigned PortId);
	static PROPrinter* FindPrinterPort(int PortNum);
	static bool Print(int PortId, char *PBuf);
	bool Print(char* PBuf);
	void PrinterTask(TSNUart *Port);
};
//---------------------------------------------------------------------------
#endif
