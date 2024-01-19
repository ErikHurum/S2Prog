//---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"

#pragma hdrstop

#include "SelectReportCargoUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SelectReportUnit"
#pragma link "frxCross"
#pragma link "frCoreClasses"
#pragma link "frxSmartMemo"
#pragma resource "*.dfm"
TSelectReportPictureCargo *SelectReportPictureCargo;
//---------------------------------------------------------------------------
__fastcall TSelectReportPictureCargo::TSelectReportPictureCargo(TComponent* Owner)
    : TSelectReportForm(Owner,PROCargoTank::ObjVector)
{
}
//---------------------------------------------------------------------------
