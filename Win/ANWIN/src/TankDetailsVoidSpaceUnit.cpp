#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "TankDetailsVoidSpaceUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankDetailUnit"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TTankDetailsVoidSpace *TankDetailsVoidSpace;
//---------------------------------------------------------------------------
__fastcall TTankDetailsVoidSpace::TTankDetailsVoidSpace(TComponent* Owner)
    : TTankDetailsForm(Owner, PROVoidSpace::ObjVector)
{
}
//---------------------------------------------------------------------------
