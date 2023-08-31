#pragma once
//---------------------------------------------------------------------------
#ifndef Anpro10PacketsH
#define Anpro10PacketsH

//#ifdef S2TXU
//#pragma bitfields=reversed
//#endif

#pragma pack(push,1)

struct NetHeading {
    U8  RxTypeId,
    RxAddress,
    TxTypeId,
    TxAddress;
    U16 Size;
    U8  CheckSum;
} ;
struct NetPacket {
    U16   Command;
    U16   Size;
    U8    RxTypeId,
    RxAddress;
    bool  RequestAck;
    void  *Data;
} ;
struct ANPRO10_PacketHeading {
    U8  rxtypeid,
    rxadr,
    txtypeid,
    txadr;
    U16 nob;
    U8  HCRC;
};

struct ANPRO10_PacketTail {  // cmd 0 No ack / 1 with ack
    U16 ecmd;
    U8  edata,
    SEQ,
    PCRC,
    EOT;
};

struct InternalCommandStruct {
    TSNUart *Port;
    U8      rxAddr;
    U8      rxId;
};

struct ANPRO10_CommandHeading {
    U16   CommandNo;
    U16   ndb;
};

struct QueueANPRO10_CommandHeading {
    InternalCommandStruct  TxInfo;
    ANPRO10_CommandHeading Data;
};

// TXU status
struct ANPRO10_COMMAND_OneByte {
    U16     CommandNo;
    U16     ndb;                // 85 bytes
    U8      Data;
};

struct QueueANPRO10_COMMAND_OneByte {
    InternalCommandStruct   TxInfo;
    ANPRO10_COMMAND_OneByte Data;
};

// 0/1
struct ANPRO10_COMMAND_END {
    U16   CommandNo;
    U16   ndb;

    U8    edata; // 0 = no error
};


struct ANPRO10_COMMAND_1001 {
    U8    CardChannel;
    U8    CardId;
    U8    CardAddress;
    U8    UnitProgVersion;
    U8    ComVersion;
    U8    StoreVersion;
    U16   RxBufSize;
    U16   TxBufSize;
    U8    ResetStatus;
    U8    ProgamTypeRunning;
    U16   TotalUnitRestart;
};

struct ANPRO10_COMMAND_1091 {
    U16   InternalAD[3];
};
#define ANPRO10_IO_PDATA_SIZE   256
struct IOFlashData {
    U16 Address;
    U16 Size;
    U8  FlashData[ANPRO10_IO_PDATA_SIZE];
};

struct ANPRO10_Command_1160_Single {
    U8 Channel;
    U8 Size;
    U8 Cmd;
    U8 DSize;
    U8 Data[MAX_ANPRO10_AD_DATA_SIZE-4];
};
struct ANPRO10_Command_1160 {
    U8 Channel;
    U8 Size;
    U8 Data[MAX_ANPRO10_AD_DATA_SIZE-2];
};


//struct ANPRO10_COMMAND_2000  // Request for TXU to send status (only heading)
#define ANPRO10_NAME_LENGTH 25
#define ANPRO10_ID_LENGTH   20
#include "FixedVariables.h"

struct SysInfoPacket {
    U8   DeviceId;
    U8   Address;
    U8   ProgramRunning;
    char SystemID[ANPRO10_ID_LENGTH];
    U16  DataVersion;
    ProgramVersionInfo ProgVersion;
    time_t ProgDate;
} ;

// TXU status
struct ANPRO10_COMMAND_2001 {
    U16     CommandNo;
    U16     ndb;                // 85 bytes

    U8      UnitID;
    U8      UnitAdress;
    U8      ProgramType; // 0 = Bootloader, 1 = Application, 2= ANWin

    char    SystemID[ANPRO10_ID_LENGTH];    // 20 bytes
    U16     DataVersion;
    ProgramVersionInfo ProgramVersion;
    ProgramVersionInfo BootVersion;
    time_t  ProgrDate;

    unsigned  LastOSError;
    unsigned  LastErrAddress;
    unsigned  FlashErrorStatus;
    char      LastOSErrorTask[TASK_NAME_LENGTH];
    U8        ComPortNo;


};

struct QueueANPRO10_COMMAND_2001 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2001 Data;
};

// ObjectPacket
struct ANPRO10_COMMAND_OBJ_PACKET {
    U16     CommandNo;
    U16     ndb;
    U32     ObjectId;
};

