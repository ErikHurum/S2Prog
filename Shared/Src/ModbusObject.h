//---------------------------------------------------------------------------
#ifndef ModbusObjectH
#define ModbusObjectH
class ModbusObject : public PRogramObject, public ModbusPro {
private:
#ifdef S2TXU
    static TSN_STACKPTR int ModbusStack[4096];
#endif
    static void ExchangeData(void);

	static map<U32, ModbusObject *>DeviceMap;

protected:
    AnsiString IPAddress;
    int TCUAddress;
    int TCUPortNo;
    int Address;
    int Channel;
    int ProChannel;
    bool IsCreatedFromMultiple;
public:
#ifdef S2TXU
	static vector<OS_TASK*>ModbusTaskVector;
#endif
    bool IsActive;
    static set<ModbusObject *>ModbusSet;
    static set<ModbusObject *>MyModbusSet;
#ifdef S2TXU
    static OS_TASK *ModbusTaskPtr;
    static OS_TASK *ModbusUpdateTaskPtr;
#endif

    ModbusObject(void);
    ~ModbusObject(void);
// Routines for the Configuration
    virtual AnsiString MakeConfigString(int ExtraTabs = 0);
    virtual bool LoadConfigString(TSNConfigString &ConfigString);
    virtual void SetAlarmList(void);
    virtual void SetProList(void);
    bool AddressMatch(int TCUAddr, int TCUPort, int Addr, int Chn);
    bool TCUPortMatch(int TCUAddr, int TCUPort);

    ModbusUnit* FindUnit(void);

    static void StartExchangeData(void);

    static void InitMap(void);

    virtual void Update(void) = 0;
    static bool ChannelIsReserved(set<ModbusObject *>MySet, int Addr, int Chn);
    static int FindFirstFree(set<ModbusObject *>MySet, int Addr, int FirstChannel);
    static int LastChannel(set<ModbusObject *>MySet, int Addr);
    static void HandleRequest(TSNUart *Port, int FrameTimeOut, int FrameSpaceTime);

#ifdef ANWIN
    static set<ModbusUnit *>GetModbusUnits(void);
    //static bool ThreadModBusHandle(HANDLE m_hWagoSocketHandle, mbtReadRegistersFunc pMBTReadRegisters, mbtWriteRegistersFunc pMBTWriteRegisters, mbtReadCoilsFunc pMBTReadCoils, mbtWriteCoilsFunc pMBTWriteCoils);
#else
    static set<ModbusUnit *>GetModbusUnits(unsigned PortNumber);
    static void ModbusTask(TSNUart *Port);
    static TSN_TASK ExchangeDataTask;
#endif
    static void DeleteAllInDeviceMap(void);
    static void SetGlobalProList(void);
    static set<PRogramObjectBase *> GetModbusObjectSet(void);
    static bool HasModbusMasterPC(void);
    virtual void UpdateFromMultiple(unsigned pIdNumber, int pChannel);
    int GetChannel(void);
    int GetTCUAddress();
    int GetTCUPortNo(void);
    int GetAddress(void);
    virtual int GetObjectId(void);
    virtual AnsiString GetValueKey(void);
    virtual AnsiString GetRegisterType(void);
	virtual AnsiString GetRegisterValue(void);
    bool GetDigitalStatus(void);
    virtual AlarmBasic* GetAlarmPtr(void);





};
//---------------------------------------------------------------------------
#endif

