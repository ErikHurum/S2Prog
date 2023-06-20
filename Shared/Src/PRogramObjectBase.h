#pragma once
//---------------------------------------------------------------------------
#ifndef PRogramObjectBaseH
#define PRogramObjectBaseH

#include "TSNIncludes.h"
#ifdef ANWIn
using namespace std;
#endif

class PRogramObjectBase;
struct pair_struct {
    bool Inserted;
    PRogramObjectBase *Ptr;
};

class PRogramObjectBase {
private:
    static map<int, PRogramObjectBase *> IdMap;
    static set<PRogramObjectBase *> PRogramObjectBaseSet;
    static set<PRogramObjectBase *> MySet;


protected:
    volatile bool IsModified;
    int LineNumber;
public:
	static set<PRogramObjectBase *>DataTransferSet;
    set<unsigned>ReadPermissionSet;
    set<unsigned>WritePermissionSet;
    volatile int        ActiveAlarms;
    volatile bool       HWFailure;
    volatile clock_t    TimeStamp;
    volatile clock_t    LastRTTxTime;
    static volatile bool WriteAll;
    PRogramObjectBase(bool AddToList = true);
    virtual ~PRogramObjectBase(void);
    AnsiString  Name;
    AnsiString  TagName;
    AnsiString  Description;
    int         SortNo;
    unsigned    IDNumber;
    int         Type;


// Routines for the Configuration
    AnsiString IdNumString(void);

    set<unsigned> ReadIdTable(TSNConfigString &ConfigInputLines, int &ErrorStatus, int EndKw);
    AnsiString MakeIdTableString(int ExtraTabs = 0);
    AnsiString MakeIdTableString(set<unsigned>IdSet, int StartKW, int EndKW, int ExtraTabs = 0);
    virtual void WriteConfigToFile(TSNConfigString &ConfigString);
    virtual int LoadConfigFromFile(TSNConfigString &ConfigString);
    virtual AnsiString MakeConfigString(int ExtraTabs = 0);
    virtual bool LoadConfigString(TSNConfigString &ConfigString);
    virtual bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for the librarian
    virtual AnsiString GetName(void);
    AnsiString FindStatusChar(int Stat);
    virtual int FindPROStatus(AnsiString &MyString);
    float ConvertFromSiUnit(char Buf[], int ValKey, int Index, int Width);
    virtual int GetFloatValue(int ValueId, int Index, float &MyValue);
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int GetBitValue(int ValueId, int Index, bool &MyBit);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    virtual int PutFloatValue(int ValueId, float NewValue);
    virtual int PutBitValue(int ValueId, int Index, bool NewValue);

// Routines for object internode communication
    virtual int ReceiveData(U8 *data);
    virtual int SendData(U16 Cmd = CMD_GENERIC_REALTIME_DATA);
    int SendModbusData(U16 ValueId, float Value, U16 Cmd = CMD_GENERIC_MODBUS_RT_DATA);
    static void SendStaticData(void);
    virtual void StartTimer(void);
    virtual void InputTimeout(void);
    virtual ValueList* GetValueInfoTable(int &Entries, int Index = 0);
    virtual ValueList* GetServiceValueInfoTable(int &Entries);
    static  ValueList* GetValueInfoTableStatic(int &Entries, int Index = 0, bool Redundancy = false);
    static  ValueList* GetServiceValueInfoTableStatic(int &Entries);
    static vector<int>GetValueIdVector(int Index);
    static vector<ValueList>GetValueInfoVector(int Index);
    static vector<ValueList>GetServiceValueInfoVector(void);
    virtual void SetModifiedFlag(void);
    static unsigned GetMaxId(unsigned IdTypeKey);
    static int CorrectIds(void);
    static void InitObjTable(void);
    pair_struct InsertInMap(void);
    static void InitMap(void);
    static PRogramObjectBase* FindObject(int IdNum);
    bool ReadPermission(unsigned IdNum = 0);
    bool CheckReadPermissionSet(unsigned IdNum);
    bool WritePermission(unsigned IdNum = 0);
    bool CheckWritePermissionSet(unsigned IdNum);
    static void DeleteAllObjects(void);
    void EraseFromVector(vector<PRogramObjectBase *> &MyVect, PRogramObjectBase *MyPtr);
    unsigned GetIdNumber(void);
    void SetIdNumber(unsigned IDNum);

    virtual bool IsAvailableNewData(void);
    virtual bool IsTimeToSend(void);
    static unsigned GetFirstFreeId(int ObjectType, vector<PRogramObjectBase *>ObjVector, bool ExcludeLast = false);
    static unsigned GetFirstFreeId(int ObjectType, set<PRogramObjectBase *>ObjSet, bool ExcludeLast = false);
    static void SetIdNumber(PRogramObjectBase *ObjPtr, int ProposedId, int ObjectType, vector<PRogramObjectBase *>ObjVector, bool CreatedFromOther = false);
    static void SetIdNumber(PRogramObjectBase *ObjPtr, int ProposedId, int ObjectType, set<PRogramObjectBase *>ObjSet, bool CreatedFromOther = false);
    void SetLineNumber(int pLineNumber);
    int GetLineNumber(void);
    static bool Compare(PRogramObjectBase *Ptr1, PRogramObjectBase *Ptr2);
    void SetTimeStamp(void);
    static vector<PRogramObjectBase *>SortVector(vector<PRogramObjectBase *>UnsortedVector);
    static vector<PRogramObjectBase*> GetReadPermissionVector(vector<PRogramObjectBase*>MyVect , unsigned  pIDNumber=0);
    static vector<PRogramObjectBase*> GetWritePermissionVector(vector<PRogramObjectBase*>MyVect, unsigned  pIDNumber=0);

};

//---------------------------------------------------------------------------
#endif
