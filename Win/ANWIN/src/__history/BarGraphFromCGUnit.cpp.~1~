//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BarGraphFromCGUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BargraphUnit"
#pragma resource "*.dfm"
TBarGraphFromCGForm *BarGraphFromCGForm;
//---------------------------------------------------------------------------
__fastcall TBarGraphFromCGForm::TBarGraphFromCGForm(TComponent* Owner)
	: TBarGraphForm(Owner)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphFromCargo\\";
	Caption = "Cargo tanks bargraph window( From Group Window)";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_ULLAGE;
	ValueName = "Ullage";
}
//---------------------------------------------------------------------------
