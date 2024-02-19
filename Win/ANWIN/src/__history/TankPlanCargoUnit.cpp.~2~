//---------------------------------------------------------------------------

#include <vcl.h>
#include "TSNIncludes.h"
#pragma hdrstop

#include "TankPlanCargoUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankPlanUnit"
#pragma link "RzPanel"
#pragma link "AdvMenus"
#pragma link "ES.PaintBox"
#pragma resource "*.dfm"
TTankPlanDrawingCargoForm *TankPlanDrawingCargoForm;
//---------------------------------------------------------------------------
__fastcall TTankPlanDrawingCargoForm::TTankPlanDrawingCargoForm(TComponent* Owner)
	: TTankPlanDrawingForm(Owner,PROCargoTank::ObjVector,CargoTanksDrawingFile)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\CargoTankPlan\\";
	ReadRegistry();
}
//---------------------------------------------------------------------------