// Input packet 2010, 2011
struct ANPRO10_COMMAND_201X {
    U16     CommandNo;
    U16     ndb;
    U32     ObjectId;
    U32     ValueId;
    I16     UnitId;
    I16     CurrentUnit;
    char    InputBuffer[40];
    double  AlternativeInput;
    int     Index;
};

struct QueueANPRO10_COMMAND_201X {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_201X   Data;
};

// Input packet
struct ANPRO10_COMMAND_2020 {
    U16     CommandNo;
    U16     ndb;
    time_t  NewTime;
    long    TimeZone;
    int     DaylightSaving;
};

struct QueueANPRO10_COMMAND_2020 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2020   Data;
};

// PROTank real-time data
struct ANPRO10_COMMAND_2100 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    bool    HasLevelSensors;
    bool    HWFailure;
    bool    NotEmptyTank;
    U32     VapourAlarmSet;
    float   Level;
    float   LevelFC;
    float   LevelRef;
    float   Sounding;
    float   LevelDifference;
    float   Density;
    float   MeasuredDens;
    float   LoadRate;
    float   RemainingTime;
    float   LCWeight;
    float   LCVolume;
    time_t  LCDataTime;
    float   UllageFC;
    float   UllageAtSns;
    float   Volume;
    float   VolumePercent;
    char    HasWater;

    bool    IsNewData;
    float   RemainingVolume;
    float   FilteredVolPercent;
    float   UllageRef;
    bool    IsOnline;
};

struct QueueANPRO10_COMMAND_2100 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2100   Data;
};
// PROTank static data
struct ANPRO10_COMMAND_2102 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    float   SteelExp;
    float   AdjustedDBU;
    float   LevelOffset;
    float   StartVolPercent;
    float   NoiseLimitR;
    float   TableOffset;
    bool    UseMeasuredDensity;
    U8		State;
    float   VolCorrFactor;
    float   VolumeOffset;
};

struct QueueANPRO10_COMMAND_2102 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2102   Data;
};

// PROTankPressure realtime data
struct ANPRO10_COMMAND_2104 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    bool    HasPressure;
    bool    HWFailure;

    float   Pressure;
    bool    IsNewData;
};

struct QueueANPRO10_COMMAND_2104 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2104   Data;
};
// PROTankPressure realtime data
struct ANPRO10_COMMAND_2105 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     VapourAlarmSet;
};

struct QueueANPRO10_COMMAND_2105 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2105   Data;
};

// PROTemprature realtime data
struct ANPRO10_COMMAND_2106 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    bool    HasTemp;
    bool    HWFailure;
    int     StatusTemp;
    float   Temperature;
    float   VaporTemp;
    bool    IsNewData;
    float   BottomTemp;
    bool    IsOnline;
};

struct QueueANPRO10_COMMAND_2106 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2106   Data;
};


// PROLevelSwitch realtime data
struct ANPRO10_COMMAND_2120 {
    U16       CommandNo;
    U16       ndb;

    U32       ObjectId;
    bool      IsActive;
    bool      IsFailure;
    bool      HWFailure;
    bool      IsNewData;
    U8        State;
};

struct QueueANPRO10_COMMAND_2120 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2120   Data;
};

// PROTankWashingMachine realtime data
struct ANPRO10_COMMAND_2140 {
    U16       CommandNo;
    U16       ndb;

    U32       ObjectId;
    int       machineStatus;
    bool      IsFailure;
    bool      HWFailure;
    bool      IsNewData;
    float     Speed;
    time_t    RunningTime;
};

struct QueueANPRO10_COMMAND_2140 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2140   Data;
};

// PROTWaterHeater realtime data
struct ANPRO10_COMMAND_2150 {
    U16       CommandNo;
    U16       ndb;

    U32       ObjectId;
    float     PressureValue;
    float     InputTemperatureValue;
    float     OutputTemperatureValue;
    bool      HWFailure;
    bool      IsNewData;

    bool      HasPressure;
    bool      HasInputTemperature;
    bool      HasOutputTemperature;
};

struct QueueANPRO10_COMMAND_2150 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2150   Data;
};

// PROTWaterHeater realtime data
struct ANPRO10_COMMAND_2151 {
    U16       CommandNo;
    U16       ndb;

