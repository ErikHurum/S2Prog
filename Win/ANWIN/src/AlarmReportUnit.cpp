//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AlarmReportUnit.h"
#include "AlarmLogUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "qrpBaseCtrls"
#pragma link "qrpctrls"
#pragma link "QuickRpt"
#pragma link "QRCtrls"
#pragma resource "*.dfm"
TAlarmReportForm *AlarmReportForm;
//---------------------------------------------------------------------------
__fastcall TAlarmReportForm::TAlarmReportForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAlarmReportForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TAlarmReportForm::FormCreate(TObject *Sender)
{
   //	QRPQuickrepAlarm->Page->Orientation = poLandscape;
	AlarmLogForm->QRGridReportAlarmLog->PreviewReport(QRPQuickrepAlarm);

}
//---------------------------------------------------------------------------


