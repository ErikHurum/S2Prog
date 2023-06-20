//---------------------------------------------------------------------------
#ifndef PROBallastTankH
#define PROBallastTankH

class PROBallastTank :
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
	PROBallastTank(int TType,int number, int LNumber=0);
	~PROBallastTank(void);
	float GetNoiseLimitB(void);
	float GetNoiseLimitU(void);
    static ValueList* GetValueInfoTableStatic(int& Entries, int Index = 0);
    static ValueList* GetServiceValueInfoTableStatic(int& Entries);
	void SetState(TankState newState);
};

//---------------------------------------------------------------------------
#endif
