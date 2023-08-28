//---------------------------------------------------------------------------
#ifndef PROTanksystemUnitH
#define PROTanksystemUnitH

struct DeviceData {
    int DeviceKey;
    int Address;
    AnsiString Description;
};

struct NetworkedDevice {
  int device_id;
  int device_address;
  AnsiString Description;
};

class PROTanksystemUnit :
   public PRogramObject {

protected:
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
    AnsiString LastOSErrTask;
    float  RunningHours;
    int IOLoadDelay;
    int   IO_ScanPeriod;
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
    static PROTanksystemUnit *MyTCUPtr;

#ifdef S2TXU
    static OS_STACKPTR int TaskStack[2048];
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
    static PROTanksystemUnit *MySelf;

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
    vector<PRogramObjectBase *>PROCargoTankVector            ;
    vector<PRogramObjectBase *>PROBallastTankVector          ;
    vector<PRogramObjectBase *>PROServiceTankVector          ;
    vector<PRogramObjectBase *>PROServiceTankvyFuelOilVector ;
    vector<PRogramObjectBase *>PROServiceTankselVector       ;
    vector<PRogramObjectBase *>PROServiceTankricantsVector   ;
    vector<PRogramObjectBase *>PROServiceTankcVector         ;
    vector<PRogramObjectBase *>PROServiceTankshWaterVector   ;
    vector<PRogramObjectBase *>PROTemperatureVector          ;
    vector<PRogramObjectBase *>PROTankPressureVector         ;
    vector<PRogramObjectBase *>PROLinePressureVector         ;
    vector<PRogramObjectBase *>PROVoidSpaceVector            ;
    vector<PRogramObjectBase *>PROWaterIngressVector         ;
    vector<PRogramObjectBase *>PROLevelSwitchVector          ;

    unsigned RxErrId;
    unsigned RxErrCmd;
    unsigned RxErrMsg;
    unsigned RxErrCnt;
    time_t	 RxErrTime;
    unsigned SysInfoRxFailCnt;

    AnsiString  TaskName[MAX_ANPRO10_NUMBER_OF_TASKS];
    int         StackUsed[MAX_ANPRO10_NUMBER_OF_TASKS];
    int         RawPerformance[MAX_ANPRO10_NUMBER_OF_TASKS];
    int         StackSpace[MAX_ANPRO10_NUMBER_OF_TASKS];
    int         NumberOfTasks;

    PROTanksystemUnit(int PortNo, int addr, int DevId, PROTanksystemUnit *TCUPtr);
    PROTanksystemUnit(void);

	PROTanksystemUnit(int addr, int DevId);
	void Initiate(void);
    void InitTDUWinUarts(void);
    ~PROTanksystemUnit(void);
    void AddAtmReferenceSensor(AIPressSensor *AtmRefSns);

    bool SetUart(int uart, int key, int Baudrate, int DataBit, int StopBit, char Parity);

// Routines for the Configuration
    void WriteConfigToFile(TSNConfigString& ConfigString);
    int LoadConfigFromFile(TSNConfigString& ConfigString);
    bool LoadConfigNetwork(TSNConfigString& ConfigString);
    void SetKeyFromUart(void);
    void SetProList(void);
    void SetId(void);
	void SetIdNet(void);
    static unsigned CreateId(int TCUAddr, int PortNo, int Addr);
    static PROTanksystemUnit* FindMySelf(int TCUAddress, int TCUPortNo, int MyAddress);
    U8 GetProgramType(void);

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
    static PROTanksystemUnit* FindDevice(TSNUart *Port, int SAddress, int SUnitId);
    void Update_Device_Info(TSNUart *Port, ANPRO10_COMMAND_2001 *InfoStruct);
    static void Update_Unit_Info(TSNUart *Port, ANPRO10_COMMAND_2001 *InfoStruct);

    void VersionControl(TSNUart *Port);
    void SetIOLoadDelay(int Delay);
    int  GetIOLoadDelay(void);
    void SetIO_ScanPeriod(int Delay);
    int  GetIO_ScanPeriod(void);


    static PROTanksystemUnit* FindTCU(int Address);
    static TSNUart *GetComPort(int TCUAddress, int PortNum);

    static vector<NetworkedDevice>  _net_devices;
    static PROTanksystemUnit* FindUnit(int address, int dev_id);

};
//---------------------------------------------------------------------------
#endif

