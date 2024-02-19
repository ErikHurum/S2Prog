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
