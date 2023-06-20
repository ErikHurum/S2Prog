// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "BarGraphVoidSpaceUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BargraphUnit"
#pragma resource "*.dfm"
TBarGraphVoidSpaceForm *BarGraphVoidSpaceForm;

// ---------------------------------------------------------------------------
__fastcall TBarGraphVoidSpaceForm::TBarGraphVoidSpaceForm(TComponent* Owner)
	: TBarGraphForm(Owner,PROVoidSpace::ObjVector)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphVoidSpace\\";
	Caption = "Void Space bargraph window";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_LEVEL_REF;
	ValueName = "Level";
}
// ---------------------------------------------------------------------------
