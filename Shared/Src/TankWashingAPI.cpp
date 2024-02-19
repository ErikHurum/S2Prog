#include "TSNIncludes.h"
#ifdef ANWIN
	#include "LiteCall.hpp"
    #include "LiteAccess.hpp"
    #pragma hdrstop
	#include "ChildUnit.h"
	#include "Anpro_Net.h"
	#include "MainUnit.h"
#endif

#include "TankWashingAPI.h"
#include "PROTank.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#ifdef ANWIN
#pragma package(smart_init)
#endif
// Forward decls
class PROTank;
#ifdef ANWIN
twmRunCache_t TankWashingAPI::twmRunCache;
#endif
tankId_to_TWMId_Cache_t TankWashingAPI::tankId_to_TWMId_Cache;
long TankWashingAPI::lastCacheUpdateTime = 0;


TankWashingAPI::TankWashingAPI()
{
#ifdef ANWIN
	pUnitOfWork = new UnitOfWork();
#else
	pUnitOfWork = NULL;
#endif

	lastErrorMessage = AnsiString("");
}


TankWashingAPI::~TankWashingAPI()
{
	if (pUnitOfWork != NULL) {
#ifdef ANWIN
		delete pUnitOfWork;
#endif
	}
}


bool TankWashingAPI::PrepareWashingRun(int twmId, int tankId, TankWashingMachineRun_Type washType, int cleaningMediaId, string& batchGUID, int& twmRunId)
{
#ifdef ANWIN
	bool proceedCreatingWashingRun = false;
	bool opSuccess = false;

	// ** First ensure database state is correct so that it is possible to create
	// ** a new washing run. The code does some checks, then sets the
	// ** proceedCreatingWashingRun bool to true if it is okay to proceed. If not
	// ** then no washing run object is created.

	// If no washing run exists for this washing machine then it is OK to create one:
	bool runExists = false;
	opSuccess = pUnitOfWork->TWMRun_Repository->ExistsByWashingMachineId(twmId, runExists);

	if (opSuccess && !runExists) {
		proceedCreatingWashingRun = true;
	}
	else if (opSuccess && runExists) {

		// A previous run exists. Ensure it is has status "completed" or "error":
		TankWashingMachineRun latestRun;
		opSuccess = pUnitOfWork->TWMRun_Repository->ReadLatestByWashingMachineId(twmId, latestRun);

		if (opSuccess && (latestRun.Status == twmr_completed || latestRun.Status == twmr_error))
		{
			proceedCreatingWashingRun = true;
		}
		else
		{
			// 21.05.2013: Keep twm runs if they together give the "idle" status for the whole tank.
			// This avoids unecessary creation of twm runs and hence fewer useless log items:
			TankWashingMachineRunCollection twmRunColl;
			pUnitOfWork->TWMRun_Repository->ReadMultipleLatestByTankId(tankId, twmRunColl);

			TankWashingMachineRun_Statuses status = twmRunColl.GetAggregateStatus();
			if (status != twmr_idle) {
            	proceedCreatingWashingRun = true;
			}
		}
	}

	// If an error occured then return from this function with an error:
	if (!opSuccess) {
    	lastErrorMessage = AnsiString("Failed to read database data for tank washing machine w/");
		lastErrorMessage.cat_sprintf("ID=%d, function=%s", twmId, __FUNC__);
		return false;
	}


	if (proceedCreatingWashingRun) {

		TankWashingMachineRun twmRun;
		twmRun.InitializeIdle(twmId,batchGUID.c_str());
		twmRun.WashType         = (int)washType;
		twmRun.CleaningMediaId  = cleaningMediaId;

		PROTank* pTank = PROTank::FindTankById(tankId);
		AnsiString unitStr;

		// Set cargo related properties
		if (pTank != NULL && pTank->CargoType != NULL) {
			twmRun.SystemCargoId = pTank->CargoType->IDNumber;
			twmRun.CargoDisplayName = LibGetValue(SVT_CARGO_TYPE_NAME, pTank, &unitStr);
		}
		else
		{
			twmRun.SystemCargoId 	= 0;
			twmRun.CargoDisplayName = "";
		}

		opSuccess = pUnitOfWork->TWMRun_Repository->Create(twmRun);

		if (opSuccess) {
			// Pass back the DB assigned Id of the TWM Run object created:
			TankWashingMachineRun twmRun_readBack;
			opSuccess = pUnitOfWork->TWMRun_Repository->ReadLatestByWashingMachineId(twmId, twmRun_readBack);

			if (opSuccess) {
				twmRunId = twmRun_readBack.Id;
			}
		}

		if (!opSuccess) {
			lastErrorMessage = AnsiString("Failed initalize new washing machine run on machine w/");
			lastErrorMessage.cat_sprintf("ID=%d, function=%s", twmId, __FUNC__);
		}
	}
	else
	{
		lastErrorMessage = AnsiString("Open TWM Run already exists for this machine, please close it first ");
		lastErrorMessage.cat_sprintf("TWM ID=%d", twmId );
		opSuccess = false;
	}

    TankWashingAPI::EnsureCacheHasTWMRunObject(twmId, true);

	return opSuccess;
#else
	return false;
#endif
}



