//---------------------------------------------------------------------------

#ifndef TWMRunRepositoryH
#define TWMRunRepositoryH
//---------------------------------------------------------------------------

#include <vector>
#include <LiteCall.hpp>

#include "TSNIncludes.h"

#include "TankWashingMachineRun.h"
#include "TankWashingMachineRunCollection.h"
#include "SQLiteAccessor.h"

// Forward declarations:
class TWMLogItem;
class TankWashingCompoundLogObject;

/// Data repository for TankWashingMachineRun objects. Used for reading and writing
/// objects of the entity class TankWashingMachineRun to the database.
///
class TWMRunRepository {

private:
	TLiteQuery *LiteQuery;
	TLiteTable *LiteTable;
public:
	TWMRunRepository(void);
    ~TWMRunRepository();

	/// Determine if one or more TankWashingMachineRun entities exists based on the
	/// id of the washing machine they belong to.
	///
	/// @param 		id id-number of tank washing machine the twm.run belongs to
	/// @param		dest reference to object to store the data in
	/// @return 	true on success, false on error
	bool ExistsByWashingMachineId(int twmId, bool& exists);


	/// Determine if one or more TankWashingMachineRun entities exists based on the
	/// id of the TankWashingMachineRun object itself.
	///
	bool ExistsById(int id, bool& exists);


	/// Read a single TankWashingMachineRun entity by known Id.
	///
	/// @param 		id id-number of tank washing machine run object to read
	/// @param		dest reference to object to store the data in
	/// @return 	true on success, false on error
	bool ReadById(int id, TankWashingMachineRun& dest);


	/// Read a single TankWashingMachineRun entity based on the id of the washing machine
	/// it belongs to.
	///
	/// @param 		id id-number of tank washing machine the twm.run belongs to
	/// @param		dest reference to object to store the data in
	/// @return 	true on success, false on error
	bool ReadLatestByWashingMachineId(int twmId, TankWashingMachineRun& dest);



	/// Read multiple TankWashingMachineRun entities based on a list
	/// of washing machine ids
	///
	/// @param 		twmIDs ids of tank washing machines whose latest runs to read
	/// @param		dest reference to object to store the data in
	/// @return 	true on success, false on error
	bool ReadMultipleLatestByListOfWashingMachineIds(vector<int>& twmIDs, TankWashingMachineRunCollection& dest);

	/// Prepare query for multiple TankWashingMachineRun entities
	/// based on a list of washing machine ids
	///
	/// @param 		twmIDs ids of tank washing machines whose latest runs to read
	/// @return 	Query string
	AnsiString PrepareQueryMultipleLatestByListOfWashingMachineIds(vector<int>& twmIDs);



	/// Read multiple and TankWashingMachineRun entities based on a Tank Id.
	/// Gets exactly one run per machine (if available), which is the most recent run.
	///
	/// @param 		tankid id of tank to get latest washing run data from
	/// @param		dest reference to object to store the data in
	/// @return 	true on success, false on error
	bool ReadMultipleLatestByTankId(int tankId, TankWashingMachineRunCollection& dest);


	/// Read all TankWashingMachineRun objects for each TankWashingMachine given as parameter.
	///
	/// @param		tankWashingMachineIDs set of IDs to tank washing machines. Runs belonging to these machines will be read, but only the most recent per machine.
	/// @param		dest Collection to hold the read objects.
	/// @return		true on success, false on error
	bool ReadMultipleLatestByListOfTWMIds(vector<int>& tankWashingMachineIDs, TankWashingMachineRunCollection& dest);



	/// Read info for each batch of washing runs having been run in a set of tanks, within a certain date range
	///
	/// @param		tankIDs IDs of tanks to read log info for
	/// @param		startDate unix time stamp, inclusive
	/// @param		endDate unix time stamp, inclusive
	/// @param		dest Vector to hold the objects read. Remember to free them when done.
	/// @return		true on success, false on error
	bool ReadMultipleLogObjects(vector<int>& tankIDs, double startDate, double endDate, AnsiString& nullStringReplacement, vector<TankWashingCompoundLogObject*>& dest);

	bool ReadLogObject(AnsiString batchId, AnsiString& nullStringReplacement, TankWashingCompoundLogObject& dest);

	bool Create(TankWashingMachineRun& twmRun);

	bool Update(TankWashingMachineRun& twmRun);

	bool CreateOrUpdate(TankWashingMachineRun& twmRun);



	bool Delete(int id);


protected:
	void ParseDataRow(TLiteQuery *LiteQuery, TankWashingMachineRun* twmRun);
	void ParseCompoundLogObject(TLiteQuery *LiteQuery, TankWashingCompoundLogObject* pLogObj);
};


#endif
