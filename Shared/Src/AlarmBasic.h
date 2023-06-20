//---------------------------------------------------------------------------
#ifndef AlarmBasicH
    #define AlarmBasicH
    #ifdef BORLAND
        #include <stdlib.h>
		#include "dinkumware\iomanip.h"
    #endif


enum EnableCmd {
    EnableFalse, EnableTrue, EnableUsePrevious, EnableNoChange, EnableNoMemFalse, EnableNoMemTrue,
};

class AlarmBasic:
public PRogramObjectBase {
protected:
    int     AlarmDelay;
    int     LastInactiveTime;
    bool    IsVisible;
    int     TPCMessageKey;
    int     MessageKey;
    float   Deadband;
    clock_t LastActiveTime;
    PRogramObjectBase *PROPointer;
    // Used for sorting in linked list
    U32     AlarmNo;
	bool    PreviousEnable;


public:

    enum AlarmState {
        AlIdle,AlActive,AlAknowledged,AlBlocked,AlError
    };
    struct StateAlarmTable {
        AlarmBasic *AlarmPtr;
        EnableCmd   Enable[pLimitUndefined];
    };
    static PROSafeLinkedList  PROActiveAlarmList;
    static PROSafeLinkedList  PROAcknowAlarmList;
    static set<AlarmBasic*>AlarmSet;
    static U32 CurrentAlarmNo;
    static volatile bool AlarmSound;
    bool   IsExtraAlarm;
    bool   IsHWAlarm;
    time_t  Time_Rised;
    time_t  Time_Acknowledged;
    time_t  Time_Disappeared;
    time_t  Time_Changed;
    static int    LocalResetCnt;
    static bool AlarmSilence;
    static AnsiString LogFileName;
    static ANCriticalSection AlarmSema;
	static ANCriticalSection LogSema;


    // Array used for a cyclic update of alarms
    static void AckAll(void);
    static void SetAllToIdle(void);
    static int CompareOnTimeRised(PRogramObjectBase *obj1, PRogramObjectBase *obj2);
    static int CompareOnTimeAcknowledged(PRogramObjectBase *obj1, PRogramObjectBase *obj2);
    static int CompareOnAlarmNo(PRogramObjectBase *obj1, PRogramObjectBase *obj2);


    AlarmBasic(void);
    AlarmBasic(PRogramObjectBase *PROPtr);
    AlarmBasic(PRogramObjectBase *PROPtr,float Lim);
    AlarmBasic(PRogramObjectBase *PROPtr,float Lim, float Dband,bool Enable);

    volatile AlarmState State;
    volatile AlarmState StateAtLastSend;
    bool   Enable;
    float  Limit;
    bool   Locked;
    volatile bool   OutsideLimit;
    virtual AnsiString Get_CompleteMessage(void);
    AnsiString Get_LogMessage(void);
    AnsiString Get_ANPro3Message(void);

    virtual AnsiString Get_Location(void);
    virtual void Check(void);
    AnsiString Get_TPCMessage(void);
    virtual AnsiString Get_Message(void);
    void UpdateAlarm(int Status);
protected:
    bool   CanDisableOnly;
    void Initiate(void);
    virtual void AddAlarm(void);
    virtual void RemoveAlarm(void);
public:
    void MoveAlarmToAknowledge(void);

    AnsiString GetRisedTime(void);
    AnsiString GetRisedTime(char *FormatStr);
    AnsiString GetResetTime(void);
    AnsiString GetResetTime(char *FormatStr);
    AnsiString GetDisappearedTime(void);
    AnsiString GetDisappearedTime(char *FormatStr);

// Routines for the Configuration
    AnsiString MakeConfigString(int ExtraTabs=0);
    bool LoadConfigString(TSNConfigString &ConfigString);
// Routines for Saving of Settings
    AnsiString SaveSettings(void);
    virtual bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int GetBitValue(int ValueId, int Index, bool &MyBit) ;
    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int PutFloatValue( int ValueId, float NewValue);
    virtual int PutBitValue(int ValueId, int Index, bool NewValue);

    virtual int ReceiveData(U8* data);
    virtual int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
    void SetModifiedFlag(void);
    void LogAlarm(AlarmState NewState);
    PRogramObjectBase* GetPROPointer(void);
    void operator=(const AlarmBasic& Alarm2);
    void SetEnable(EnableCmd Cmd);
    void SetAlarmToNormal(void);
    static void InitAlarmSystem(void);
	void SetAlarmDelay(int Dly);
	void SetAlarmLimit(float NewLim);
    static void SetRWPermissions(void);
    void LogEvent(AnsiString NewState);
    bool IsalreadyLogged(bool isEvent = false);
#ifdef ANWIN
    static void __fastcall InitDatabase(void);
	static void __fastcall PrepareDatabase(void);
	static void __fastcall CleanAlarmLogData(TLiteQuery *LiteQuery, int MaxAge);

#endif
    time_t GetEventTime(bool NewEvent=false);
};




#endif