bool TankWashingAPI::PrepareWholeTank(int tankId, TankWashingMachineRun_Type washType, int cleaningMediaId, vector<int>& createdTWMRunIds)
{
#ifdef ANWIN
	// Load current washing runs
	TankWashingMachineRunCollection twmRuns;

	// Generate a unique value for grouping multiple washing run objects (these are created in the PrepareWashingRun method):
	string batchGUIDstr;
	TGUID guid;
	HRESULT hres = CreateGUID(guid);

	if ((hres >> 31) == 0) {
		AnsiString batchGUIDAnsiString = Sysutils::GUIDToString(guid);

		int gsLength = batchGUIDAnsiString.Length();
		AnsiString guidStrStripped = batchGUIDAnsiString.SubString(2, gsLength - 2);

		batchGUIDstr = string(guidStrStripped.c_str());
	}
	else
	{
		lastErrorMessage = AnsiString("Failed to generate BatchGUID: ");
		lastErrorMessage.cat_sprintf("%s", __FUNC__);
		return false;
	}


	bool opSuccess = pUnitOfWork->TWMRun_Repository->ReadMultipleLatestByTankId(tankId, twmRuns);

	if (opSuccess) {
		// Check that they are all completed or error
		TankWashingMachineRun_Statuses aggregateStatus = twmRuns.GetAggregateStatus();

        // Possible error. Expression was overrided by true
		if (true || (aggregateStatus == twmr_completed || aggregateStatus == twmr_error) || twmRuns.Count() == 0)
		{
			// Create new washing runs:
			// Get the machine ids in this tank:
			TankWashingMachineCollection twmCollection;
			opSuccess = pUnitOfWork->TWM_Repository->ReadAllTankWashingMachinesInTank(tankId, twmCollection);

			if (opSuccess) {
				vector<TankWashingMachine*> twmVector;
				twmCollection.GetTWMObjects(twmVector);

				vector<TankWashingMachine*>::iterator twmIter = twmVector.begin();

				while (twmIter != twmVector.end())
				{
					int twmId = (*twmIter)->IDNumber;
					int twmRunId = 0;

					// PrepareWashingRun will close running washes if they exists
					opSuccess = PrepareWashingRun(twmId, tankId, washType, cleaningMediaId, batchGUIDstr, twmRunId);

					if (!opSuccess) {
						// error message has already been set, so just break out of this function on failure:
						return false;
					}
					else
					{
						createdTWMRunIds.push_back(twmRunId);
					}

					++twmIter;
				}
			}
			else
			{
				lastErrorMessage = AnsiString("Failed to read washing machines in Tank w/");
				lastErrorMessage.cat_sprintf("Id=%d", tankId);
				opSuccess = false;
			}
		}
		else
		{
			lastErrorMessage = AnsiString("Tank has aggregate status not suitable for preparing new washing runs, ag.status=");
			lastErrorMessage.cat_sprintf("%d", aggregateStatus );
			opSuccess = false;
		}
	}
	else
	{
		// Cannot prepare
		lastErrorMessage = AnsiString("Failed to read Ids of Tank washing machines in tank w/Id=");
		lastErrorMessage.cat_sprintf("%d", tankId );
		opSuccess = false;
	}

	return opSuccess;
#else
	return false;
#endif
}




