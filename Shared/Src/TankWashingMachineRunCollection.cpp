#pragma hdrstop
#include "TSNIncludes.h"

#include "TankWashingMachineRunCollection.h"
#include <algorithm>

//---------------------------------------------------------------------------
#pragma package(smart_init)


TankWashingMachineRunCollection::TankWashingMachineRunCollection()
{
}


TankWashingMachineRunCollection::~TankWashingMachineRunCollection()
{
	// Free all tank washing machine run objects
	TWMRunVector_t::iterator iter = TWMRunVector.begin();
	TWMRunVector_t::iterator end = TWMRunVector.end();

	while (iter != end)
	{
		TankWashingMachineRun *twmRun = const_cast<TankWashingMachineRun*>(*iter);
		delete twmRun;
		++iter;
	}

}


void TankWashingMachineRunCollection::Add(TankWashingMachineRun* twmRun)
{
	TWMRunVector.push_back(twmRun);
}


bool TankWashingMachineRunCollection::Empty()
{
	return TWMRunVector.empty();
}


void TankWashingMachineRunCollection::GetTWMRunObjects(std::vector<TankWashingMachineRun*>& runsPtrVector)
{
	TWMRunVector_t::iterator iter;
	int i = 0;

	for (iter = TWMRunVector.begin(); iter != TWMRunVector.end(); ++iter)
	{
		runsPtrVector.push_back(*iter);
		++i;
	}
}


int TankWashingMachineRunCollection::Count()
{
	return TWMRunVector.size();
}


/// Get the combined status of all tank washing machine runs in this collection.
///
/// Statuses have precedence like this:
/// error (highest precedence)
/// washing
/// prewash
/// idle (lowest precedence)
///
/// For example if a single machine has an error then the aggregate status is "error", regardless
/// of what the status of the other machines is.
///
TankWashingMachineRun_Statuses TankWashingMachineRunCollection::GetAggregateStatus()
{
	int aggregateStatus = twmr_idle;

	TWMRunVector_t::iterator iter = TWMRunVector.begin();
	TWMRunVector_t::iterator endIter = TWMRunVector.end();

	for (; iter != endIter; ++iter)
	{
		int tankWashStatus = (*iter)->Status;

		if (aggregateStatus < tankWashStatus )
		{
			aggregateStatus = tankWashStatus;
        }
	}
	return (TankWashingMachineRun_Statuses) aggregateStatus;
}


double TankWashingMachineRunCollection::GetEarliestStartTime()
{
	TWMRunVector_t::iterator iter;
	double result = 0.0;

	for (iter = TWMRunVector.begin(); iter != TWMRunVector.end(); ++iter)
	{
		double thisStartDT = (*iter)->startDateTime;

		if (result <= 0.0) {
			result = thisStartDT;
		}
		else if (thisStartDT > 0.0) {
			result = min(result, thisStartDT);
		}
	}
	return result;
}


double TankWashingMachineRunCollection::GetLastEndTime()
{
	TWMRunVector_t::iterator iter;
	double result = -1.0;

	for (iter = TWMRunVector.begin(); iter != TWMRunVector.end(); ++iter)
	{
		if (result <= 0.0) {
			result = (*iter)->endDateTime;
		}
		else {
        	result = max(result, (*iter)->endDateTime);
        }
	}
	return result;
}


double TankWashingMachineRunCollection::GetLastErrorTime()
{
	TWMRunVector_t::iterator iter;
	double result = -1.0;

	for (iter = TWMRunVector.begin(); iter != TWMRunVector.end(); ++iter)
	{
		if ((*iter)->Status == twmr_error) {
			if (result < 0.0) {
				result = (*iter)->endDateTime;
			}
			else {
				result = max(result, (*iter)->endDateTime);
			}
		}
	}
	return result;
}



/// Get pointer to single object from the collection based on what tank washing machine it belongs to.
///
TankWashingMachineRun* TankWashingMachineRunCollection::GetTWMRun(int tankWashingMachineId)
{
	TankWashingMachineRun* twmrPtr = NULL;
	TWMRunVector_t::iterator iter;

	for (iter = TWMRunVector.begin(); iter != TWMRunVector.end(); ++iter)
	{
		if ((*iter)->WashingMachineId == tankWashingMachineId)
		{
			twmrPtr = (*iter);
			break;
		}
	}
	return twmrPtr;
}



void TankWashingMachineRunCollection::TankWashingMessage(AnsiString& message)
{
	// FIXME not implemented yet
	message = AnsiString("");
}



double TankWashingMachineRunCollection::GetElapsedTime(TankWashingMachineRun_Statuses aggregateStatus, double nowTime)
{
	double elapsedTime = 0;

	switch (aggregateStatus) {
	case twmr_completed:
		elapsedTime = GetLastEndTime() - GetEarliestStartTime();
		break;
	case twmr_running:
		elapsedTime = nowTime - GetEarliestStartTime();
		break;
	case twmr_error:
		elapsedTime = GetLastErrorTime() - GetEarliestStartTime();
		break;
	case twmr_idle:
	default:
		elapsedTime = 0;
		break;
	}

	return elapsedTime;
}




TankWashingMachineRun* TankWashingMachineRunCollection::GetItem(int i)
{
	if (i < 0 || i >= Count()) {
		return NULL;
	}
	else
	{
        return TWMRunVector[i];
    }
}