    U32       ObjectId;
    float     ManualPressure; 
    float     ManualInputTemp;
    float     ManualOutputTemp;
    float     MDO_Efficiency;
    float     MDO_kWh_per_ton;
};

struct QueueANPRO10_COMMAND_2151 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2151   Data;
};


// PROPrinter print RT data
struct ANPRO10_COMMAND_2400 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     Progress;
    bool    Offline;
};

struct QueueANPRO10_COMMAND_2400 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2400   Data;
};

// PROPrinter print data
struct ANPRO10_COMMAND_2402 {
    U16    CommandNo;
    U16    ndb;
    U8     ReportId;
    unsigned PortId;
};

struct QueueANPRO10_COMMAND_2402 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2402   Data;
};


// PROAnalogIn realtime data
struct ANPRO10_COMMAND_2508 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    bool    HWFailure;
    bool    MyHWFailure;
    bool    ResultOK;
    int     ActiveAlarms;
    float   CalcValue;
    float   FilteredValue;
    float   FreeValue;

};

struct QueueANPRO10_COMMAND_2508 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2508   Data;
};
// PROAnalogIn static data
struct ANPRO10_COMMAND_2510 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    float   Gain;
    float   Offset;
    float   MinRange;
    float   MaxRange;
    bool    Enable;
    bool    NewSensor;
    char    SerialNo[15];
};

struct QueueANPRO10_COMMAND_2510 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2510   Data;
};

struct ANPRO10_COMMAND_P906 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    float   Gain;
    float   Offset;
    float   MinRange;
    float   MaxRange;
    bool    Enable;
    bool    NewSensor;
    char    SerialNo[10];

	short   FRO[MAX_MV_CALDATA];
	short   G1[MAX_MV_CALDATA];
	short   G2[MAX_MV_CALDATA];
	short   G3[MAX_MV_CALDATA];
	short   NL1;
	short   NL2;
	float 	EEPromGain;
	float 	EEPromOffset;
};

struct QueueANPRO10_COMMAND_P906 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_P906   Data;
};


// AIRadarSensorHart realtime data
struct ANPRO10_COMMAND_2520 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    bool    HWFailure;
    bool    MyHWFailure;
    bool    ResultOK;
    U8      Failure;
    int     ActiveAlarms;
    float   CalcValue;
    float   FilteredValue;
    float   HartValue;
    int     HartComErrorCnt;
    clock_t TimeStamp;

};

struct QueueANPRO10_COMMAND_2520 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2520   Data;
};

// AIRadarSensorHart realtime data
struct ANPRO10_COMMAND_2522 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    bool    HWFailure;
    bool    MyHWFailure;
    bool    ResultOK;
    U8      Failure;
    int     ActiveAlarms;
    float   CalcValue;
    float   FilteredValue;
    clock_t TimeStamp;

};

struct QueueANPRO10_COMMAND_2522 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2522   Data;
};

struct ANPRO10_COMMAND_2530 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    bool    HWFailure;
    bool    Override;
    float   MainAlarmValue;
    float   PreAlarmValue;
    bool    IsNewData;
};

struct QueueANPRO10_COMMAND_2530 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2530   Data;
};

struct ANPRO10_COMMAND_2601 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     FailCntTotal;
    U32     FailCnt;
    U16     PowerStatus;
    U8      Filters[MAX_AN_ZBANA_CHANNELS];
    U8      Status[MAX_AN_ZBANA_CHANNELS];
    float   mAValues[MAX_AN_ZBANA_CHANNELS];
};

struct QueueANPRO10_COMMAND_2601 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2601   Data;
};

struct ANPRO10_COMMAND_2603 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     FailCntTotal;
    U32     FailCnt;
    U16     PowerStatus;
    U8      Filters[MAX_AN_ZBANA_CHANNELS];
    U8      Status[MAX_AN_ZBANA_CHANNELS];
    float   mAValues[MAX_AN_ZBANA_CHANNELS];
    U16     FailCnt1[MAX_AN_ZBANA_CHANNELS];
    U16     FailCnt2[MAX_AN_ZBANA_CHANNELS];
};

struct QueueANPRO10_COMMAND_2603 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2603   Data;
};



struct ANPRO10_COMMAND_2602 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
    U8    CardChannel;
    U8    CardId;
    U8    CardAddress;
    U8    UnitProgVersion;
    U8    ComVersion;
    U8    StoreVersion;
    U16   RxBufSize;
    U16   TxBufSize;
    U8    ResetStatus;
    U8    ProgamTypeRunning;
    U16   TotalUnitRestart;
    float CardVoltage;
};