bool TankWashingAPI::StartWashingRun(int twmId, int& twmRunId)
{
#ifdef ANWIN
	// Get latest washing run
	bool opSuccess = false;
	TankWashingMachineRun twmRun;
	bool twmRunExists;

	opSuccess = pUnitOfWork->TWMRun_Repository->ReadLatestByWashingMachineId(twmId, twmRun);

	// Update it's status and start date etc, then store it again:
	if (opSuccess) {

		if (twmRun.Id <= 0) {
			lastErrorMessage = AnsiString("No tank washing run exists for this machine. Must be prepared first ");
			lastErrorMessage.cat_sprintf("TWM Id=%d", twmId);
			return false;
		}
		else if (twmRun.Status != twmr_idle) {

			lastErrorMessage = AnsiString("Tank washing run must be prepared before starting. Data: ");
			lastErrorMessage.cat_sprintf("TWM Id=%d, TWM Run Id=%d, TWM Run status=%d:\"%s\"",
				twmId, twmRun.Id, twmRun.Status, TankWashingMachineRun::StatusToString(twmRun.Status).c_str());
			return false;
		}

		if (opSuccess) {
			// Finally done, just start run and update stored data:
			twmRun.Start();
			opSuccess = pUnitOfWork->TWMRun_Repository->Update(twmRun);

			if (opSuccess) {
				// Pass back the DB assigned Id of the TWM Run object created:
				TankWashingMachineRun twmRun_readBack;
				opSuccess = pUnitOfWork->TWMRun_Repository->ReadLatestByWashingMachineId(twmId, twmRun_readBack);

				if (opSuccess) {
					twmRunId = twmRun_readBack.Id;
				}
			}
		}
	}

	if (!opSuccess) {
		lastErrorMessage = AnsiString("Failed to start washing machine run on machine w/");
		lastErrorMessage.cat_printf("ID=%d, function=%s", twmId, __FUNC__);
	}


	TankWashingAPI::EnsureCacheHasTWMRunObject(twmId, true);

	return opSuccess;
#else
	return false;
#endif
}



