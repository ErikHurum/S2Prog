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

#include "TankDetailsCargoUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "RzPanel"
#pragma link "AdvDateTimePicker"
#pragma link "DBAccess"
#pragma link "DBAdvGrid"
#pragma link "LiteAccess"
#pragma link "MemDS"
#pragma resource "*.dfm"
TTankDetailsCargo *TankDetailsCargo;
//---------------------------------------------------------------------------
__fastcall TTankDetailsCargo::TTankDetailsCargo(TComponent* Owner)
    : TTankDetailsForm(Owner,PROCargoTank::ObjVector)
{
}
//---------------------------------------------------------------------------


