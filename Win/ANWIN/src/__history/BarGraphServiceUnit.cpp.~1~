// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "BarGraphServiceUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BargraphUnit"
#pragma resource "*.dfm"
TBarGraphServiceForm *BarGraphServiceForm;

// ---------------------------------------------------------------------------
__fastcall TBarGraphServiceForm::TBarGraphServiceForm(TComponent* Owner)
	: TBarGraphForm(Owner, PROServiceTank::ObjVector)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphService\\";
	Caption = "Service tanks bargraph window";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_LEVEL_REF;
	ValueName = "Level";
}
// ---------------------------------------------------------------------------
