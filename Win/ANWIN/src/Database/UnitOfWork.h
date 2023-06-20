//---------------------------------------------------------------------------

#ifndef UnitOfWorkH
#define UnitOfWorkH

#include "TWMRepository.h"
#include "TWMRunRepository.h"
#include "TankWashingMachine.h"
#include "TankWashingCleaningMedia.h"
#include "TWCleaningMediaRepository.h"
#ifdef ANWIn
#include <System.hpp>
#endif

#define UnitOfWork_SecInDay 86400.0

//---------------------------------------------------------------------------

// Forward declarations:
class TWMRepository;
class TWMRunRepository;
class TankWashingCleaningMediaRepository;

/// Class for conveniently working with the database. Sets up all repositories
/// so they are ready for use, and you can immediately start reading and writing
/// objects to the database.
///
class UnitOfWork
{
public:
	UnitOfWork();
	~UnitOfWork();

	TWMRepository*      TWM_Repository;
	TWMRunRepository*   TWMRun_Repository;
	TankWashingCleaningMediaRepository* TWCleaningMedia_Repository;

	void InitializeData();
	void OutputWarning(AnsiString contextMessage);
	void TankIdToTankName(unsigned tankId, AnsiString& dest);

	static double DateTimeToUnixTimestamp(TDateTime& dt);
	static TDateTime TimestampToDateTime(double unixTimestamp, bool toLocalTime = false);
	static double DateFloor(double unixTimestamp);
	static double DateCeiling(double unixTimestamp);

protected:

	map<int, AnsiString*> tankNameMap;
};






#endif
