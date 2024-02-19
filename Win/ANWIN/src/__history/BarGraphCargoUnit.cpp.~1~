// ---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "BarGraphCargoUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBarGraphCargoForm *BarGraphCargoForm;

// ---------------------------------------------------------------------------
__fastcall TBarGraphCargoForm::TBarGraphCargoForm(TComponent* Owner)
	: TBarGraphForm(Owner,PROCargoTank::ObjVector)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BarGraphCargo\\";
	Caption += "Cargo tanks bargraph window";
	if (Tag) {
		Caption += " " + Tag;
	}
	ValueKey = SVT_ULLAGE;
	ValueName = "Ullage";
}
// ---------------------------------------------------------------------------
