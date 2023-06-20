//---------------------------------------------------------------------------

#include "TSNIncludes.h"

#pragma hdrstop

#include "TankPlanServiceUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankPlanUnit"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TTankPlanDrawingServiceForm *TankPlanDrawingServiceForm;
//---------------------------------------------------------------------------
__fastcall TTankPlanDrawingServiceForm::TTankPlanDrawingServiceForm(TComponent* Owner)
	: TTankPlanDrawingForm(Owner,PROServiceTank::ObjVector,ServiceTanksDrawingFile)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\ServiceTankPlan\\";
	ReadRegistry();
}
//---------------------------------------------------------------------------
