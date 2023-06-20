//---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"

#pragma hdrstop

#include "SelectCargoTankUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SelectTankUnit"
#pragma resource "*.dfm"
TSelectPROCargoTank *SelectPROCargoTank;
//---------------------------------------------------------------------------
__fastcall TSelectPROCargoTank::TSelectPROCargoTank(TComponent* Owner)
	: TSelectTankForm(Owner,PROCargoTank::ObjVector)
{
}
//---------------------------------------------------------------------------
