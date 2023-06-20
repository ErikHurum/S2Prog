
#ifndef ModbusUnitH
#define ModbusUnitH
class ModbusUnit:public ModbusPro,public PRogramObject {
private:
    struct AddressRange{
        unsigned First;
        unsigned Last;
        unsigned NumberOfAddr;
    };
    vector<AddressRange>AddressesVectAnalogIn;
    vector<AddressRange>AddressesVectAnalogOut;
    vector<AddressRange>AddressesVectDigitalIn;
    vector<AddressRange>AddressesVectDigitalOut;
    set<AnalogInput*>SensorSet;
    bool IsMaster;
    int Address;
    int ComPort;
    TSNUart *myPort;
    int MaxRegisters;
    int MaxCoils;
    int AddressSystem;
    int myRequestDelay;
    int myTimeOut;
    int myFrameSpaceTime;
    int myFrameTimeOut;
    static map<unsigned, ModbusUnit *>DeviceMap;
    set<int>ObjectIdSet;
    U16 AnalogOut    [MODBUS_MAX_REGISTERS];
    U16 AnalogIn     [MODBUS_MAX_REGISTERS];
    set<unsigned>AnalogInSet;
    set<unsigned>AnalogOutSet;
    set<unsigned>DigitalInSet;
    set<unsigned>DigitalOutSet;
    bool NewAnalogIn[MODBUS_MAX_REGISTERS];
    bool NewDigitalIn[MODBUS_MAX_REGISTERS];
    bool PreviousDigitalIn[MODBUS_MAX_REGISTERS];
    U8  DigitalOut[MODBUS_MAX_COILS/8];
    U8  DigitalIn [MODBUS_MAX_COILS/8];
    int LastAnalogOut;
    int LastAnalogIn;
    int LastDigitalOut;
    int LastDigitalIn;
    int StartAnalogOut;
    int StartAnalogIn;
    int StartDigitalOut;
    int StartDigitalIn;
    bool HasAnalogOut   ;
    bool HasDigitalOut  ;
    bool HasAnalogIn    ;
    bool HasDigitalIn   ;
    int  ComFailCount   ;
    int  ComTotalFailCount;
    set<PRogramObject*>IOUniquePROSet;
    bool hasNewRegOutput;
    bool hasNewCoilOutput;

public:
    static set<PRogramObjectBase*>ObjectSet;
    ModbusUnit(int Addr, int ComPortNo);
    ~ModbusUnit();
    U16  GetOutputRegister(int Index, bool LittleEndian = false);
    U16  GetRegister(int Index, bool LittleEndian = false);
    void SetRegister(int Index, U16 NewVal, bool LittleEndian = false);
    void SetRegisterString(int Index, AnsiString MyString, int Size);

    U16  GetRegisterDirect(int Channel, bool LittleEndian = false);
    void SetRegisterDirect(int Channel, U16 NewVal);

    void SetHoldingRegister(int Index, U16 NewVal, bool LittleEndian=false);
    void MoveRegisters(int Index, int Entries, int Size);
    bool HasNewValue(int Index);
    void HasReadValue(int Index);
    bool FlagNewValues(int FirstReg, int NumberOfRegs);
    bool HasNewDigitalValue(int Index);
    void HasReadDigitalValue(int Index);
    bool FlagNewDigitalValues(int FirstReg, int NumberOfRegs);

    bool GetCoilIn(int Index);
    bool GetCoilOut(int Index);
    bool GetCoils(U8 *Coils,int FirstCoil, int NumberOfCoils, U8 *DataPtr);
    bool SetInCoil(int Index, U16 State);
    bool InitInCoil(int Index, U16 State);
    bool SetHistoryCoil(int Index, U16 State, int Entries);
    bool SetCoil(int Index, bool State);
    bool SetCoilDirect(int Channel, bool State);
    bool SetCoils(int FirstCoil, int NumberOfCoils, U8 *DataPtr);
    void SetCoilHistory(int Index, bool State, int Entries);
    void SetPreviousState(int Channel, bool CurrentState);
    bool IsNewDigitalInput(int Channel, bool CurrentState);
    void HandleRequest(U8 *RequestData);
	ANCriticalSection AccessDigitalSema;
#ifdef ANWIN
	//bool HandleIO(HANDLE m_hWagoSocketHandle, mbtReadRegistersFunc pMBTReadRegisters, mbtWriteRegistersFunc pMBTWriteRegisters, mbtReadCoilsFunc pMBTReadCoils, mbtWriteCoilsFunc pMBTWriteCoils);
#else
    void HandleIO(void);
#endif
    static ModbusUnit* FindDevice(U8 TCUUnit, U16 ComPort, U8 Address);
    static void InsertInMap(U8 TCUUnit, U16 ComPort, U8 Address, int ObjType, int Channel, unsigned RefObjId = 0, bool isVolatile=false);
    static void DeleteAllInDeviceMap(void);
    bool SlaveSetRegisters(U16 *Registers,int FirstReg, int NumberOfRegs, U8 *DataPtr);
    bool SlaveGetRegisters(U16 *Registers,int FirstReg, int NumberOfRegs, U8 *DataPtr);
    void SetIsMaster(void);
    void SetAddressRanges(set<unsigned>AddressSet, vector<AddressRange>&AddressVector, int MaxAddressStep);
    int  GetFailCount(void);
    int  GetTotalFailCount(void);
    void SetHWFailure(bool Failure);
    void SetAlarmList(void);
    void SetProList(void);
    static void SetGlobalProList(void);
    static void SetToMaster(void);
	int ReceiveData(U8* data);
	int SendData(U16 Cmd=CMD_GENERIC_REALTIME_DATA);
    int GetActiveAlarms(void);
    void SetUpCom(TSNUart *Port, int RequestDelay, int TimeOut, int FrameSpaceTime, int FrameTimeOut);

};

#endif