bool TankWashingAPI::FinishWashingRun(int twmId, bool force)
{
#ifdef ANWIN
	// Get latest washing run
	bool opSuccess = false;

	TankWashingMachineRun twmRun;

	opSuccess = pUnitOfWork->TWMRun_Repository->ReadLatestByWashingMachineId(twmId, twmRun);
	//CalculateExpenditures(twmRunCollection, twmCollection, timeNow, WaterConsumption, EnergyConsumption, FuelConsumption);


	// Update it's status and end date etc, then store it again:
	if (opSuccess) {
		twmRun.Completed(force);
		// Get a hold of the TWM object:
		TankWashingMachine twm;
		//twm.NumberOfNozzles = 1;
		//EHSMArk fix database
		bool twmFound = pUnitOfWork->TWM_Repository->ReadById(twmId, twm);

		// Find the tank which the TWM is mounted in:
		if (twmFound) {

			PROTank* pTank 				  = PROTank::FindTankById( twm.TankId );
			PROTankWashingMachine* TWMptr = (PROTankWashingMachine*)PRogramObjectBase::FindObject(twmId);
			if (TWMptr) {
				twmRun.RunningTime = TWMptr->RunningTime;
				// Refresh cargo type saved in this TWM Run:
				if (pTank != NULL && pTank->CargoType != NULL) {
					AnsiString unitStr;
					twmRun.SystemCargoId = pTank->CargoType->IDNumber;
					twmRun.CargoDisplayName = LibGetValue(SVT_CARGO_TYPE_NAME, pTank, &unitStr);
				}
				else
				{
					twmRun.SystemCargoId 	= 0;
					twmRun.CargoDisplayName = "";
				}

				PROWaterHeater* pWaterHeater = NULL;
				for (unsigned i=0; i<PROWaterHeater::AllObjVector.size(); i++)
				{
					PROWaterHeater *pTmp = (PROWaterHeater*) PROWaterHeater::AllObjVector[i];
					if (pTmp->HasPressure && pTmp->HasInputTemperature && pTmp->HasOutputTemperature)
					{
						pWaterHeater = pTmp;
					}
				}

				// Get calculated water, energy and money useage (cost)
				double WaterConsumption 	= 0.0;
				double EnergyConsumption 	= 0.0;
				double FuelConsumption 		= 0.0;
				double Flow             	= 0.0;
				TankWashingCalcResources res;
				TankWashingMachineWaterUseParams* pWaterUseParams = res.FindParameters(twm.MachineTypeId, twm.NozzleDiameter_mm);
				if (pWaterHeater != NULL && pWaterUseParams != NULL)
				{
					TankWashingCalcParams calcParams;
					calcParams.waterUseParams       = pWaterUseParams;
					calcParams.waterPressure_bar    = pWaterHeater->PressureValue*MH2O_TO_BAR; //We use SI units so must convert to Bar.
					calcParams.numberOfNozzles      = twm.NumberOfNozzles;
					calcParams.waterTemp1_c         = pWaterHeater->InputTemperatureValue;
					calcParams.waterTemp2_c         = pWaterHeater->OutputTemperatureValue;
					calcParams.HeatCapacity 		= WATER_HEAT_CAPACITY;
					calcParams.MDO_kWh_per_ton      = pWaterHeater->MDO_kWh_per_ton*pWaterHeater->MDO_Efficiency/100.0;
					if (twmRun.Status != twmr_idle)
					{
						double elapsedTime =  twmRun.RunningTime;// twmRun.GetElapsedTime();
						CalculateExpenditures(calcParams, elapsedTime, WaterConsumption, EnergyConsumption, FuelConsumption, Flow);
					}
				}
				twmRun.EnergyConsumption 	= EnergyConsumption;
				twmRun.WaterConsumption  	= WaterConsumption;
				twmRun.FuelConsumption  	= FuelConsumption;
				twmRun.Flow                 = Flow;

				opSuccess = pUnitOfWork->TWMRun_Repository->Update(twmRun);


				// Update TWM's total life running time stored in the tank washing machine object:
				//TankWashingMachine twm;
				//if (opSuccess) {
				//	opSuccess = pUnitOfWork->TWM_Repository->ReadById(twmId, twm);

				if (opSuccess ) {
					double runTimeSpent = TWMptr->RunningTime;//    twmRun.endDateTime - twmRun.startDateTime;
					twm.GearRatio 		= TWMptr->GetGearRatio();
					twm.NumberOfNozzles	= TWMptr->GetNumberOfNozzles();
					twm.LifeRunningTime += runTimeSpent;
					twm.RunningTimeSinceLastService += runTimeSpent;

					opSuccess = pUnitOfWork->TWM_Repository->Update(twm);
				}
			}
		}
	}

	if (!opSuccess) {
		lastErrorMessage = AnsiString("Failed to stop washing machine run. ");
		lastErrorMessage.cat_sprintf("TWM Id=%d, function=%s", twmId, __FUNC__);
	}

	TankWashingAPI::EnsureCacheHasTWMRunObject(twmId, true);

	return opSuccess;
#else
	return false;
#endif
}