struct QueueANPRO10_COMMAND_2602 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2602   Data;
};

struct ANPRO10_COMMAND_2611 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
    U8    CardChannel;
    U8    CardId;
    U8    CardAddress;
    U8    UnitProgVersion;
    U8    ComVersion;
    U8    StoreVersion;
    U16   RxBufSize;
    U16   TxBufSize;
    U8    ResetStatus;
    U8    ProgamTypeRunning;
    U16   TotalUnitRestart;
    float CardVoltage;
};

struct QueueANPRO10_COMMAND_2611 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2611   Data;
};

struct ANPRO10_COMMAND_2610 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     FailCntTotal;
    U32     FailCnt;
    U16     PowerStatus;
};
struct QueueANPRO10_COMMAND_2610 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2610   Data;
};

// This struct should have been defined in ANPRO1.h, but must be
// defined here, because this file is included for the bootloader where ANPRO1
// is excluded
//
//#pragma pack(pop)
struct ConfigPacket {

    unsigned ConvError   : 1;   // 0       Channel setup Byte 1 from AD
    unsigned CalError    : 1;   // 1
    unsigned PCSensor    : 2;   // 32
    unsigned UsePCSetUp  : 1;   // 4
    unsigned FoundSensor : 2;   // 65
    unsigned NewSensor   : 1;   // 7

    unsigned EEP_PCStatus: 3;   // 012      EEPROM Setup Byte 2 from AD
    unsigned EEPUsePCData: 1;   // 3
    unsigned EEPromStatus: 4;   // 4567
    unsigned IsError     : 1;   // This status is set by calculate
    unsigned             : 15;
} ;
//#pragma pack(push,1)

struct ANPRO10_COMMAND_2620 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     FailCntTotal;
    U32     FailCnt;
    float   MsrdValues[MAX_AN_SGCNV_CHANNELS];
    U16     CalValues[MAX_AN_SGCNV_CHANNELS];
    U16     RawValues[MAX_AN_SGCNV_CHANNELS];
    ConfigPacket    ADConfigData[MAX_AN_SGCNV_CHANNELS];
    float   Speed[MAX_WASHTRACK_CHANNELS];
    U8      LevelSwitches;
    U16     WashTrackCnt[MAX_WASHTRACK_CHANNELS];
};

struct QueueANPRO10_COMMAND_2620 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2620   Data;
};

struct ANPRO10_COMMAND_2621 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;

    U16     SoftwareVersion;
    U16     RxBufSize;
    U16     TxBufSize;
    U16     CalNull;
    U32     SerialNumber;
    float   EEPromGain;
};

struct QueueANPRO10_COMMAND_2621 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2621   Data;
};



struct ANPRO10_COMMAND_2630 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     SerialNumber;
    U8      IOUnitStatus;
    U8      CardStatus;
    U16     FailCnt;
    U16     FailCntTotal;
    int     ActiveAlarms;
    float   MsrdValues[MAX_W_INGR_CHANNELS];
    U8      ChStatus[MAX_W_INGR_CHANNELS];
    U16     CalValues[MAX_W_INGR_CHANNELS];
    U16     RawValues[MAX_W_INGR_CHANNELS];
};


struct QueueANPRO10_COMMAND_2630 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2630   Data;
};

struct ANPRO10_COMMAND_2640 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     SerialNumber;
    U8      Status;
    U16     FailCntTotal;
    U16     FailCnt;
    int     ActiveAlarms;
    float   MsrdValues[MAX_RADAR_CHANNELS];
};

struct QueueANPRO10_COMMAND_2640 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2640   Data;
};
// PROTanksystemUnitInfo Realtime data
struct ANPRO10_COMMAND_2700 {
    U16       CommandNo;
    U16       ndb;
    U32       ObjectId;
    float     ADResults[MAX_TCU_AD_CHANNELS];
    float     RxLoad[MAX_COM_PORTS];
    float     TxLoad[MAX_COM_PORTS];
    U32       TxCnt[MAX_COM_PORTS];
    U32       RxCnt[MAX_COM_PORTS];
    float     RunningHours;
    unsigned  RxErrId;
    unsigned  RxErrCmd;
    unsigned  RxErrMsg;
    unsigned  RxErrCnt;
    time_t    RxErrTime;
    int       IOLoadDelay;
    unsigned  SysInfoRxFailCnt;
    float     RawLoad;
    float     AvgLoad;
    float     MaxLoad;
    int       IO_ScanPeriod;    // May be moved to static
};

