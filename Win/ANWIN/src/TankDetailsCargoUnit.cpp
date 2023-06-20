//---------------------------------------------------------------------------

#include <vcl.h>
#include "TSNIncludes.h"
#pragma hdrstop

#include "TankDetailsCargoUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TTankDetailsCargo *TankDetailsCargo;
//---------------------------------------------------------------------------
__fastcall TTankDetailsCargo::TTankDetailsCargo(TComponent* Owner)
    : TTankDetailsForm(Owner,PROCargoTank::ObjVector)
{
}
//---------------------------------------------------------------------------


