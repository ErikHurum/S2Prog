//---------------------------------------------------------------------------

#ifndef TankWashingMachineServiceUnitH
#define TankWashingMachineServiceUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>

#include "ChildUnit.h"
#include "TSNIncludes.h"
//---------------------------------------------------------------------------
class TTankWashingMachineServiceUnitForm : public TChildForm
{
__published:	// IDE-managed Components
	TStringGrid *ServiceInfoStringGrid;
	TButton *ResetButton;
	TLabel *HeadlineLabel;
	void __fastcall OnFormPaint(TObject *Sender);
	void __fastcall ResetButtonClick(TObject *Sender);
private:	// User declarations
	int tankWashingMachineId;
	bool mustRefreshData;
public:		// User declarations
	__fastcall TTankWashingMachineServiceUnitForm(TComponent* Owner);
	void __fastcall RefreshForm();

	void __fastcall SetTankWashingMachineId(int id);
	static void CreateOrShowWindow(int tankWashingMachineId);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankWashingMachineServiceUnitForm *TankWashingMachineServiceUnitForm;
//---------------------------------------------------------------------------
#endif
