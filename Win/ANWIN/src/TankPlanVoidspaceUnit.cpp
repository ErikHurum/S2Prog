//---------------------------------------------------------------------------

#include <vcl.h>
#include "TSNIncludes.h"
#pragma hdrstop

#include "TankPlanVoidspaceUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankPlanUnit"
#pragma link "RzPanel"
#pragma link "ES.BaseControls"
#pragma link "ES.PaintBox"
#pragma link "ES.Labels"
#pragma link "AdvMenus"
#pragma resource "*.dfm"
TTankPlanDrawingVoidSpaceForm *TankPlanDrawingVoidSpaceForm;
//---------------------------------------------------------------------------
__fastcall TTankPlanDrawingVoidSpaceForm::TTankPlanDrawingVoidSpaceForm(TComponent* Owner)
	: TTankPlanDrawingForm(Owner,PROVoidSpace::ObjVector,VoidSpaceTanksDrawingFile)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\VoidSpaceTankPlan\\";
	ReadRegistry();
}
//---------------------------------------------------------------------------
