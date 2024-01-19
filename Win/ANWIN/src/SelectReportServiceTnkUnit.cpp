//---------------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"

#pragma hdrstop

#include "SelectReportServiceTnkUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SelectReportUnit"
#pragma link "SelectReportUnit"
#pragma link "frxCross"
#pragma link "frCoreClasses"
#pragma link "frxSmartMemo"
#pragma resource "*.dfm"
TSelectReportPictureService *SelectReportPictureService;
//---------------------------------------------------------------------------
__fastcall TSelectReportPictureService::TSelectReportPictureService(TComponent* Owner)
    : TSelectReportForm(Owner, PROServiceTank::ObjVector)
{
}
//---------------------------------------------------------------------------


