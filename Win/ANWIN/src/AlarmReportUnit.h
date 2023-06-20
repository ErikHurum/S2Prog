//---------------------------------------------------------------------------

#ifndef AlarmReportUnitH
#define AlarmReportUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TAlarmReportForm : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAlarmReportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAlarmReportForm *AlarmReportForm;
//---------------------------------------------------------------------------
#endif
