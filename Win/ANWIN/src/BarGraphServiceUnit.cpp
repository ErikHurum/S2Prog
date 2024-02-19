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
#include <Winapi.GDIPOBJ.hpp>
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
		Caption += (AnsiString)" " + Tag;
	}
	ValueKey = SVT_LEVEL_REF;
	ValueName = "Level";
}
// ---------------------------------------------------------------------------
