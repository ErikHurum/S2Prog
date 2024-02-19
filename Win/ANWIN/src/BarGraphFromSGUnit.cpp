//---------------------------------------------------------------------------

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
