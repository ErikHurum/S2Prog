//---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"

#pragma hdrstop

#include "SelectBallastTankUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SelectTankUnit"
#pragma resource "*.dfm"
TSelectPROBallastTank *SelectPROBallastTank;
//---------------------------------------------------------------------------
__fastcall TSelectPROBallastTank::TSelectPROBallastTank(TComponent* Owner)
	: TSelectTankForm(Owner,PROBallastTank::ObjVector)
{
}
//---------------------------------------------------------------------------
