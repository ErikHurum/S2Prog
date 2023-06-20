//---------------------------------------------------------------------------

#ifndef TWCleaningMediaRepositoryH
#define TWCleaningMediaRepositoryH
//---------------------------------------------------------------------------

#include "SQLiteAccessor.h"
#include "TankWashingCleaningMedia.h"
#include <vector>

// Forward declarations:
class TankWashingCleaningMedia;


class TankWashingCleaningMediaRepository
{
private:
	TLiteQuery *LiteQuery;
	TLiteTable *LiteTable;
public:
	TankWashingCleaningMediaRepository(void);
	~TankWashingCleaningMediaRepository(void);
	bool Create(TankWashingCleaningMedia& cleaningMedia);
	bool ReadAllCleaningMedia(vector<TankWashingCleaningMedia>& dest);
	bool CreateOrUpdateFromConfiguration(TankWashingCleaningMedia& cleaningMedia);
	bool ExistsByName(AnsiString cleaningMediaName, bool& exists);

private:
	void ParseOneRecord(TankWashingCleaningMedia& twcm, TLiteQuery *LiteQuery);
};

#endif
