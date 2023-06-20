#pragma once
//---------------------------------------------------------------------------
#ifndef PROXRefObjectH
#define PROXRefObjectH
class PROXRefObject :
public PRogramObject {
private:
    static set<PROXRefObject*>ObjectSet;
    static bool IsSetTonline;
protected:
    TankState   State;
    bool        ExcludeState;
    bool        IsOnline;
public:
    static map<int, PROXRefObject*>SaabXRefList;
    static multimap<int, PROXRefObject*>ANPro3XRefList;
    int SaabId;
    int ANPro3Id;
    int TankType;
    PROXRefObject(bool AddToList=true);
    ~PROXRefObject();
// Routines for the Configuration
  virtual AnsiString MakeConfigString(int ExtraTabs=0);
  virtual bool LoadConfigString(TSNConfigString &ConfigString);
    bool SetSaabXref(int Id);
    void SetANPro3Xref(int Id);

    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);

    static PROXRefObject* GetSaabObject(int Id);
    static PROXRefObject* GetANProObject(int Id, int Type);
    virtual void SetState(TankState newState);
    virtual TankState GetState(void);
    static void SetStateAll(TankState newState);
    static TankState GetStateAll(void);
    static void VectorSetState(vector<PRogramObjectBase*>MyVect, TankState newState);
    static TankState VectorGetState(vector<PRogramObjectBase*>MyVect);
    static AnsiString GetStateString(TankState tState);
    static TankState GetStateKey(AnsiString KeyWord);
    virtual float GetTemperature(void);
    virtual void SetTemperature(float NewTemp);
    virtual float GetPressure(void);
    virtual void SetPressure(float NewPress);
    bool GetIsOnline(void);
    static void SetToOnline(void);
    static void SetToOffline(void);
    static bool GetIsSetToOnline(void);
};
#endif
