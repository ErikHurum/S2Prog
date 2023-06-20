//---------------------------------------------------------------------------
#ifndef SCWaterIngressH
    #define SCWaterIngressH

class SCWaterIngress:
public SignalConverter {
private:
    static ValueList SCWaterIngressValueList[];
protected:
    volatile U8    ChStatus[MAX_W_INGR_CHANNELS];

public:
    SCWaterIngress(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr,IOUnit *IOModulePtr);
    ~SCWaterIngress(void);

    int WIType;

    #ifndef ANCONF
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);
    ValueList *GetValueInfoTable(int &Entries, int Index=0);
    // For communication
    void SetHWFailure(bool Failure);
    bool ANPRO10_IO_UnpackPacket(U8 *Buf);
    void RequestMeasuredData(int  DataType);
    void GetEEPromData(U8 *DataPtr);
//  void SetFilters(void);
    bool HandleCard(int Delay);
    int ReceiveData(U8* data);
    int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
    #endif
};

//---------------------------------------------------------------------------
#endif
