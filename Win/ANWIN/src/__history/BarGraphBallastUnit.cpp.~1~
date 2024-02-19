// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "BarGraphBallastUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBarGraphBallastForm *BarGraphBallastForm;

// ---------------------------------------------------------------------------
__fastcall TBarGraphBallastForm::TBarGraphBallastForm(TComponent* Owner)
	: TBarGraphForm(Owner, PROBallastTank::ObjVector)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphBallast\\";
	Caption = "Ballast tanks bargraph window";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_LEVEL_REF;
	ValueName = "Level";
}
// ---------------------------------------------------------------------------

