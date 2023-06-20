//---------------------------------------------------------------------------
#ifndef PROCargoTankH
#define PROCargoTankH

class PROCargoTank :
	public PROTank
{
private:
	static const float &NoiseLimitB;
	static const float &NoiseLimitU;
public:
	static vector<PRogramObjectBase*>AllObjVector;
	static vector<PRogramObjectBase*>ObjVector;
	static set<PRogramObjectBase*>ObjectSet;
	static bool Redundancy;
	PROCargoTank(int type,int number, int LNumber=0);
	~PROCargoTank(void);
	float GetNoiseLimitB(void);
	float GetNoiseLimitU(void);
    static ValueList* GetValueInfoTableStatic(int& Entries, int Index = 0);
    static ValueList* GetServiceValueInfoTableStatic(int& Entries);
//  For data log database
#ifdef ANWIN
	static void PrepareDatabase(TLiteQuery *LiteQuery);
	void AddTankRecord(TLiteQuery *LiteQuery);
	static void LogData(TLiteQuery *LiteQuery, const volatile bool &Terminated, int Delay);
	void LogDataFromTank(TLiteQuery *LiteQuery);
	static void CleanLogDataFromTank(TLiteQuery *LiteQuery, int MaxAge);
	bool IsallreadyAdded(void);
#endif
	void SetState(TankState newState);
};



//---------------------------------------------------------------------------
#endif
