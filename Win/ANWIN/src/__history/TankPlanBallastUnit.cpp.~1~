//---------------------------------------------------------------------------

#include <vcl.h>
#include "TSNIncludes.h"
#pragma hdrstop

#include "TankPlanBallastUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankPlanUnit"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TTankPlanDrawingBallastForm *TankPlanDrawingBallastForm;
//---------------------------------------------------------------------------
__fastcall TTankPlanDrawingBallastForm::TTankPlanDrawingBallastForm(TComponent* Owner)
	: TTankPlanDrawingForm(Owner,PROBallastTank::ObjVector,BallastTanksDrawingFile)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BallastTankPlan\\";
	ReadRegistry();
}
//---------------------------------------------------------------------------
