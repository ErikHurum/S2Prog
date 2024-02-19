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
#pragma hdrstop

#include "TankPlanCargoUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankPlanUnit"
#pragma link "RzPanel"
#pragma link "AdvMenus"
#pragma link "ES.PaintBox"
#pragma resource "*.dfm"
TTankPlanDrawingCargoForm *TankPlanDrawingCargoForm;
//---------------------------------------------------------------------------
__fastcall TTankPlanDrawingCargoForm::TTankPlanDrawingCargoForm(TComponent* Owner)
	: TTankPlanDrawingForm(Owner,PROCargoTank::ObjVector,CargoTanksDrawingFile)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\CargoTankPlan\\";
	ReadRegistry();
}
//---------------------------------------------------------------------------


