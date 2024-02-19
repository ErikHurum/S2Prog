//---------------------------------------------------------------------------

#ifndef TWMRunCollectionH
#define TWMRunCollectionH
//---------------------------------------------------------------------------
#ifdef S2TXU
#include <set>
#include <vector>
#endif
#include "TankWashingMachineRun.h"
#if defined(ANWIN) || defined(ANTDUSIM)
//using namespace std;
#endif

// forward declarations
class TankWashingMachineRun;
enum TankWashingMachineRun_Type;
enum TankWashingMachineRun_Statuses;

typedef vector<TankWashingMachineRun*> TWMRunVector_t;


class TankWashingMachineRunCollection {

protected:
	TWMRunVector_t TWMRunVector;

public:
	TankWashingMachineRunCollection();
	~TankWashingMachineRunCollection();

	void Add(TankWashingMachineRun* twmRun);
	bool Empty();
	void GetTWMRunObjects(TWMRunVector_t&);
	int Count();

	TankWashingMachineRun_Statuses GetAggregateStatus();
	double GetEarliestStartTime();
	double GetLastEndTime();
	double GetLastErrorTime();
	TankWashingMachineRun* GetTWMRun(int tankWashingMachineId);
	void TankWashingMessage(AnsiString&);
	double GetElapsedTime(TankWashingMachineRun_Statuses aggregateStatus, double nowTime);
	TankWashingMachineRun* GetItem(int i);
};



#endif
