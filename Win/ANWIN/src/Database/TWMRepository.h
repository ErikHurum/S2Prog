//---------------------------------------------------------------------------

#ifndef TWMRepositoryH
#define TWMRepositoryH
//---------------------------------------------------------------------------

#include "TankWashingMachine.h"
#include "TankWashingMachineCollection.h"
#include "SQLiteAccessor.h"

// Forward declarations:
class TankWashingMachine;
class TankWashingMachineCollection;


class TWMRepository
{
private:
	TLiteQuery *LiteQuery;
	TLiteTable *LiteTable;
public:
	TWMRepository(void);
	~TWMRepository(void);

	bool ExistsById(int id, bool& exists);
	bool ExistsByTankId(int tankId, bool& exists);
	bool Create(TankWashingMachine& twm);
	bool Update(TankWashingMachine& twm);
	bool UpdateFromConfiguration(TankWashingMachine& twm);

	bool Delete(int id);
	bool ReadById(int id, TankWashingMachine& twm);
	bool ReadAllTankWashingMachineIDs(vector<int>& tankWashingMachineIDs);
	bool ReadAllTankWashingMachinesInTank(int tankId, TankWashingMachineCollection& dest);

private:
	static void ParseOneTankWashingMachine(TankWashingMachine* twmPtr, sqlite3_stmt* stmtHandle);
	void ParseOneTankWashingMachine(TankWashingMachine *twmPtr, TLiteQuery *LiteQuery);
};

#endif
