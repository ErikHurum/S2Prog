//---------------------------------------------------------------------------
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"


#pragma hdrstop

#include "CargoLegendObject.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
CargoLegend::CargoLegend(CargoTypeObject *CargoTypePtr,vector<PRogramObjectBase*> ObjVector)
{
   CargoTypePtr->GetStringValue(SVT_CARGO_TYPE_NAME,0,CargoName);
   CargoName 		= " "+CargoName;
   CargoTypeKey		= CargoTypePtr->CargoTypeKey;
   BasicCargoType 	= CargoTypePtr->BaseCargoType;
   CargoColor 		= (TColor)CargoTypePtr->Colour;
   // Could also use returned Cnt of found tanks with volume
   SumOneCargoAllTanks( CargoTypeKey,BasicCargoType, &Weight, &Volume,ObjVector);
}