struct QueueANPRO10_COMMAND_2700 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2700   Data;
};

// PROTanksystemUnitInfo Static data
struct ANPRO10_COMMAND_2701 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
    ProgramVersionInfo  ActualProgramVersion;
    ProgramVersionInfo  ActualBootVersion;
    char      ActualSystemID[ANPRO10_ID_LENGTH];
    U16       ActualDataVersion;
    time_t    ProgrDate;
    time_t    UpdateTime;
    U8        ProgramType; // 0 = Bootloader, 1 = Application
    U8        HWDeviceId;
    unsigned  LastOSError;
    unsigned  LastErrAddress;
    unsigned  FlashErrorStatus;
    char      LastOSErrorTask[MAX_ANPRO10_NAME_LENGTH];
    int       NumberOfTasks;
    /*
    char      TaskNames[MAX_ANPRO10_NUMBER_OF_TASKS][MAX_ANPRO10_NAME_LENGTH];
    int       StackUsed[MAX_ANPRO10_NUMBER_OF_TASKS];
    int       StackSpace[MAX_ANPRO10_NUMBER_OF_TASKS];
    int       RawPerformance[MAX_ANPRO10_NUMBER_OF_TASKS];
    */
};

struct QueueANPRO10_COMMAND_2701 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2701   Data;
};

// PROInclinometer RT data
struct ANPRO10_COMMAND_2710 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
    float Trim;
    float List;
    float RolPeriod;
    float RolFrequency;
    float MaxP;
    float MaxS;
};

struct QueueANPRO10_COMMAND_2710 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2710   Data;
};
// PROInclinometer ST data
struct ANPRO10_COMMAND_2711 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
};

struct QueueANPRO10_COMMAND_2711 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2711   Data;
};

// PROInclinometer RT data
struct ANPRO10_COMMAND_2720 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
    float Trim;
    float List;
    float CargoVolume;
    float CargoWeight;
    float BallastVolume;
    float BallastWeight;
    float HeavyFuelVolume;
    float HeavyFuelWeight;
    float DieselOilVolume;
    float DieselOilWeight;
    float LubricantsVolume;
    float LubricantsWeight;
    float FreshWaterVolume;
    float FreshWaterWeight;
    float MiscVolume;
    float MiscWeight;
};

struct QueueANPRO10_COMMAND_2720 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2720   Data;
};
// PROInclinometer ST data
struct ANPRO10_COMMAND_2721 {
    U16       CommandNo;
    U16       ndb;
    U32       ObjectId;
    float     ManualTrim;
    float     ManualList;
    float     BallastDensity;
    float     SeaWaterDensity;
    float     FreshWaterDensity;
    float     HeavyFuelDensity;
    float     DieselDensity;
    float     LubricantsDensity;
    float     SeaWaterTemp;
    int       TrimSource;
    int       ListSource;
    int       Logtime;
    bool      LogAlarms;
    bool      LogBallastExchange;
    bool      LogCargo;
    bool      LogService;
    bool      LogTemperature;
    bool      LogTankPressure;
    int       CurrentLanguage;
    bool      LogToFile;
    bool      ReceiveWeightVolume;
    float     Latitude;
    bool      HasConfigWritePermission;
    bool      AlarmSoundSleep;
    float     AmbientTemp;
};

struct QueueANPRO10_COMMAND_2721 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2721   Data;
};


struct ANPRO10_COMMAND_2730 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
    bool  HasTrimValue;
    bool  HasListValue;
    bool  HasDeflection;
    bool  DraftAtPP;
    float TrimValue;
    float ListValue;
    float DftFwdMark;
    float DftAftMark;
    float DftFwd;
    float DftAft;
    float DftP;
    float DftS;

    float Deflection;
    float MaxDraft;
    float MeanDraft;
    int   StatusDftFwd;
    int   StatusDftAft;
    int   StatusDftP;
    int   StatusDftS;

    float DftAftP    ;  // New values
    float DftAftS    ;
    float DftFwdP    ;
    float DftFwdS    ;
    float DftFwdMarkP;
    float DftFwdMarkS;
    float DftAftMarkP;
    float DftAftMarkS;
    int   StatusDftAftP;
    int   StatusDftAftS;
    int   StatusDftFwdP;
    int   StatusDftFwdS;
    int   StatusDftMean;
};

