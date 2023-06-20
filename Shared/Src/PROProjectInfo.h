//---------------------------------------------------------------------------
#ifndef PROProjectInfoH
#define PROProjectInfoH
#define FLASH_RET_MODE_NONE 0
#define FLASH_RET_MODE_CONF 1
#define FLASH_RET_MODE_SETT 2

class PROProjectInfo :
public PRogramObjectBase {
public:
    static PROProjectInfo *PROProjectInfoPtr;
    static int NumberOfPRO;
    PROProjectInfo(void);
    ~PROProjectInfo(void);

    static int ProjectType;
    int NumberOfApp;
    int ApplicationList[MAX_APPL];
    static int AlarmSystemStartUpDelay;
    static bool isChemGasProject;
    static AnsiString ProjOwner;
    static AnsiString ProjTypeName;
    static AnsiString ProjectName;
    static AnsiString CallSign;
    static AnsiString IMONumber;
    static float LengthBetweenPP;
    static float LengthBetweenMarks;
    static float Width;
    static bool L_English,L_Norwegian,L_German,L_French,L_Spanish,L_Portuguese,L_Dutch;
    static float NoiseLimCargoB;
    static float NoiseLimCargoU;
    static float NoiseLimBallastB;
    static float NoiseLimBallastU;
    static float NoiseLimServiceB;
    static float NoiseLimServiceU;
    static float NoiseLimDefaultB;
    static float NoiseLimDefaultU;
    static float NoiseLimDefaultR;
    static float NoiseLimVoidSpace;
    static float OverfillLimit;
    static float HighLevelLimit;
    static float LowLevelLimit;
    static float LoLoLevelLimit;
    static float VoidSpaceLimit;
    static float LevelDiffLimit;
    static float HighTempLimit;
    static float LowTempLimit;
    static float IntHighTankPressLimit1;
    static float IntLowTankPressLimit1;
    static float IntHighTankPressLimit2;
    static float IntLowTankPressLimit2;
    static float HighTankPressLimit;
    static float LowTankPressLimit;
    static float HighVapourRetLimit;
    static float LowVapourRetLimit;
    static float HighPressVacLimit;
    static float LowPressVacLimit;
    static float HighIGP_Limit;
    static float LowIGP_Limit;
    static float HiHiLinePressLimit;
    static float HighLinePressLimit;
    static float LowLinePressLimit;

    static bool hasHighVapourRetLimit;
    static bool hasLowVapourRetLimit;
    static bool hasHighPressVacLimit;
    static bool hasLowPressVacLimit;
    static bool hasHighIGP_Limit;
    static bool hasLowIGP_Limit;
    static bool hasLoLoLevelLimit;

    static bool OverfillLocked;
    static bool HighLevelLocked;
    static bool LowLevelLocked;
    static bool LowLowLevelLocked;
    static bool HighTempLocked;
    static bool LowTempLocked;
    static bool HighTankPressLocked;
    static bool LowTankPressLocked;
    static bool HighIGP_Locked;
    static bool LowIGP_Locked ;
    static bool HighLinePressLocked;
    static bool LowLinePressLocked;
    static int  NumberOfHandheldUnits;
    static int  DecimalPointVolume;
    static int  DecimalPointWeight;
    static bool AutoAcknowledge;
    static bool SimulateIO;
    static bool SimulateFixedValues;
    static float Default_SwitchOn_mA;
    static float Default_SwitchOff_mA;
    static float Default_SwitchWindow;
    bool HasAtmRefSensor;
    bool HasInclinometer;
    bool HasDraftSensor;
	bool AlarmSettingsPINLock;
    static bool IntegratedLoadingComputer;
    static bool IsInlandVessel;
    static bool IsCustodyTransferSys;
    static int RequestConfig;
    static float TankMaxLoadTime;
    static float CableResistanceShip;
    static float CableResistanceSensor;
    static bool hasCableResistanceShip;
    static bool hasCableResistanceSensor;
    static bool UseTemperatureWindow;
    static unsigned TemperatureWindowMaxCnt;
    static float    TemperatureWindowTmpLim;
    static AnsiString IP_Address;
    static U32 IP_AddressMain;
    static U8  IP_AddressGateWay    ;
    static U8  IP_AddressTCU_Master ;
    static U8  IP_AddressTCUMasterStart;
    static U8  IP_AddressTCUSlaveStart;
    static U8  IP_AddressTCUSlaveEnd  ;
    static U8  IP_AddressTDUStart;
    static U8  IP_AddressTDUEnd;
    static U8  IP_AddressPCStart;
    static U8  IP_AddressPCEnd;
    static U32 IP_TCP_ServerPort;
    static U32 IP_UDP_NetPort;
 //   static U32 IP_TCP_FlashPort;
    static bool PressLim_mBar;

    static int UserUnits[UNIT_SETS];
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);

    void WriteConfigToFile(TSNConfigString &ConfigString);
    int LoadConfigFromFile(TSNConfigString &ConfigString);

// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int PutFloatValue( int ValueId, float NewValue);
    static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);


};

//---------------------------------------------------------------------------
#endif

