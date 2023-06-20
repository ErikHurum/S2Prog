//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "TankWashingMachineServiceUnit.h"
//#include "GridSizer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTankWashingMachineServiceUnitForm *TankWashingMachineServiceUnitForm;

//---------------------------------------------------------------------------
__fastcall TTankWashingMachineServiceUnitForm::TTankWashingMachineServiceUnitForm(TComponent* Owner)
	: TChildForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TTankWashingMachineServiceUnitForm::RefreshForm()
{
	mustRefreshData = true;
	Invalidate();
}
//---------------------------------------------------------------------------


void __fastcall TTankWashingMachineServiceUnitForm::SetTankWashingMachineId(int id)
{
	tankWashingMachineId = id;
	RefreshForm();
}
//---------------------------------------------------------------------------


void __fastcall TTankWashingMachineServiceUnitForm::OnFormPaint(TObject *Sender)
{
	if (mustRefreshData)
	{

		// Setup columns
		ServiceInfoStringGrid->ColCount = 2;
		ServiceInfoStringGrid->ColWidths[0] =  100;
		GridSizer::MakeGridColumnFillEmptySpace(ServiceInfoStringGrid, 1);

		if (tankWashingMachineId > 0) {

			// Get the data:
			UnitOfWork unitOfWork;
			TankWashingMachine twm;
			unitOfWork.TWM_Repository->ReadById(tankWashingMachineId, twm);

			// Convert time values to strings
			AnsiString lifetimeStr;
			SQLiteAccessor::ConvertToTimeString(twm.LifeRunningTime, lifetimeStr);

			AnsiString timeSinceLastServiceStr;
			SQLiteAccessor::ConvertToTimeString(twm.RunningTimeSinceLastService, timeSinceLastServiceStr);

			// Display values
			ServiceInfoStringGrid->RowCount = 5;

			int rowCount = 1;
			ServiceInfoStringGrid->Cells[0][rowCount] = AnsiString("Machine");
			ServiceInfoStringGrid->Cells[1][rowCount] = twm.Identifier;

			rowCount++;
			ServiceInfoStringGrid->Cells[0][rowCount] = AnsiString("Serial ID");
			ServiceInfoStringGrid->Cells[1][rowCount] = twm.SerialId;

			rowCount++;
			ServiceInfoStringGrid->Cells[0][rowCount] = AnsiString("Lifetime");
			ServiceInfoStringGrid->Cells[1][rowCount] = lifetimeStr;

			rowCount++;
			ServiceInfoStringGrid->Cells[0][rowCount] = AnsiString("Since last service");
			ServiceInfoStringGrid->Cells[1][rowCount] = timeSinceLastServiceStr;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankWashingMachineServiceUnitForm::ResetButtonClick(TObject *Sender)
{
	if (tankWashingMachineId > 0)
	{
        UnitOfWork unitOfWork;
		TankWashingMachine twm;

		bool opSuccess = unitOfWork.TWM_Repository->ReadById(tankWashingMachineId, twm);

		if (opSuccess)
		{
			twm.ResetAfterService();
			opSuccess = unitOfWork.TWM_Repository->Update(twm);

			if (opSuccess) {
				RefreshForm();
			}
			else
			{
				AnsiString errorMsg("Failed to update tank washing machine w/ID=");
				errorMsg.cat_sprintf("%d", tankWashingMachineId);
				unitOfWork.OutputWarning(errorMsg);
			}
		}
		else
		{
			AnsiString errorMsg("Failed to read tank washing machine w/ID=");
			errorMsg.cat_sprintf("%d", tankWashingMachineId);
			unitOfWork.OutputWarning(errorMsg);
		}
	}
}
//---------------------------------------------------------------------------




/// Initialise this form in the VCL framework.
/// A static function is useful for this purpose since this form may be created
/// from several different places in the application.
///
void TTankWashingMachineServiceUnitForm::CreateOrShowWindow(int tankWashingMachineId)
{
	TTankWashingMachineServiceUnitForm* formPtr =
		reinterpret_cast<TTankWashingMachineServiceUnitForm*>(	Application->FindComponent("TankWashingMachineServiceUnitForm") );

	if (formPtr) {
		formPtr->SetTankWashingMachineId(tankWashingMachineId);
		formPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TTankWashingMachineServiceUnitForm),
								&TankWashingMachineServiceUnitForm);

		TankWashingMachineServiceUnitForm->SetTankWashingMachineId(tankWashingMachineId);
	}
}
