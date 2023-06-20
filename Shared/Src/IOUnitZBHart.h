//---------------------------------------------------------------------------
#ifndef IOUnitZBHartH
#define IOUnitZBHartH

class IOUnitZBHart :
    public IOUnitZBAna {
private:
    static ValueList IOUnitZBHartValueList[];

public:
    static set<PRogramObjectBase *>ObjectSet;
    unsigned short  FailCnt1[12];
    unsigned short  FailCnt2[12];
    float Distance[MAX_AN_ZBANA_CHANNELS];
    float Level[MAX_AN_ZBANA_CHANNELS];
    IOUnitZBHart(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);
    ~IOUnitZBHart(void);
    bool Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);

#ifndef ANCONF
    void PROCalculate(void);
    void CompCalculate(void);
    void ReadCh(int Ch);
    void ReadChannels(void);

// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);
    virtual ValueList* GetValueInfoTable(int &Entries, int Index = 0);
    // Routines for communication
#ifdef S2TXU
    bool ANPRO10_IO_UnpackPacket(U8 *Buf);
    void SendToIO(U16 Command, void *Data, U16 Size, bool RequestAck);
    void PowerOn(void);
    void RequestSetup(void);
    void HandleIO(int Delay);
    void SetFilters(void);
    bool UpdateProgram(void);
#endif
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);
#endif

};


//---------------------------------------------------------------------------
#endif