bool TankWashingAPI::SetError(int twmId, int &twmRunId)
{
#ifdef ANWIN
	bool opSuccess = false;
	TankWashingMachineRun twmRun;

	opSuccess = pUnitOfWork->TWMRun_Repository->ReadLatestByWashingMachineId(twmId, twmRun);

	// Set error on the current run:
	if (opSuccess) {
        twmRun.Error();
		opSuccess = pUnitOfWork->TWMRun_Repository->Update(twmRun);
		twmRunId = twmRun.Id;
	}

	if (!opSuccess) {
		lastErrorMessage = AnsiString("Failed to set error on washing machine run. ");
		lastErrorMessage.cat_sprintf("TWM Id=%d, function=%s", twmId, __FUNC__);
	}

    TankWashingAPI::EnsureCacheHasTWMRunObject(twmId, true);

	return opSuccess;
#else
	return false;
#endif
}



void TankWashingAPI::GetLastErrorMessage(AnsiString& errorMsg)
{
#ifdef ANWIN
	errorMsg = lastErrorMessage;
#else
    errorMsg = AnsiString("TankWashingAPI is only implemented for ANWin as of yet");
#endif
}



bool TankWashingAPI::InitTWMinDatabase(TankWashingMachine& twm)
{
	bool success = true; // Defauls to success  = true

#ifdef ANWIN
	// Ensure all required members of this object have been initialized:
	if (twm.IDNumber <= 0 || twm.Identifier.Length() == 0 || twm.NozzleDiameter_mm == 0){
		success = false;
		lastErrorMessage = AnsiString("Could not Init TWM in DB because not all required fields were set : ");
		twm.ToString(lastErrorMessage);
	}

	// Finally do the actual DB update of the tank washing machine based on the parsed configuration:
	if (success) {
		/*
		PROTankWashingMachine *TWMPtr = (PROTankWashingMachine *)PRogramObjectBase::FindObject(twm.IDNumberIDNumber);
		twm.GearRatio = TWMPtr->GetGearRatio();
		twm.NozzleDiameter_mm = TWMPtr->GetNozzleDiameter();
		twm.NozzleDiameter_mm = TWMPtr->GetNumberOfNozzles();
		*/
		TLiteQuery 	*LiteQuery 	= new TLiteQuery(NULL);
		try {
			// LiteConnection is either TLiteConnection already set up
			LiteQuery->Connection 	= MainForm->WashTrackLiteConnection;
			AnsiString SQLText = "SELECT * FROM WashingMachines";
			SQLText += " WHERE Id=" + AnsiString(twm.IDNumber);
			// retrieve data
			LiteQuery->SQL->Text = SQLText;

			LiteQuery->Open();
			// retrieve data
			//	ShowMessage("Records of this alarm= "+IntToStr(LiteQuery->FetchRows));

			if (LiteQuery->RecordCount) {
				success = pUnitOfWork->TWM_Repository->UpdateFromConfiguration(twm);
			} else {
				success = pUnitOfWork->TWM_Repository->Create(twm);
			}
			if (!success) {
				lastErrorMessage = AnsiString("General failure to init TWM in database : ");
				twm.ToString(lastErrorMessage);
			}

		}
		__finally{
			LiteQuery->Free();
		}


	}

#endif
	return success;
}



bool TankWashingAPI::LoadTankCleaningMediaList(TSNConfigString& configString)
{
	bool success = true;
	int errorLine=0;
	int key;
	AnsiString PROName = "Tank Cleaning Media List";

	do {
		AnsiString inputKeyWord = configString.NextWord(errorLine);
		if ( errorLine ) {
			if ( errorLine != EOF ) {
				GiveConfigWarning(PROName,errorLine);
			}
		} else {
			key = FindConfigKey(inputKeyWord);

			// Parse next tank cleaning media chunk
			if (key == TWM_CLEANING_MEDIA) {
				LoadTankCleaningMediaConfigString(configString);
				PROTank::HasTankWashingMachines = true;
			}
		}
	}
	while (( errorLine != EOF )&& ( key != TWM_END_CLEANING_MEDIA_LIST ));

	return success;

}


