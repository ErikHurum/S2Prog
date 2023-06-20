#include "ANWinInc.h"
#pragma hdrstop
#include "TankServiseReportUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TTankServiceReportForm *TankServiceReportForm;
//---------------------------------------------------------------------------
__fastcall TTankServiceReportForm::TTankServiceReportForm(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TTankServiceReportForm::FormClose(TObject *Sender,
												  TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------




