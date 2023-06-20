//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BarGraphFromBGUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BargraphUnit"
#pragma resource "*.dfm"
TBarGraphFromBGForm *BarGraphFromBGForm;
//---------------------------------------------------------------------------
__fastcall TBarGraphFromBGForm::TBarGraphFromBGForm(TComponent* Owner)
	: TBarGraphForm(Owner)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphBallast\\";
	Caption = "Ballast tanks bargraph window( From Group Window )";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_LEVEL_REF;
	ValueName = "Level";
}
//---------------------------------------------------------------------------
