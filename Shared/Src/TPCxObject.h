#pragma once
//---------------------------------------------------------------------------
#ifndef TPCXOBJECTH
	#define TPCXOBJECTH
	#define TPCX_SIZE_MARGIN	5 // This margin is 2*STX + 0 byte..
	#define TPCX_MAX_PACKET_SIZE	( TPC_DISPLAY_BUF_SIZE - sizeof(ANPRO1_PacketHeading) - sizeof(ANPRO1_PacketTail)-TPCX_SIZE_MARGIN)

class TPCxObject :
public PRogramObject {
private:
	static set<PRogramObjectBase*>tPCLists[TPC_MAX_PRIM_ADRESSES];
	static vector<int>PrimaryAddressTable;
	static bool ShowAlarmMsg;
	int     FirstTime;
	U8 Version;
	U8 PCB_Type;
	U8 RxBufSize;
	U8 TxBufSize;
	U8 Restart;
	U8 SerialNumber;
public:
	static set<PRogramObjectBase*>ObjectSet;
	TPCxObject(void);
	TPCxObject(int number);
	void Initiate(void);
	~TPCxObject(void);
	int TCUAddress;
//  int TCUPort;
	//int TCUPortNo;
	int TPCType;
	int PrimaryAddress;
	int SecondaryAddress;
	AnsiString CurrentAlMessage;
	AnsiString CurrentAlLocName;
	volatile U8 CurrentLEDStatus;
	volatile AlarmBasic *CurrentAlarmPtr;


	//AnsiString Alarm[NoOfActAl++]
//  int CurrentComponentType;
	bool OnePROPtrOnly;
	TPCAlarmWindow* TPCAlarmWinPtr;
	TPCWindow* TPCWindows[TPC_MAX_DISPLAY_WINDOWS];
	int TPCWindowCount;

// Routines for the Configuration
	AnsiString MakeConfigString(int ExtraTabs=0);
	bool LoadConfigString(TSNConfigString &ConfigString);
	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);
	void SaveSettings(TSNConfigString *SettingsString);
	U16 AddAlarmWindow(U8 *TxBuf, U16 Ptr, bool Update, bool ShowAlarm=true);
	U16 AddUpperWindow(U8 *TxBuf, U16 Ptr, bool Update);
	U16 AddLowerWindow(U8 *TxBuf, U16 Ptr, bool Update, int WinOffset=1);
	U16 AddExtraWindows(U8 *TxBuf, U16 Ptr, bool Update);
	U16 AddGraphs(U8 *TxBuf, U16 Ptr, bool Update);
	U16 AddWindows(U8 *TxBuf,U16 Ptr, bool Update, bool ShowAlarm);
	U16 SetWindow(U8 *TxBuf,U16 Ptr, U8 WinIndex);
	U16 MakeAcknowledge(U8 *TxBuf, U16 Ptr);
	void AckAlarms(void);
	void SendtPCxAcknowledge(TSNUart *PortPtr);
	AnsiString GetLibValueTPCx(int ValueId, int ValueId2, PRogramObjectBase *ObjPtr, int Width, int Flag=SVT_FLAG_NORMAL, AnsiString *UnitStr=NULL);

	static void FindMaxPacketSize(void);
	static void InitializetPCxSystem(void);
	static void Handle(TSNUart *PortPtr);
	static void TPCxTask(TSNUart *PortPtr);
	static bool UnpackPacket(TSNUart *PortPtr, U8* Buf,int Size,set<PRogramObjectBase*>CurrenttpPCxList);




};
#endif


