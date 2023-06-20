#pragma once
#ifndef AnPro3objectH
#define AnPro3objectH
///////////////////////////////////////////////////////////////
//
// ANPro3 object.
//
// This module contains ANPro3 support. Use the ANPro3 documentation for
// reference.
//
// Revision history:
// Created: ??? EHS
// Communication with Consultas loading calculator for Vikstraum
// Revision 1.
// Adjusted according to requirements from Arjen/Broere for Duch Sailor
// Revision 2.
// Adjusted configuration of delay between packets from ticks to seconds
// with decimal point
// Revision 3.
// Implemented first version of request system. Includes alarm status.
// Revision 4. 16/10/00 EHS
// Now supports request for multiple tanks
// Revision 5.
// NOT IMPLEMENTED!! Must also have RAW LEVEL.
///////////////////////////////////////////////////////////////

struct ValInfo {
    short Value;
    U8   Width,
    DecPnt;
};


class AnPro3object:public PRogramObject {
private:
    static ConfigKeyWord ValueKey[];
	static char* NextField(char* Buf, char Separator);
    static void SortANPRO3KeywordList(void);
    static int FindValueKey(AnsiString KWord);
    bool   isNEMA;

public:
    static vector<AnPro3object*>AnPro3objectVector;
	static set<PRogramObjectBase*>ObjectSet;

    time_t TraceTime;
    AnsiString RequestStr;
    AnsiString ReplyStr;
    int TCUAddress;
    int WinUart;
    vector<int>SysDataValTable;
    vector<int>TnkDataValTable;
    vector<int>LPrDataValTable;
    vector<int>TmpDataValTable;

    bool  RequestMode;
    int   Checksum_Type;
    int   ValueErrorAction;
    AnsiString SyncStr;
    int   Delay;
    char  Separator;
    bool  IncludeHWStatus;
    bool  IncludeAlarm;
    bool  ClearRxBufAfterReceive;
    bool  SOAllExtraSpace;
    bool  SendAlarmsOnly;
    vector<int>AlarmTypeList;
    vector<unsigned>IdNumbers;
    set<PRogramObject*>PROList;
    set<AlarmBasic*>AlarmSet;
    set<AlarmBasic*>ActAlarmSet;
    PROLinkedList *AlarmList;

    AnPro3object(unsigned IDNumber=0);
    ~AnPro3object(void);
    void Initiate(void);
    void WriteConfigToFile(TSNConfigString &ConfigString);
    int LoadConfigFromFile(TSNConfigString &ConfigString);
    void SetAlarmList(void);
    void SetProList(void);
    static void SetGlobalProList(void);
	static void AddAlarm(AlarmBasic *AlPtr);

    void SendString(TSNUart *PortPtr, AnsiString Buf);
    bool ControlCheckSum(char *RxBuf);
    bool ReceiveRequest(TSNUart *PortPtr, char *RxBuf, int BufSize);
    void HandleRequest(TSNUart *PortPtr);
	void SendObject(TSNUart *PortPtr,PROXRefObject *ObjPtr, char *Heading=NULL);
    bool SendSysInfo(TSNUart *PortPtr);
    bool SendTank(TSNUart *PortPtr,int Id);
    bool SendLPressure(TSNUart *PortPtr,int Id);
    bool SendTemperature(TSNUart *PortPtr,int Id);
	bool SendALarms(TSNUart *PortPtr);
    bool SendNEMA(TSNUart *PortPtr);
    void ANPRO3Task(TSNUart *PortPtr);
    int  ReceiveData(U8* data);
    int SendData(U16 cmd);

    static AnPro3object* FindANPRO3Object(int portNo);

};
#endif