struct QueueANPRO10_COMMAND_2730 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2730   Data;
};


struct ANPRO10_COMMAND_2731 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
};

struct QueueANPRO10_COMMAND_2731 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2731   Data;
};


struct ANPRO10_COMMAND_2732 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
    float Draft;
    float DraftAtMark;
    float DraftAtPP;
    int   DraftStatus;
};

struct QueueANPRO10_COMMAND_2732 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2732   Data;
};


struct ANPRO10_COMMAND_2733 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
    float DraftOffset;
};

struct QueueANPRO10_COMMAND_2733 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2733  Data;
};



struct ANPRO10_COMMAND_2740 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
    float ManualPressure;
    float AtmPressure;
    bool  UseManual;
};

struct QueueANPRO10_COMMAND_2740 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2740   Data;
};


struct ANPRO10_COMMAND_2741 {
    U16   CommandNo;
    U16   ndb;

    U32   ObjectId;
};

struct QueueANPRO10_COMMAND_2741 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2741   Data;
};

struct ANPRO10_COMMAND_2750 {
    U16 CommandNo;
    U16 ndb;
    U32 ObjectId;
    U16 ComFailCount;
    U16 ComTotalFailCount;
    U8  DigitalIn[MODBUS_MAX_COILS / 8];

};


struct QueueANPRO10_COMMAND_2750 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2750   Data;
};


struct ANPRO10_COMMAND_2751 {
    U16     CommandNo;
    U16     ndb;
    U32     ObjectId;
    U16     ValueKey;
    float   Value;
};


struct QueueANPRO10_COMMAND_2751 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2751   Data;
};

#ifndef ANBOOTLOADER
// Cargotype
struct ANPRO10_COMMAND_2800 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
    bool  IsDefined;
    int   CargoTypeKey;
    int   BaseCargoType;
    U32   Colour;
    float OD1,OD2, RefTmp1,RefTmp2,Coeff;
    char  Name[CTY_MAX_NAME_LENGTH];
    float ActualTemp;
    float MolMass;
    float Viscosity;
    int   DB_IdNumber;
};

struct QueueANPRO10_COMMAND_2800 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2800   Data;
};
// User Cargotype
struct ANPRO10_COMMAND_2810 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
    bool  IsDefined;
    int   CargoTypeKey;
    int   BaseCargoType;
    U32   Colour;
    float OD1,OD2, RefTmp1,RefTmp2,Coeff;
    char  Name[CTY_MAX_NAME_LENGTH];
    float HighTempLimit;
    float LowTempLimit;
    bool  HighTempEnable;
    bool  LowTempEnable;
    float ActualTemp;
    float MolMass;
    float Viscosity;
    int   DB_IdNumber;
};

struct QueueANPRO10_COMMAND_2810 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2810   Data;
};


// ANPRO3
struct ANPRO10_COMMAND_2900 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
};

struct QueueANPRO10_COMMAND_2900 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2900   Data;
};
struct ANPRO10_COMMAND_2910 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
};

struct QueueANPRO10_COMMAND_2910 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2910   Data;
};


struct ANPRO10_COMMAND_2901_2 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
    char  RequestStr[ANPRO3_MAX_SIZE];
};

struct QueueANPRO10_COMMAND_2901_2 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2901_2   Data;
};
// ANPRO3
struct ANPRO10_COMMAND_2920_21 {
    U16   CommandNo;
    U16   ndb;
    U32   ObjectId;
};

struct QueueANPRO10_COMMAND_2920_21 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_2920_21   Data;
};



// Alarm Status
struct ANPRO10_COMMAND_3000 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    float   Limit;
    float   Deadband;
    U32     State;
    U32     AlarmNo;
    time_t  Time_Rised;
    time_t  Time_Acknowledged;
    time_t  Time_Disappeared;
    time_t  Time_Changed;
    bool    Enable;
    bool    OutsideLimit;
    bool    AlarmSilence;
    bool    PreviousEnable;
};

struct QueueANPRO10_COMMAND_3000 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_3000   Data;
};

// AlarmAck
struct ANPRO10_COMMAND_3001 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
};

