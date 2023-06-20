//---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"

#pragma hdrstop

#include "SelectVoidSpaceUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SelectTankUnit"
#pragma resource "*.dfm"
TSelectPROVoidSpace *SelectPROVoidSpace;
//---------------------------------------------------------------------------
__fastcall TSelectPROVoidSpace::TSelectPROVoidSpace(TComponent* Owner)
	: TSelectTankForm(Owner,PROVoidSpace::ObjVector)
{
}
//---------------------------------------------------------------------------
