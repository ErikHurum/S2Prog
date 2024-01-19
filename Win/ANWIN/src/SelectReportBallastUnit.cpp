//---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"

#pragma hdrstop

#include "SelectReportBallastUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SelectReportUnit"
#pragma link "frxCross"
#pragma link "frCoreClasses"
#pragma link "frxSmartMemo"
#pragma resource "*.dfm"
TSelectReportPictureBallast *SelectReportPictureBallast;
//---------------------------------------------------------------------------
__fastcall TSelectReportPictureBallast::TSelectReportPictureBallast(TComponent* Owner)
    : TSelectReportForm(Owner, PROBallastTank::ObjVector)
{
}
//---------------------------------------------------------------------------
