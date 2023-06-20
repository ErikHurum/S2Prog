//---------------------------------------------------------------------------
#ifndef IOUnitZBAnaH
#define IOUnitZBAnaH

class IOUnitZBAna :
    public IOUnit {
private:
    static ValueList IOUnitZBAnaValueList[];

public:
    static set<PRogramObjectBase *>ObjectSet;
    U8      Filters[MAX_AN_ZBANA_CHANNELS];
    U8      Status[MAX_AN_ZBANA_CHANNELS];
    float	mAValues[MAX_AN_ZBANA_CHANNELS];
    int 	ReceiveCnt;
    IOUnitZBAna(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);
    ~IOUnitZBAna(void);
    PROIOComponent	*IOComponent[MAX_AN_ZBANA_CHANNELS];

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
    ValueList* GetValueInfoTable(int &Entries, int Index = 0);
    // Routines for communication
    void SetHWFailure(bool Failure);
#ifdef S2TXU
    virtual bool ANPRO10_IO_UnpackPacket(U8 *Buf);
    virtual void SendToIO(U16 Command, void *Data, U16 Size, bool RequestAck);
    void PowerOn(void);
    void RequestSetup(void);
    virtual void HandleIO(int Delay);
    void SetFilters(void);
#endif
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);
#endif
    int GetRequestNumber(void);

};


//---------------------------------------------------------------------------
#endif
