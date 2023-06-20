//---------------------------------------------------------------------------
#ifndef PROTanksystemUnitH
#define PROTanksystemUnitH

struct DeviceData {
    int DeviceKey;
    int Address;
    AnsiString Description;
};
class PROUnitTCU :
   public PRogramObject {

private:
    U8        ProgramType; // 0 = Bootloader, 1 = Application
    U8        ErrorStatus;

    char      ActualSystemID[ANPRO10_ID_LENGTH];
    U16       ActualDataVersion;
    ProgramVersionInfo  ActualProgramVersion;
    ProgramVersionInfo  ActualBootVersion;
    time_t    ProgrDate;
    time_t    UpdateTime;
    bool      CreatedFromUart;
    AIPressSensor *AtmRefSensor;
    bool NoADFilter;
    float ADResults[MAX_TCU_AD_CHANNELS];
    float RxLoad[MAX_COM_PORTS];
    float TxLoad[MAX_COM_PORTS];
    U32   TxCnt[MAX_COM_PORTS],
    RxCnt[MAX_COM_PORTS];
    U8 LastOSErr;
    unsigned LastErrAddr;
    U8 FlashErrStatus;
    char LastOSErrTask[0x20];
    float  RunningHours;
    int IOLoadDelay;
    AlarmTXUComFailure *TXUComFailureAlarm;
    static ValueList TCU_R1UnitValueList[];
    static ValueList TCU_R2UnitValueList[];
    static ValueList TDUUnitValueList[];
    float RawLoad;
    float AvgLoad;
    float MaxLoad;
public:
    static set<PRogramObjectBase *>TanksystemUnitSet;
    static set<PRogramObjectBase *>TanksystemTCUSet;
    static unsigned MySettingsId;
    int MyPortNumberonTCU;
    static PROUnitTCU *MyTCUPtr;

#ifdef S2TXU
    static OS_STACKPTR int TaskStack[1000];
    static OS_TASK TaskHandle;           /* Task control blocks */
    static int SysInfoReqestComPortNum;
    static int SysInfoRequestId;
    static int SysInfoRequestAddress;
#endif
    AnsiString ProgramVersion;
    AIVoltageSensor *Internal24VSns;
    AIVoltageSensor *External24VSns;
    AI_AC_Sensor	*AC_OK_Sns;
    AIFuseSensor	*FuseSns;
    static PROUnitTCU *MySelf;

    set<PRogramObjectBase *>UnitPortList[MAX_COM_PORTS]; // To be used for router EHSMark
    int UnitID;
    U8  HWDeviceId;

    int Address;
    int TCUAddress;
    int PortKey[MAX_COM_PORTS];
    int PowerSource;
    float VoltageSetPoint;

    volatile unsigned FlashReceiveStatus;
    vector<vector<DeviceData> >DeviceDataVector;
    TSNUart *Channels[MAX_COM_PORTS];
    CtrlBuzzer      *CtrlBuzzerPtr;
    CtrlLight       *CtrlLightPtr;
    CtrlAlarmRelay  *CtrlAlarmRelayPtr1;
    CtrlAlarmRelay  *CtrlAlarmRelayPtr2;
    CtrlHorn        *CtrlHornPtr;
    CtrlLamp        *CtrlLampPtr;


    unsigned RxErrId;
    unsigned RxErrCmd;
    unsigned RxErrMsg;
    unsigned RxErrCnt;
    time_t	 RxErrTime;
    unsigned SysInfoRxFailCnt;

    PROUnitTCU(int PortNo, int addr, int id, PROUnitTCU *TCUPtr);
    PROUnitTCU(void);
    void Initiate(void);
    void InitTDUWinUarts(void);
    ~PROUnitTCU(void);
    void AddAtmReferenceSensor(AIPressSensor *AtmRefSns);

    bool SetUart(int uart, int key, int Baudrate, int DataBit, int StopBit, char Parity);

// Routines for the Configuration
    void WriteConfigToFile(TSNConfigString& ConfigString);
    int LoadConfigFromFile(TSNConfigString& ConfigString);
    void SetKeyFromUart(void);
    void SetProList(void);
    void SetId(void);
    static unsigned CreateId(int TCUAddr, int PortNo, int Addr);
    static PROUnitTCU* FindMySelf(int TCUAddress, int TCUPortNo, int MyAddress);


// Routines for the librarian
    int GetValue(int ValueId, int Index, float& MyValue,  int& DecPnt, int& Unit);
    int GetStringValue(int ValueId, int Index, AnsiString& MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);
    void FilterValue(float *OldVal, float NewVal, float FilterDegree = FILTER_INTERNAL_VOLTAGE);
    void Calculate(void);
    void AdjustVoltage(float Voltage, int Delay);
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);

	virtual ValueList* GetValueInfoTable(int& Entries, int Index=0);
	static ValueList* GetValueInfoTableStatic(int& Entries, int Index = 0, int HWDevId=0);



    // Communication routines to handle flashing and system info exchange
    void CheckSysInfo(void);
    void CheckSysInfo(TSNUart *Port);

    void GetConfigFromTDU(TSNUart *Port);
    static void SysInfoTask(void);
    static PROUnitTCU* FindDevice(TSNUart *Port, int SAddress, int SUnitId);
    void Update_Device_Info(TSNUart *Port, ANPRO10_COMMAND_2001 *InfoStruct);
    static void Update_Unit_Info(TSNUart *Port, ANPRO10_COMMAND_2001 *InfoStruct);

    void VersionControl(TSNUart *Port);
    void SetIOLoadDelay(int Delay);
    static PROUnitTCU* FindTCU(int Address);
};
//---------------------------------------------------------------------------
#endif

