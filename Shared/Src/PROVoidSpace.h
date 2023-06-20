//---------------------------------------------------------------------------
#ifndef PROVoidSpaceH
#define PROVoidSpaceH

class PROVoidSpace :
	public PROTank
{
private:
	static const float &NoiseLimitB;
public:
	static bool Redundancy;
	static vector<PRogramObjectBase*>ObjVector;
	static vector<PRogramObjectBase*>AllObjVector;
	static set<PRogramObjectBase*>ObjectSet;
	PROVoidSpace(void);
	PROVoidSpace(int Number, int LNumber=0);
	~PROVoidSpace(void);
	bool IsLevelInsideWindow(float NewValue, float OldValue);
	void Calculate(void);
    static ValueList* GetValueInfoTableStatic(int& Entries, int Index=0);
    static ValueList* GetServiceValueInfoTableStatic(int& Entries);
	void SetState(TankState newState);
};

//---------------------------------------------------------------------------
#endif
