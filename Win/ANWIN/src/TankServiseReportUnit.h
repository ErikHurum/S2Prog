//---------------------------------------------------------------------------

#ifndef TankServiseReportUnitH
#define TankServiseReportUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TTankServiceReportForm : public TForm
{
__published:	// IDE-managed Components
  TToolBar *ToolBar1;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
	PROTank *CurrentTankPtr;
public:		// User declarations
	__fastcall TTankServiceReportForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TTankServiceReportForm *TankServiceReportForm;
//---------------------------------------------------------------------------
#endif