void TankWashingAPI::CalculateExpenditures(TankWashingMachineRunCollection& twmRunCollection, TankWashingMachineCollection& twmCollection, double currentUnixTime, double &WaterConsumption, double &EnergyConsumption, double &FuelConsumption, double &Flow)
{
	TankWashingCalcResources res;

	// Loop over tank washing machines, and calculate info for each machine's current run. Summarize them later
	vector<TankWashingMachine*> twmVector;
	twmCollection.GetTWMObjects(twmVector);

	vector<TankWashingMachine*>::iterator twmIter = twmVector.begin();

	double totalConsumedVolume 	= 0.0;
	double totalEnergyCost 		= 0.0;
	double totalMoneyCost 		= 0.0;
	double totalFlow			= 0.0;

    PROWaterHeater* pWaterHeater = NULL;
    for (unsigned i=0; i<PROWaterHeater::AllObjVector.size(); i++)
    {
        PROWaterHeater *pTmp = (PROWaterHeater*) PROWaterHeater::AllObjVector[i];
        if (pTmp->HasPressure && pTmp->HasInputTemperature && pTmp->HasOutputTemperature)
        {
            pWaterHeater = pTmp;
        }
    }


    while(pWaterHeater != NULL &&  twmIter != twmVector.end())
	{
		TankWashingMachine* pTwm = *twmIter;
		PROTankWashingMachine *TWMptr = (PROTankWashingMachine *)PRogramObjectBase::FindObject(pTwm->IDNumber);
		//pTwm->NumberOfNozzles = 1;
		//EHSMArk fix database
		TankWashingMachineRun* pTwmRun = twmRunCollection.GetTWMRun(pTwm->IDNumber);

		// Get basic parameters based on the machine's model/type and nozzle size:
		TankWashingMachineWaterUseParams* pWaterUseParams = res.FindParameters(pTwm->MachineTypeId, pTwm->NozzleDiameter_mm);

		// Collect data needed for calculation from water heater and other places:
		if (pWaterHeater != NULL && pTwmRun != NULL && pWaterUseParams != NULL)
		{
			TankWashingCalcParams calcParams;
			calcParams.waterUseParams       = pWaterUseParams;
            calcParams.waterPressure_bar    = pWaterHeater->PressureValue*MH2O_TO_BAR; //We use SI units so must convert to Bar.;
            calcParams.numberOfNozzles      = pTwm->NumberOfNozzles;
            calcParams.waterTemp1_c         = pWaterHeater->InputTemperatureValue;
			calcParams.waterTemp2_c         = pWaterHeater->OutputTemperatureValue;
			calcParams.HeatCapacity 		= WATER_HEAT_CAPACITY;
			calcParams.MDO_kWh_per_ton      = pWaterHeater->MDO_kWh_per_ton*pWaterHeater->MDO_Efficiency/100.0;
			double WaterConsumption    		= 0.0;
			double EnergyConsumption   		= 0.0;
			double FuelConsumption    		= 0.0;
			double Flow  					= 0.0;

			if (pTwmRun->Status != twmr_idle)
			{
				double elapsedTime = TWMptr->RunningTime;//  pTwmRun->GetElapsedTime(currentUnixTime);
				CalculateExpenditures(calcParams, elapsedTime, WaterConsumption, EnergyConsumption, FuelConsumption,Flow);

				totalConsumedVolume += WaterConsumption;
				totalEnergyCost     += EnergyConsumption;
				totalMoneyCost      += FuelConsumption;
				totalFlow  		    += Flow;
			}
		}

		++twmIter;
	}

	WaterConsumption 	= totalConsumedVolume;
	EnergyConsumption 	= totalEnergyCost;
	FuelConsumption 	= totalMoneyCost;
	Flow				= totalFlow;
}



