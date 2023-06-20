//---------------------------------------------------------------------------

#ifndef CargoLegendObjectH
#define CargoLegendObjectH
//---------------------------------------------------------------------------
#include "ANWinInc.h"

class CargoLegend
{
private:
    int CargoTypeKey;
    int BasicCargoType;
public:
    TColor CargoColor;
    AnsiString CargoName;
    float    Weight;
    float      Volume;
    CargoLegend(CargoTypeObject *CargoTypePtr,vector<PRogramObjectBase*> ObjVector);
};

#endif
