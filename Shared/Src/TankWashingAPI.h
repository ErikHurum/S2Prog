//---------------------------------------------------------------------------

#ifndef TankWashingAPIH
#define TankWashingAPIH
//---------------------------------------------------------------------------
#include "TSNIncludes.h"

#include "TankWashingMachine.h"
#include "TankWashingException.h"
#include "TankWashingCleaningMedia.h"
#ifdef ANWIN
#include "TankWashingMachineRun.h"
#include "UnitOfWork.h"
#endif

// Forward declarations:
class UnitOfWork;
class TankWashingMachineRun;
class TankWashingMachineRunCollection;
class TankWashingMachineCollection;
class TankWashingCleaningMedia;
class PROTankWashingMachine;
struct TankWashingMachineParameterGroup;
enum TankWashingMachineRun_Type;
enum TankWashingMachineRun_Statuses;

#ifdef ANWIN
typedef map<int, TankWashingMachineRun> twmRunCache_t;
#endif
typedef map<int, vector<int> > tankId_to_TWMId_Cache_t;


class TankWashingAPI
{
public:
	TankWashingAPI();
	~TankWashingAPI();
	bool PrepareWashingRun(int twmId, int tankId, TankWashingMachineRun_Type washType, int cleaningMediaId, string& batchGUID, int& twmRunId);
	bool PrepareWholeTank(int tankId, TankWashingMachineRun_Type washType, int cleaningMediaId, vector<int>& twmRunIds);

	bool StartWashingRun(int twmId, int& twmRunId);
	static bool StartWashingRunIfIdle(int twmId, int& twmRunId);

	bool FinishWashingRun(int twmId, bool force = false);
	bool FinishAllWashingRunsInTank(int tankId, bool force = false);
	static bool FinishWashingRunIfRunningOrError(int twmId, bool force = false);

	bool SetError(int twmId, int &twmRunId);
	void GetLastErrorMessage(AnsiString& errorMsg);

	//bool LoadConfigStringForTank(TSNConfigString &ConfigString, int tankId, vector<PROTankWashingMachine*>& programObjVector);
	bool LoadTankCleaningMediaList(TSNConfigString& configString);

	void CalculateExpenditures(TankWashingMachineRunCollection& twmRunCollection, TankWashingMachineCollection& twmCollection, double currentUnixTime, double &WaterConsumption, double &EnergyConsumption, double &FuelConsumption, double &Flow);
	void CalculateExpenditures(TankWashingCalcParams &calcParams, double runningTimeSecs, double &WaterConsumption, double &EnergyConsumption, double &FuelConsumption, double &Flow);

	// TODO: We need to clean up the caching infrastructure, so that it is more robust
	// and better architected with regards to the other classes TWMRunRepository, TankWashingMachineCollection and so on
	void GetTankWashingMachineIDsByTank(int tankId, vector<int> *twmIds);
	void GetWholeTankInfo(int tankId, TankWashingMachineRun_Statuses& aggregateStatus);

	static bool GetPROTankWashingStatus(PROTank* pTank);

	long GetTimeOfLastTankWashingRunUpdate();

	bool InitTWMinDatabase(TankWashingMachine& twm);
	static void InitTWMMapping(int tankId, int twmId);

private:
	UnitOfWork* pUnitOfWork;
	AnsiString lastErrorMessage;
	static long lastCacheUpdateTime;
#ifdef ANWIN
	static twmRunCache_t  twmRunCache;
#endif
	static tankId_to_TWMId_Cache_t     tankId_to_TWMId_Cache;


	bool InitCleaningMediaInDatabase(TankWashingCleaningMedia& twcm);
	bool LoadTankCleaningMediaConfigString(TSNConfigString& ConfigString);
	static void EnsureCacheHasTWMRunObject(int twmId, bool forceUpdate = false);
};





#endif