struct QueueANPRO10_COMMAND_3001 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_3001   Data;
};

// Alarm RT Data
struct ANPRO10_COMMAND_3002 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    U32     State;
    U32     AlarmNo;

    time_t  Time_Rised;
};

struct QueueANPRO10_COMMAND_3002 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_3002   Data;
};



// Alarm Status with extra data block
struct ANPRO10_COMMAND_3010 {
    U16     CommandNo;
    U16     ndb;

    U32     ObjectId;
    float   Limit;
    float   Deadband;
    U32     State;
    U32     AlarmNo;
    time_t  Time_Rised;
    time_t  Time_Acknowledged;
    time_t  Time_Disappeared;
    bool    Enable;
    time_t  LastOKTime;

};

struct QueueANPRO10_COMMAND_3010 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_3010   Data;
};

// TXU status
struct ANPRO10_COMMAND_3110 {
    U16     CommandNo;
    U16     ndb;                // 5 bytes
    char    TestMode;
};

struct QueueANPRO10_COMMAND_3110 {
    InternalCommandStruct  TxInfo;
    ANPRO10_COMMAND_3110   Data;
};
#endif
// Request CONFIG/PROGRAM/BOOTLOADER
struct ANPRO10_FLASH_DATA_STATUS {
    U16     CommandNo;
    U16     ndb;                // 5 bytes
    U8      RequestStatus;
};

struct QueueANPRO10_FLASH_DATA_STATUS {
    InternalCommandStruct  TxInfo;
    ANPRO10_FLASH_DATA_STATUS    Data;
};

// Request Flash Erase
struct ANPRO10_FLASH_ERASE {
    U16     CommandNo;
    U16     ndb;                // 5 bytes
    U8      EraseCommand;
};

struct QueueANPRO10_FLASH_ERASE {
    InternalCommandStruct  TxInfo;
    ANPRO10_FLASH_ERASE    Data;
};

// DATA - CONFIG/PROGRAM/BOOTLOADER
struct ANPRO10_FLASH_DATA {
    U16     CommandNo;
    U16     ndb;                // 5 bytes
    U32     Offset,
    LastPacket;
    char    Data[ANPRO10_MAX_DATA_SIZE];

};

struct QueueANPRO10_FLASH_DATA {
    InternalCommandStruct  TxInfo;
    ANPRO10_FLASH_DATA     Data;
};

#define ANPRO10_FLASH_DATA_HSIZE (2*sizeof(U32))


////////////////////////////////////////
//
// Module status packet
// Rev 0
// Packet Id   = 2001
// Packet size = 6
//
//
////////////////////////////////////////


struct ProgramPacket {
    U32 Offset,
    Size,
    LastPacket;
    char Data[ANPRO10_MAX_DATA_SIZE];
};

struct FlashPacket {
    U32 Offset,
    Size,
    LastPacket;
    char Data[ANPRO10_MAX_DATA_SIZE];
};



//////////////////////////////////////////////////
//
// Packets for SignalConverter
//
//////////////////////////////////////////////////

struct MeasuredChannelDataStruct {
    U8 Status1;
    U8 Status2;
    float MsrdValue;
};

struct EEPromDataStruct {
    bool DataAvailable;
    U8  IOChannel;
    U8  ADChannel;
    U8  EEPromData[EEPROM_SIZE];
};


struct SgCnvMeasuredDataStruct {
    U8  IOChannel;
    U8  IOUnitStatus;
    U16 FailCnt;
    U16 FailCntTotal;
    U8  TargetStatusSWVer;
    U8  TargetStatusAddress;
    MeasuredChannelDataStruct Channel[MAX_AN_SGCNV_CHANNELS];
};

struct SgCnvRawDataStruct {
    U8  IOChannel;
    U16 Channel[MAX_AN_SGCNV_CHANNELS][2];
};
struct SgCnvWHDataStruct {
    U16  Counter[MAX_WASHTRACK_CHANNELS];
    U8 LevelSwitch;
    U16  Ticks;
};


#pragma pack(pop)

//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
//  Flash Upload message struct
//
///////////////////////////////////////////////////////////////
struct UploadMessageStruct {
    TSNUart *Port;
    int   Address;
    int   UnitId;
    U16   Cmd;
    bool  isVersionControl;
};

//#ifdef S2TXU
//#pragma bitfields=default
//#endif


#endif


