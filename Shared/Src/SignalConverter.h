//---------------------------------------------------------------------------
#ifndef SignalConverterH
    #define SignalConverterH

class SignalConverter:public ANPRO10Object {
protected:
    volatile bool Restart;
    volatile bool NewSensor;
    U32  SoftwareVersion;
    U32  SerialNumber;
    U8  CardStatus;
    IOUnit *IOModule;
public:
    static set<PRogramObjectBase*>ObjectSet;
//  int  SCType;
    int  TCUAddress;
    int  TCUPortNo;
    int  IOType;
    int  IOAddress;
    int  IOChannel;
    int  SCAddress;
    U8   IOUnitStatus;
    bool ForcePowerOff;

    set<PRogramObject*>UniquePROList;
    PROIOComponent *IOComponent[MAX_AN_SGCNV_CHANNELS];
    volatile float MsrdValues[MAX_AN_SGCNV_CHANNELS];
    volatile U16   CalValues[MAX_AN_SGCNV_CHANNELS];
    volatile U16   RawValues[MAX_AN_SGCNV_CHANNELS];


    SignalConverter(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr,IOUnit *IOModulePtr);
    ~SignalConverter(void);
    virtual bool Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);


    AnsiString MakeConfigString(int ExtraTabs=0);
    bool LoadConfigString(TSNConfigString &ConfigString);
    //virtual bool Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);

    #ifndef ANCONF
// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int PutFloatValue( int ValueId, float NewValue);

    virtual void SetHWFailure(bool Failure);
    // For communication
    virtual bool ANPRO10_IO_UnpackPacket(U8 *Buf);
    virtual void RequestMeasuredData(int  DataType);
    virtual void GetEEPromData(U8 *DataPtr);
    SignalConverter *FindSignalConverter(U8 IOChannel);
//  virtual void SetFilters(void);
    virtual bool HandleCard(int Delay);
    #endif
};

//---------------------------------------------------------------------------
#endif
