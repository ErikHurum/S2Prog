//---------------------------------------------------------------------------

#ifndef TankWashingCleaningMediaH
#define TankWashingCleaningMediaH
//---------------------------------------------------------------------------

#include "TSNIncludes.h"

enum TankWashingCleaningMedia_Type { twcm_type_unknown = 1, twcm_type_default };
class TankWashingCleaningMedia
{
public:
	int Id;
	AnsiString Name;
	void ToString(AnsiString& dest);

	TankWashingCleaningMedia();
};

#endif
