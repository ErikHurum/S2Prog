//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BarGraphFromSGUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BargraphUnit"
#pragma resource "*.dfm"
TBarGraphFromSGForm *BarGraphFromSGForm;
//---------------------------------------------------------------------------
__fastcall TBarGraphFromSGForm::TBarGraphFromSGForm(TComponent* Owner)
	: TBarGraphForm(Owner)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphService\\";
	Caption = "Service tanks bargraph window( From Group )";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_LEVEL_REF;
	ValueName = "Level";
}
//---------------------------------------------------------------------------
