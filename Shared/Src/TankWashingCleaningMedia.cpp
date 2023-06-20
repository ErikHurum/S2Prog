//---------------------------------------------------------------------------

#pragma hdrstop

#include "TankWashingCleaningMedia.h"
//---------------------------------------------------------------------------
#ifdef ANWIN
#pragma package(smart_init)
#endif

TankWashingCleaningMedia::TankWashingCleaningMedia()
{
    Id = twcm_type_unknown;
}


void TankWashingCleaningMedia::ToString(AnsiString& dest)
{
    dest.cat_sprintf("TankWashingCleaningMedia DB.ID='%d' Name='%s'", Id, Name.c_str());
}
