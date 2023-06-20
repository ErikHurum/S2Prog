//---------------------------------------------------------------------------

#ifndef PROTankWashingMachineH
#define PROTankWashingMachineH

#include <deque>
#include "TSNIncludes.h"
//---------------------------------------------------------------------------
#ifdef ANWIN
using namespace std;
#endif


enum tcm_operation_status {
    tcmos_running, tcmos_idle
};

class TankWashingMachine;
class PROTankWashingMachine : public PROXRefObject {

public:
    static set<PRogramObjectBase *>ObjectSet;
    static vector<PRogramObjectBase *>AllObjVector;
    static vector<PROTankWashingMachine *> AllTankWashingMachinesVector;
    int 	TankId;
    float   Speed;
    time_t  RunningTime;
    TankWashingMachine twm;
    PROTankWashingMachine(int tankId, AnsiString TankName);
    ~PROTankWashingMachine(void);

    // overridden functions from base class
    int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);

    float FilterValue(float FilteredValue, float RawVal, float FilterDegree);
    void Calculate(void);
    int LoadConfigFromFile(TSNConfigString &ConfigString);

    // Routines for the Configuration
    void WriteConfigToFile(TSNConfigString &ConfigString);

    //void SetProList(void);
    //static void SetAllProList(void);

    // Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);

    // Functions for displaying this object's data
    static  ValueList* GetValueInfoTableStatic(int &Entries, int Index = 0);

    static const int ValueNameList_Length;
    static ValueList ValueNameList[];
    int FindPROStatus(AnsiString &MyString);
    time_t GetRemainingRunTime(void);
    AlarmBasic::AlarmState GetPresetTimeAlarmState(void);
    AlarmBasic::AlarmState GetLowSpeedAlarmState(void);
    tcm_operation_status GetRunningState(void);

    bool IsPresetTimeAlarmEnabled(void);
    bool IsLowSpeedAlarmEnabled(void);
    int  GetGearRatio(void);
    int GetNozzleDiameter(void);
    int GetNumberOfNozzles(void);

private:
    //int 	                  nozzleMM;
    //int 	                  NumberOfNozzles;
    //float 	                  GearRatio;
    /// Scanjet serial number
    //AnsiString                SerialNumber;
    AiWashTrackSensor         *WashTrackSnsPtr;
    AnsiString                serialId;
    tcm_operation_status      machineStatus;
    /// identifies the model of the tank washing machine
    //int                       MachineTypeId;
    time_t                    IdleTimeStart;
    time_t                    TotalIdleTime;
    time_t                    RunningTimeStart;
    time_t                    TotalRunningTime;
    AlarmTCMLowSpeed          *TCMLowSpeedPtr;
    AlarmTCMPresetTimePassed  *TCMPresetTimePassedPtr;

};

#endif
