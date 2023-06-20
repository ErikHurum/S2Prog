//---------------------------------------------------------------------------
#ifndef PROServiceTankH
#define PROServiceTankH

class PROServiceTank :
	public PROTank
{
private:
	static const float &NoiseLimitB;
	static const float &NoiseLimitU;
public:
	static bool Redundancy;
	static vector<PRogramObjectBase*>ObjVector;
	static vector<PRogramObjectBase*>HeavyFuelOilVector;
	static vector<PRogramObjectBase*>DieselVector;
	static vector<PRogramObjectBase*>LubricantsVector;
	static vector<PRogramObjectBase*>FreshWaterVector;
	static vector<PRogramObjectBase*>MiscVector;
	static vector<PRogramObjectBase*>AllObjVector;
	static vector<PRogramObjectBase*>AllHeavyFuelOilVector;
	static vector<PRogramObjectBase*>AllDieselVector;
	static vector<PRogramObjectBase*>AllLubricantsVector;
	static vector<PRogramObjectBase*>AllFreshWaterVector;
	static vector<PRogramObjectBase*>AllMiscVector;
	static set<PRogramObjectBase*>ObjectSet;
	PROServiceTank(int TType,int number, int LNumber=0);
	~PROServiceTank(void);
	float GetNoiseLimitB(void);
	float GetNoiseLimitU(void);
    static ValueList* GetValueInfoTableStatic(int& Entries, int Index = 0);
    static ValueList* GetServiceValueInfoTableStatic(int& Entries);
    void SetState(TankState newState);
};

//---------------------------------------------------------------------------
#endif
