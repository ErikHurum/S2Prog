// ---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <Winapi.GDIPAPI.hpp>
#include <Winapi.GDIPOBJ.hpp>#include "ANWinInc.h"
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
