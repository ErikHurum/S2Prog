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

#include "TankPlanBallastUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankPlanUnit"
#pragma link "RzPanel"
#pragma link "AdvMenus"
#pragma link "ES.PaintBox"
#pragma resource "*.dfm"
TTankPlanDrawingBallastForm *TankPlanDrawingBallastForm;
//---------------------------------------------------------------------------
__fastcall TTankPlanDrawingBallastForm::TTankPlanDrawingBallastForm(TComponent* Owner)
	: TTankPlanDrawingForm(Owner,PROBallastTank::ObjVector,BallastTanksDrawingFile)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\BallastTankPlan\\";
	ReadRegistry();
}
//---------------------------------------------------------------------------
