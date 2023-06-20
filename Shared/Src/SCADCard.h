//---------------------------------------------------------------------------
#ifndef SCADCardH
    #define SCADCardH




class SCADCard:
public SignalConverter {
private:
    volatile int RequestADConfig;
    int  RequestRawCnt;
    bool IsFirstTime;
    int RequestTime;
    static ValueList SCAdCardValueList[];
    unsigned WashTrackNoMoveCnt[MAX_WASHTRACK_CHANNELS];
    unsigned WashTrackCnt[MAX_WASHTRACK_CHANNELS];
    float    WashTrackSpeed[MAX_WASHTRACK_CHANNELS];
    bool     LevelSwitch[MAX_LEVEL_SWITCH_CHANNELS];
    bool     hasForcedPressureSensor;

protected:
    volatile ConfigPacket ADConfigData[MAX_AN_SGCNV_CHANNELS];
    U8    SensorType[MAX_AN_SGCNV_CHANNELS];
    volatile bool  HasPressureSensor;
    U8   FilterDegreeOther;

    U8    RxBufSize;
    U8    TxBufSize;
    I16   CalNull;
    float EEPromGain;



public:
    static const int EEPromInfo[4];
    static const int ADSensorType[AD_SNS_TYPES];
    PROIOComponent *IOComponentWT[MAX_WASHTRACK_CHANNELS];
    SCADCard(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr,IOUnit *IOModulePtr);
    ~SCADCard(void);
    void InitSensorTypes(bool ForceDummyPress = false);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId,int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);
    ValueList *GetValueInfoTable(int &Entries, int Index=0);
    // For communication
    void SetHWFailure(bool Failure);
        #ifdef S2TXU
    int AddCommand(U8* BufPtr, U8 Command, U8 Size, U8* Data);

   // void GetADConfigInfo(int Delay, int *DownloadTime);
    void SendToAD(U8 Size, U8* Data);
    void SendToAD(U8 Command, U8 Size, U8* Data);
    void SendGainAndOffset(void);
    bool Correct_AD_Config(void);
    void GetADConfigInfo(void);
    bool ExtraADSetUp(void);

    bool ANPRO10_IO_UnpackPacket(U8 *Buf);
    void RequestMeasuredData(int  DataType);
    void GetEEPromData(U8 *DataPtr);

//  void SetFilters(void);
    bool HandleCard(int Delay);
        #endif
    int ReceiveData(U8* data);
    int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
    bool Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);
};

//---------------------------------------------------------------------------
#endif