void TankWashingAPI::CalculateExpenditures(TankWashingCalcParams &calcParams, double runningTimeSecs, double &WaterConsumption, double &EnergyConsumption, double &FuelConsumption, double &Flow)
{
	// for making the code match the equation, copy the formula terms into locals:
	double a        	= calcParams.waterUseParams->A_value;
	double k        	= calcParams.waterUseParams->K_value;
	double T1       	= calcParams.waterTemp1_c;
	double T2       	= calcParams.waterTemp2_c;
	double HeatCapacity	= calcParams.HeatCapacity;
	double hours    	= runningTimeSecs / 3600.0;

	double Q        	= a + k * calcParams.waterPressure_bar;		// Q = water flow at nozzle
	Flow     			= Q * calcParams.numberOfNozzles;
	WaterConsumption 	= Flow * hours;

	// Set output variables
	EnergyConsumption	= HeatCapacity * (T2 - T1) * WaterConsumption;

	FuelConsumption 	= EnergyConsumption / calcParams.MDO_kWh_per_ton;
}



void TankWashingAPI::GetTankWashingMachineIDsByTank(int tankId, vector<int> *twmIds)
{
	if (twmIds)
	{
		tankId_to_TWMId_Cache_t::iterator iter = tankId_to_TWMId_Cache.find(tankId);

		if (iter != tankId_to_TWMId_Cache.end())
		{
			// copy twm id's belonging to this tank to the output vector:

			vector<int>::iterator twmIdStart = (*iter).second.begin();
			vector<int>::iterator twmIdEnd = (*iter).second.end();

			twmIds->assign(twmIdStart, twmIdEnd);
		}
	}
}



void TankWashingAPI::GetWholeTankInfo(int tankId, TankWashingMachineRun_Statuses& aggregateStatus)
{
#ifdef ANWIN
	vector<int> twmIds;
	GetTankWashingMachineIDsByTank(tankId, &twmIds);

	aggregateStatus = twmr_idle;

	vector<int>::iterator iter = twmIds.begin();

	while (iter != twmIds.end())
	{
		int twmId = *iter;

		twmRunCache_t::iterator twmRunIter = twmRunCache.find(twmId);

		if (twmRunIter != twmRunCache.end())
		{
			int twmStat = (int) ((*twmRunIter).second.Status);

			if (aggregateStatus < twmStat)
			{
				aggregateStatus = (TankWashingMachineRun_Statuses) twmStat;
			}
		}

		++iter;
	}
#endif
}


long TankWashingAPI::GetTimeOfLastTankWashingRunUpdate()
{
	return lastCacheUpdateTime;
}


bool TankWashingAPI::LoadTankCleaningMediaConfigString(TSNConfigString& ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	AnsiString PROName = "Tank Cleaning Media";

	// vars used in parsing loop
	AnsiString cleaningMediaName;
	TankWashingCleaningMedia cleaningMedia;
	cleaningMedia.Id = -1; // Initialize. The database will update this number automatically

	do {
		AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);

		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning(PROName,ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);

			switch (Key) {
			case TWM_IDENTIFIER:
				cleaningMediaName = ConfigString.GetRemainingLine(ErrorLine);

				if (!ErrorLine) {
					cleaningMedia.Name = cleaningMediaName;
				}
				break;
			case TWM_END_CLEANING_MEDIA:
				break;
			default:
				ErrorLine = 1;
				GiveConfigWarning(PROName,ErrorLine);
				break;
			}
		}
	}
	while (( ErrorLine != EOF )&& ( Key != TWM_END_CLEANING_MEDIA ));

	if (NoError) {
		NoError = InitCleaningMediaInDatabase(cleaningMedia);
	}

	return(NoError);
}



