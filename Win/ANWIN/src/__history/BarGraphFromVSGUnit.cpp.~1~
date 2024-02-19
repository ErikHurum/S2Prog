//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BarGraphFromVSGUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BargraphUnit"
#pragma resource "*.dfm"
TBarGraphFromVSGForm *BarGraphFromVSGForm;
//---------------------------------------------------------------------------
__fastcall TBarGraphFromVSGForm::TBarGraphFromVSGForm(TComponent* Owner)
	: TBarGraphForm(Owner)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphVoidSpace\\";
	Caption = "Void space bargraph window( From Cargo Group )";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_LEVEL_REF;
	ValueName = "Level";
}
//---------------------------------------------------------------------------
