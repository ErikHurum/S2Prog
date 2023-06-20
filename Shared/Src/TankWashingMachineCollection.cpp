//---------------------------------------------------------------------------

#pragma hdrstop

#include "TankWashingMachineCollection.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

class TankWashingMachine;


TankWashingMachineCollection::TankWashingMachineCollection()
{

}


TankWashingMachineCollection::~TankWashingMachineCollection()
{
	// Free all tank washing machine objects
	TankWashMachineVector_t::iterator iter = TWMSet.begin();

	while (iter != TWMSet.end())
	{
		TankWashingMachine *twm = *iter;
		delete twm;
		++iter;
    }
}

/// Add a tank washing machine to this collection.
///
void TankWashingMachineCollection::Add(TankWashingMachine* washingMachine)
{
	TWMSet.push_back(washingMachine);
}


/// Return true if the collection is empty, false otherwise.
///
bool TankWashingMachineCollection::Empty()
{
    return TWMSet.empty();
}


/// Get the number of Tank washing machines in this collection.
///
int TankWashingMachineCollection::Count()
{
	return TWMSet.size();
			}


/// Get the ID number of all Tank Washing Machines in this collection
///
void TankWashingMachineCollection::GetTankWashingMachineIDs(vector<int>& idVector)
				{
	TankWashMachineVector_t::iterator iter = TWMSet.begin();

	while (iter != TWMSet.end())
	{
        idVector.push_back((*iter)->IDNumber);
		++iter;
    }
                }


/// Fills in an array with pointers to the tank washing machine objects in this collection.
///
void TankWashingMachineCollection::GetTWMObjects(vector<TankWashingMachine*>& twmPtrVector)
{
	int i = 0;
	TankWashMachineVector_t::iterator iter;

	for (iter = TWMSet.begin(); iter != TWMSet.end(); ++iter) {
		twmPtrVector.push_back(*iter);
		++i;
			}
		}



TankWashingMachine* TankWashingMachineCollection::First()
{
	const TankWashingMachine* retPtr = NULL;

	if (!TWMSet.empty()) {
    	retPtr = *(TWMSet.begin());
	}

	return const_cast<TankWashingMachine*>(retPtr);
}


