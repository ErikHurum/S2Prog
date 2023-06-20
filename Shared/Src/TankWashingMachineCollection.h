//---------------------------------------------------------------------------

#ifndef TankWashingMachineCollectionH
#define TankWashingMachineCollectionH
//---------------------------------------------------------------------------

#include "TSNIncludes.h"
#include "TankWashingMachine.h"




// Forward declarations:
class TankWashingMachine;
class UnitOfWork;
struct TankWashingMachineComparer;



/// Type used for storing collection of tank washing machines (per cargo tank).
///
typedef vector<TankWashingMachine*> TankWashMachineVector_t;


///
/// One collection of tank washing machines exists per cargo tank, and a collection
/// will usually contain from one to four individual tank washing machines.
///
class TankWashingMachineCollection
{
public:
	TankWashingMachineCollection();
	~TankWashingMachineCollection();
	void Add(TankWashingMachine* washingMachine);
	bool Empty();
	void GetTWMObjects(vector<TankWashingMachine*>&);
	int Count();
	void GetTankWashingMachineIDs(vector<int>& idVector);
	TankWashingMachine* First();

private:
	TankWashMachineVector_t TWMSet;
};






#endif