bool TankWashingAPI::InitCleaningMediaInDatabase(TankWashingCleaningMedia &twcm)
{
	bool success = false;

#ifdef ANWIN
	// Ensure all required members of this object have been initialized:
	if (twcm.Name.Length() == 0)
	{
		success = false;
		lastErrorMessage = AnsiString("Could not Init cleaning media in DB because not all required fields were set.");
	}
	else
	{
		success = true;
	}

	// Finally do the actual DB update of the tank washing machine based on the parsed configuration:
	if (success) {
		success = pUnitOfWork->TWCleaningMedia_Repository->CreateOrUpdateFromConfiguration(twcm);

		if (!success) {
			lastErrorMessage = AnsiString("General failure to init tank cleaning media in database : ");
			twcm.ToString(lastErrorMessage);
		}
	}

#endif
	return success;
}





/// Same as Start Washing run, but can be called multiple times without problem
/// Static function
bool TankWashingAPI::StartWashingRunIfIdle(int twmId, int& twmRunId)
{
	bool returnValue = false;
#ifdef ANWIN
	TankWashingAPI::EnsureCacheHasTWMRunObject(twmId);
	twmRunId = 0;

	if (TankWashingAPI::twmRunCache.count(twmId) >= 1) {
		if (TankWashingAPI::twmRunCache[twmId].Status == twmr_idle)
		{
			TankWashingAPI twmAPI;
			returnValue = twmAPI.StartWashingRun(twmId, twmRunId);
		}
	}
#else
    twmRunId = 0;
#endif

	return returnValue;
}


/// Static function
bool TankWashingAPI::FinishWashingRunIfRunningOrError(int twmId, bool force)
{
	bool returnValue = false;
#ifdef ANWIN
	TankWashingAPI::EnsureCacheHasTWMRunObject(twmId);

	if (TankWashingAPI::twmRunCache.count(twmId) >= 1) {
		int Status =  (int)TankWashingAPI::twmRunCache[twmId].Status;
		if (TankWashingAPI::twmRunCache[twmId].Status == twmr_running ||
			TankWashingAPI::twmRunCache[twmId].Status == twmr_error ||
			force == true)
		{
			TankWashingAPI twmAPI;
			returnValue = twmAPI.FinishWashingRun(twmId, force);
		}
	}
#endif
	return returnValue;
}




void TankWashingAPI::EnsureCacheHasTWMRunObject(int twmId, bool forceUpdate)
{
#ifdef ANWIN
	if (TankWashingAPI::twmRunCache.count(twmId) == 0 || forceUpdate)
	{
		// Add item to the cache:
		UnitOfWork unitOfWork;
		TankWashingMachineRun twmRun;
		bool readSuccess = false;

		readSuccess = unitOfWork.TWMRun_Repository->ReadLatestByWashingMachineId(twmId, twmRun);
		if (readSuccess)
		{
			TankWashingAPI::twmRunCache[twmId] = twmRun;
			lastCacheUpdateTime = time(NULL);
		}
	}
#endif
}



void TankWashingAPI::InitTWMMapping(int tankId, int twmId)
{
	 tankId_to_TWMId_Cache[tankId].push_back(twmId);
}



/// Loops through the PROTankWashingMachine objects attached to a PROTank, and returns
/// the aggregate (combined) status of washing in this tank.
/// True means washing is in progress, false all TCMs in the tank are idle.
///
bool TankWashingAPI::GetPROTankWashingStatus(PROTank* pTank)
{
	vector<PROTankWashingMachine*>::iterator it = pTank->TankWashingMachineVector.begin();
	vector<PROTankWashingMachine*>::iterator end =  pTank->TankWashingMachineVector.end();

	bool washRunning = false;

	for (;it != end; it++)
	{
		float floatValue;
		int index = 0;
		int decPnt = 0;
		int unit = 0;

		PROTankWashingMachine* pTWM = *it;
		pTWM->GetValue(SVT_TWM_ON_OFF_STATUS, index, floatValue, decPnt, unit);

		if (floatValue > 0.5)
		{
			washRunning = true;
		}
	}

	return washRunning;
}
