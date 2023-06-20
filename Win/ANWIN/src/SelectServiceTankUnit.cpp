//---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"

#pragma hdrstop

#include "SelectServiceTankUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SelectTankUnit"
#pragma resource "*.dfm"
TSelectPROServiceTank *SelectPROServiceTank;
//---------------------------------------------------------------------------
__fastcall TSelectPROServiceTank::TSelectPROServiceTank(TComponent* Owner)
	: TSelectTankForm(Owner,PROServiceTank::ObjVector)
{
}
//---------------------------------------------------------------------------
